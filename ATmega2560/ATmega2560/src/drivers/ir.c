/*
 * ir.c
 *
 * Created: 02.11.2016 10:43:23
 *  Author: lassehh
 */ 

#include "ir.h"
#include "adc.h"

void IR_init() {
	ADC_init();
}

uint8_t IR_read() {
	// TODO: Implement filter
	return ADC_read(IR_CHANNEL) < THRESHOLD;
}