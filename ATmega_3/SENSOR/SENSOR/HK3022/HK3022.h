/*
 * HK3022.h
 *
 * Created: 27/10/2021 16:02:43
 *  Author: Alessandro
 */ 


#ifndef HK3022_H_
#define HK3022_H_

	#define F_CPU 16000000UL // 16 MHz clock speed

	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdbool.h>
	#include <math.h>

	#include "./../ADC/ADC.h"

	float HK3022_Data();


#endif /* HK3022_H_ */