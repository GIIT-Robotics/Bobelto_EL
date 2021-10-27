/*
 * TIM.c
 *
 * Created: 27/10/2021 17:08:06
 *  Author: Alessandro
 */ 
#include "TIM.h"

void TIM_init()
{
	PRR	&=~ (1<<PRTIM1);

	TCCR1B &=~ (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &=~ (1<<CS12);
	TCCR1B |= (1<<ICES1);

	TCNT1 = 0;
}