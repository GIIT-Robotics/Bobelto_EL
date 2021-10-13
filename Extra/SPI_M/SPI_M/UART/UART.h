/*
 * UART.h
 *
 * Created: 6/10/2021 13:30:15
 *  Author: Alessandro
 */ 


#ifndef UART_H_
#define UART_H_


#define	F_CPU 16000000UL

#include <avr/io.h>
#include <stdbool.h>
#include <math.h>

void UART_init();							//función para iniciar el USART AVR asíncrono, 8 bits, 9600 baudios,
unsigned char UART_read();					//función para la recepción de caracteres
void UART_write(unsigned char);				//función para la transmisión de caracteres
void UART_write_txt(char*);						//función para la transmisión de cadenas de caracteres
void UART_write_data(float);



#endif /* UART_H_ */