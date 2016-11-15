/*
 * controller.c
 *
 * Created: 14.11.2016 12:02:01
 *  Author: audunel
 */

#include "ATmega2560.h"

#include <stdio.h>
#include <avr/interrupt.h>

const float Kp = 1.0;
const float Ki = 1.0;
const float Kd = 0.0;

float reference = 0.0;
float prev_err = 0.0;
float integral = 0.0;

volatile uint16_t* timer_source = &TCNT1;

void CONTROLLER_set_reference(float ref) {
	reference = ref;
}

float CONTROLLER_actuate(float y) {
	float dt = ((float)*timer_source)/((float)F_CPU);
	*timer_source = 0;
	
	float err = reference - y;
	
	integral += err * dt;

	float derivative = (err - prev_err)/dt;
	prev_err = err;	
	
	return Kp*err + Ki*integral + Kd*derivative;
}