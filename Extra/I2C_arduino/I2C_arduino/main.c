/*
 * I2C_arduino.c
 *
 * Created: 22/09/2021 15:41:28
 * Author : Alessandro
 */ 

#ifndef F_CPU
	#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "I2C/I2C.h"

uint8_t GyroX_data_H = 0, GyroX_data_L = 0, GyroY_data_H = 0, GyroY_data_L = 0, AccelX_data_H = 0, AccelX_data_L = 0;

void MPU6050_Init()
{
	// Apaga el Sleep Mode
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x6B);
	I2C_Write(0x00);
	I2C_StopCondition();
	
	// LPF, BW = 184 (accel) and 188 (gyro)
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x1A);
	I2C_Write(0x01);
	I2C_StopCondition();
	
	// gyro ADC scale 1000 deg/s
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x1B);
	I2C_Write(1<<4);
	I2C_StopCondition();
	
	// accel ADC scale 2 g
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x1C);
	I2C_Write(0x00);
	I2C_StopCondition();
	
	/*
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x38);
	I2C_Write(0x00);
	I2C_StopCondition();
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x68);
	I2C_Write(0x00);
	I2C_StopCondition();
	*/
}

uint8_t MPU6050_ReadGyroX_H()
{	
	uint8_t buff = 0;
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x43);
	I2C_RestartCondition();
	I2C_SendAddress(0x68, I2C_R);
	buff = I2C_Read(I2C_ACK);
	I2C_StopCondition();
	
	return buff;	
}

uint8_t MPU6050_ReadGyroX_L()
{
	uint8_t buff = 0;
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x44);
	I2C_RestartCondition();
	I2C_SendAddress(0x68, I2C_R);
	buff = I2C_Read(I2C_ACK);
	I2C_StopCondition();
	
	return buff;
}

uint8_t MPU6050_ReadGyroY_H()
{
	uint8_t buff = 0;
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x45);
	I2C_RestartCondition();
	I2C_SendAddress(0x68, I2C_R);
	buff = I2C_Read(I2C_ACK);
	I2C_StopCondition();
	
	return buff;
}

uint8_t MPU6050_ReadGyroY_L()
{
	uint8_t buff = 0;
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x46);
	I2C_RestartCondition();
	I2C_SendAddress(0x68, I2C_R);
	buff = I2C_Read(I2C_ACK);
	I2C_StopCondition();
	
	return buff;
}

uint8_t MPU6050_ReadAccelX_H()
{
	uint8_t buff = 0;
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x3B);
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_R);
	buff = I2C_Read(I2C_ACK);
	I2C_StopCondition();
	
	return buff;
}

uint8_t MPU6050_ReadAccelX_L()
{
	uint8_t buff = 0;
	
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_W);
	I2C_Write(0x3C);
	I2C_StartCondition();
	I2C_SendAddress(0x68, I2C_R);
	buff = I2C_Read(I2C_ACK);
	I2C_StopCondition();
	
	return buff;
}

int main(void)
{
	cli();
	I2C_Init();
	sei();
	
	_delay_ms(10);
	
	DDRD = 0xFF;
	MPU6050_Init();

	while(1)
	{
		
		//I2C_StartCondition();
		//I2C_SendAddress(0x68, I2C_W);
		//I2C_StartCondition();
		//I2C_Write(0xAA);
		//I2C_data_H = I2C_Read(I2C_ACK);
		//I2C_StartCondition();
		//I2C_SendAddress(0x68, I2C_R);
		//I2C_StartCondition();
		//I2C_Write(0xA7);
		//I2C_data_H = I2C_Read(I2C_ACK);
		//I2C_data_L = I2C_Read(I2C_ACK);
		//I2C_StopCondition();
		
		/*
		GyroX_data_H = MPU6050_ReadGyroX_H();
		GyroX_data_L = MPU6050_ReadGyroX_L();
		
		_delay_ms(100);
		
		GyroY_data_H = MPU6050_ReadGyroX_H();
		GyroY_data_L = MPU6050_ReadGyroX_L();
		
		_delay_ms(100);
		
		AccelX_data_H = MPU6050_ReadAccelX_H();
		AccelX_data_L = MPU6050_ReadAccelX_L();
		
		_delay_ms(100);
		*/
	}
}

