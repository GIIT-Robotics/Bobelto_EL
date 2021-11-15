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
#include "TWI/TWI.h"
#include "BMP280/BMP280.h"

int main(void)
{
	//-DDRB = 1<<DDB5;
	//-PORTB = 0<<PORTB5;
	
	cli();
	UART_write_txt("INIT UART");
	UART_write('\n');
	
	UART_init();
	
	UART_write_txt("INIT ADC");
	UART_write('\n');
	
	ADC_init();
	
	UART_write_txt("INIT TWI");
	UART_write('\n');
	
	TWI_init();
	
	UART_write_txt("INIT BMP280");
	UART_write('\n');
	
	BMP280_init();
	
	UART_write_txt("10ms delay");
	UART_write('\n');
	_delay_ms(10);
	sei();
	
    while (1) 
    {
		/*
		float T_int = LM335_Data();
		float P_ext = HK3022_Data();
		
		
		UART_write_data(T_int);
		UART_write_txt(" grad C");
		UART_write('\n');
		UART_write_data(P_ext);
		UART_write_txt(" bar");
		UART_write('\n');
		*/	
		float p_int = BMP280_pres();
		
		UART_write('\n');
		UART_write_txt("Presion interna: ");
		UART_write_data(p_int);
		UART_write('\n');
	
		float t_int = BMP280_temp();
		
		UART_write('\n');
		UART_write_txt("Temperatura 1: ");
		UART_write_data(t_int);
		UART_write('\n');
		
		_delay_ms(500);
    }
}
