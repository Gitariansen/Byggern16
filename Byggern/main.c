/*
 * main.c
 *
 * Created: 31.08.2016 15:30:26
 *  Author: audunel
 */ 

#include "uart.h"

int main(void)
{
	UART_init(MYUBRR);
	while(1){
		printf("Hello world ");
		_delay_ms(1000);
	}	
}