/*
 * LM335.c
 *
 * Created: 27/10/2021 12:13:48
 *  Author: Alessandro
 */ 
#include "LM335.h"

float LM335_Data()
{	
	float t_K	= ADC_GetData(1) * 0.004882812 * 100;
	float t_C	= t_K - 273.15;
	
	return t_C;
}
