/*
 * TWI.h
 *
 * Created: 10/11/2021 21:05:53
 *  Author: Alessandro
 */ 


#ifndef TWI_H_
#define TWI_H_

	#define F_CPU 16000000UL // 16 MHz clock speed
	
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdbool.h>

	//- Lista de constantes
	#define	TWI_W			0x00
	#define	TWI_R			0x01
	#define TWI_ACK			0x01
	#define TWI_NACK		0x00

	#define TWI_START		0x08
	#define TWI_RESTART		0x10
	#define TWI_WT_SLA_ACK	0x18
	#define TWI_MT_DATA_ACK	0x28
	#define TWI_RD_SLA_ACK	0x40




#endif /* TWI_H_ */