#include "SPI.h"

void SPI_init()		//- Inicializa SPI como Master
{
	DDRB |=  (1<<DDB3)|(1<<DDB5); 	// PB3 es MOSI y PB5 es SCK
	DDRB &=~ (1<<DDB4);                 	// PB4 es MISO
	
	// Esclavos
	DDRB |= (1<<DDB1)|(1<<DDB2);                  	// PB2, PB1 ser? SS
	PORTB |= (1<<PORTB1)|(1<<PORTB2);               // En alta significa que est? desactivado
	
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

uint8_t SPI_trans(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}