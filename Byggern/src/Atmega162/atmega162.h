#ifndef _ATMEGA162_H_
#define _ATMEGA162_H_

// Constants
#define F_CPU	4915200
#define FOSC	4915200
#define BAUD	9600
#define MYUBRR	FOSC/16/BAUD-1

// Macros
#define BitGet(reg,bit)((reg)&(bit))
#define BitSet(reg,bit)((reg)|=(bit))
#define BitFlip(reg,bit)((reg)^=(bit))
#define Bit(x)(0x01<<(x))

typedef int bool;
#define true 1
#define false 0

#endif
