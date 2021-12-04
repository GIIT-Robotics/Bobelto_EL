/*
 * 
 *	SPI Slave v2.0
 *
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "SPI/SPI.h"
#include "UART/UART.h"

uint8_t SPI_BUFF = 0x00;
uint8_t flag = 0x00;
uint8_t data = 0x48;

ISR(SPI_STC_vect)
{
	UART_write_txt("Interrumpe: ");
	SPI_BUFF = SPDR;
	SPI_tx(data);
	UART_write_data(SPI_BUFF);
	UART_write('\n');
}

int main(void)
{
	cli();
	
	SPI_init();
	UART_init();
	
	sei();
	
	_delay_ms(10);
	
    while (1) 
    {
		//UART_write_txt("Entra while");
		//UART_write('\n');
		//
		//if (SPI_BUFF == 0x01)
		//{
			//UART_write_txt("Envía: ");
			//UART_write(data);
			//UART_write('\n');
			//SPI_tx(data);
		//}
		
		//if (flag != 0x00)
		//{
			//SPI_tx(0x48);
			//switch(SPI_BUFF)
			//{
				//case 0x00:
					//SPI_tx(0x48);
					//UART_write(0x48);
					//UART_write('\n');
					//_delay_us(10);
					//break;
				//
				//case 0x01:
					//SPI_tx(0x4F);
					//UART_write(0x47);
					//UART_write('\n');
					//break;
					//
				//default:
					//break;
			//}
			//
			//flag = 0x00;
		//}
		//_delay_ms(100);
    }
}

