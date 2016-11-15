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
#include "drivers/can.h"
#include "drivers/servo.h"
#include "drivers/ir.h"
#include "drivers/motor.h"
#include "drivers/solenoid.h"
#include "controller.h"

int main(void)
{
	UART_init(MYUBRR);
	CAN_init();
	IR_init();
	SERVO_init();
	MOTOR_init();
	SOLENOID_init();

	struct can_message_t send_msg;
	struct can_message_t receive_msg;
	
	/*while(1) {
		// Testing CAN
		send_msg.id = 5;
		send_msg.length = 1;
		send_msg.data[0] = 15;
		printf("Sending message\n");
		printf("id: %d\ndata: %d\n\n", send_msg.id, send_msg.data[0]);
		CAN_message_send(&send_msg);
		_delay_ms(10);
		receive_msg = CAN_data_receive();
		printf("Received message\n");
		printf("id: %d\ndata: %d\n\n", receive_msg.id, receive_msg.data[0]);
		_delay_ms(10);
	}*/

	uint8_t ir_value = IR_read();
	uint8_t old_ir_value = ir_value;
	while(1) {
		receive_msg = CAN_data_receive();
		if(receive_msg.id == 1) {
			// Message is joystick data
			int8_t x = receive_msg.data[0];
			int8_t click = receive_msg.data[2];
			
			SERVO_write(-x);
			SOLENOID_shoot(click);
		} else if(receive_msg.id == 3) {
			// Slider data
			int8_t ref = receive_msg.data[1]; // Use right slider position as reference
			CONTROLLER_set_reference(ref);
		}
		
		ir_value = IR_read();
		if(ir_value != old_ir_value) {
			old_ir_value = ir_value;
			printf("%d\n", ir_value);
			// Send score to node 1
			send_msg.id = 0;
			send_msg.data[0] = ir_value;
			send_msg.length = 1;
				CAN_message_send(&send_msg);
		}

		// Apply controller
		float encoder_value = (100.0f * MOTOR_read_encoder())/MOTOR_max_encoder_value();
		float vel = CONTROLLER_actuate(encoder_value);
		MOTOR_set_dir_right(vel > 0);
		MOTOR_set_velocity(vel/100.0f * 0xFF);

		_delay_ms(10);
	}
}