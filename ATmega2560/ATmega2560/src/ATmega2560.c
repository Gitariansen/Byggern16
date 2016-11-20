/*
 * ATmega2560.c
 *
 * Created: 19.10.2016 10:43:18
 *  Author: elsala
 */ 

#include <avr/io.h>
#include "ATmega2560.h"
#include <util/delay.h>
#include "drivers/uart.h"
#include "drivers/servo.h"
#include "drivers/ir.h"
#include "drivers/motor.h"
#include "drivers/solenoid.h"
#include "drivers/ultrasound.h"
#include "drivers/can.h"
#include "controller.h"
#include "../../../can_protocol.h"


int main(void)
{
	UART_init(MYUBRR);
	CAN_init();
	IR_init();
	SERVO_init();
	MOTOR_init();
	SOLENOID_init();
	US_init();

	struct can_message_t send_msg;
	struct can_message_t receive_msg;

	uint8_t ir_value = IR_read();
	uint8_t old_ir_value = ir_value;

	int use_ultrasound = 0;

	while(1) {
		receive_msg = CAN_data_receive();

		if(receive_msg.id == GAME_MSG_ID) {
			// Message is joystick data
			int8_t x = receive_msg.data[X_INDEX];
			int8_t click = receive_msg.data[CLICK_INDEX];
			SERVO_write(x);
			SOLENOID_shoot(click);
			if(use_ultrasound == 0) {
				uint8_t ref = receive_msg.data[RIGHT_INDEX]; // Use right slider position as reference
				CONTROLLER_set_reference(ref);
			}
		} else if(receive_msg.id == OPTIONS_MSG_ID) {
			use_ultrasound = receive_msg.data[ULTRASOUND_INDEX];
		}
		
		if(use_ultrasound) {
			uint8_t ref = 0xFF * ((float)US_get_distance())/((float)US_max_distance());
			CONTROLLER_set_reference(ref);
		}
		
		ir_value = IR_read();
		if(ir_value != old_ir_value) {
			// Send score to node 1
			send_msg.id = NODE_2_ID;
			send_msg.length = 1;
			send_msg.data[IR_INDEX] = ir_value;
			CAN_message_send(&send_msg);
			old_ir_value = ir_value;
		}

		// Apply controller
		float encoder_value = 0xFF * ((float)MOTOR_read_encoder())/((float)MOTOR_max_encoder_value());
		float vel = CONTROLLER_actuate(encoder_value);
		MOTOR_set_dir_right(vel > 0);
		MOTOR_set_velocity(vel);

		_delay_ms(10);
	}
}