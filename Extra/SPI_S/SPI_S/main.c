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
<<<<<<< HEAD
uint8_t flag = 0;

void SPI_init()
{
	DDRB &=~  (1<<DDB3)|(1<<DDB5); 			// PB3 es MOSI y PB5 es SCK
	DDRB |= (1<<DDB4);                 		// PB4 es MISO
=======
uint8_t flag = 0x00;

void SPI_init()
{
	DDRB &=~ (1<<DDB2)|(1<<DDB3)|(1<<DDB5); 	// PB3 es MOSI y PB5 es SCK
	DDRB |=  (1<<DDB4);                 		// PB4 es MISO
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3
	
	PORTB |= (1<<PORTB2);               		// Configurado como pull-up
	
	SPCR &=~ (1<<DORD)|(1<<CPOL)|(1<<CPHA);
	
<<<<<<< HEAD
	// Polaridad y fase
	SPCR &=~ (1<<CPOL);                 	// Clock inactivo en baja
	SPCR &=~ (1<<CPHA);                 	// Se trabaja en flancos de subida
	
	// Configurado como esclavo
=======
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3
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

<<<<<<< HEAD
ISR(SPI_STC_vect)
{
	SPI_Rx = SPDR;
	flag = 1;
	
	UART_write_txt("Interrumpe");
	UART_write('\n');
	//if (SPI_Rx == 0x01)
	//{
		//if (cont == 0x00)
		//{
			//SPI_tx(0x48);
			//cont++;
		//}
		//else if (cont == 0x01)
		//{
			//SPI_tx(0x4F);
			//cont++;
		//}
		//else if (cont == 0x02)
		//{
			//SPI_tx(0x4C);
			//cont++;
		//}
		//else if (cont == 0x03)
		//{
			//SPI_tx(0x41);
			//cont = 0;
		//}
	//}
	//else if(SPI_Rx == 2)
	//{
		//SPI_tx(0xF1);
	//}
}
=======
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
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3

int main(void)
{
	cli();
	SPI_init();
	sei();
	
	_delay_ms(10);
	
    while (1) 
<<<<<<< HEAD
    {	
		if (flag == 1)
		{
			UART_write_txt("Entra a flag");
			UART_write('\n');
			if (SPI_Rx == 0x01)
			{
				UART_write_txt("Entra a 0x01");
				UART_write('\n');
				if (cont == 0x00)
				{
					UART_write_txt("Envia: ");
					UART_write(0x48);
					UART_write('\n');
					SPI_tx(0x48);
					cont++;
				}
				else if (cont == 0x01)
				{
					SPI_tx(0x4F);
					cont++;
				}
				else if (cont == 0x02)
				{
					SPI_tx(0x4C);
					cont++;
				}
				else if (cont == 0x03)
				{
					SPI_tx(0x41);
					cont = 0;
				}
			}
			else if(SPI_Rx == 2)
			{
				SPI_tx(0xF1);
			}
			flag = 0;
=======
    {
		SPI_Rx = SPI_rx();
		
		if (SPI_Rx == 0x01)
		{
		SPDR = 0x41;
		}
		else if(SPI_Rx == 0x02)
		{
		SPDR = 0x42;
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3
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

