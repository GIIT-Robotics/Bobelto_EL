/*
 * MPU6050.h
 *
 * Created: 14/11/2021 13:31:42
 *  Author: Usuario
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

	#include "../TWI/TWI.h"
	#include "../UART/UART.h"
	#define MPU6050_ADDRESS 0x68	//- MPU6050 Address
	
	void MPU6050_init();
	int16_t MPU6050_read_acce(int axis);
	int16_t MPU6050_read_gyro();
	

#endif /* MPU6050_H_ */