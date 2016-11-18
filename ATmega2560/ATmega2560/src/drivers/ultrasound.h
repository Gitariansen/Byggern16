#ifndef ULTRASOUND_H_
#define ULTRASOUND_H_

#define US_PORT					PORTE
#define US_DDR					DDRE
#define US_ECHO_PIN				PE5
#define US_TRIG_PIN				PE3

#define US_ECHO_EDGE			INT5_vect
#define US_ECHO_TIMER_OVERFLOW	TIMER3_OVF_vect

void Initialize_timer3();
void US_init();
void US_trigger();
int US_get_distance();

#endif /* SOLENOID_H_ */