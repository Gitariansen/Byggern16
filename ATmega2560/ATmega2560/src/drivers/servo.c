/*
 * servo.c
 *
 * Created: 26.10.2016 12:14:26
 *  Author: audunel
 */ 

#include "servo.h"
#include "pwm.h"

const float min = 0.9;
const float max = 2.1;

void SERVO_init() {
	PWM_set_period(20.0f);
	SERVO_write((max + min)/2);
}

void SERVO_write(int8_t value) {
	float pulse_width = value/100.0f * 0.5f + (max + min)/2;
	if(pulse_width > max) {
		pulse_width = max;
	}
	if(pulse_width < min) {
		pulse_width = min;
	}
	PWM_set_pulse_width(pulse_width);
}