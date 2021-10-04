/*
 * I2C.h
 *
 * Created: 22/09/2021 15:37:30
 *  Author: Alessandro
 */ 


#ifndef I2C_H_
#define I2C_H_

	#include <avr/io.h>
	#include <stdbool.h>
	
	/* Variables del I2C */
	#define I2C_W			0x00
	#define I2C_R			0x01
	#define I2C_ACK			0x01
	#define I2C_NACK		0x00
	#define I2C_START		0x08
	#define I2C_RESTART		0x10
	#define I2C_WT_SLA_ACK	0x18
	#define I2C_MT_DATA_ACK 0x28
	#define I2C_RD_SLA_ACK	0x40

	/* Funciones del I2C */
	void I2C_Init();
	bool I2C_StartCondition();
	bool I2C_RestartCondition();
	void I2C_StopCondition();
	bool I2C_SendAddress(uint8_t, uint8_t);
	bool I2C_Write(uint8_t);
	uint8_t I2C_Read(uint8_t);
	
#endif /* I2C_H_ */