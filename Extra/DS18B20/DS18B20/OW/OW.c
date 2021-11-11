#include "OW.h"
#include <util/delay.h>

void OW_pinlow(int io)
{
	//- Establece el pin "io" en baja para salida
	DDRD = 1 << io;
}

void OW_pinrelease(int io)
{
	//- Establece el pin "io" en entrada
	DDRD = 0 << io;
}

uint8_t OW_pinread(int io)
{
	//- Devuelve el bit en baja o alta
	return PIND>>io & 1;
}

void TIM0_init()
{
	//- modo CTC (comparador)
	TCCR1A = 1<<WGM12 | 0<<WGM11 | 0<<WGM10;
	//- f = 250 KHz (clk = 16 MHz)
	TCCR1B = 0<<CS12 | 1<<CS11 | 1<<CS10;
}

void DelayMicros(int us)
{
	//- Contador en 0
	TCNT1 = 0;
	//- Reset de banderas
	TIFR1 = 1<<OCF1A;
	//- Establecemos límite de cuenta
	OCR1A = (us>>1) - 1;
	//- Loop mientras la bandera no se active
	while ((TIFR1 & 1<<OCF1A) == 0);
}

void LowRelease(int low, int high)
{
	OW_pinlow(2);
	DelayMicros(low);
	OW_pinrelease(2);
	DelayMicros(high);
}

uint8_t OW_reset()
{
	uint8_t data = 1;
	LowRelease(480, 70);
	data = OW_pinread(2);
	DelayMicros(410);
	//- Retorna 0 cuando se encuentra presente
	return data;
}

void OW_write(uint8_t data)
{
	int del;
	for (int i=0; i<8; i++)
	{
		if((data & 1) == 1) del = 6; else del = 60;
		LowRelease(del, 70-del);
		data = data >> 1;
	}
}

uint8_t OW_read()
{
	uint8_t data = 0;
	for (int i=0; i<8; i++)
	{
		LowRelease(6, 9);
		data = data | OW_pinread(7)<<i;
		DelayMicros(55);
	}
	return data;
}

void OW_readbytes (int bytes) 
{
	for (int i=0; i<bytes; i++) 
	{
		DataBytes[i] = OW_read();
	}
}

uint8_t OneWireCRC (int bytes)
{
	uint8_t crc = 0;
	for (int j=0; j<bytes; j++) 
	{
		crc = crc ^ DataBytes[j];
		for (int i=0; i<8; i++) crc = crc>>1 ^ ((crc & 1) ? 0x8c : 0);
	}
	return crc;
}

void OW_work(int io)
{
	//- Lo ponemos en baja
	PORTD = PORTD & ~(io);	 
}