//#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>
#include "TWI/TWI.h"
#include "mpu6050_reg.h"
#include "bmp280_reg.h"
#include "UART.h"

//Ratios de conversion
#define A_R 16384.0    // 32768/2
#define G_R 131.0       // 32768/250

//Conversion de radianes a grados 180/PI
#define RAD_TO_DEG 57.295779

//Valores MPU6050
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

//Angulos
float Acc[2];
float Gy[3];
float Angle[3];

//Valores BMP280
int32_t  Temperatura, Presion;
uint16_t T1, P1;
int16_t  T2, T3, P2, P3, P4, P5, P6, P7, P8, P9;
int32_t  t_fine;
int64_t var1, var2, T;


//Variables temporales 
int8_t currentSeg = 0;
float dt = 0;
uint8_t tmp[2]; //ACELEROMETRO
uint8_t prs[3]; //PRESION

void TWI_write_sensor(uint16_t Address, uint16_t reg, uint8_t val){
	while(TWI_startCond());
	while(TWI_sendAdrr(Address, TWI_W));
	while(TWI_write(reg));
	while(TWI_write(val));
	TWI_stopCond();
}
uint8_t TWI_read_sensor(uint16_t Address, uint16_t reg){
	while(TWI_startCond());
	while(TWI_sendAdrr(Address, TWI_W));
	while(TWI_write(reg));
	while(TWI_restrtCond());
	while(TWI_sendAdrr(Address, TWI_R));
	currentSeg = TWI_read(TWI_NACK);
	TWI_stopCond();
	return(currentSeg);
}

void mpu6050_init(uint16_t Address){
	//	TWI_write_sensor( Address, reg, val);
	TWI_write_sensor( Address, 0x6B, 0x00); //Sacar del sleep mode
	TWI_write_sensor( Address, 0x1A, 0x01);
	TWI_write_sensor( Address, 0x1B, 0x00);
	TWI_write_sensor( Address, 0x1C, 0x00);
	TWI_write_sensor( Address, 0x38, 0x00);
	TWI_write_sensor( Address, 0x68, 0x07);
}
void bmp280_init(uint16_t Address){
	TWI_write_sensor( Address, 0xE0, 0xB6); //RESET
	
	// MODO: NAVIGATION INDOOR
	TWI_write_sensor( Address, 0xF4, 0x57); //NORMAL MODE [_Tx2(0),_Tx2(1),_Tx2(0),_Px16(1),_Px16(0),_Px16(1),_MODE(1),_MODE(1)] 
	TWI_write_sensor( Address, 0xF5, 0x10); //CONFIGURATION	
	//TWI_write_sensor( Address, 0xF4, 0x01); 
	DDRB |= (1<<DDB5);
}

void mpu6050_read_Acc(void){
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x3B);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x3C);
	AcX = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x3D);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x3E);
	AcY = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x3F);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x40);
	AcZ = (int16_t)(tmp[0]<<8)|(tmp[1]);
}
void mpu6050_read_Gyr(void){
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x43);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x44);
	GyX = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x45);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x46);
	GyY = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x47);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x48);
	GyZ = (int16_t)(tmp[0]<<8)|(tmp[1]);
}

