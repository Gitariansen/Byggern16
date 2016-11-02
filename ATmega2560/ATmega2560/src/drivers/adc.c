/*
 * adc.c
 *
 * Created: 02.11.2016 10:48:22
 *  Author: lassehh
 */ 

#include "adc.h"
#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN);
	// Set prescaler to 128
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

uint8_t ADC_read(uint8_t ch) {
	// AVCC with external capacitor at AREF pin. 8-bit resolution.
	ADMUX = (1 << REFS0) | (1 << ADLAR) | (0x1F & ch);
	// Start conversion
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	return ADCH;
}