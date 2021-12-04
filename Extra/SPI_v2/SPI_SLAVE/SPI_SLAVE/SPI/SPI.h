#ifndef SPI_H_
#define SPI_H_
	
	#define F_CPU 16000000UL
	
	#include <avr/io.h>

	void SPI_init();
	void SPI_tx(uint8_t data);
	uint8_t SPI_rx();
	uint8_t SPI_trx(uint8_t data);

#endif /* SPI_H_ */