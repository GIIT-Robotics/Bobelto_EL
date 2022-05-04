#define F_CPU 16000000UL 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART/UART.h"
#include "SPI/SPI.h"

uint8_t SPI_BUFFER = 0;

ISR(SPI_STC_vect)
{
	SPI_BUFFER = SPDR;
	if (SPI_BUFFER == 0x01)
	{
		SPDR = 0x41;
		SPI_BUFFER = 0x00;
	}
	else if (SPI_BUFFER == 0x02)
	{
		SPDR = 0x42;
		SPI_BUFFER = 0x00;
	}
}

int main(void)
{
	cli();
	SPI_init();
	sei();
	
	_delay_ms(10);
	
    while (1) 
    {	
    }
}