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
	JOYSTICK_init();
	SLIDER_init();
	SRAM_init();
	UART_init(MYUBRR);
	OLED_init();
	
	printf("Hello world\n");
	
	SRAM_test();
	
	while(1){
		joystick_position pos1 = JOYSTICK_get_position();
		printf("x: %i\ny: %i\n\n", pos1.x, pos1.y);
		slider_position pos2 = SLIDER_get_position();
		printf("left: %i\nright: %i\n\n", pos2.left, pos2.right);
		_delay_ms(1000);
	}
}