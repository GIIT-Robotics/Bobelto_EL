/*
 * BMP280.h
 *
 * Created: 20/10/2021 16:00:28
 *  Author: Alessandro
 */ 


#ifndef BPM280_H_
#define BPM280_H_
	
	#include "../TWI/TWI.h"
	
	#define BMP280_ADDRESS 0x76 // Address with end write bit
	//#define BMP280_ADDRESS 0x77 // Address with end write bit
	
	// #define BMP280_CHIP_ADDRESS 0x58
	#define BMP280_REGISTER_DIG_T1 0x88
	#define BMP280_REGISTER_DIG_T2 0x8A
	#define BMP280_REGISTER_DIG_T3 0x8C
	#define BMP280_REGISTER_DIG_P1 0x8E
	#define BMP280_REGISTER_DIG_P2 0x90
	#define BMP280_REGISTER_DIG_P3 0x92
	#define BMP280_REGISTER_DIG_P4 0x94
	#define BMP280_REGISTER_DIG_P5 0x96
	#define BMP280_REGISTER_DIG_P6 0x98
	#define BMP280_REGISTER_DIG_P7 0x9A
	#define BMP280_REGISTER_DIG_P8 0x9C
	#define BMP280_REGISTER_DIG_P9 0x9E
	#define BMP280_REGISTER_CHIPID 0xD0
	#define BMP280_REGISTER_VERSION 0xD1
	#define BMP280_REGISTER_SOFTRESET 0xE0
	#define BMP280_REGISTER_CAL26 0xE1 /**< R calibration = 0xE1-0xF0 */
	#define BMP280_REGISTER_STATUS 0xF3
	#define BMP280_REGISTER_CONTROL 0xF4
	#define BMP280_REGISTER_CONFIG 0xF5
	#define BMP280_REGISTER_PRESSUREDATA 0xF7
	#define BMP280_REGISTER_TEMPDATA 0xFA
	
	void bmp280_init(uint16_t Address);
	int32_t bmp280_read_Temp(void);
	int32_t bmp280_read_Prs(void);
	uint16_t bmp280_read_parameters(uint16_t reg);
	void Parameters(void);
	
#endif /* BPM280_H_ */