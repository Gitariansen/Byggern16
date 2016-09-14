/*
 * CFile1.c
 *
 * Created: 14.09.2016 10:30:16
 *  Author: elsala
 */ 
#include "adc.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

int ADC_init(void){
	/* Enables external memory interface, and releases PC7-PC4 from external memory. */
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	/* Set the interrupt pin to input */
	//DDRE &= ~(1 << DDE0);
	
	return 0;
}

uint8_t ADC_test(void){
	volatile char *ext_adc = (char *) 0x1400;
	*ext_adc = 0x04 | 0;
	_delay_us(6000);
	//printf("ADC: %i \n", *ext_adc);
	return (uint8_t) *ext_adc;
	
	return 0;
}