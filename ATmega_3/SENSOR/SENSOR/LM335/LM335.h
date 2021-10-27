/*
 * LM335.h
 *
 * Created: 27/10/2021 12:13:30
 *  Author: Alessandro
 */ 


#ifndef LM335_H_
#define LM335_H_

	#define F_CPU 16000000UL // 16 MHz clock speed

	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdbool.h>
	#include <math.h>
	
	#include "./../ADC/ADC.h"
	
	float LM335_Data();

#endif /* LM335_H_ */