/*
 * solenoid.h
 *
 * Created: 15.11.2016 11:06:44
 *  Author: elsala
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

#include <avr/io.h>

#define SOLENOID_PORT	PORTE
#define SOLENOID_DDR	DDRE
#define SOLENOID_PIN	PE4

void SOLENOID_init();
void SOLENOID_shoot(uint8_t enable);

#endif /* SOLENOID_H_ */