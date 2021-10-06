/*
 * TWI.h
 *
 * Created: 21/09/2017 04:32:03 p.m.
 *  Author: Marlon
 */ 
 

#ifndef TWI_H_
#define TWI_H_
		
	#include <avr/io.h>
	#include <stdbool.h>
	
	///// TIW //////
	#define	TWI_W			0x00
	#define	TWI_R			0x01
	#define TWI_ACK			0x01
	#define TWI_NACK		0x00
	 
	#define TWI_START		0x08
	#define TWI_RESTART		0x10
	#define TWI_WT_SLA_ACK	0x18
	#define TWI_MT_DATA_ACK	0x28
	#define TWI_RD_SLA_ACK	0x40

	void TWI_Init();
	bool TWI_startCond();
	bool TWI_restrtCond();
	void TWI_stopCond();
	bool TWI_write(uint8_t);
	uint8_t TWI_read(uint8_t);
	bool TWI_sendAdrr(uint8_t, uint8_t);

#endif /* TWI_H_ */