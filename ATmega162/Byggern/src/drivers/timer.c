/*
 * timer.c
 *
 * Created: 16.11.2016 15:49:55
 *  Author: elsala
 */ 

#include "timer.h"
#include "../ATmega162.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t ms_since_init;

void TIMER_init() {
	cli();
	
	// Set fast PWM mode 14
	TCCR1A = (1 << WGM11);
	TCCR1B = (1 << WGM12) | (1 << WGM13);
	
	// Clear OC1A on compare match, set OC1A at BOTTOM (non-inverting mode)
	TCCR1A |= (1 << COM1A1);
	
	// Set prescalar to 1/64
	TCCR1B |= (1 << CS11) | (1 << CS10);
	
	// Set TOP
	ICR1 = F_CPU/64/1000;
	
	// Set OC1A as output
	DDRB |= (1 << DDB5);
	
	TIMSK |= (1 << OCIE1A);
		
	sei();

	ms_since_init = 0;
}

uint16_t TIMER_time() {
	return ms_since_init;
}

ISR(TIMER1_COMPA_vect) {
	ms_since_init += 1;
}