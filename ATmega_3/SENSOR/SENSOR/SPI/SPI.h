/*
 * SPI.h
 *
 * Created: 29/11/2021 11:17:46
 *  Author: Alessandro
 */ 


#ifndef SPI_H_
#define SPI_H_

	#define F_CPU 16000000UL // 16 MHz clock speed
	#include <avr/io.h>
	
	void SPI_init();
	void SPI_tx(uint8_t data);
	void SPI_tx_16bit(uint16_t data);
	void SPI_tx_32bit(uint32_t data);
	

#endif /* SPI_H_ */