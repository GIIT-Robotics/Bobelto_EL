#ifndef UART_H_
#define UART_H_

	void UART_init();							//funci�n para iniciar el USART AVR as�ncrono, 8 bits, 9600 baudios,
	unsigned char UART_read();					//funci�n para la recepci�n de caracteres
	void UART_write(unsigned char);				//funci�n para la transmisi�n de caracteres
	void UART_msg(char*);						//funci�n para la transmisi�n de cadenas de caracteres
	void UART_write_float(float);
	void UART_write_uint(uint32_t);
	void UART_write_int(int64_t);
	
#endif /* UART_H_ */