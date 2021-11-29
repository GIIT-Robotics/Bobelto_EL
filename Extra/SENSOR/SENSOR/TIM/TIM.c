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