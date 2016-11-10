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
#include "drivers/MCP2515.h"
#include "drivers/ir.h"
#include "drivers/motor.h"

#include "drivers/pwm.h"

int main(void)
{
	UART_init(MYUBRR);
	CAN_init();
	IR_init();
	SERVO_init();
	MOTOR_init();

	struct can_message_t send_msg;
	struct can_message_t receive_msg;

	uint8_t ir_value = IR_read();
	uint8_t old_ir_value = ir_value;
	while(1) {
		receive_msg = CAN_data_receive();
		if(receive_msg.id == 1) {
			// Message is joystick data
			int8_t x = receive_msg.data[0];
			SERVO_write(-x);
			MOTOR_set_dir_right(x > 0);
			MOTOR_set_velocity(abs(x)/100.0f * 0xFF);
		}
		
		ir_value = IR_read();
		printf("IR value: %d\n", ir_value);
		if(ir_value != old_ir_value) {
			old_ir_value = ir_value;
			// Send score to node 1
			send_msg.id = 2;
			send_msg.data[0] = ir_value;
			send_msg.length = 1;
			CAN_message_send(&send_msg);
		}
		_delay_ms(10);
	}
}