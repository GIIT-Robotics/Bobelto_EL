#ifndef UART_H_
#define UART_H_

	void UART_init();							//función para iniciar el USART AVR asíncrono, 8 bits, 9600 baudios,
	unsigned char UART_read();					//función para la recepción de caracteres
	void UART_write(unsigned char);				//función para la transmisión de caracteres
	void UART_msg(char*);						//función para la transmisión de cadenas de caracteres
	void UART_write_float(float);
	void UART_write_uint(uint32_t);
	void UART_write_int(int64_t);
	
#endif /* UART_H_ */