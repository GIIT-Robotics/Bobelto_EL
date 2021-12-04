/*
 * LM335.c
 *
 * Created: 27/10/2021 12:13:48
 *  Author: Alessandro
 */ 
#include "LM335.h"

int16_t LM335_Data()
{	
	//float t_K	= ADC_GetData(1) * 0.004882812 * 100;	//- Transforma la medición del ADC en grados Kelvin
	//float t_C	= t_K - 273.15;							//- Transforma Kelvin a Celsius
	//
	//return t_C;
	return (int16_t)ADC_GetData(1);
}
