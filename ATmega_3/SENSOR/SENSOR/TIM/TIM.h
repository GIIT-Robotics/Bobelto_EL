/*
 * TIM.h
 *
 * Created: 27/10/2021 17:07:55
 *  Author: Alessandro
 */ 


#ifndef TIM_H_
#define TIM_H_

	#define F_CPU 16000000UL // 16 MHz clock speed
	
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdbool.h>

	void TIM_init();

#endif /* TIM_H_ */