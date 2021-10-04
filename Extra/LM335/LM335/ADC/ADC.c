/*
 * ADC.c
 *
 * Created: 23/07/2021 00:08:25
 *  Author: Alessandro
 */ 

#include "ADC.h"

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