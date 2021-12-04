#include "SPI.h"

void SPI_init()
{
	DDRB |=  (1<<DDB3)|(1<<DDB5); 			// PB3 es MOSI y PB5 es SCK
	DDRB &=~ (1<<DDB4);                 	// PB4 es MISO
	
	// Esclavos
	DDRB |= (1<<DDB1)|(1<<DDB2);            // PB2, PB1 ser? SS
	PORTB |= (1<<PORTB1)|(1<<PORTB2);       // En alta significa que est? desactivado
	
	// Orden de los datos
	SPCR &=~ (1<<DORD);                 	// Primero el MSB
	
	// Polaridad y fase
	SPCR &=~ (1<<CPOL);                 	// Clock inactivo en baja
	SPCR &=~ (1<<CPHA);                 	// Se trabaja en flancos de subida
	
	// Configurado como esclavo
	SPCR &=~ (1<<MSTR);
	
	// Activar SPI
	SPCR |= (1<<SPE);
	
	// Activar interrupcion SPI
	SPCR |= (1<<SPIE);
}

void SPI_tx(uint8_t data)
{
	/* Cargar dato al registro */
	SPDR = data;
	/* Esperar a que la transmisi?n se realice */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_rx()
{
	/* Esperar a la recepci?n del dato */
	while(!(SPSR & (1<<SPIF)));
	/* Retorna el dato recibido */
	return SPDR;
}