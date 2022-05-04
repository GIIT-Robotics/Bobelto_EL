#include "SPI.h"

/************************************************************************/
/* Inicializacion del SPI como esclavo                                  */
/************************************************************************/
void SPI_init()
{
	DDRB &=~ (1 << DDB2) | ( 1 << DDB3) | (1 << DDB5);		//- PB3 es MOSI y PB5 es SCK
	DDRB |=  (1 << DDB4);                 					//- PB4 es MISO
	
	SPCR &=~ (1<<DORD);										// Orden de bits

	SPCR &=~ (1<<CPOL);                 					// Clock inactivo en baja
	SPCR &=~ (1<<CPHA);                 					// Se trabaja en flancos de subida
	
	SPCR &=~ (1<<MSTR);										// Configurado como esclavo
	SPCR |=  (1<<SPE);										//- Enciende SPI
	
	SPCR |= (1<<SPIE);										// Activa interrupcion
}

/*
 *
 *	SPI Transmission
 *
 */
void SPI_tx(uint8_t data)
{
	SPDR = data;													//- Sube el Byte al registro del bus
	while(!(SPSR & (1<<SPIF)));										//- Espera a que el esclavo reciba el dato
}

/*
 *
 *	SPI Reception
 *
 */
uint8_t SPI_rx()
{
	while(!(SPSR & (1<<SPIF)));										//- Espera a que haya algun Byte en el bus
	return SPDR;													//- Retorna el Byte recivido
}

/*
 *
 *	SPI Transciever
 *
 */
uint8_t SPI_trx(uint8_t data)
{
	SPDR = data;													//- Sube el Byte al registro del bus
	while(!(SPSR & (1<<SPIF)));										//- Espera a que haya algun Byte en el bus
	return SPDR;													//- Retorna el Byte recivido
}