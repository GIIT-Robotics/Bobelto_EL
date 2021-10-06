/*
 * TWI.c
 *
 * Created: 21/09/2017 04:31:53 p.m.
 *  Author: Marlon
 */

 #include "TWI.h"
 
 void TWI_Init(){

	/////// Setting frequency ///////
	/*
		F = 	CPUclk/(16 + (2*TWBR*Prescaler))
		F =		16000000/(16 + 2*42*1)
		F =		200kHz
	*/

	//Prescaler
	TWSR &=~ (1<<TWPS0);
	TWSR &=~ (1<<TWPS1);

	//factor divisor
	TWBR = 32;

	/////// TWI POWER ON ///////
	PRR	 &=~ (1<<PRTWI);

 }

 bool TWI_startCond(){
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));

	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) == TWI_START)
		return false;

	return true;
 }

 bool TWI_restrtCond(){
   TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));

   while(!(TWCR & (1<<TWINT)));

   if ((TWSR & 0xF8) == TWI_RESTART)
	  return false;

   return true;
 }

 void TWI_stopCond(){
	TWCR |= ((1<<TWINT) | (1<<TWSTO) | (1<<TWEN));
 }

 bool TWI_sendAdrr(uint8_t adrr, uint8_t action){
	
	uint8_t cmp = 0;
	adrr = (adrr << 1 );

	if (action == TWI_W){
		adrr &=~ 1;
		cmp = TWI_WT_SLA_ACK;
	}
	else{
		adrr |= 1;
		cmp = TWI_RD_SLA_ACK;
	}

	TWDR = adrr;
	TWCR = ((1<<TWINT) | (1<<TWEN));

	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) == cmp)
		return false;
	 
	return true;
 }

 bool TWI_write(uint8_t data2write){
	
	bool ret = true;
	
	TWDR = data2write;
	TWCR = ((1<<TWINT) | (1<<TWEN));
	while(!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) == TWI_MT_DATA_ACK)
		ret = false;
	
	return ret;
 }


 uint8_t TWI_read(uint8_t ACK_NACK){
	
	TWCR = ((1 << TWINT) | (1 << TWEN) | (ACK_NACK << TWEA));

	while(!(TWCR & (1<<TWINT)));
	return TWDR;
 }