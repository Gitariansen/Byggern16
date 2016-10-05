/*
 * main.c
 *
 * Created: 31.08.2016 15:30:26
 *  Author: audunel
 */ 

#include "byggern.h"
#include "menu.h"
#include "drivers/sram.h"
#include "drivers/uart.h"
#include "drivers/joystick.h"
#include "drivers/slider.h"
#include "drivers/can.h"

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
	MENU_init();
	CAN_init();
/*
	joystick_state_t joystick_state = JOYSTICK_get_state();
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
		if(new_joystick_state.x_dirn != joystick_state.x_dirn) {
			switch(new_joystick_state.x_dirn) {
				case LEFT:
					printf("LEFT\n");
					MENU_return_to_parent();
					break;
				case RIGHT:
					printf("RIGHT\n");
					break;
				case X_NEUTRAL:
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
*/
}