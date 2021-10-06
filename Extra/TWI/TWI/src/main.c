//#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>
#include "TWI/TWI.h"
#include "mpu6050_reg.h"
#include "UART.h"

//Ratios de conversion
#define A_R 16384.0    // 32768/2
#define G_R 131.0       // 32768/250

//Conversion de radianes a grados 180/PI
#define RAD_TO_DEG 57.295779

//Valores RAW
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

//Angulos
float Acc[2];
float Gy[3];
float Angle[3];

//Variables temporales
int8_t currentSeg = 0;
float dt = 0;
uint8_t tmp[12];

void TWI_write_sensor(uint16_t Address, uint16_t reg, uint8_t val){
	while(TWI_startCond());
	while(TWI_sendAdrr(Address, TWI_W));
	while(TWI_write(reg));
	while(TWI_write(val));
	TWI_stopCond();
}
int8_t TWI_read_sensor(uint16_t Address, uint16_t reg){
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
void mpu6050_read_Acc(void){
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS, 0x3B);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS, 0x3C);
	AcX = (tmp[0]<<8)|(tmp[1]);
	
	tmp[2] = TWI_read_sensor(MPU6050_ADDRESS, 0x3D);
	tmp[3] = TWI_read_sensor(MPU6050_ADDRESS, 0x3E);
	AcY = (tmp[2]<<8)|(tmp[3]);
	
	tmp[4] = TWI_read_sensor(MPU6050_ADDRESS, 0x3F);
	tmp[5] = TWI_read_sensor(MPU6050_ADDRESS, 0x40);
	AcZ = (tmp[4]<<8)|(tmp[5]);
}
void mpu6050_read_Gyr(void){
	tmp[6] = TWI_read_sensor(MPU6050_ADDRESS, 0x43);
	tmp[7] = TWI_read_sensor(MPU6050_ADDRESS, 0x44);
	GyX = (tmp[6]<<8)|(tmp[7]);
	
	tmp[8] = TWI_read_sensor(MPU6050_ADDRESS, 0x45);
	tmp[9] = TWI_read_sensor(MPU6050_ADDRESS, 0x46);
	GyY = (tmp[8]<<8)|(tmp[9]);
	
	tmp[10] = TWI_read_sensor(MPU6050_ADDRESS, 0x47);
	tmp[11] = TWI_read_sensor(MPU6050_ADDRESS, 0x48);
	GyZ = (tmp[10]<<8)|(tmp[11]);
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
	
int main(void)
{
	cli();
    TWI_Init();
	UART_init();
	timer_Init();
	mpu6050_init(MPU6050_ADDRESS);
	sei();
	DDRB |= (1<<DDB5);
	_delay_ms(10);	
	//TIM16_ReadTCNT1();
	
	while (1){				
		//PRENDIDO
		//PORTB ^= (1<<PORTB5);	
		mpu6050_read_Acc();
		mpu6050_read_Gyr();		
		Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
		Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
		
		//Calculo del angulo del Giroscopio
		Gy[0] = GyX/G_R;
		Gy[1] = GyY/G_R;
		Gy[2] = GyZ/G_R;
				
		dt = Read_TIMER1();	
		//Aplicar el Filtro Complementario
		Angle[0] = 0.98 *(Angle[0]+Gy[0]*dt) + 0.02*Acc[0];
		Angle[1] = 0.98 *(Angle[1]+Gy[1]*dt) + 0.02*Acc[1];
		
		//Integración respecto del tiempo paras calcular el YAW
		Angle[2] = Angle[2]+Gy[2]*dt;
							
		UART_write_txt("\n\rAngle 1: " );		
		UART_write_data(Angle[0]);	
		UART_write_txt("\n\rAngle 2: " );
		UART_write_data(Angle[1]);
		UART_write_txt("\n\rAngle 3: " );			
		UART_write_data(Angle[2]);
		_delay_ms(20);
	}
}

// dato = UART_read();
// uint8_t dato = 0;