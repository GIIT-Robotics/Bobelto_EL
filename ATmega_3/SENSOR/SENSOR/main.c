/*
 * SENSOR.c
 *
 * Created: 27/10/2021 10:56:36
 * Author : Alessandro
 */ 
#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>

#include "ADC/ADC.h"
#include "LM335/LM335.h"
#include "UART/UART.h"
#include "HK3022/HK3022.h"

int main(void)
{
	cli();
	UART_init();
	ADC_init();
	_delay_ms(10);
	sei();
	
    while (1) 
    {
		float T_int = LM335_Data();
		float P_ext = HK3022_Data();
		
		
		UART_write_data(T_int);
		UART_write_txt(" grad C");
		UART_write('\n');
		UART_write_data(P_ext);
		UART_write_txt(" bar");
		UART_write('\n');
		
		_delay_ms(500);
    }
}
