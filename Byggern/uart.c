/*
 * Byggern.c
 *
 * Created: 31.08.2016 08:22:33
 *  Author: audunel
 */ 

#include "uart.h"

#include <stdio.h>
#include <avr/io.h>

int UART_init(unsigned int ubrr){
	/* Set Baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter*/
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << URSEL0)|(1 << USBS0)|(3 << UCSZ00);
	
	fdevopen(&UART_transmit, &UART_receive);
	
	return 0;
}

int UART_transmit(char data, FILE* f){
	while ( !( UCSR0A & (1 << UDRE0)));
	UDR0 = data;
	
	return 0;
}

unsigned char UART_receive(void){
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}