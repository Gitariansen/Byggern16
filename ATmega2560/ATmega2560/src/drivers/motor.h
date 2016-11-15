/*
 * motor.h
 *
 * Created: 02.11.2016 16:09:29
 *  Author: lassehh
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdio.h>
#include <avr/io.h>

#define MJ1_DDR		DDRH
#define MJ1_PORT	PORTH
#define MJ2_DDR		DDRK
#define MJ2_PORT	PORTK
#define MJ2_DATA	PINK
#define DIR			PH1
#define SEL			PH3
#define EN			PH4
#define OE			PH5
#define RST			PH6


void MOTOR_init();
void MOTOR_calibrate();
void MOTOR_set_velocity(uint8_t vel);
void MOTOR_set_dir_right(uint8_t dir);
void MOTOR_stop();
int16_t MOTOR_read_encoder();
int16_t MOTOR_max_encoder_value();
uint8_t reverse_byte(uint8_t byte);

#endif /* MOTOR_H_ */