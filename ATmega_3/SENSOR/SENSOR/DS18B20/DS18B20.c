/*
 * DS18B20.c
 *
 * Created: 3/11/2021 20:09:52
 *  Author: Alessandro
 */ 
#include "DS18B20.h"

void DS18B20_Data()
{
	float adcV = ADC_GetData(2)*5.0f/1024.0f;
	float pres = (adcV*100)/4.5;
	
	return pres;
}