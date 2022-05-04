/*
 * HK3022.c
 *
 * Created: 27/10/2021 16:02:57
 *  Author: Alessandro
 */ 
#include "HK3022.h"

uint16_t HK3022_Data()
{
	//float adcV = ADC_GetData(0)*5.0f/1024.0f;	//- Lo pasa a voltios
	//float pres = (adcV*100)/4.5;				//- lo pasa a presión hPa
	//
	//return pres;
	return (uint16_t)ADC_GetData(0);
}