/*
 * can.h
 *
 * Created: 05.10.2016 13:50:35
 *  Author: elsala
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "stdio.h"

struct can_message_t {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message_t;

void CAN_init();
void CAN_message_send(struct can_message_t* msg);
void CAN_error();
struct can_message_t CAN_message_receive();
void CAN_int_vect();

#endif /* CAN_H_ */