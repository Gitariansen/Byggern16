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

const uint8_t max_velocity = 0.80;

int16_t max_encoder_value;

void MOTOR_init() {
	DAC_init();
	// Set MJ1_PORT to input
	MJ1_DDR		|= (1 << DIR) | (1 << EN) | (1 << SEL) | (1 << OE) | (1 << RST);
	// Set MJ2_PORT to output
	MJ2_DDR		= 0x00;
	// Enable motor and set direction to 1
	MJ1_PORT	|= (1 << EN) | (1 << DIR);
	// Toggle !RST to reset encoder
	MJ1_PORT &= ~(1 << RST); 
	_delay_ms(20);
	MJ1_PORT |= (1 << RST);
	
	MOTOR_calibrate();
}

void MOTOR_calibrate() {
	MOTOR_set_dir_right(0);
	MOTOR_set_velocity(0x80);
	_delay_ms(3000);
	MOTOR_set_velocity(0);
	_delay_ms(20);
	
	// Toggle !RST to reset encoder
	MJ1_PORT &= ~(1 << RST);
	_delay_ms(20);
	MJ1_PORT |= (1 << RST);
	
	printf("Zero: %d\n", MOTOR_read_encoder());
	
	MOTOR_set_dir_right(1);
	MOTOR_set_velocity(0x80);
	_delay_ms(3000);
	//MOTOR_set_velocity(0);

	max_encoder_value = MOTOR_read_encoder();
	
	printf("Max: %d\n", max_encoder_value);
	
	_delay_ms(1000);
}

int16_t MOTOR_max_encoder_value() {
	return max_encoder_value;
}

void MOTOR_set_velocity(uint8_t vel) {
	vel > max_velocity ?
		DAC_write(vel) :
		DAC_write(max_velocity);
}

void MOTOR_set_dir_right(uint8_t dirn_is_right) {
	if(dirn_is_right) {
		MJ1_PORT |= (1 << DIR);
	} else {
		MJ1_PORT &= ~(1 << DIR);
	}
}

void MOTOR_stop() {
	MOTOR_set_velocity(0);
}

uint8_t reverse_byte(uint8_t byte) {
	uint8_t reversed_byte = 0;
	for(int i = 0; i < 8; i++) {
		if(byte & (1 << i)) {
			reversed_byte |= (1 << (7 - i));
		}
	}
	return reversed_byte;
}

int16_t MOTOR_read_encoder() {
	volatile int16_t encoder_value = 0;

	MJ1_PORT &= ~(1 << OE); // Set !OE low to enable output of encoder

	MJ1_PORT |= (1 << SEL); // Set SEL low to get low byte
	_delay_ms(20);
	encoder_value |= (MJ2_DATA << 0);

	MJ1_PORT &= ~(1 << SEL); // Set SEL high to get high byte
	_delay_ms(20);
	encoder_value |= (MJ2_DATA << 8);

	/*MJ1_PORT &= ~(1 << RST); // Toggle !RST to reset encoder
	_delay_ms(20);
	MJ1_PORT |= (1 << RST);*/

	MJ1_PORT |= (1 << OE); // Set !OE high to disable output of encoder
	
	// Return negative of encoder value as we want right to be the positive direction
	return -encoder_value;
}