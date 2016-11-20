#ifndef ULTRASOUND_H_
#define ULTRASOUND_H_

#define US_PORT					PORTE
#define US_DDR					DDRE
#define US_ECHO_PIN				PE5
#define US_TRIG_PIN				PE3

#define US_ECHO_EDGE_DETECT		INT5_vect
#define US_ECHO_TIMER_OVERFLOW	TIMER3_OVF_vect

//#define 

/*
	-EXTRA-
	This module uses an ultrasonic sensor to measure distance in centimeters
	which can be used as a reference to the PID controller, hence the motor can be 
	controlled with e.g your hand.
	
	Component description: http://www.micropik.com/PDF/HCSR04.pdf
*/

/* PIN setup and interrupt enable for any logical change */
void US_init();
void US_calibrate();
/* Triggers range measurement on the ultrasonic sensor */
void US_trigger();
/* Returns the distance in [cm] */
int US_get_distance();
int US_max_distance();

#endif /* ULTRASOUND_H_ */