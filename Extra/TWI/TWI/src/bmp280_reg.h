/*
 * bmp280_reg.h
 *
 * Created: 11/10/2021 3:47:29 p. m.
 *  Author: Rebeca
 */ 


#ifndef BMP280_REG_H_
#define BMP280_REG_H_

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

// CONFIGURACIONES
/* 
sensor_sampling
	No over-sampling. 
		SAMPLING_NONE = 0x00,
	1x over-sampling. 
		SAMPLING_X1 = 0x01,
	2x over-sampling. 
		SAMPLING_X2 = 0x02,      //////TEMPERATURA
	4x over-sampling. 
		SAMPLING_X4 = 0x03,
	8x over-sampling. 
		SAMPLING_X8 = 0x04,
	16x over-sampling. 
		SAMPLING_X16 = 0x05      //////PRESION

sensor_mode
	Sleep mode. 
		MODE_SLEEP = 0x00,
	Forced mode. 
		MODE_FORCED = 0x01,
	Normal mode. 
		MODE_NORMAL = 0x03,     /////AQUI
	Software reset. 
		MODE_SOFT_RESET_CODE = 0xB6

sensor_filter
	No filtering. 
		FILTER_OFF = 0x00,
	2x filtering. 
		FILTER_X2 = 0x01,
	4x filtering. 
		FILTER_X4 = 0x02,
	8x filtering. 
		FILTER_X8 = 0x03,
	16x filtering. 
		FILTER_X16 = 0x04     /////AQUI

standby_duration
	1 ms standby. 
		STANDBY_MS_1 = 0x00,     /////AQUI
	62.5 ms standby. 
		STANDBY_MS_63 = 0x01,
	125 ms standby. 
		STANDBY_MS_125 = 0x02,
	250 ms standby. 
		STANDBY_MS_250 = 0x03,
	500 ms standby. 
		STANDBY_MS_500 = 0x04,
	1000 ms standby. 
		STANDBY_MS_1000 = 0x05,
	2000 ms standby. 
		STANDBY_MS_2000 = 0x06,
	4000 ms standby. 
		STANDBY_MS_4000 = 0x07
*/
#endif /* BMP280_REG_H_ */