#include "ultrasound.h"

#include "../ATmega2560.h"
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t working;
uint8_t rising_edge;
uint16_t timer_value;
unsigned int distance_cm_avg;
unsigned int max_distance;
uint8_t error;


void Initialize_timer3()
{
	TCCR3B &= ~(1 << CS30);		// clk_io/8 prescaler
	TCCR3B |= (1 << CS31);
	TCNT0 = 0;					//Reset timer
	TIMSK3 |= (1 << TOIE0);		//Timer overflow interrupt enable
}

void US_init(){
	cli();
	
	US_DDR |= (1 << US_TRIG_PIN);
	US_DDR &= ~(1 << US_ECHO_PIN);

	EIMSK |= (1 << INT5);		// Enable interrupt at PE5->echo pin
	EICRB |= (1 << ISC50);		// Trigger interrupt at any logical change at PE5

	sei();
}

void US_calibrate() {
	for(int i = 0; i < 10; i++) {
		US_get_distance();
		_delay_ms(10);
	}
	max_distance = US_get_distance();
	printf("Max distance is %d\n", max_distance);
}

void US_trigger(){
	if(working == 0)
	{
		/* 60ms measurement cycle is suggested by the data sheet to prevent trigger signal to the echo signal */
		_delay_ms(60);
		/* Ensure the pin is low before sending the trigger*/
		US_PORT &=~ (1 << US_TRIG_PIN);
		_delay_us(1);
		/* 10us trigger input */
		US_PORT |= (1 << US_TRIG_PIN); 
		_delay_us(10);
		US_PORT &=~ (1 << US_TRIG_PIN);
		working = 1;
		error = 0;
		_delay_us(30);
	}

}

int US_get_distance(){
	US_trigger();
	//_delay_ms(10);
	return distance_cm_avg;
}

int US_max_distance() {
	return max_distance;
}

ISR (US_ECHO_EDGE_DETECT)
{
	if(working = 1)		// Trigger has been sent, 
						// this is the returning signal proportional to the range
	{
		if(rising_edge == 0)		// Start measuring echo width
		{
			rising_edge = 1;
			TCCR3B |= (1 << CS31);
			timer_value = 0;
		}
		else if (rising_edge == 1)	// Echo is finished
		{	
			/* 3th order moving average filter */
			static int filter[3];
			int new_val = (timer_value*30.5 + TCNT3)/2/*/58*/; //(2MHz/16bit = 30.5)
			distance_cm_avg = (timer_value*30.5 + TCNT3)/2/*/58*/;
			for(int i = 1; i < 3; i++) {
				distance_cm_avg += filter[i];
				filter[i - 1] = filter[i];
			}
			distance_cm_avg /= 4;
			filter[2] = new_val;
			 
			 
			//printf("timer_value: %d", timer_value);
			rising_edge = 0;
			working = 0;
			/* Stop and reset timer */
			TCCR3B &= ~(1 << CS31);
			TCNT3 = 0;
		}
	}
}

ISR (US_ECHO_TIMER_OVERFLOW)
{
	if(rising_edge == 1) //Check if the echo signal is active
	{
		timer_value++;
		/* Check if not out of range wrt to some user defined tresholds */
		if(timer_value > 100000)
		{
			working = 0;
			rising_edge = 0;
			error = 1;
		}
	}
}