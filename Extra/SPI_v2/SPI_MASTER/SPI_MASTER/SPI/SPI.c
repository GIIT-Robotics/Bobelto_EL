#include "SPI.h"

/*
 *
 *	Inicializacion del SPI como Maestro
 *
 */
void SPI_init()
{
	DDRB  = (1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(0<<DDB4)|(1<<DDB5);		//- PB1 es CS1/SS1 | PB2 es CS2/SS2 | PB3 es MOSI | PB4 es MISO | PB5 es SCK
	PORTB = (1<<PORTB1)|(1<<PORTB2);								//- En alta para que los esclavos no estén seleccionados
	SPCR  = (1<<MSTR)|(1<<SPR0);									//- Configurado como maestro | F_SPI = F_CPU/16
	
	SPCR  = 1<<SPE;													//- Enciende SPI
}

/*
 *
 *	Encendido de esclavo
 *
 */
void SPI_slaveON(uint8_t slave)
{
	switch (slave)
	{
		case 1:
		PORTB &=~ (1<<PORTB1);										//- Enciende comunicacion con esclavo 1
		break;
		
		case 2:
		PORTB &=~ (1<<PORTB2);										//- Enciende comunicacion con esclavo 2
		break;
	}
}

/*
 *
 *	Apagado de esclavo
 *
 */
void SPI_slaveOFF(uint8_t slave)
{
	switch (slave)
	{
		case 1:
		PORTB &=~ (1<<PORTB1);										//- Apaga comunicacion con esclavo 1
		break;
		
		case 2:
		PORTB &=~ (1<<PORTB2);										//- Apaga comunicacion con esclavo 2
		break;
	}
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