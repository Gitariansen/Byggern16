/*
 * main.c
 *
 * Created: 31.08.2016 15:30:26
 *  Author: audunel
 */ 

#include "uart.h"
#include <stdlib.h>

int main(void)
{
	UART_init(MYUBRR);
	SRAM_init();
	SRAM_test();
	while(1) {
		print("Hello!")
	}
}