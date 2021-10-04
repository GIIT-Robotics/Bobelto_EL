/*
 * Servo.c
 *
 * Created: 3/10/2021 23:12:10
 * Author : Usuario
 */ 
#ifndef F_CPU
	#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "PWM/PWM.h"

int main(void)
{
	cli();
	PWM_init(100);	// Encendemos el PWM con una freq de 50 Hz (20 ms)
	sei();
	
	
	
    while (1) 
    {
		PWM_setDutyA(15);
		PWM_on();
		
		_delay_ms(1000);
		
		PWM_setDutyA(10);
		PWM_on();
		
		_delay_ms(1000);
		
		PWM_setDutyA(15);
		PWM_on();
		
		_delay_ms(1000);
		
		PWM_setDutyA(20);
		PWM_on();
		
		_delay_ms(1000);
    }
}

