/*
 * USONIC.c
 *
 * Created: 6/10/2021 12:28:43
 * Author : Alessandro
 */ 
#define	F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART/UART.h"

uint16_t dist = 0;

ISR(PCINT2_vect)
{
	if(PIND & (1<<PIND2))
	{
		TCNT1 = 0;
	} else
	{
		uint16_t t = TCNT1;
		cli();
		dist = t * 0.03432 / 4;
		sei();
	}
}

int main(void)
{
	cli();
	DDRD |= (1<<DDD3);	//- Solo PD3 será output como TRIGGER
	DDRB |= (1<<DDB5);
	
	PORTD &=~ (1<<PORTD3);
	
	PRR &=~ (1<<PRTIM1);

	TCCR1B &=~ (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &=~ (1<<CS12);
	TCCR1B |= (1<<ICES1);

	TCNT1 = 0;
	
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT18);
	
	UART_init();
	
	sei();
		
    while (1) 
    {
		PORTD |= (1<<PORTD3);
		_delay_us(2);
		PORTD &=~ (1<<PORTD3);
		_delay_ms(60);
		
		UART_write_data(dist);
		UART_write_txt(" cm");
		UART_write('\n');
    }
}



