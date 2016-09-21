/*
 * joystick.c
 *
 * Created: 14.09.2016 16:22:18
 *  Author: elsala
 */ 

#include "byggern.h"
#include "joystick.h"
#include "adc.h"

#include <avr/io.h>

void JOYSTICK_init(void)
{
	ADC_init();
	
	DDRB &= ~(1 << PB0);
	PORTB |= (1 << PB0);
}

joystick_state JOYSTICK_get_state() {
	joystick_state state;
	
	// Position
	uint8_t x_voltage = ADC_read(X_JOYSTICK_CHANNEL);
	uint8_t y_voltage = ADC_read(Y_JOYSTICK_CHANNEL);
	
	state.x = 2 * 100 * ((float)(x_voltage - 127) / (0xFF - 1));
	state.y = 2 * 100 * ((float)(y_voltage - 127) / (0xFF - 1));
	
	// Click
	state.click = (PINB & 1) == 0;
	
	return state;
}