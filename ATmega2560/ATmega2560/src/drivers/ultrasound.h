#ifndef ULTRASOUND_H_
#define ULTRASOUND_H_

#define US_PORT	PORTE
#define US_DDR	DDRE
#define US_ECHO_PIN	PE5
#define US_TRIG_PIN PE3

#define US_ECHO_INTR INT5_vect

void US_init();
void US_distance();

#endif /* SOLENOID_H_ */