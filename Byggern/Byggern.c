/*
 * Byggern.c
 *
 * Created: 31.08.2016 08:22:33
 *  Author: audunel
 */ 


#include <avr/io.h>

#define F_CPU 4900000

#include <util/delay.h>

// Macro definitions
#define BitGet(p,m)((p)&(m)))
#define BitSet(p,m)((p)|=(m))
#define BitFlip(p,m)((p)^=(m))
#define Bit(x)(0x01<<(x))

int main(void)
{
	BitSet(DDRC,Bit(0));
	BitSet(PORTC,Bit(0));
    while(1)
    {
		BitFlip(PORTC,Bit(0));
		_delay_ms(1000);
    }
}