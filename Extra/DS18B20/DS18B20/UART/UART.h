#ifndef UART_H_
#define UART_H_

	#define	F_CPU 16000000UL

	#include <avr/io.h>
	#include <stdbool.h>
	#include <math.h>

	void UART_init();							//funci?n para iniciar el USART AVR as?ncrono, 8 bits, 9600 baudios,
	unsigned char UART_read();					//funci?n para la recepci?n de caracteres
	void UART_write(unsigned char);				//funci?n para la transmisi?n de caracteres
	void UART_write_txt(char*);						//funci?n para la transmisi?n de cadenas de caracteres
	void UART_write_data(float);

#endif /* UART_H_ */