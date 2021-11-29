/*
 * ADC.h
 *
 * Created: 23/07/2021 00:08:31
 *  Author: Usuario
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>

void ADC_init();
float ADC_GetData(int canal);

#endif /* ADC_H_ */