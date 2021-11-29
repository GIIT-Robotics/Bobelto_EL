/*
 * Servo.c
 *
 * Created: 3/10/2021 23:12:10
 * Author : Usuario
 */ 
#define F_CPU 16000000UL // 16 MHz clock speed

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "PWM/PWM.h"
#include "ADC/ADC.h"
#include "UART/UART.h"

int main(void)
{
	cli();
	PWM_init(200);	// Encendemos el PWM con una freq de 200 Hz (5 ms)
	ADC_init();
	UART_init();
	sei();
	
	float val = 0;
	
	PWM_setDutyA(30);
	PWM_on();
	_delay_ms(100);
	
	//PWM_setDutyA(15);
	//PWM_on();
	
    while (1) 
    {
		val = ADC_GetData(0);
		int a = 10 + (val*(50-10)/(1024-0));
		
		UART_write_txt("PWM: ");
		UART_write_data(a);
		UART_write('\n');
	
		PWM_setDutyA(a);
		PWM_on();
		_delay_ms(1);
		
	    /*
		for(int i=10;i<20;i++)
		{
			PWM_setDutyA(i);
			PWM_on();
			_delay_ms(100);
		}
		
		for(int i=20;i>10;i--)
		{
			PWM_setDutyA(i);
			PWM_on();
			_delay_ms(100);
		}
		PWM_setDutyA(10);
		PWM_on();
		
		_delay_ms(1000);
		
		PWM_setDutyA(15);
		PWM_on();
		
		_delay_ms(1000);
		
		PWM_setDutyA(20);
		PWM_on();
		
		_delay_ms(1000);*/
    }
}

