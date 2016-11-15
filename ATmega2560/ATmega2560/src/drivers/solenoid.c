/*
 * solenoid.c
 *
 * Created: 15.11.2016 11:06:56
 *  Author: elsala
 */ 

#include "../ATmega2560.h"
#include <util/delay.h>

#include "solenoid.h"

void SOLENOID_init() {
	SOLENOID_DDR |= (1 << SOLENOID_PIN);
}

void SOLENOID_shoot(uint8_t enable) {
	static uint8_t enabled = 0;
	if(enable != enabled) {
		if(enable) {
			SOLENOID_PORT &= ~(1 << SOLENOID_PIN);
		} else {
			SOLENOID_PORT |= (1 << SOLENOID_PIN);
		}
		_delay_ms(10);
		enabled = enable;
	}
}