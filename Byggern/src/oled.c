/*
 * oled.c
 *
 * Created: 21.09.2016 10:22:25
 *  Author: elsala
 */ 

#include "oled.h"
#include "byggern.h"
#include "adc.h"

#include <stdio.h>
#include <util/delay.h>

volatile uint8_t *command	= (uint8_t *) OLED_COMMAND;
volatile uint8_t *data		= (uint8_t *) OLED_DATA;

void OLED_init() {
	ADC_init();
	
	*command = 0xAE; // Display off
	*command = 0xA1; // Segment remap
	*command = 0xDA; // Common pads hardware: alternative
	*command = 0x12;
	*command = 0xC8; // Common output scan direction: com63~com0
	*command = 0xA8; // multiplex ration mode: 63
	*command = 0x3F;
	*command = 0xD5; // display divide ratio/osc. freq. mode
	*command = 0x80;
	*command = 0x81; // contrast control
	*command = 0x50;
	*command = 0xD9; // set pre-charge period
	*command = 0x21;
	*command = 0x20; // set memory addressing mode
	*command = 0x02;
	*command = 0xDB; // VCOM deselect level mode
	*command = 0x30;
	*command = 0xAD; // Master configuration
	*command = 0x00;
	*command = 0xA4; // out follows RAM content
	*command = 0xA6; // set normal display
	*command = 0xAF; // Display on
}

void OLED_command(uint8_t cmd) {
	volatile uint8_t *command = (uint8_t *) OLED_COMMAND;
	*command = cmd;
}