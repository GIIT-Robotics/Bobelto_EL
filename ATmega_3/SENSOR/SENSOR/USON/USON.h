/*
 * USON.h
 *
 * Created: 27/10/2021 16:53:29
 *  Author: Alessandro
 */ 


#ifndef USON_H_
#define USON_H_

	#define F_CPU 16000000UL // 16 MHz clock speed

	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdbool.h>

	void USON_init();
	float USON_Data();


#endif /* USON_H_ */