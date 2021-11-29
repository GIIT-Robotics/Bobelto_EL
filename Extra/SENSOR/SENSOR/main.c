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
#include "UART/UART.h"
#include "HK3022/HK3022.h"
#include "TWI/TWI.h"
#include "BMP280/BMP280.h"
#include "MPU6050/MPU6050.h"
#include "USON/USON.h"

uint16_t dist = 0;
unsigned char UART_RX;

ISR(USART_RX_vect)
{
	UART_RX = UART_read();
	UART_write(UART_RX);
	UART_write('\n');
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
	UART_init();
	ADC_init();
	TWI_init();
	BMP280_init();
	MPU6050_init();
	USON_init();
	_delay_ms(10);
	sei();
	
    while (1) 
    {
		float T_int = LM335_Data();
		float P_ext = HK3022_Data();
		float P_int = BMP280_pres();
		float T_ext = BMP280_temp();
		int16_t a_x = MPU6050_read_acce(1);
		int16_t a_y = MPU6050_read_acce(2);
		int16_t a_z = MPU6050_read_acce(3);
		int16_t g_x = MPU6050_read_gyro(1);
		int16_t g_y = MPU6050_read_gyro(2);
		int16_t g_z = MPU6050_read_gyro(3);
		USON_Data();	//- La data se guarda en dist
		
		if (UART_RX == 0x41)	//- A
		{
			UART_write_data(P_int);
			UART_write('\n');
			
			// UART_write(P_int);
		}
		else if (UART_RX == 0x42)	//- B
		{
			UART_write_data(P_ext);
			UART_write('\n');
			
			// UART_write(P_ext);
		} 
		else if (UART_RX == 0x43)	//- C
		{
			UART_write_data(T_int);
			UART_write('\n');
			
			// UART_write(T_int);
		}
		else if (UART_RX == 0x44)	//- D
		{
			UART_write_data(T_ext);
			UART_write('\n');
			
			// UART_write(T_ext);
		}
		else if (UART_RX == 0x45)	//- E
		{
			UART_write_data(g_x);
			UART_write('\n');
			
			//UART_write(g_x);
		}
		else if (UART_RX == 0x46)	//- F
		{
			UART_write_data(g_y);
			UART_write('\n');
			
			//UART_write(g_y);
		}
		else if (UART_RX == 0x47)	//- G
		{
			UART_write_data(g_z);
			UART_write('\n');
			
			//UART_write(g_z);
		}
		else if (UART_RX == 0x48)	//- H
		{
			UART_write_data(a_x);
			UART_write('\n');
			
			//UART_write(a_x);
		}
		else if (UART_RX == 0x49)	//- I
		{
			UART_write_data(a_y);
			UART_write('\n');
			
			//UART_write(a_y);
		}
		else if (UART_RX == 0x4A)	//- J
		{
			UART_write_data(a_z);
			UART_write('\n');
			
			//UART_write(a_z);
		}
		else if (UART_RX == 0x4B)	//- K
		{
			UART_write_data(dist);
			UART_write('\n');
			
			//UART_write(dist);
		}
		
		_delay_ms(10);
    }
}
