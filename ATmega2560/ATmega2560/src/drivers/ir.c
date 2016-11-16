/*
 * ir.c
 *
 * Created: 02.11.2016 10:43:23
 *  Author: lassehh
 */ 

#include "ir.h"
#include "adc.h"

const uint8_t threshold = 50;

void IR_init() {
	ADC_init();
}

uint8_t IR_read() {
	// Using a 4th order moving average filter
	static uint8_t filter[4];
	uint8_t value = ADC_read(IR_CHANNEL);
	uint16_t avg_value = value;
	for(int i = 1; i < 4; i++) {
		avg_value += filter[i];
		filter[i - 1] = filter[i];
	}
	avg_value /= 4;
	filter[3] = value;

	return (avg_value < threshold);
}