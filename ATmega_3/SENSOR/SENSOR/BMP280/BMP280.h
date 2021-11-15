/*
 * BMP280.h
 *
 * Created: 14/11/2021 14:00:01
 *  Author: Usuario
 */ 


#ifndef BMP280_H_
#define BMP280_H_

	#include "../TWI/TWI.h"
	#define BMP280_ADDRESS 0x76		//- BMP280 Address

	void BMP280_init();
	uint16_t BMP280_params(uint8_t reg);
	int32_t BMP280_t_fine();
	float BMP280_temp();
	float BMP280_pres();


#endif /* BMP280_H_ */