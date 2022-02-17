/*
 * USON.c
 *
 * Created: 27/10/2021 16:53:08
 *  Author: Alessandro
 */ 
#include "USON.h"

void USON_init()
{
	DDRD |=  (1<<DDD3);		//- Trigger
	DDRD &=~ (1<<DDD2);		//- Echo
	
	PORTD &=~ (1<<PORTD3);
	
	TCCR1B &=~ (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &=~ (1<<CS12);
	TCCR1B |= (1<<ICES1);

	TCNT1 = 0;
	
	//- Conf de Int por Echo
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT18);
}

void USON_Data()
{
	PORTD |= (1<<PORTD3);
	_delay_us(2);
	PORTD &=~ (1<<PORTD3);
	_delay_ms(60);
}