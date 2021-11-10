/*
 * TIM.c
 *
 * Created: 20/10/2021 16:25:57
 *  Author: Alessandro
 */ 

#include "TIM.h"

void timer_Init()
{
	// Configure Timer 1
	PRR &=~ (1<<PRTIM1);
	TCCR1A = 0x00; // Normal mode, OC1A/OC1B disconnected
	TCCR1B = (0<<WGM12)|(1<<CS12)|(1<<CS10); // CTC and prescaler 1024
	
/*
	TCCR1B &=~ (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &=~ (1<<CS12);*/
	TCCR1B |= (1<<ICES1);

	TCNT1 = 0;	
}

float Read_TIMER1()
{
	uint16_t i;
	/* Read TCNT0 into i */
	i = TCNT1;
	TCNT1 = 0;
	//PORTB ^= (1<<PORTB5);
	return i*0.000064;
}