/*
 * Byggern.h
 *
 * Created: 31.08.2016 15:28:40
 *  Author: audunel
 */ 

#ifndef UART_H_
#define UART_H_

#define F_CPU 4915200

#include <util/delay.h>

// Macro definitions
#define BitGet(p,m)((p)&(m)))
#define BitSet(p,m)((p)|=(m))
#define BitFlip(p,m)((p)^=(m))
#define Bit(x)(0x01<<(x))

#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

//Function declarations

int UART_init(unsigned int ubrr);
int UART_transmit(char data, FILE* f);
unsigned char UART_receive(void);
#endif /* BYGGERN_H_ */