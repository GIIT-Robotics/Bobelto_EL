/*
 * LM335.c
 *
 * Created: 29/09/2021 17:14:57
 * Author : Alessandro
 */ 

#ifndef F_CPU
	#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ADC/ADC.h"

int main(void)
{
    cli();
    
    DDRC |= (1<<DDC0);
    DDRB |= (1<<DDB5);
    
    ADC_init();
    
    _delay_ms(10);
    
    sei();
			
	while (1) 
    {
	    float adcV = ADC_GetData(0)*5.0f/1024.0f;
	    float t_K = adcV * 0.004882812 * 100;
		float t_C = t_K - 2.5 - 273.15;
	    
		if (t_C < 20.0)
		{
			PORTB |= (1<<PORTB5);
		}
			
    }
}

