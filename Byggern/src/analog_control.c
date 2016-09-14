/*
 * CFile1.c
 *
 * Created: 14.09.2016 16:22:18
 *  Author: elsala
 */ 

#include "byggern.h"
#include "analog_control.h"
#include "adc.h"

void ANALOG_init(void)
{
	ADC_init();
}

joystick ANALOG_get_joystick() {
	joystick joystick_t;
	
	uint8_t x_voltage = ADC_read(X_JOYSTICK_CHANNEL);
	uint8_t y_voltage = ADC_read(Y_JOYSTICK_CHANNEL);
	
	joystick_t.x_pos = 2 * 100 * ((float)(x_voltage - 127) / (0xFF - 1));
	joystick_t.y_pos = 2 * 100 * ((float)(y_voltage - 127) / (0xFF - 1));
	
	return joystick_t;
}