/*
 * ir.c
 *
 * Created: 02.11.2016 10:43:23
 *  Author: lassehh
 */ 

#include "ir.h"
#include "adc.h"

const uint8_t threshold = 0x0F;

void IR_init() {
	ADC_init();
}

uint8_t IR_read() {
	// Using a 3rd order moving average filter
	static uint8_t filter[3];
	uint8_t value = ADC_read(IR_CHANNEL);
	uint8_t avg_value = value;
	for(int i = 1; i < 3; i++) {
		avg_value += filter[i];
		filter[i - 1] = filter[i];
	}
	avg_value /= 3;
	filter[3 - 1] = value;

	return (ADC_read(IR_CHANNEL) < threshold);
}