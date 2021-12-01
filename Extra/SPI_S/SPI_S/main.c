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

uint8_t datoRecibido = 0x00;
uint8_t pinesB = 0x00;
uint8_t SPI_Rx = 0x00;
uint8_t cont = 0x00;
uint8_t flag = 0x00;

void SPI_init()
{
	DDRB &=~ (1<<DDB2)|(1<<DDB3)|(1<<DDB5); 	// PB3 es MOSI y PB5 es SCK
	DDRB |=  (1<<DDB4);                 		// PB4 es MISO
	
	PORTB |= (1<<PORTB2);               		// Configurado como pull-up
	
	SPCR &=~ (1<<DORD)|(1<<CPOL)|(1<<CPHA);
	
	SPCR &=~ (1<<MSTR);
	
	//SPCR |= (1<<SPIE);
	
	// Activar SPI
	SPCR |= (1<<SPE);
}

void SPI_tx(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_rx()
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

//ISR(SPI_STC_vect)
//{
	//SPI_Rx = SPDR;
	////_delay_us(10);
	//if (SPI_Rx == 0x01)
	//{
		//SPDR = 0x41;
	//}
	//else if(SPI_Rx == 0x02)
	//{
		//SPDR = 0x42;
	//}
	//else if(SPI_Rx == 0x03)
	//{
		//SPDR = 0x43;
	//}
	//else if(SPI_Rx == 0x04)
	//{
		//SPDR = 0x44;
	//}
//}

int main(void)
{
	cli();
	SPI_init();
	sei();
	
	_delay_ms(10);
	
    while (1) 
    {
		SPI_Rx = SPI_rx();
		
		if (SPI_Rx == 0x01)
		{
		SPDR = 0x41;
		}
		else if(SPI_Rx == 0x02)
		{
		SPDR = 0x42;
		}
		else if(SPI_Rx == 0x03)
		{
		SPDR = 0x43;
		}
		else if(SPI_Rx == 0x04)
		{
		SPDR = 0x44;
		}	
		
	    _delay_ms(10);
    }
}

