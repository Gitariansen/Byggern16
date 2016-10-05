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

#include "menu.h"

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
	
	//SRAM_test();
	
	MENU_init();
	
	joystick_state_t joystick_state;
	while(1){
		joystick_state_t new_joystick_state = JOYSTICK_get_state();
		if(new_joystick_state.y_dirn != joystick_state.y_dirn) {
			switch(new_joystick_state.y_dirn) {
				case UP:
				printf("UP\n");
				MENU_decrease_index();
				break;
				case DOWN:
				printf("DOWN\n");
				MENU_increase_index();
				break;
				case Y_NEUTRAL:
				printf("NEUTRAL\n");
				break;
			}
		}
		if(new_joystick_state.click != joystick_state.click) {
			if(new_joystick_state.click == 1) {
				MENU_perform_action();
			}
		}
		_delay_ms(20);
		joystick_state = new_joystick_state;
		
	}
	
	
}