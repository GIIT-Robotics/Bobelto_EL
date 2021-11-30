/*
 * SPI.c
 *
 * Created: 29/11/2021 11:17:37
 *  Author: Alessandro
 */
 #include "SPI.h"

void SPI_init()		//- Inicializa SPI como Master
{
	DDRB &=~  (1<<DDB3)|(1<<DDB5); 	// PB3 es MOSI y PB5 es SCK
	DDRB |=   (1<<DDB4);                 	// PB4 es MISO
	
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
	
	//Activar interrupcion SPI
	SPCR |= (1<<SPIE);
}

void SPI_tx(uint8_t data)
{
	/* Cargar dato al registro */
	SPDR = data;
	/* Esperar a que la transmisión se realice */
	while(!(SPSR & (1<<SPIF)));
}

void SPI_tx_16bit(uint16_t data)
{
	uint8_t bytes[sizeof(data)] = 
	{
		((uint16_t)data >> 0) & 0xFF,
		((uint16_t)data >> 8) & 0xFF 
	};
	
	SPI_tx(bytes[0]);
	SPI_tx(bytes[1]);
}

void SPI_tx_32bit(uint32_t data)
{
	uint8_t bytes[sizeof(data)] =
	{
		((uint32_t)data >>  0) & 0xFF,
		((uint32_t)data >>  8) & 0xFF,
		((uint32_t)data >> 16) & 0xFF,
		((uint32_t)data >> 24) & 0xFF
	};
	
	SPI_tx(bytes[0]);
	SPI_tx(bytes[1]);
	SPI_tx(bytes[2]);
	SPI_tx(bytes[3]);
}

