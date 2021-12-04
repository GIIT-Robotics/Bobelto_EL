#include "SPI.h"

/************************************************************************/
/*  Inicializacion del SPI como Maestro                                 */
/************************************************************************/
void SPI_init()
{
	DDRB |=  (1 << DDB2) | (1 << DDB3) | (1 << DDB5);		//- PB2 es SS, PB3 es MOSI y PB5 es SCK
	DDRB &=~ (1 << DDB4);									//- PB4 es MISO
	
	PORTB |= (1 << PORTB2);									//- Mantenemos el SS en alta

	SPCR |=  (1 << MSTR);									//- Configurado como maestro
	SPCR &=~ (1 << DORD);									//- Orden de los datos -> Primero el MSB
	SPCR &=~ (1 << CPOL);									//- Clock inactivo en baja
	SPCR &=~ (1 << CPHA);									//- Se trabaja en flancos de subida

	// Preescalador (16) => 1 MHz
	SPCR |=  (1 << SPR0);
	SPCR &=~ (1 << SPR1);
	SPSR &=~ (1 << SPI2X);

	SPCR |=  (1 << SPE);									//- Activar SPI
}

/************************************************************************/
/*  Encendido de esclavo                                                */
/************************************************************************/
void SPI_slaveON(uint8_t slave)
{
	switch (slave)
	{
		case 1:
		PORTB &=~ (1<<PORTB2);								//- Enciende comunicacion con esclavo 1
		break;
		
		case 2:
		PORTB &=~ (1<<PORTB2);								//- Enciende comunicacion con esclavo 2
		break;
	}
}

/************************************************************************/
/* Apagado de esclavo                                                   */
/************************************************************************/
void SPI_slaveOFF(uint8_t slave)
{
	switch (slave)
	{
		case 1:
		PORTB &=~ (1<<PORTB2);								//- Apaga comunicacion con esclavo 1
		break;
		
		case 2:
		PORTB &=~ (1<<PORTB2);								//- Apaga comunicacion con esclavo 2
		break;
	}
}

/************************************************************************/
/* SPI Transmission                                                     */
/************************************************************************/
void SPI_tx(uint8_t data)
{
	SPDR = data;											//- Sube el Byte al registro del bus
	while(!(SPSR & (1<<SPIF)));								//- Espera a que el esclavo reciba el dato						
}

/************************************************************************/
/* SPI Reception                                                        */
/************************************************************************/
uint8_t SPI_rx()
{
	while(!(SPSR & (1<<SPIF)));								//- Espera a que haya algun Byte en el bus
	return SPDR;											//- Retorna el Byte recivido
}

/************************************************************************/
/* SPI Transciever                                                      */
/************************************************************************/
uint8_t SPI_trx(uint8_t data)
{
	SPDR = data;											//- Sube el Byte al registro del bus
	while(!(SPSR & (1<<SPIF)));								//- Espera a que haya algun Byte en el bus
	return SPDR;											//- Retorna el Byte recivido
}