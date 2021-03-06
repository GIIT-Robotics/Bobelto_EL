

void UART_init();							//funci?n para iniciar el USART AVR as?ncrono, 8 bits, 9600 baudios,
unsigned char UART_read();					//funci?n para la recepci?n de caracteres
void UART_write(unsigned char);				//funci?n para la transmisi?n de caracteres
void UART_msg(char*);						//funci?n para la transmisi?n de cadenas de caracteres
void UART_write_float(float);
void UART_write_uint(uint32_t);
void UART_write_int(int64_t);

void UART_init()
{
	DDRD |= (1<<1);							//PD1	COMO SALIDA TXa
	DDRD &= ~(1<<0);						//PD0	COMO ENTRADA RX
	UCSR0A = (0<<TXC0)|(0<<U2X0)|(0<<MPCM0);
	UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<TXB80);
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
	UBRR0 = 103;								//NO DUPLICA VELOCIDAD 9600B A 160000
}

unsigned char UART_read(){
	if(UCSR0A&(1<<7)){			//si el bit7 del registro UCSR0A se ha puesto a 1
		return UDR0;			//devuelve el dato almacenado en el registro UDR0
	}
	else
	return 0;
}

void UART_write(unsigned char caracter){
	while(!(UCSR0A&(1<<5)));    // mientras el registro UDR0 est? lleno espera
	UDR0 = caracter;            //cuando el el registro UDR0 est? vacio se envia el caracter
}

void UART_write_txt(char* cadena){			//cadena de caracteres de tipo char
	while(*cadena !=0x00){				//mientras el ?ltimo valor de la cadena sea diferente a el caracter nulo
		UART_write(*cadena);			//transmite los caracteres de cadena
		cadena++;						//incrementa la ubicaci?n de los caracteres en cadena
										//para enviar el siguiente caracter de cadena
	}
}

void UART_write_float(float dato){
	int16_t data =  (int16_t)dato;
	uint8_t cantidad = 0;
	bool signo = true; //true => '+' / false => '-'/
	uint8_t numeros[10];
	
	if (data<0){
		signo = false;
		data = data*-1;
		dato = dato*-1;
	}
	
	for(int i=0; i<11; i++){
		if ( data/10 > 0 ){
			cantidad++;
			numeros[i] =  data%(10) ;
			data = data/(10);
			
		}else{
			if (data!=0){
				cantidad++;
				numeros[i] = data;				
			}
			break;			
		}
	}
	
	if(signo==false){
		UART_write(45);
	}
	if (cantidad == 0 ){
		cantidad++;
		numeros[0] = 0;
	}
	
	for (int i =1; i<cantidad+1; i++){
		UART_write(numeros[cantidad-i] + 48);
		dato = dato - numeros[cantidad-i]*pow(10,cantidad-i);
	}
	UART_write(46);
	for (int i = 0; i < 2; i++){
		dato = dato*10;
		UART_write(dato+48);
		dato = dato - (int8_t)dato;		
	}
	UART_write_txt("\n\r");
}
void UART_write_uint(uint32_t data){
	uint8_t cantidad = 0;
	uint8_t numeros[13];
	
	for(int i=0; i<14; i++){
		if ( data/10 > 0 ){
			cantidad++;
			numeros[i] =  data%(10) ;
			data = data/(10);
			
			}else{
			if (data!=0){
				cantidad++;
				numeros[i] = data;
			}
			break;
		}
	}
	
	if (cantidad == 0 ){
		cantidad++;
		numeros[0] = 0;
	}
	
	for (int i =1; i<cantidad+1; i++){
		UART_write(numeros[cantidad-i] + 48);
		}
	UART_write_txt("\n\r");
}
void UART_write_int(int64_t data){
	uint8_t cantidad = 0;
	bool signo = true; //true => '+' / false => '-'/
	uint8_t numeros[13];
		
	if (data<0){
		signo = false;
		data = data*-1;
	}
		
	for(int i=0; i<11; i++){
		if ( data/10 > 0 ){
			cantidad++;
			numeros[i] =  data%(10) ;
			data = data/(10);
				
			}else{
			if (data!=0){
				cantidad++;
				numeros[i] = data;
			}
			break;
		}
	}
		
	if(signo==false){
		UART_write(45);
	}
	if (cantidad == 0 ){
		cantidad++;
		numeros[0] = 0;
	}
		
	for (int i =1; i<cantidad+1; i++){
		UART_write(numeros[cantidad-i] + 48);
	}
	UART_write_txt("\n\r");
}