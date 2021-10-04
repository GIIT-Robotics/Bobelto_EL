/*
 * ULTRASOUND.c
 *
 * Created: 4/10/2021 11:54:48
 * Author : Alessandro
 */ 

#ifndef F_CPU
	#define F_CPU 1000000UL // 16 MHz clock speed
#endif

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))

int dist = 0;

void ultrasonic_init()
{
	DDRD = 0x04;			//- Usaremos PD2 como receptor (echo) y PD3 como emisor (trigger)
	PORTD |= (1<<PORTD2);	//- PD2 estará como pull up
	PORTD &=~ (1<<PORTD3);	//- PD3 iniciará en low
	
	PRR &=~ (1<<PRTIM1);	//- Activa TIM1
	TCNT1 = 0;				//- Contador en 0
	TCCR1B |= (1<<CS10);	//- Preescalador nulo
	TCCR1B &=~ (1<<CS11);	//- Siendo CLK 1 MHz => 1 us
	TCCR1B &=~ (1<<CS12);
	TCCR1B |= (1<<ICES1);	//- Primera captura es por un rising edge
	
	PCICR |= (1<<PCIE2);	//- Habilitamos interrupciones para los PCINT[23:16] (PD2 es PCINT18)
	PCMSK2 |= (1<<PCINT18);	//- Habilitamos interrupción por el PCINT18 (PD2)
}

int main(void)
{
	DDRB |= (1<<DDB5);
	
	cli();
	ultrasonic_init();
	sei();
	
    while (1) 
    {
		_delay_ms(60);
		
		PORTD |= (1<<PORTD3);	//- Enviamos un trigger
		_delay_us(10);			//- Por 10 us
		PORTD &=~ (1<<PORTD3);	//- Bajamos la señal
		
		if(dist > 8)
		{
			PORTB |= (1<<PORTB5);
		} else 
		{
			PORTB &=~ (1<<PORTB5);
		}
    }
}

ISR(PCINT2_vect)
{
	if(PIND & (1 << PIND2))
	{
		TCNT1 = 0;
	} else {
		uint16_t t = TCNT1;
		//uint8_t oldSREG = SREG;
		cli();
		dist = t/58;
		sei();
		
		//SREG = oldSREG;
	}
}

