/*
 * can.c
 *
 * Created: 05.10.2016 13:50:46
 *  Author: elsala
 */ 

#include "can.h"
#include "MCP2515.h"

void CAN_init(){
	// Initialize MCP2515
	MCP2515_init();
	// Set loopback mode
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	// Enable interrupts for receive and error
	MCP2515_bit_modify(MCP_CANINTE, 0xFF, MCP_RX_INT | (1 << 5));
}

void CAN_message_send(struct can_message_t* msg){
	int data_length = 5 + msg->length;
	uint8_t data[data_length];
	data[0] = msg->id << 5; // Bit 3 to 10 to TXB0SIDH
	data[1] = msg->id >> 3; // Bit 0 to 2 to TXB0SIDL
	// Not using extended ID
	data[2] = 0;
	data[3] = 0;
	// length to TXB0DLC
	data[4] = msg->length;
	// Fill rest of array with message data
	for(int i = 5; i < data_length; i++) {
		data[i] = msg->data[i - 5];
	}
	// Write starting from TXB0SIDH
	MCP2515_write(MCP_TXB0CTRL + 1, data, data_length); 
	// Request to send from buffer TX0
	MCP2515_request_to_send(1);
}

struct can_message_t CAN_data_receive() {
	// TODO: actually check that there is a message in buffer
	struct can_message_t msg;
	msg.id = MCP2515_read((MCP_RXB0SIDH >> 3) | ((MCP_RXB0SIDL) << 5));
	msg.length = (0x0F) & MCP2515_read(MCP_RXB0DLC);
	for(int i = 0; i < msg.length; i++) {
		msg.data[i] = MCP2515_read(MCP_RXB0D0 + i);
	}
	return msg;
}