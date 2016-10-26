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

int main(void)
{
	UART_init(MYUBRR);
	CAN_init();

	printf("Hello world!\n");

	SERVO_init();
	SERVO_write(100);
	
	struct can_message_t receive_msg;
	
	//printf("CANSTAT: 0x%0X\n", MCP2551_read_data(MCP_CANSTAT));
	
	while(1) {
		_delay_ms(1);
		receive_msg = CAN_data_receive();

		SERVO_write(-receive_msg.data[0]);
	}
}