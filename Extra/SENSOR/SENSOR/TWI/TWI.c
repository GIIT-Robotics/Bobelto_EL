#include "TWI.h"

void TWI_init()
{
	//- F_TWI = F_CPU/(16+(2*TWBR*Preescaler))
	
	//- Preescalador = 1
	TWSR = 0<<TWPS0 | 0<<TWPS1;
	
	//- TWBR
	TWBR = 32;
	
	//- ... F_TWI = 200 kHz
	
	//- Encendido del TWI
	PRR = 0<<PRTWI;
}

bool TWI_startCond()
{
	TWCR = 1<<TWINT | 1<<TWSTA | 1<<TWEN;
	
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) == TWI_START) return false;
	
	return true;
}

bool TWI_restrtCond()
{
	TWCR = 1<<TWINT | 1<<TWSTA | 1<<TWEN;
	
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) == TWI_RESTART) return false;
	
	return true;
}

void TWI_stopCond()
{
	TWCR = 1<<TWINT | 1<<TWSTO | 1<<TWEN;
}

bool TWI_sendAdrr(uint8_t adrr, uint8_t action)
{
	uint8_t cmp = 0;
	adrr = adrr<<1;
	
	if (action == TWI_W)
	{
		adrr &=~ 1;
		cmp = TWI_WT_SLA_ACK;
	}
	else
	{
		adrr |= 1;
		cmp = TWI_RD_SLA_ACK;
	}
	
	TWDR = adrr;
	TWCR = 1<<TWINT | 1<<TWEN;
	
	while(!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) == cmp) return false;
	
	return true;
}

bool TWI_write(uint8_t data)
{
	TWDR = data;
	TWCR = 1<<TWINT | 1<<TWEN;
	
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) == TWI_MT_DATA_ACK) return false;

	return true;
}

uint8_t TWI_read(uint8_t ACK_NACK)
{
	TWCR = 1<<TWINT | 1<<TWEN | ACK_NACK<<TWEA;
	
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}

void TWI_write_sensor(uint8_t Address, uint8_t reg, uint8_t val)
{
	while(TWI_startCond());
	while(TWI_sendAdrr(Address, TWI_W));
	while(TWI_write(reg));
	while(TWI_write(val));
	TWI_stopCond();
	_delay_us(100);
	//if(reg == 0xF5)	PORTB = 1<<PORTB5;
}

uint8_t TWI_read_sensor(uint8_t Address, uint8_t reg)
{
	uint8_t data;
	
	while(TWI_startCond());
	while(TWI_sendAdrr(Address, TWI_W));
	while(TWI_write(reg));
	while(TWI_restrtCond());
	while(TWI_sendAdrr(Address, TWI_R));
	data = TWI_read(TWI_NACK);
	TWI_stopCond();
	
	_delay_us(100);
	
	return data;
}


