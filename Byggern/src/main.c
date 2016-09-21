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
#include "joystick.h"
#include "slider.h"
#include "oled.h"

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

int main(void)
{	
	UART_init(MYUBRR);
	JOYSTICK_init();
	SLIDER_init();
	SRAM_init();
	OLED_init();
	
	printf("Hello world\n");
	
	SRAM_test();
	
	while(1){
		joystick_state pos1 = JOYSTICK_get_state();
		printf("x: %i\ny: %i\nclick: %i\n\n", pos1.x, pos1.y, pos1.click);
		slider_position pos2 = SLIDER_get_position();
		printf("left: %i\nright: %i\n\n", pos2.left, pos2.right);
		_delay_ms(1000);
	}
}