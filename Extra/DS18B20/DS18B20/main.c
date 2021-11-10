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

#define SkipROM 0xCC
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
	_delay_ms(1000);
}

int main(void)
{
	TIM0_init();
    while (1) 
    {
		
		UART_write_txt("ERROR");
		UART_write('\n');
		temperature();		
    }
}

