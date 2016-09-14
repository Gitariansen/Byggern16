/*
 * main.c
 *
 * Created: 31.08.2016 15:30:26
 *  Author: audunel
 */ 

#include "byggern.h"
#include "sram.h"
#include "uart.h"
#include "adc.h"

#include <stdlib.h>
#include <util/delay.h>

int main(void)
{	
	ADC_init();
	SRAM_init();
	UART_init(MYUBRR);
	printf("Hello worldsadasdsa");
	while(1){
		ADC_JoystickPos();
		ADC_SliderPos();
		_delay_ms(500);
		//SRAM_test();
	}
}