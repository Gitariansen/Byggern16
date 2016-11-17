#ifndef ULTRASOUND_H_
#define ULTRASOUND_H_

#include <avr/io.h>

#define US_PORT	PORTE
#define US_DDR	DDRE
#define US_ECHO_PIN	PE5
#define US_TRIG_PIN PE6

void US_init();
void US_distance();

#endif /* SOLENOID_H_ */