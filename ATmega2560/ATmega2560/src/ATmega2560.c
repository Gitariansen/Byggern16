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
#include "drivers/MCP2551.h"
#include "drivers/ir.h"
#include "drivers/motor.h"

int main(void)
{
	UART_init(MYUBRR);
	CAN_init();
	IR_init();

	//SERVO_init();
	MOTOR_init();
	// Test motor
	MOTOR_set_velocity(100);
	printf("Hello world\n");
	_delay_ms(2000);
	MOTOR_stop();
	

	struct can_message_t send_msg;
	struct can_message_t receive_msg;
	
	uint8_t ir_value;
	uint8_t old_ir_value;
	while(1) {
		
		receive_msg = CAN_data_receive();
		if(receive_msg.id == 1) {
			SERVO_write(-receive_msg.data[0]);
		}
		
		ir_value = IR_read();
		if(ir_value != old_ir_value) {
			old_ir_value = ir_value;
			// Send score to node 1
			send_msg.id = 2;
			send_msg.data[0] = ir_value;
			send_msg.length = 1;
			CAN_message_send(&send_msg);
		}
		_delay_ms(1);
	}
}