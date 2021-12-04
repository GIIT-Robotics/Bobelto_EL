#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "SPI/SPI.h"
#include "UART/UART.h"

unsigned char UART_BUFFER = 0x00;
uint8_t SPI_BUFFER[2] = {0,0};

ISR(USART_RX_vect)
{
	UART_BUFFER = UART_read();
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
		switch(UART_BUFFER)
		{
			case '1':
				UART_write_txt("Entra al comando 1 \n");
				
				SPI_slaveON(1);
				SPI_tx(0x01);
				SPI_BUFFER[0] = SPI_rx();
				SPI_slaveOFF(1);
				
				UART_write_txt("Envio comando 0x01 \n");
				UART_write(SPI_BUFFER[0]);
				UART_write('\n');
				
				UART_BUFFER = 0x00;
				break;

			case '2':
				UART_write_txt("Entra al comando 2 \n");
				
				SPI_slaveON(1);
				SPI_BUFFER[0] = SPI_trx(0x02);
				SPI_slaveOFF(1);
				
				_delay_ms(50);
				
				SPI_slaveON(1);
				SPI_BUFFER[1] = SPI_trx(0x02);
				SPI_slaveOFF(1);
				
				UART_write_txt("Envio comando 0x02 \n");
				
				UART_write(SPI_BUFFER[0]);
				UART_write(SPI_BUFFER[1]);
				UART_write('\n');
				
				UART_BUFFER = 0x00;
				break;
			
			/************************************************************************/
			/* ESTE ES EL QUE FUNCIONA                                              */
			/************************************************************************/
			case '3':
				UART_write_txt("Entra al comando 3 \n");
				
				SPI_slaveON(1);
				
				SPI_BUFFER[0] = SPI_trx(0x01);		//- Pide el primer dato y se almacena una respuesta fantasma
				_delay_ms(50);
				SPI_BUFFER[0] = SPI_trx(0x02);		//- Pide el segundo dato (pero se almacena el primero)
				_delay_ms(50);
				SPI_BUFFER[1] = SPI_trx(0x01);		//- Pide el primer dato (pero se almacena el segundo)
				
				SPI_slaveOFF(1);
				
				UART_write_txt("Envio comando 0x03 \n");
				
				UART_write(SPI_BUFFER[0]);
				UART_write(SPI_BUFFER[1]);
				UART_write('\n');
	
			default:
				UART_BUFFER = 0x00;
				break;
		}
		
		_delay_ms(100);
    }
}

