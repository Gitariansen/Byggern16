/*
 * slider.c
 *
 * Created: 21.09.2016 09:37:13
 *  Author: elsala
 */ 

#include "slider.h"

#include "adc.h"

void SLIDER_init() {
	ADC_init();
}

slider_position_t SLIDER_get_position(){
	slider_position_t position;
	
	uint8_t left_slider_voltage = ADC_read(LEFT_SLIDER_CHANNEL);
	uint8_t right_slider_voltage = ADC_read(RIGHT_SLIDER_CHANNEL);
	
	position.left = 100 * ((float)left_slider_voltage / (0xFF - 1));
	position.right = 100 * ((float)right_slider_voltage / (0xFF - 1));
	
	return position;
}