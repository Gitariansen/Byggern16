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

int SLIDER_compare(slider_position_t slider_a, slider_position_t slider_b) {
	return (abs(slider_a.left -slider_b.left) < 2) && (abs(slider_a.right - slider_b.right) < 2);
}

slider_position_t SLIDER_get_position(){
	slider_position_t position;

	uint8_t left_slider_voltage = ADC_read(LEFT_SLIDER_CHANNEL);
	uint8_t right_slider_voltage = ADC_read(RIGHT_SLIDER_CHANNEL);
	
	position.left = left_slider_voltage;
	position.right = right_slider_voltage;
	
	return position;
}