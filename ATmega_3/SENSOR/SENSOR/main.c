/*
 * SENSOR.c
 *
 * Created: 27/10/2021 10:56:36
 * Author : Alessandro
 */ 
#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>

#include "ADC/ADC.h"
#include "LM335/LM335.h"
#include "SPI/SPI.h"
#include "HK3022/HK3022.h"
#include "TWI/TWI.h"
#include "BMP280/BMP280.h"
#include "MPU6050/MPU6050.h"
#include "USON/USON.h"

uint16_t dist = 0;
uint8_t SPI_Rx = 0;

ISR(SPI_STC_vect)
{
	SPI_Rx = SPDR;
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
	ADC_init();
	TWI_init();
	BMP280_init();
	MPU6050_init();
	USON_init();
	
	_delay_ms(10);
	
	sei();
	
    while (1) 
    {
	    float T_ext = LM335_Data();				//- Temperatura externa
	    float P_ext = HK3022_Data();			//- Presion externa
	    float P_int = BMP280_pres();			//- Presion interna
	    float T_int = BMP280_temp();			//- Temperatura interna
	    int16_t a_x = MPU6050_read_acce(1);		//- Acelerometro en X
	    int16_t a_y = MPU6050_read_acce(2);		//- Acelerometro en Y
	    int16_t a_z = MPU6050_read_acce(3);		//- Acelerometro en Z
	    int16_t g_x = MPU6050_read_gyro(1);		//- Giroscopio en X
	    int16_t g_y = MPU6050_read_gyro(2);		//- Giroscopio en Y
	    int16_t g_z = MPU6050_read_gyro(3);		//- Giroscopio en Z
	    USON_Data();	//- La data se guarda en dist
		
		if (SPI_Rx == 0x01)
		{
			SPI_tx_32bit(P_int);
		} 
		else if (SPI_Rx == 0x02)
		{
			SPI_tx_32bit(P_ext);
		} 
		else if (SPI_Rx == 0x03)
		{
			SPI_tx_32bit(T_int);
		} 
		else if (SPI_Rx == 0x04)
		{
			SPI_tx_32bit(T_ext);
		} 
		else if (SPI_Rx == 0x05)
		{
			SPI_tx_16bit(g_x);
		} 
		else if (SPI_Rx == 0x06)
		{
			SPI_tx_16bit(g_y);
		} 
		else if (SPI_Rx == 0x07)
		{
			SPI_tx_16bit(g_z);
		} 
		else if (SPI_Rx == 0x08)
		{
			SPI_tx_16bit(a_x);
		} 
		else if (SPI_Rx == 0x09)
		{
			SPI_tx_16bit(a_y);
		} 
		else if (SPI_Rx == 0x0A)
		{
			SPI_tx_16bit(a_z);
		} 
		else if (SPI_Rx == 0x0B)
		{
			SPI_tx_16bit(dist);
		}
		
		_delay_us(10);
    }
}
