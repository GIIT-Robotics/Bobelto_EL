#ifndef OW_H_
#define OW_H_

	#define	F_CPU 16000000UL

	#include <stdint.h>
	#include <avr/io.h>
	#include <util/delay.h>
	#include <math.h>
	
	uint8_t DataBytes[9];
	unsigned int DataWords[4];
	
	void OW_work(int io);
	void OW_pinlow(int io);
	void OW_pinrelease(int io);
	uint8_t OW_pinread(int io);
	void TIM0_init();
	void DelayMicros(int sec);
	void LowRelease(int low, int high);
	uint8_t OW_reset();
	void OW_write(uint8_t data);
	uint8_t OW_read();
	void OW_readbytes (int bytes);
	uint8_t OneWireCRC (int bytes);
	void OW_work(int io);

#endif /* OW_H_ */