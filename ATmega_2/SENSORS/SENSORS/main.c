/*
 * SENSORS.c
 *
 * Created: 20/10/2021 15:56:34
 * Author : Alessandro
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>

/*
#include "BPM280/BMP280.h"
#include "MPU6050/MPU6050.h"
#include "TIM/TIM.h"
#include "TWI/TWI.h"
#include "UART/UART.h"
*/

int main(void)
{
	cli();
	
	/*TWI_Init();
	UART_init();
	timer_Init();
	
	MPU6050_init(MPU6050_ADDRESS);
	bmp280_init(BMP280_ADDRESS);*/
	
	sei();
	
    while (1) 
    {
    }
}

