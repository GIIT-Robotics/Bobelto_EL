#include "MPU6050.h"

void MPU6050_init()
{
	TWI_write_sensor(MPU6050_ADDRESS,0x6B,0x00);	//- Lo saca del sleep mode
	TWI_write_sensor(MPU6050_ADDRESS,0x1A,0x01);
	TWI_write_sensor(MPU6050_ADDRESS,0x1B,0x00);
	TWI_write_sensor(MPU6050_ADDRESS,0x1C,0x00);
	TWI_write_sensor(MPU6050_ADDRESS,0x38,0x00);
	TWI_write_sensor(MPU6050_ADDRESS,0x68,0x07);
}

int16_t MPU6050_read_acce()
{
	uint8_t tmp[2];		//- tmp[0]->msb | tmp[1]->lsb 
	
	int16_t acc[3];		//- acc[0]->X | acc[1]->Y | acc[2]->Z
	
	//- Eje X
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x3B);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x3C);
	acc[0] = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	//- Eje Y
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x3D);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x3E);
	acc[1] = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	//- Eje Z
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x3F);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x40);
	acc[2] = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	return acc;
}

int16_t MPU6050_read_gyro()
{
	uint8_t tmp[2];		//- tmp[0]->msb | tmp[1]->lsb
	
	int16_t gyr[3];		//- gyr[0]->X | gyr[1]->Y | gyr[2]->Z
	
	//- Eje X
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x43);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x44);
	gyr[0] = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	//- Eje Y
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x45);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x46);
	gyr[1] = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	//- Eje Z
	tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x47);
	tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x48);
	gyr[2] = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	return gyr;
}