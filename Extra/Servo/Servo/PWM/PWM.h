/*
 * PWM.h
 *
 * Created: 3/10/2021 23:22:08
 *  Author: Usuario
 */ 


#ifndef PWM_H_
#define PWM_H_

	#ifndef F_CPU
		#define F_CPU 16000000UL // 16 MHz clock speed
	#endif

	#include <avr/io.h>

	void PWM_init(int freq);
	void PWM_on();
	void PWM_off();

	void PWM_setDutyA(int duty);
	void PWM_setDutyB(int duty);

#endif /* PWM_H_ */