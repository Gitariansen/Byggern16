#ifndef ULTRASOUND_H_
#define ULTRASOUND_H_

#include "../ATmega2560.h"
#include <util/delay.h>

#include "ultrasound.h"

static volatile int duration = 0;
static volatile int prevOutput = 0;

void US_init(){
	US_DDR |= (1 << US_TRIG_PIN);
	US_DDR &= ~(1 << US_ECHO_PIN);
	
	SREG |= (1 << I); // SREG bit 7 must be enabled for global interrupts
	EIMSK |=  (1 << INT5); // Enable interrupt at PE6->echo pin
	EICRB |= (1 << ISC00); // Trigger interrupt at any logical change at PE6

}

void US_distance(){
	US_PORT |= (1 << US_TRIG_PIN);
	_delay_us(15);
	US_PORT &= ~(1 << US_TRIG_PIN);
	int distance = duration/58; //Convert duration to distance in cm
	printf("US Distance: %d", distance);
}


ISR(US_ECHO_INTR)
{
    if (prevOutput) // Falling edge
    {
        TCCR1B=0; // Stop the counter
        duration=TCNT1;
        TCNT1=0; // Reset counter
        i=0;
    }
    if (prevOutput==0) //Rising edge
    {
        TCCR1B|=(1<<CS10); // CS10 to start counter with no prescaler
        i=1;
    }
}