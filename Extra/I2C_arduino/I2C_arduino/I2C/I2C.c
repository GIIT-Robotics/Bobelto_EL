/*
 * I2C.c
 *
 * Created: 22/09/2021 15:37:19
 *  Author: Alessandro
 */ 

#include "I2C.h"

/* Inicializacion del periferico de I2C (TWI) */
void I2C_Init()
{
	/* F = CPUclk/(16+(2*TWBR*Preescalador))
	 * F = 16 MHz /(16+2*2*1)
	 * F = 400 kHz
	 */
	TWSR ;		//--- Preescalador (1)
	TWBR = 0x0C;		//--- Divisor (2)
	PRR &=~ (1<<PRTWI);	//--- Enciende el periferico
}

/* Envio del estado START */
//bool I2C_StartCondition()
void I2C_StartCondition()
{
	TWCR = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
	while(!(TWCR & (1<<TWINT)));
	/*
	if((TWSR & 0xF8) == I2C_START)
		return false;
	
	return true;
	*/
}

/* Envio del estado RESTART */
//bool I2C_RestartCondition()
void I2C_RestartCondition()
{
	TWCR = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
	while(!(TWCR & (1<<TWINT)));
	
	/*
	if((TWSR & 0xF8) == I2C_RESTART)
		return false;
	
	return true;
	*/
}

/* Envio del estado STOP */
void I2C_StopCondition()
{
	TWCR = ((1<<TWINT)|(1<<TWSTO)|(1<<TWEN));
}

/* Envio del address con configuracion R/W */
bool I2C_SendAddress(uint8_t addr, uint8_t action)
{
	//uint8_t cmp = 0;
	addr = (addr<<1);
	
	if(action == I2C_W)
	{
		addr &=~ 1;
		//cmp = I2C_WT_SLA_ACK;
	} else 
	{
		addr |= 1;
		//cmp = I2C_RD_SLA_ACK;
	}
	
	TWDR = addr;
	TWCR = ((1<<TWINT)|(1<<TWEN));
	
	while(!(TWCR & (1<<TWINT)));
	/*
	if((TWSR & 0xF8) == cmp)
		return false;
	
	return true;
	*/
}

/* Escritura */
bool I2C_Write(uint8_t data)
{
	bool ret = true;
	
	TWDR = data;
	TWCR = ((1<<TWINT)|(1<<TWEN));
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) == I2C_MT_DATA_ACK)
		ret = false;
	
	return ret;
}

/* Lectura */
uint8_t I2C_Read(uint8_t ACK_NACK)
{
	TWCR = ((1<<TWINT)|(1<<TWEN)|(ACK_NACK<<TWEA));
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
	


