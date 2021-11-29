#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include "UART/UART.h"

void ADC_init()
{
	// Output right
	ADMUX &=~ (1<<ADLAR);
	
	// Voltage Reference
	ADMUX |= (1<<REFS0);
	ADMUX &=~ (1<<REFS1);
	
	// Freq divisor
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
}

float ADC_GetData(int canal)
{
	// Selección del canal de l ADC //
	ADMUX &=~  0x0F;
	ADMUX |=  canal;
	
	// Encendemos en ADC
	ADCSRA |= (1<<ADEN);
	_delay_us(10);	// Esperamos a que caliente

	// Mandamos el muestreo
	ADCSRA |= (1<<ADSC);

	// Esperamos a que muestree, leyendo el flag
	while( !(ADCSRA & (1<<ADIF)) );
	ADCSRA |= (1<<ADIF);	// Reiniciamos el flag

	// Apagamos el ADC
	ADCSRA &=~ (1<<ADEN);

	return ADC;
}

int main(void)
{
	cli();
	
	float val = 0;
	int a;
	
    DDRB = 1<<DDB0;
	
	ADC_init();
	UART_init();
	_delay_ms(10);
	
	sei();
	
	for (int i=0; i<25; i++)
	{
		//- a = 400 -> 0°
		a = 400;
		PORTB = 1<<PORTB0;
		_delay_us(a);
		PORTB = 0<<PORTB0;
		
		_delay_us(20000-a);
	}
	
    while (1) 
    {
		
		val = ADC_GetData(0);
		UART_write_txt("WA: ");
		UART_write_data((float)val);
		UART_write('\n');
		
		//- NO SE PUEDE USAR EL DELAY CON VARIABLES
		
		//- max 1400 - 2024
		//- min 400 - x
		a = (int)val * 1400 / 1024;
		
		for (int i=0; i<10; i++)
		{
			PORTB = 1<<PORTB0;
			_delay_us(a);
			PORTB = 0<<PORTB0;
			
			_delay_us(20000-a);
		}
		
		/*
		
		for (int i=0; i<10; i++)
		{
			//- a = 400 -> 0°
			int a = 400;
			PORTB = 1<<PORTB0;
			_delay_us(a);
			PORTB = 0<<PORTB0;
			
			_delay_us(20000-a);
		}
		
		for (int i=0; i<25; i++)
		{
			//- a = 1400 -> 90°
			int a = 1400;
			PORTB = 1<<PORTB0;
			_delay_us(a);
			PORTB = 0<<PORTB0;
			
			_delay_us(20000-a);
		}
		for (int i=0; i<25; i++)
		{
			//- a = 400 -> 180°
			int a = 2400;
			PORTB = 1<<PORTB0;
			_delay_us(a);
			PORTB = 0<<PORTB0;
			
			_delay_us(20000-a);
		}
		*/
    }
}

