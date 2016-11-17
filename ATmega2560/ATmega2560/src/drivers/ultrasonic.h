/*
 * ultrasonic.h
 *
 * Created: 17.11.2016 11:16:47
 *  Author: audunel
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define US_PORT	PORTE
#define US_DDR	DDRE
#define US_PIN	PE5


void US_init();

void US_calibrate();




#endif /* ULTRASONIC_H_ */