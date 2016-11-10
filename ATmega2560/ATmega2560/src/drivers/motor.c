/*
 * motor.c
 *
 * Created: 02.11.2016 16:09:41
 *  Author: lassehh
 */ 

#include "motor.h"
#include "dac.h"

#include "../ATmega2560.h" // Need F_CPU
#include <util/delay.h>

void MOTOR_init() {
	DAC_init();
	// Set MJ1_PORT to input
	MJ1_DDR		|= (1 << DIR) | (1 << EN) | (1 << SEL) | (1 << OE) | (1 << RST);
	// Enable motor and set direction to 1
	MJ1_PORT	|= (1 << EN) | (1 << DIR);
	MOTOR_stop();
}

void MOTOR_test() {
	MOTOR_set_velocity(100);
	_delay_ms(500);
	MOTOR_stop();
	MOTOR_set_dir_right(0);
	MOTOR_set_velocity(100);
	_delay_ms(500);
	MOTOR_stop();
	MOTOR_set_dir_right(1);
}

void MOTOR_set_velocity(uint8_t vel) {
	DAC_write(vel);
}

void MOTOR_set_dir_right(uint8_t dirn) {
	if(dirn == 0) {
		MJ1_PORT &= ~(1 << DIR);
	} else {
		MJ1_PORT |= (1 << DIR);
	}
}

void MOTOR_stop() {
	MOTOR_set_velocity(0);
}