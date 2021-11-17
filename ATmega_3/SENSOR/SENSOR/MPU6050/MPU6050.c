#include "MPU6050.h"

void MPU6050_init()
{
	UART_write_txt("MPU: Primer init");
	UART_write('\n');	
	TWI_write_sensor(MPU6050_ADDRESS,0x6B,0x00);	//- Lo saca del sleep mode
	UART_write_txt("MPU: Segundo init");
	UART_write('\n');
	TWI_write_sensor(MPU6050_ADDRESS,0x1A,0x01);
	UART_write_txt("MPU: Tercer init");
	UART_write('\n');
	TWI_write_sensor(MPU6050_ADDRESS,0x1B,0x00);
	UART_write_txt("MPU: Cuarto init");
	UART_write('\n');
	TWI_write_sensor(MPU6050_ADDRESS,0x1C,0x00);
	UART_write_txt("MPU: Quinto init");
	UART_write('\n');
	TWI_write_sensor(MPU6050_ADDRESS,0x38,0x00);
	UART_write_txt("MPU: Sexto init");
	UART_write('\n');
	TWI_write_sensor(MPU6050_ADDRESS,0x68,0x07);
}

int16_t MPU6050_read_acce(int axis)
{
	uint8_t tmp[2];		//- tmp[0]->msb | tmp[1]->lsb 
	int16_t acc;
	
	if (axis == 1)
	{
		//- Eje X
		tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x3B);
		tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x3C);
	} 
	else if (axis == 2)
	{
		//- Eje Y
		tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x3D);
		tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x3E);
	} 
	else if (axis == 3)
	{
		//- Eje Z
		tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x3F);
		tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x40);
	} 
	else 
	{
		//- No axis
		tmp[0] = 0xFF;
		tmp[1] = 0xFF;
	}

	acc = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	return acc;
}

int16_t MPU6050_read_gyro(int axis)
{
	uint8_t tmp[2];		//- tmp[0]->msb | tmp[1]->lsb
	int16_t gyr;
	
	if (axis == 1)
	{
		//- Eje X
		tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x43);
		tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x44);
	} 
	else if (axis == 2)
	{
		//- Eje Y
		tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x45);
		tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x46);
	} 
	else if (axis == 3)
	{
		//- Eje Z
		tmp[0] = TWI_read_sensor(MPU6050_ADDRESS,0x47);
		tmp[1] = TWI_read_sensor(MPU6050_ADDRESS,0x48);
	} 
	else
	{
		//- No axis
		tmp[0] = 0xFF;
		tmp[1] = 0xFF;
	}
		
	gyr = (int16_t)(tmp[0]<<8)|(tmp[1]);
	
	return gyr;
}