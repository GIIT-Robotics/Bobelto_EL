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
uint8_t SPI_Rx = 0x00;
uint8_t count = 0x00;
unsigned char UART_Rx = 0x00;

<<<<<<< HEAD
ISR(USART_RX_vect)
{
	UART_Rx = UART_read();
}

void SPI_init() //- Inicializa SPI como Master
{
	DDRB |= (1 << DDB3) | (1 << DDB5); // PB3 es MOSI y PB5 es SCK
	DDRB &= ~(1 << DDB4);			   // PB4 es MISO

	// Esclavos
	DDRB |= (1 << DDB1) | (1 << DDB2);		// PB2, PB1 serï¿½ SS
	PORTB |= (1 << PORTB1) | (1 << PORTB2); // En alta significa que estï¿½ desactivado

	// Orden de los datos
	SPCR &= ~(1 << DORD); // Primero el MSB

	// Polaridad y fase
	SPCR &= ~(1 << CPOL); // Clock inactivo en baja
	SPCR &= ~(1 << CPHA); // Se trabaja en flancos de subida

	// Preescalador (8) => 1 MHz
	SPCR |= (1 << SPR0);
	SPCR &= ~(1 << SPR1);
	SPSR &= ~(1 << SPI2X);

=======
void SPI_init()		//- Inicializa SPI como Master
{
	DDRB |=  (1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB5); 	// PB2, PB1 será SS. PB3 es MOSI y PB5 es SCK
	DDRB &=~ (1<<DDB4);                 				// PB4 es MISO
	
	// Esclavos
	PORTB |= (1<<PORTB1)|(1<<PORTB2);               // En alta significa que está desactivado
	
	// Orden de los datos
	SPCR &=~ (1<<DORD)|(1<<CPOL)|(1<<CPHA);                 	// Primero el MSB
	
	// Preescalador (16) => 1 kHz
	SPCR = (0<<SPR1) | (1<<SPR0);
	SPSR = (0<<SPI2X); 
	
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3
	// Configurado como maestro
	SPCR |= (1 << MSTR);

	// Activar SPI
	SPCR |= (1 << SPE);

	// Activar interrupcion SPI
	// SPCR |= (1<<SPIE);
}

void SPI_slaveON(uint8_t slave)
{
	switch (slave)
	{
	case 1:
		PORTB &= ~(1 << PORTB1);
		break;

	case 2:
		PORTB &= ~(1 << PORTB2);
		break;
	}
}

void SPI_slaveOFF(uint8_t slave)
{
	switch (slave)
	{
<<<<<<< HEAD
	case 1:
		PORTB &= ~(1 << PORTB1);
		break;

	case 2:
		PORTB &= ~(1 << PORTB2);
=======
		case 1:
			PORTB |= (1<<PORTB1);
		break;
		
		case 2:
			PORTB |= (1<<PORTB2);
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3
		break;
	}
}

void SPI_tx(uint8_t data)
{
	/* Cargar dato al registro */
	SPDR = data;
	/* Esperar a que la transmisiï¿½n se realice */
	while (!(SPSR & (1 << SPIF)))
		;
}

uint8_t SPI_rx()
{
	/* Esperar a la recepciï¿½n del dato */
	while (!(SPSR & (1 << SPIF)))
		;
	/* Retorna el dato recibido */
	return SPDR;
}

uint8_t SPI_trans(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

ISR(USART_RX_vect)
{
	UART_Rx = UART_read();
}

int main(void)
{
	uint8_t temp[4] = {0, 0, 0, 0};

	cli();
	SPI_init();
	UART_init();
	sei();

	_delay_ms(10);

	while (1)
	{
		float F = 0.0;
<<<<<<< HEAD
		// uint32_t Buff = 0;
		// int16_t I16 = 0;

		switch (UART_Rx)
		{
		case '0':
			SPI_slaveON(1);

			SPI_tx(0x01);

			_delay_us(1);

			temp[3] = temp[2];
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = SPI_rx();

			UART_write(temp[0]);
			UART_write(temp[1]);
			UART_write(temp[2]);
			UART_write(temp[3]);
			UART_write('\n');

			SPI_slaveOFF(1);

			if (temp[3] |= 0x00)
			{
				F = (int32_t)temp[0] << 24 | (int32_t)temp[1] << 16 | (int32_t)temp[2] << 8 | (int32_t)temp[3];
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;

				UART_write_txt("F es: ");
				UART_write_data(F);
				UART_write('\n');
			}

			break;

		case '1':
			SPI_slaveON(1);

			SPI_tx(0x01);

			temp[3] = temp[2];
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = SPI_rx();

			SPI_slaveOFF(1);

			if (temp[3] |= 0x00)
			{
				F = (int32_t)temp[3] << 24 | (int32_t)temp[2] << 16 | (int32_t)temp[0] << 8 | (int32_t)temp[1];
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;

				UART_write_txt("Presion interna: ");
				UART_write_data(F);
				UART_write('\n');

				_delay_ms(500);
			}

			break;

		case '2':
			SPI_slaveON(1);

			SPI_tx(0x02);

			temp[3] = temp[2];
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = SPI_rx();

			SPI_slaveOFF(1);

			if (temp[3] |= 0x00)
			{
				F = (int32_t)temp[3] << 24 | (int32_t)temp[2] << 16 | (int32_t)temp[0] << 8 | (int32_t)temp[1];
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;

				UART_write_txt("Presion externa: ");
				UART_write_data(F);
				UART_write('\n');

				_delay_ms(500);
			}

			break;

		case '3':
			SPI_slaveON(1);

			SPI_tx(0x03);

			temp[3] = temp[2];
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = SPI_rx();

			SPI_slaveOFF(1);

			if (temp[3] |= 0x00)
			{
				F = (int32_t)temp[3] << 24 | (int32_t)temp[2] << 16 | (int32_t)temp[0] << 8 | (int32_t)temp[1];
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;

				UART_write_txt("Temperatura interna: ");
				UART_write_data(F);
				UART_write('\n');

				_delay_ms(500);
			}

			break;

		case '4':
			SPI_slaveON(1);

			SPI_tx(0x02);

			temp[3] = temp[2];
			temp[2] = temp[1];
			temp[1] = temp[0];
			temp[0] = SPI_rx();

			SPI_slaveOFF(1);

			if (temp[3] |= 0x00)
			{
				F = (int32_t)temp[3] << 24 | (int32_t)temp[2] << 16 | (int32_t)temp[0] << 8 | (int32_t)temp[1];
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;

				UART_write_txt("Temperatura externa: ");
				UART_write_data(F);
				UART_write('\n');

				_delay_ms(500);
			}

			break;

		default:
			// UART_write_txt("Error.");
			// UART_write('\n');
			// UART_write('.');

			// UART_write_txt("Presion interna:");
			// UART_write('\n');
			//
			// SPI_slaveON(1);
			//
			// SPI_tx(0x01);
			//
			// temp[0] = SPI_rx();
			// temp[1] = SPI_rx();
			// temp[2] = SPI_rx();
			// temp[3] = SPI_rx();
			//
			// F = (int32_t)temp[0]<<24 | (int32_t)temp[1]<<16 | (int32_t)temp[2]<<8 | (int32_t)temp[3];
			//
			// UART_write_data(F);
			// UART_write('\n');
			//
			// SPI_slaveOFF(1);

			break;
		}

		_delay_ms(500);
	}
=======
		
		switch(UART_Rx)
		{
			case '0':
				SPI_slaveON(1);
				temp[0] = SPI_trans(0x01);
				SPI_slaveOFF(1);
				
				UART_write(temp[0]);
				
				UART_Rx = 0x00;
				
				break;
			
			case '1':
				SPI_slaveON(1);
				temp[1] = SPI_trans(0x02);
				SPI_slaveOFF(1);
				
				F = (uint8_t)temp[0] << 8 | (uint8_t)temp[1] << 0;
				
				UART_write(temp[1]);
				
				UART_write_data(F);
				UART_write('\n');
				
				UART_Rx = 0x00;
					
				break;
			
			
			case '2':
				
				break;
			
			case '3':
				
				break;
			
			case '4':
				
				break;	
			
			default:
				break;
		}
		
		_delay_ms(10);
    }
>>>>>>> a480e008b884e89538d8bf8699e927791b75daf3
}
