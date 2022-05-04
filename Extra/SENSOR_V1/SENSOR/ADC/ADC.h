/*
 * ADC.h
 *
 * Created: 27/10/2021 11:15:14
 *  Author: Alessandro
 */ 


#ifndef ADC_H_
#define ADC_H_
	
	#define F_CPU 16000000UL // 16 MHz clock speed
	
	#include <avr/io.h>
	#include <util/delay.h>
	
	void ADC_init();
	float ADC_GetData(int canal);

#endif /* ADC_H_ */