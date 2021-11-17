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
	
	//- Conf de Int por Echo
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT18);
}

/*
float USON_Data()
{
	
	
}*/