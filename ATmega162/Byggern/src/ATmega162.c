/*
 * main.c
 *
 * Created: 31.08.2016 15:30:26
 *  Author: audunel
 */ 

#include "ATmega162.h"
#include "menu.h"
#include "game.h"
#include "drivers/sram.h"
#include "drivers/joystick.h"
#include "drivers/slider.h"
#include "drivers/uart.h"
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

	struct can_message_t send_msg;
	struct can_message_t receive_msg;
	
	/*while(1) {
		// Testing CAN
		send_msg.id = 10;
		send_msg.length = 1;
		send_msg.data[0] = 20;
		printf("Sending message\n");
		printf("id: %d\ndata: %d\n\n", send_msg.id, send_msg.data[0]);
		CAN_message_send(&send_msg);
		_delay_ms(10);
		receive_msg = CAN_data_receive();
		printf("Received message\n");
		printf("id: %d\ndata: %d\n\n", receive_msg.id, receive_msg.data[0]);
		_delay_ms(10);
	}*/
	
	GAME_new();

	joystick_state_t joystick_state;
	joystick_state_t old_joystick_state;
	while(1) {
		receive_msg = CAN_data_receive();
		switch(receive_msg.id) {
			case 2:
			if(receive_msg.data[0] == 1) {
				GAME_score();
				printf("Score: %d\n", GAME_get_goals());
			}
			break;
		}

		joystick_state = JOYSTICK_get_state();
		if(joystick_state.x != old_joystick_state.x || joystick_state.y != old_joystick_state.y || joystick_state.click != old_joystick_state.click) {
			send_msg.id = 1;
			send_msg.data[0] = joystick_state.x;
			send_msg.data[1] = joystick_state.y;
			send_msg.data[2] = joystick_state.click;
			send_msg.length = 3;
			printf("Sending message\n");
			printf("id: %d\ndata: %d\n\n", send_msg.id, send_msg.data[0]);
			CAN_message_send(&send_msg);
		}
	
		_delay_ms(80);
	}
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