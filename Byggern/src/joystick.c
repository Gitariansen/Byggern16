/*
 * joystick.c
 *
 * Created: 14.09.2016 16:22:18
 *  Author: elsala
 */ 

#include "byggern.h"
#include "joystick.h"
#include "adc.h"

void JOYSTICK_init(void)
{
	ADC_init();
}

joystick_position JOYSTICK_get_position() {
	joystick_position position;
	
	uint8_t x_voltage = ADC_read(X_JOYSTICK_CHANNEL);
	uint8_t y_voltage = ADC_read(Y_JOYSTICK_CHANNEL);
	
	position.x = 2 * 100 * ((float)(x_voltage - 127) / (0xFF - 1));
	position.y = 2 * 100 * ((float)(y_voltage - 127) / (0xFF - 1));
	
	return position;
}