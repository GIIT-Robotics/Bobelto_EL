/*
 * DS18B20.c
 *
 * Created: 8/11/2021 00:19:56
 * Author : Usuario
 */ 
#define	F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "OW/OW.h"
#include "UART/UART.h"

/*#define SkipROM 0xCC
#define ConvertT 0x44
#define ReadScratchpad 0xBE

void temperature()
{
	cli();                            // No interrupts
	OW_work(7);
	if (OW_reset() != 0) {
		sei();
		UART_write_txt("ERROR");
		UART_write('\n');
	} else {
		OW_write(SkipROM);
		OW_write(ConvertT);
		while (OW_read() != 0xFF);
		OW_reset();
		OW_write(SkipROM);
		OW_write(ReadScratchpad);
		OW_readbytes(9);
		sei();                          // Interrupts
		if (OneWireCRC(9) == 0) {
			UART_write_data(DataWords[0]);
			UART_write('\n');
		} else
		{
			UART_write_txt("CRC");
			UART_write('\n');
		} 
	}
	sei();
	_delay_ms(1000);
}*/

int main(void)
{
	//-TIM0_init();
	UART_init();
	
	_delay_us(10);
	
    while (1) 
    {
		UART_write_txt("INICIA: ");
		UART_write('\n');
		//---------------------------------	
		UART_write_txt("PD2 en baja.");
		UART_write('\n');
		PORTD = 0<<2;		//- PORTD2 en baja
		//---------------------------------
		UART_write_txt("Enviamos RES y esperamos una PRES");
		UART_write('\n');
		DDRD = 1<<2;
		PORTD = 1<<2;	//- Envío de RESET
		_delay_us(480);
		PORTD = 0<<2;	//- Apaga RESET
		_delay_us(70);
		DDRD = 0<<2;	//- Espera un PRESENCE
		int pres = PIND & 0x02;
		_delay_us(410);
		if (!(PIND & (1<<2)))
		{
			DDRB = 1<<5;
			PORTB = 1<<5;
			UART_write_txt("Hay presencia.");
			UART_write('\n');
		} 
		else
		{
			PORTB = 0<<5;
			DDRB = 0<<5;
			UART_write_txt("No hay presencia.");
			UART_write('\n');
		}
		PORTB = 0<<5;
		DDRB = 0<<5;
		//---------------------------------
		_delay_ms(100);
		//temperature();		
    }
}

