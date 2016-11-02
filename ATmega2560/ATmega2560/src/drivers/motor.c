/*
 * motor.c
 *
 * Created: 02.11.2016 16:09:41
 *  Author: lassehh
 */ 

#include "motor.h"
#include "dac.h"

void MOTOR_init() {
	DAC_init();
	// Set MJ1_PORT to input
	MJ1_DDR		|= (1 << DIR) | (1 << EN) | (1 << SEL) | (1 << OE) | (1 << RST);
	// Enable motor and set direction to 1
	MJ1_PORT	|= (1 << EN) | (1 << DIR);
	MOTOR_set_velocity(0);
}

void MOTOR_set_velocity(uint8_t vel) {
	DAC_write(vel);
}

void MOTOR_set_dir(uint8_t dirn) {
	// TODO: Implement
}

void MOTOR_stop() {
	MOTOR_set_velocity(0);
}