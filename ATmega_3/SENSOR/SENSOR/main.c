/*
 * SENSOR.c
 *
 * Created: 27/10/2021 10:56:36
 * Author : Alessandro
 */ 
#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "ADC/ADC.h"
#include "LM335/LM335.h"
#include "SPI/SPI.h"
#include "HK3022/HK3022.h"
#include "TWI/TWI.h"
#include "BMP280/BMP280.h"
#include "MPU6050/MPU6050.h"
#include "USON/USON.h"

uint8_t SPI_Rx = 0;
bool flag = false;

int16_t T_ext = 0;		//- Temperatura externa
int16_t P_ext = 0;		//- Presion externa
int16_t P_int = 0;		//- Presion interna
int16_t T_int = 0;		//- Temperatura interna
int16_t a_x = 0;		//- Acelerometro en X
int16_t a_y = 0;		//- Acelerometro en Y
int16_t a_z = 0;		//- Acelerometro en Z
int16_t g_x = 0;		//- Giroscopio en X
int16_t g_y = 0;		//- Giroscopio en Y
int16_t g_z = 0;		//- Giroscopio en Z
uint16_t dist = 0;		//- Distancia Ultrasonido

uint8_t bit_crop(uint16_t data, uint8_t byte)
{	
	uint8_t bytes[2] =
	{
		((uint16_t)data >> 0) & 0xFF,
		((uint16_t)data >> 8) & 0xFF
	};
	
	if (byte == 0x00) return bytes[0];			//- LSB
	else if (byte == 0x01) return bytes[1];		//- MSB
	else return 0;
}

ISR(SPI_STC_vect)
{
	SPI_Rx = SPDR;
	
	switch(SPI_Rx)
	{
		case 0x11:
			SPDR = bit_crop(P_int,1);
			break;
			
		case 0x12:
			SPDR = bit_crop(P_int,0);
			break;
			
		case 0x21:
			SPDR = bit_crop(P_ext,1);
			break;
			
		case 0x22:
			SPDR = bit_crop(P_ext,0);
			break;
			
		case 0x31:
			SPDR = bit_crop(T_int,1);
			break;
			
		case 0x32:
			SPDR = bit_crop(T_int,0);
			break;
			
		case 0x41:
			SPDR = bit_crop(T_ext,1);
			break;
			
		case 0x42:
			SPDR = bit_crop(T_ext,0);
			break;
			
		case 0x51:
			SPDR = bit_crop(g_x,1);
			break;
			
		case 0x52:
			SPDR = bit_crop(g_x,0);
			break;
			
		case 0x61:
			SPDR = bit_crop(g_y,1);
			break;
			
		case 0x62:
			SPDR = bit_crop(g_y,0);
			break;
			
		case 0x71:
			SPDR = bit_crop(g_z,1);
			break;
			
		case 0x72:
			SPDR = bit_crop(g_z,0);
			break;
			
		case 0x81:
			SPDR = bit_crop(a_x,1);
			break;
			
		case 0x82:
			SPDR = bit_crop(a_x,0);
			break;
			
		case 0x91:
			SPDR = bit_crop(a_y,1);
			break;
			
		case 0x92:
			SPDR = bit_crop(a_y,0);
			break;
			
		case 0xA1:
			SPDR = bit_crop(a_z,1);
			break;
			
		case 0xA2:
			SPDR = bit_crop(a_z,0);
			break;
			
		case 0xB1:
			SPDR = bit_crop(dist,1);
			break;
			
		case 0xB2:
			SPDR = bit_crop(dist,0);
			break;
		
		default:
			break;
	}	
	
	SPI_Rx = 0x00;
}

ISR(PCINT2_vect)
{
	if(PIND & (1<<PIND2))
	{
		TCNT1 = 0;
	} else
	{
		uint16_t t = TCNT1;
		cli();
		dist = t * 0.03432 / 4;
		sei();
	}
}

int main(void)
{
	cli();

	SPI_init();
	//UART_init();
	ADC_init();
	TWI_init();
	BMP280_init();
	MPU6050_init();
	USON_init();
	
	_delay_ms(10);
	
	sei();
	
    while (1) 
    {
	    T_ext = (int16_t)LM335_Data();				//- Temperatura externa
	    P_ext = (int16_t)HK3022_Data();				//- Presion externa
	    P_int = (int16_t)BMP280_pres();				//- Presion interna
	    T_int = (int16_t)BMP280_temp();				//- Temperatura interna
	    a_x   = (int16_t)MPU6050_read_acce(1);		//- Acelerometro en X
	    a_y   = (int16_t)MPU6050_read_acce(2);		//- Acelerometro en Y
	    a_z   = (int16_t)MPU6050_read_acce(3);		//- Acelerometro en Z
	    g_x   = (int16_t)MPU6050_read_gyro(1);		//- Giroscopio en X
	    g_y   = (int16_t)MPU6050_read_gyro(2);		//- Giroscopio en Y
	    g_z   = (int16_t)MPU6050_read_gyro(3);		//- Giroscopio en Z
	    USON_Data();	//- La data se guarda en dist
		
		_delay_us(10);
    }
}
