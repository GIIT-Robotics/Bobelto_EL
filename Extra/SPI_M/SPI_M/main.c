/*
 * SPI_M.c
 *
 * Created: 13/10/2021 17:07:48
 * Author : Alessandro
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART/UART.h"

uint8_t datoRecibido = 0x00;
uint8_t pinesB = 0x00;

void SPI_init()		//- Inicializa SPI como Master
{
	DDRB |=  (1<<DDB3)|(1<<DDB5); 	// PB3 es MOSI y PB5 es SCK
	DDRB &=~ (1<<DDB4);                 	// PB4 es MISO
	
	// Esclavos
	DDRB |= (1<<DDB1)|(1<<DDB2);                  	// PB2, PB1 será SS
	PORTB |= (1<<PORTB1)|(1<<PORTB2);               // En alta significa que está desactivado
	
	// Orden de los datos
	SPCR &=~ (1<<DORD);                 	// Primero el MSB
	
	// Polaridad y fase
	SPCR &=~ (1<<CPOL);                 	// Clock inactivo en baja
	SPCR &=~ (1<<CPHA);                 	// Se trabaja en flancos de subida
	
	// Preescalador (8) => 1 MHz
	SPCR |=  (1<<SPR0);
	SPCR &=~ (1<<SPR1);
	SPSR &=~ (1<<SPI2X);
	
	// Configurado como maestro
	SPCR |= (1<<MSTR);
	
	// Activar SPI
	SPCR |= (1<<SPE);
}

void SPI_slaveON(uint8_t slave)
{
	switch (slave)
	{
		case 1:
			PORTB &=~ (1<<PORTB1);
		break;
		
		case 2:
			PORTB &=~ (1<<PORTB2);
		break;
	}
}

void SPI_slaveOFF(uint8_t slave)
{
	switch (slave)
	{
		case 1:
			PORTB &=~ (1<<PORTB1);
		break;
		
		case 2:
			PORTB &=~ (1<<PORTB2);
		break;
	}
}

void SPI_tx(uint8_t data)
{
	/* Cargar dato al registro */
	SPDR = data;
	/* Esperar a que la transmisión se realice */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_rx()
{
	/* Esperar a la recepción del dato */
	while(!(SPSR & (1<<SPIF)));
	/* Retorna el dato recibido */
	return SPDR;
}

int main(void)
{
	SPI_init();
	UART_init();

	_delay_ms(10);
	
    while (1) 
    {
		while(!(UCSR0A&(1<<7)));	
		unsigned char RX_data = UART_read();
		
		UART_write(RX_data);
		UART_write('\n');
		
		switch(RX_data)
		{
			case '0':
				UART_write_txt("NONE.");
				UART_write('\n');
				SPI_slaveON(1);
				SPI_tx(0x00);
				datoRecibido = SPI_rx();
				UART_write_data(datoRecibido);
				UART_write('\n');
				SPI_slaveOFF(1);
				break;
			
			case '1':
				UART_write_txt("Temperatura interna.");
				UART_write('\n');
				SPI_slaveON(1);
				SPI_tx(0x01);
				datoRecibido = SPI_rx();
				UART_write_data(datoRecibido);
				UART_write('\n');
				SPI_slaveOFF(1);
				break;
			
			
			case '2':
				UART_write_txt("Presión interna.");
				UART_write('\n');
				SPI_slaveON(1);
				SPI_tx(0x02);
				datoRecibido = SPI_rx();
				UART_write_data(datoRecibido);
				UART_write('\n');
				SPI_slaveOFF(1);
				break;
			
			case '3':
				UART_write_txt("Accelerometer.");
				UART_write('\n');
				SPI_slaveON(1);
				SPI_tx(0x02);
				datoRecibido = SPI_rx();
				UART_write_data(datoRecibido);
				UART_write('\n');
				SPI_slaveOFF(1);
				break;
			
			case '4':
				UART_write_txt("Gyroscope.");
				UART_write('\n');
				SPI_slaveON(1);
				SPI_tx(0x02);
				datoRecibido = SPI_rx();
				UART_write_data(datoRecibido);
				UART_write('\n');
				SPI_slaveOFF(1);
				break;	
			
			default:
				UART_write_txt("Error.");
				UART_write('\n');
				break;
		}
		
		/*
		SPI_slaveON(2);
		SPI_tx(15);
		datoRecibido = SPI_rx();
		SPI_slaveOFF(2);
		
		
		UART_write_txt("DATO SPI recibe M: ");
		UART_write_data(datoRecibido);
		UART_write('\n');
		*/
		
		_delay_ms(100);
    }
}