int32_t bmp280_read_Temp(void){
	prs[0] = TWI_read_sensor(BMP280_ADDRESS, 0xFA);		
	prs[1] = TWI_read_sensor(BMP280_ADDRESS, 0xFB);	
	prs[2] = TWI_read_sensor(BMP280_ADDRESS, 0xFC);
	return ((uint32_t) prs[0]<<16)|((uint32_t) prs[1]<<8)|((uint32_t) prs[2]);
}
int32_t bmp280_read_Prs(void){
	prs[0] = TWI_read_sensor(BMP280_ADDRESS, 0xF7);
	prs[1] = TWI_read_sensor(BMP280_ADDRESS, 0xF8);
	prs[2] = TWI_read_sensor(BMP280_ADDRESS, 0xF9);
	return ((uint32_t) prs[0]<<16)|((uint32_t) prs[1]<<8)|((uint32_t) prs[2]);
}
uint16_t bmp280_read_parameters(uint16_t reg){
	tmp[0] = TWI_read_sensor(BMP280_ADDRESS, reg);
	tmp[1] = TWI_read_sensor(BMP280_ADDRESS, reg+1);
	return (uint16_t)(tmp[1]<<8)|(tmp[0]);
}
void Parameters(void){
	T1 = (uint16_t)bmp280_read_parameters(0x88);
	T2 = (int16_t) bmp280_read_parameters(0x8A);
	T3 = (int16_t) bmp280_read_parameters(0x8C);

	P1 = (uint16_t)bmp280_read_parameters(0x8E);
	P2 = (int16_t) bmp280_read_parameters(0x90);
	P3 = (int16_t) bmp280_read_parameters(0x92);
	P4 = (int16_t) bmp280_read_parameters(0x94);
	P5 = (int16_t) bmp280_read_parameters(0x96);
	P6 = (int16_t) bmp280_read_parameters(0x98);
	P7 = (int16_t) bmp280_read_parameters(0x9A);
	P8 = (int16_t) bmp280_read_parameters(0x9C);
	P9 = (int16_t) bmp280_read_parameters(0x9E);
}

void timer_Init()
{
	// Configure Timer 1
	PRR &=~ (1<<PRTIM1);
	TCCR1A = 0x00; // Normal mode, OC1A/OC1B disconnected
	TCCR1B = (0<<WGM12)|(1<<CS12)|(1<<CS10); // CTC and prescaler 1024
	
/*
	TCCR1B &=~ (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &=~ (1<<CS12);*/
	TCCR1B |= (1<<ICES1);

	TCNT1 = 0;	
}
float Read_TIMER1( void )
{
	uint16_t i;
	/* Read TCNT0 into i */
	i = TCNT1;
	TCNT1 = 0;
	//PORTB ^= (1<<PORTB5);		
	return i*0.000064;
}
	
	//FALTA APAGAR LOS SENSORES
	
int main(void)
{
	cli();
    TWI_Init();
	UART_init();
	//timer_Init();
	//mpu6050_init(MPU6050_ADDRESS);
	bmp280_init(BMP280_ADDRESS);
	sei();	
	_delay_ms(10);	
	//TIM16_ReadTCNT1();
	
	while (1){				
		_delay_ms(200);
		Parameters();
				
		// TEMPERATURA //
		Temperatura = (int32_t) bmp280_read_Temp();
		Temperatura >>= 4;
				
		var1 = ((((Temperatura >> 3) - ((int32_t)T1 << 1))) * ((int32_t)T2)) >> 11;
		var2 = (((((Temperatura >> 4) - ((int32_t)T1)) * ((Temperatura >> 4) - ((int32_t)T1))) >> 12) * ((int32_t)T3)) >> 14;
		t_fine = var1 + var2;
		float T = (t_fine * 5 + 128) >> 8;
		T = T/ 100;
		
		UART_write_float(T);
		
		// PRESION //
		Presion = (int32_t) bmp280_read_Prs();
		Presion >>= 4;		
		
		var1 = ((int64_t)t_fine) - 128000;
		var2 = var1 * var1 * (int64_t)P6;
		var2 = var2 + ((var1 * (int64_t)P5) << 17);
		var2 = var2 + (((int64_t)P4) << 35);
		var1 = ((var1 * var1 * (int64_t)P3) >> 8) + ((var1 * (int64_t)P2) << 12);
		var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)P1) >> 33;
		
		if (var1 == 0) {
			return 0; // avoid exception caused by division by zero
		}
		
		int64_t P = 1048576 - Presion;
		P = (((P << 31) - (int64_t)var2) * 3125) / var1;		
		var1 = (((int64_t)P9) * (P >> 13) * (P >> 13)) >> 25;
		var2 = (((int64_t)P8) * P) >> 19;

		P = ((P + var1 + var2) >> 8) + (((int64_t)P7) << 4);
			
		UART_write_float((float)P / 25600);
	}
}

// dato = UART_read();
// uint8_t dato = 0;