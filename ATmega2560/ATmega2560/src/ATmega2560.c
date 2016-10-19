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

int main(void)
{
	UART_init(MYUBRR);
	CAN_init();

	printf("Hello world!\n");

	struct can_message_t receive_msg;
	const uint8_t data = 42;
	struct can_message_t send_msg = {
		.id = 2,
		.data = data,
		.length = 1
	};
	while(1) {
		_delay_ms(1000);
		receive_msg = CAN_data_receive();
		printf("Message received\n");
		printf("ID: %d\n", receive_msg.id);
		printf("x: %d y: %d\n\n", receive_msg.data[0], receive_msg.data[1]);
	}
	/*
	const uint8_t data = 42;
	struct can_message_t send_msg = {
		.id = 2,
		.data[0] = data,
		.length = 1
	};
	struct can_message_t receive_msg;

    CAN_message_send(&send_msg);
    _delay_ms(1000);
	
    receive_msg = CAN_data_receive();
    printf("ID: %d, DATA: %d\n", receive_msg.id, receive_msg.data[0]);
	*/
}