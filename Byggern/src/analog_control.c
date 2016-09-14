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

slider ANALOG_get_slider(){
	slider slider_t;
	uint8_t left_slider_voltage = ADC_read(LEFT_SLIDER_CHANNEL);
	uint8_t right_slider_voltage = ADC_read(RIGHT_SLIDER_CHANNEL);
	
	slider_t.left = 100 * ((float)left_slider_voltage / (0xFF - 1));
	slider_t.right = 100 * ((float)right_slider_voltage / (0xFF - 1));
	
	return slider_t;
}