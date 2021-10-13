/*
 * SPI_S.c
 *
 * Created: 13/10/2021 13:31:49
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
	DDRB &=~  (1<<DDB3)|(1<<DDB5); 	// PB3 es MOSI y PB5 es SCK
	DDRB |= (1<<DDB4);                 	// PB4 es MISO
	
	// Esclavos
	DDRB &=~ (1<<DDB2);                  	// PB2 será SS del esclavo
	PORTB |= (1<<PORTB2);               	// Configurado como pull-up
	
	// Orden de los datos
	SPCR &=~ (1<<DORD);                 	// Primero el MSB
	
	// Polaridad y fase
	SPCR &=~ (1<<CPOL);                 	// Clock inactivo en baja
	SPCR &=~ (1<<CPHA);                 	// Se trabaja en flancos de subida
	
	// Preescalador (8) => 1 MHz
	SPCR |=  (1<<SPR0);
	SPCR &=~ (1<<SPR1);
	SPSR &=~ (1<<SPI2X);
	
	// Configurado como esclavo
	SPCR &=~ (1<<MSTR);
	
	// Activar SPI
	SPCR |= (1<<SPE);
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
	    datoRecibido = SPI_rx();
	    if (datoRecibido == 20)
	    {
		    SPI_tx(25);
	    } else if(datoRecibido == 15){
			SPI_tx(10);
		}
		
		// si envias 0 por spi, se raya con el valor anterior.
		/*
		if(PORTB & (1<<PORTB2))
		{
			datoRecibido = SPI_rx();
			if(datoRecibido == 0xBB)
			{
				SPI_tx(0xAA);
			}
		}
		*/
		UART_write_txt("DATO SPI recibe S: ");
		UART_write_data(datoRecibido);
		UART_write('\n');
		
		_delay_ms(100);
    }
}

