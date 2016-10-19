/*
 * ATmega2560.h
 *
 * Created: 19.10.2016 10:52:03
 *  Author: elsala
 */ 


#ifndef ATMEGA2560_H_
#define ATMEGA2560_H_

// Constants
#define F_CPU	16000000
#define FOSC	F_CPU
#define BAUD	9600
#define MYUBRR	FOSC/16/BAUD-1

#endif /* ATMEGA2560_H_ */