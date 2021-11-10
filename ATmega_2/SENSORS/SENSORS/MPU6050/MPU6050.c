#include "MPU6050.h"

void MPU6050_init(uint16_t Address){
	TWI_write_sensor( Address, 0x6B, 0x00); //Sacar del sleep mode
	TWI_write_sensor( Address, 0x1A, 0x01);
	TWI_write_sensor( Address, 0x1B, 0x00);
	TWI_write_sensor( Address, 0x1C, 0x00);
	TWI_write_sensor( Address, 0x38, 0x00);
	TWI_write_sensor( Address, 0x68, 0x07);
}

void MPU6050_Read_Acc(void){
	uint8_t tmp[2];
	
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

void MPU6050_Read_Gyr(void){
	uint8_t tmp[2];
	
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