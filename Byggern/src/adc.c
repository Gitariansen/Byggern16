/*
 * CFile1.c
 *
 * Created: 14.09.2016 10:30:16
 *  Author: elsala
 */ 
#include "adc.h"
#include "byggern.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define XAXIS 0x05;
#define YAXIS 0x04;
#define ADC_MEMORY 0x1400;

///INT0_vect()
//{
//	printf("Interrupt");
//}

int ADC_init(void){
	/* Enables external memory interface, and releases PC7-PC4 from external memory. */
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	/* Set the interrupt pin to input */
	//GICR |= (1 << INT0);
	//EMCUCR &= ~((1 << ISC00)|(1 << ISC01));
	
	return 0;
}

uint8_t ADC_read(uint8_t chan) {
	volatile uint8_t *ext_adc = (uint8_t*) 0x1400;
	*ext_adc = 0x04 | chan;
	_delay_us(60);
	return *ext_adc;
}

// TODO: Make own module
int ADC_JoystickPos(void) {
	uint8_t x = ADC_read(1);
	uint8_t y = ADC_read(0);
	
	int x_pos = 2 * 100 * ((float)(x - 127) / (0xFF - 1));
	int y_pos = 2 * 100 * ((float)(y - 127) / (0xFF - 1));
	
	printf("x: %i\ny: %i\n\n", x_pos, y_pos);
}

// TODO: Make own module
int ADC_SliderPos(void) {
	uint8_t pos = ADC_read(2);
	
	int pos_percentage = 100 * ((float)pos / (0xFF - 1));
	
	printf("pos: %i\n\n",pos_percentage);
}