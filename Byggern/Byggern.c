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

#define FOSC 4900000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void initUSART(unsigned int ubrr){
	/* Set Baud rate */ 
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter*/
	USCRB = (1 << RXEN)|(1 << TXEN)
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1 << URSEL)|(1 << USBS)|(3 << UCSZ0)
}

void transmit_USART(unsigned int data){
	while ( !( USCRA & (1 << UDRE))){}
	UDR = data;
}

void receive_USART(unsigned int data){
	
}



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