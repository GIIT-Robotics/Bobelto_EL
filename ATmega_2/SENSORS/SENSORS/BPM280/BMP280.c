#include "BMP280.h"

void bmp280_init(uint16_t Address){
	TWI_write_sensor( Address, 0xE0, 0xB6); //RESET
	
	// MODO: NAVIGATION INDOOR
	TWI_write_sensor( Address, 0xF4, 0x57); //NORMAL MODE [_Tx2(0),_Tx2(1),_Tx2(0),_Px16(1),_Px16(0),_Px16(1),_MODE(1),_MODE(1)]
	TWI_write_sensor( Address, 0xF5, 0x10); //CONFIGURATION
	//TWI_write_sensor( Address, 0xF4, 0x01);
	DDRB |= (1<<DDB5);
}

int32_t bmp280_read_Temp(void){
	uint8_t prs[3];
	
	prs[0] = TWI_read_sensor(BMP280_ADDRESS, 0xFA);
	prs[1] = TWI_read_sensor(BMP280_ADDRESS, 0xFB);
	prs[2] = TWI_read_sensor(BMP280_ADDRESS, 0xFC);
	return ((uint32_t) prs[0]<<16)|((uint32_t) prs[1]<<8)|((uint32_t) prs[2]);
}

int32_t bmp280_read_Prs(void){
	uint8_t prs[3];
	
	prs[0] = TWI_read_sensor(BMP280_ADDRESS, 0xF7);
	prs[1] = TWI_read_sensor(BMP280_ADDRESS, 0xF8);
	prs[2] = TWI_read_sensor(BMP280_ADDRESS, 0xF9);
	return ((uint32_t) prs[0]<<16)|((uint32_t) prs[1]<<8)|((uint32_t) prs[2]);
}

uint16_t bmp280_read_parameters(uint16_t reg){
	uint8_t tmp[2];
	
	tmp[0] = TWI_read_sensor(BMP280_ADDRESS, reg);
	tmp[1] = TWI_read_sensor(BMP280_ADDRESS, reg+1);
	return (uint16_t)(tmp[1]<<8)|(tmp[0]);
}

void Parameters(void){
	uint16_t T1, P1;
	int16_t  T2, T3, P2, P3, P4, P5, P6, P7, P8, P9;
	
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