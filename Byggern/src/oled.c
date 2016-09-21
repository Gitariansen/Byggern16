/*
 * oled.c
 *
 * Created: 21.09.2016 10:22:25
 *  Author: elsala
 */ 

#include "oled.h"
#include "byggern.h"
#include "adc.h"
#include "font5x7.h"

#include <stdio.h>
#include <util/delay.h>

volatile uint8_t *command	= (uint8_t *) OLED_COMMAND;
volatile uint8_t *data		= (uint8_t *) OLED_DATA;

static uint8_t line		= 0;
static uint8_t column	= 0;

// How to printf
// static FILE oled_stdout = FDEV_SETUP_STREAM(oled_printf, NULL, _FDEV_SETUP_WRITE)
// Implementer oled_printf
// stdout = oled_stdout

void OLED_init() {
	ADC_init();
	
	OLED_set_command(0xAE); // Display off
	OLED_set_command(0xA1); // Segment remap
	OLED_set_command(0xDA); // Common pads hardware: alternative
	OLED_set_command(0x12);
	OLED_set_command(0xC8); // Common output scan direction: com63~com0
	OLED_set_command(0xA8); // Multiplex ration mode: 63
	OLED_set_command(0x3F);
	OLED_set_command(0xD5); // Display divide ratio/osc. freq. mode
	OLED_set_command(0x80);
	OLED_set_command(0x81); // Contrast control
	OLED_set_command(0x50);
	OLED_set_command(0xD9); // Set pre-charge period
	OLED_set_command(0x21);
	OLED_set_command(0x20); // Set memory addressing mode
	OLED_set_command(0x00);
	OLED_set_command(0xDB); // VCOM deselect level mode
	OLED_set_command(0x30);
	OLED_set_command(0xAD); // Master configuration
	OLED_set_command(0x00);
	OLED_set_command(0xA4); // Out follows RAM content
	OLED_set_command(0xA6); // Set normal display
	OLED_set_command(0xAF); // Display on
	
	OLED_reset();
	OLED_print_string("Hello\n");
	OLED_print_string("Elsa er awesome");
}

void OLED_reset() {
	OLED_clear();
	OLED_home();
}

void OLED_set_command(uint8_t cmd) {
	*command = cmd;
}

void OLED_write_data(uint8_t d) {
	*data = d;
}

void OLED_home() {
	OLED_pos(0,0);
}

void OLED_goto_line(uint8_t l) {
	if(line < NUM_LINES) {
		OLED_set_command(0x22);
		line = l;
		OLED_set_command(line);
		OLED_set_command(0x7);
	}
}

void OLED_goto_column(uint8_t col) {
	if(column < NUM_COLUMNS) {
		OLED_set_command(0x21);
		column = col;
		OLED_set_command(column);
		OLED_set_command(0x7F);
	}
}

void OLED_pos(uint8_t line, uint8_t column) {
	OLED_goto_line(line);
	OLED_goto_column(column);
}

void OLED_print_char(char c){
	if(c == '\n') {
		OLED_pos((line + 1)%NUM_LINES, 0);
		return;
	}
	for(int i = 0; i < font_width; i++) {
		OLED_write_data(pgm_read_byte(&font[c - font_cutoff_character][i]));
	}
}

void OLED_print_string(char* s){
	int i = 0;
	while(s[i] != '\0'){
		OLED_print_char(s[i]);
		i++;
	}
}

void OLED_clear_line(uint8_t line) {
	OLED_pos(line,0);
	for(int column = 0; column < NUM_COLUMNS; column++) {
		OLED_write_data(0x00);
	}
}

void OLED_clear() {
	for(int line = 0; line < NUM_LINES; line++) {
		OLED_clear_line(line);
	}
}