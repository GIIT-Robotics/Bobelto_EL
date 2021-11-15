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

	//- Funciones TWI generales
	void TWI_init();
	bool TWI_startCond();
	bool TWI_restrtCond();
	void TWI_stopCond();
	bool TWI_sendAdrr(uint8_t adrr, uint8_t action);
	bool TWI_write(uint8_t data);
	uint8_t TWI_read(uint8_t ACK_NACK);
	
	//- Funciones para sensores de I2C
	void TWI_write_sensor(uint8_t Address, uint8_t reg, uint8_t val);
	uint8_t TWI_read_sensor(uint8_t Address, uint8_t reg);



#endif /* TWI_H_ */