/*
 * UART.h
 *
 * Created: 27/10/2021 12:32:01
 *  Author: Alessandro
 */ 


#ifndef UART_H_
#define UART_H_

	#define F_CPU 16000000UL // 16 MHz clock speed
	
	#include <avr/io.h>
	#include <stdbool.h>
	#include <math.h>
	
	void UART_init();
	unsigned char UART_read();
	void UART_write(unsigned char);
	void UART_write_txt(char*);
	void UART_write_data(float);

#endif /* UART_H_ */