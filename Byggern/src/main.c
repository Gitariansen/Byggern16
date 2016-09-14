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
#include "analog_control.h"

#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{	
	ANALOG_init();
	SRAM_init();
	UART_init(MYUBRR);
	printf("Hello world\n");
	while(1){
		joystick pos = ANALOG_get_joystick();
		printf("x: %i\ny: %i\n\n", pos.x_pos, pos.y_pos);
		//ADC_JoystickPos();
		//ADC_SliderPos();
		_delay_ms(1000);
		//SRAM_test();
	}
}