/*
 * ADC.c
 *
 * Created: 27/10/2021 11:15:01
 *  Author: Alessandro
 */ 
#include "ADC.h"

void ADC_init()
{
	//- Output right
	ADMUX	&=~	(1<<ADLAR);
	
	//- Voltage Reference
	ADMUX	|=	(1<<REFS0);
	ADMUX	&=~ (1<<REFS1);
	
	//- Freq divisor
	ADCSRA	|=	(1<<ADPS0);
	ADCSRA	|=	(1<<ADPS1);
	ADCSRA	|=	(1<<ADPS2);
	
	//- Port selector
	DDRC = (0<<DDC0)|(0<<DDC1)|(0<<DDC2)|(0<<DDC3)|(0<<DDC4)|(0<<DDC5);
}

float ADC_GetData(int canal) 
{
	//- Selección del canal de ADC
	ADMUX	&=~	0x0F;
	ADMUX	|=	canal;
	
	//- Encendemos en ADC
	ADCSRA	|=	(1<<ADEN);
	_delay_us(10);
	
	//- Envio de muestreo
	ADCSRA	|=	(1<<ADSC);
	
	//- Espera a que finalice la toma de datos
	while( !(ADCSRA & (1<<ADIF)) );
	ADCSRA	|=	(1<<ADIF);
	
	//- Se apaga el ADC
	ADCSRA	&=~	(1<<ADEN);
	
	//- Se devuelve el valor medido
	return ADC;
}