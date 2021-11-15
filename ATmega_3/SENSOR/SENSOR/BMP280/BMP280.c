#include "BMP280.h"

void BMP280_init()
{
	UART_write_txt("BMP: RESET ON");
	UART_write('\n');

	TWI_write_sensor(BMP280_ADDRESS,0xE0,0XB6);		//- Reset
	
	UART_write_txt("BMP: NORMAL MODE");
	UART_write('\n');
	//- Modo de navegacion interior
	TWI_write_sensor(BMP280_ADDRESS,0xF4,0x57);		//- Normal mode
	
	UART_write_txt("BMP: CONFIG");
	UART_write('\n');
	TWI_write_sensor(BMP280_ADDRESS,0xF5,0x10);		//- Config
	
	UART_write_txt("BMP: END INIT");
	UART_write('\n');
}

uint16_t BMP280_params(uint8_t reg)
{
	uint8_t tmp[2];
	
	uint16_t param;
	
	tmp[0] = TWI_read_sensor(BMP280_ADDRESS, reg);
	tmp[1] = TWI_read_sensor(BMP280_ADDRESS, reg+1);
	
	param = (uint16_t)tmp[1]<<8 | tmp[0];
	
	return param;
}

int32_t BMP280_t_fine()
{
	uint8_t tmp[3];		//- para almacenar 3 Bytes de valores
	uint16_t T1;
	int16_t  T2, T3;
	int32_t Temp, T_fine;			//- almacenamos la temperatura
	int64_t var1, var2;
	
	//- Pedimos medición de la temperatura
	tmp[0] = TWI_read_sensor(BMP280_ADDRESS,0xFA);		
	tmp[1] = TWI_read_sensor(BMP280_ADDRESS,0xFB);
	tmp[2] = TWI_read_sensor(BMP280_ADDRESS,0xFC);

	Temp = (int32_t)tmp[0]<<16 | (int32_t)tmp[1]<<8 | (int32_t)tmp[2];
	Temp >>= 4;

	//- Pedimos parámetros de presición
	T1 = (uint16_t)BMP280_params(0x88);
	T2 = (int16_t)BMP280_params(0x8A);
	T3 = (int16_t)BMP280_params(0x8C);
	
	var1 = (((Temp>>3) - ((int32_t)T1<<1)) * (int32_t)T2) >> 11;
	var2 = (((((Temp>>4) - (int32_t)T1) * ((Temp>>4) - ((int32_t)T1)) >> 12)) * (int32_t)T3) >> 14;
	T_fine = var1 + var2;
	
	return T_fine;	
}

float BMP280_temp()
{
	int32_t T_fine;
	float T;
	
	T_fine = BMP280_t_fine();
	
	T = ((T_fine * 5 + 128) >> 8)/100;
	
	return T;
}

float BMP280_pres()
{
	uint8_t tmp[3];		//- para almacenar 3 Bytes de valores
	uint16_t P1;
	int16_t  P2, P3, P4, P5, P6, P7, P8, P9;
	int32_t Pres, t_fine;
	int64_t var1, var2,p_fine;
	float P;
	
	tmp[0] = TWI_read_sensor(BMP280_ADDRESS,0xF7);
	tmp[1] = TWI_read_sensor(BMP280_ADDRESS,0xF8);
	tmp[2] = TWI_read_sensor(BMP280_ADDRESS,0xF9);
	
	Pres = (int32_t)tmp[0]<<16 | (int32_t)tmp[1]<<8 | (int32_t)tmp[2];
	Pres >>= 4;
	
	P1 = (uint16_t)BMP280_params(0x8E);
	P2 = (uint16_t)BMP280_params(0x90);
	P3 = (uint16_t)BMP280_params(0x92);
	P4 = (uint16_t)BMP280_params(0x94);
	P5 = (uint16_t)BMP280_params(0x96);
	P6 = (uint16_t)BMP280_params(0x98);
	P7 = (uint16_t)BMP280_params(0x9A);
	P8 = (uint16_t)BMP280_params(0x9C);
	P9 = (uint16_t)BMP280_params(0x9E);
	
	t_fine = BMP280_t_fine();
	
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)P6;
	var2 = var2 + ((var1 * (int64_t)P5) << 17);
	var2 = var2 + (((int64_t)P4) << 35);
	var1 = ((var1 * var1 * (int64_t)P3) >> 8) + ((var1 * (int64_t)P2) << 12);
	var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)P1) >> 33;
	
	if (var1 == 0) return 0;	//- avoid exception caused by division by zero
	
	p_fine = 1048576 - Pres;
	p_fine = (((p_fine << 31) - (int64_t)var2) * 3125) / var1;
	var1 = (((int64_t)P9) * (p_fine >> 13) * (p_fine >> 13)) >> 25;
	var2 = (((int64_t)P8) * p_fine) >> 19;
	
	p_fine = ((p_fine + var1 + var2) >> 8) + (((int64_t)P7) << 4);
	
	P = p_fine/25600;
	
	return P;
}