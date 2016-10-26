/*
 * pwm.c
 *
 * Created: 26.10.2016 10:24:05
 *  Author: audunel
 */

#include "pwm.h"
#include "../ATmega2560.h"
#include <avr/io.h>

void PWM_set_period(float period_ms) {
	// Set fast PWM mode 14
	TCCR1A = (1 << WGM11);
	TCCR1B = (1 << WGM12) | (1 << WGM13);
	
	// Clear OC1A on compare match, set OC1A at BOTTOM (non-inverting mode)
	TCCR1A |= (1 << COM1A1);
	
	// Set prescalar to 1/64
	TCCR1B |= (1 << CS11) | (1 << CS10);
	
	// Set TOP
	ICR1 = F_CPU/64/1000 * period_ms;
	
	// Set OC1A as output
	DDRB |= (1 << DDB5);
}

void PWM_set_pulse_width(float pulse_width_ms) {
	OCR1A = F_CPU/64/1000 * pulse_width_ms;
}