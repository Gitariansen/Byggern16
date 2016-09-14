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
#include <avr/interrupt.h>

int main(void)
{	
	ADC_init();
//	sei();
	SRAM_init();
	UART_init(MYUBRR);
	printf("Hello world\n");
	while(1){
		printf("%i\n",ADC_read(0));
		//ADC_JoystickPos();
		//ADC_SliderPos();
		//_delay_ms(500);
		//SRAM_test();
	}
}