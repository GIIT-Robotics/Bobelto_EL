/*
 * HK3022.c
 *
 * Created: 27/10/2021 16:02:57
 *  Author: Alessandro
 */ 
#include "HK3022.h"

float HK3022_Data()
{
	float adcV = ADC_GetData(0)*5.0f/1024.0f;
	float pres = (adcV*100)/4.5;
	
	return pres;
}