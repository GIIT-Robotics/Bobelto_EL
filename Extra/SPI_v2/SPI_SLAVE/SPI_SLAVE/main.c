#define F_CPU 16000000UL 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART/UART.h"
#include "SPI/SPI.h"

uint8_t SPI_BUFFER = 0;

ISR(SPI_STC_vect)
{
	UART_write_txt("Interrumpe por SPI \n");
	SPI_BUFFER = SPDR;
	if (SPI_BUFFER == 0x01)
	{
		UART_write_txt("Comando 0x01 \n");
		SPDR = 0x41;
		SPI_BUFFER = 0x00;
	}
	else if (SPI_BUFFER == 0x02)
	{
		UART_write_txt("Comando 0x02 \n");
		SPDR = 0x42;
		SPI_BUFFER = 0x00;
	}
}

int main(void)
{
	cli();
	
	UART_init();
	
	UART_write_txt("Configura SPI \n");
	SPI_init();
	
	sei();
	
	_delay_ms(10);
	
    while (1) 
    {	
		_delay_ms(10);
    }
}