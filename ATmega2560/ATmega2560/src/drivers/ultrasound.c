#include "ultrasound.h"

#include "../ATmega2560.h"
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint16_t duration = 0x000;
static volatile uint8_t prevOutput = 0x00;

void US_init(){
	US_DDR |= (1 << US_TRIG_PIN);
	US_DDR &= ~(1 << US_ECHO_PIN);

	EIMSK |= (1 << INT5); // Enable interrupt at PE5->echo pin
	EICRB |= (1 << ISC50); // Trigger interrupt at any logical change at PE5

	sei();
}

void US_distance(){
	US_PORT |= (1 << US_TRIG_PIN);
	_delay_us(15);
	US_PORT &= ~(1 << US_TRIG_PIN);
}

ISR(US_ECHO_INTR) {
    if (prevOutput) // Falling edge-> stop counter and read value
    {
        TCCR3B = 0;//~(1 << CS30); // Stop the counter
		
        duration = TCNT3;
		printf("Duration: %d\n", duration);
        TCNT3 = 0x000; // Reset counter
        prevOutput=0;
    } 
	else //Rising edge-> start counter
    {
        //TCCR3B |= (1 << CS31) | (1 << CS30); // CS30 to start counter with no prescaler
		TCCR3B |= (1 << CS30);
        prevOutput=1;
    }
}