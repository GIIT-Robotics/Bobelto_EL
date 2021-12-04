/*
 * 
 *	SPI Master v2.0
 *
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART/UART.h"
#include "SPI/SPI.h"

uint8_t UART_BUFF = 0x00;
uint8_t flag = 0x00;

ISR(USART_RX_vect)
{
	UART_BUFF = UART_read();
	flag = 0x01;
}

int main(void)
{
	uint8_t temp[4] = {0,0,0,0};
	
	cli();
	
	SPI_init();
	UART_init();
	
	sei();
	
	_delay_ms(10);
	
    while (1) 
    {
		//if (flag == 0x01)
		//{
			//switch(UART_BUFF)
			//{
				//case '0':
					//SPI_slaveON(1);
					//SPI_tx(0x00);
					//temp[0] = SPI_rx();
					//UART_write(temp[0]);
					//UART_write('\n');
					//SPI_slaveOFF(1);
					//break;
				//
				//case '1':
					//SPI_slaveON(1);
					//SPI_tx(0x01);
					//temp[0] = SPI_rx();
					//UART_write(temp[0]);
					//UART_write('\n');
					//SPI_slaveOFF(1);
					//break;
				//
				//default:
					//break;
			//}
			//
			//flag = 0x00;
		//}
		//_delay_ms(100);
		
		SPI_slaveON(1);
		temp[0] = SPI_trans(0x01);
		UART_write(temp[0]);
		UART_write('\n');
		SPI_slaveOFF(1);
		UART_BUFF = 0x00;
		
		_delay_ms(1000);
    }
}

