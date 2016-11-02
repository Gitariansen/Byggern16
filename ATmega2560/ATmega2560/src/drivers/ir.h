/*
 * ir.h
 *
 * Created: 02.11.2016 10:43:11
 *  Author: lassehh
 */ 


#ifndef IR_H_
#define IR_H_

#include <stdio.h>

#define THRESHOLD 127

void IR_init();
uint8_t IR_read();

#endif /* IR_H_ */