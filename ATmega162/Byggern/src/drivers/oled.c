/*
 * oled.c
 *
 * Created: 21.09.2016 10:22:25
 *  Author: elsala
 */ 

#include "../memory_layout.h"
#include "oled.h"
#include "adc.h"
#include "font5x7.h"

#include <stdio.h>
#include <util/delay.h>

volatile uint8_t *command	= (uint8_t *) OLED_COMMAND;
volatile uint8_t *data		= (uint8_t *) OLED_DATA;

static uint8_t line		= 0;
static uint8_t column	= 0;

static FILE oled_stdout = FDEV_SETUP_STREAM(OLED_print_char, NULL, _FDEV_SETUP_WRITE);

void OLED_init() {
	ADC_init();
	
	OLED_set_command(SET_DISPLAY_OFF);

	OLED_set_command(SET_SEGMENT_REMAP);

	OLED_set_command(SET_COM_PIN_HARDWARE_CONF);
	OLED_set_command(0x12); // Common pads hardware: alternative

	OLED_set_command(SET_COM_OUTPUT_SCAN_DIR_REMAP); // Common output scan direction: com63~com0

	OLED_set_command(SET_MULTIPLEX_RATIO);
	OLED_set_command(0x3F); // Multiplex ration mode: 63

	OLED_set_command(SET_CLCK_DIV_RATIO_OSC_FREQ);
	OLED_set_command(0x80); // Display divide ratio/osc. freq. mode

	OLED_set_command(SET_CONTRAST_CONTROL);
	OLED_set_command(MEDIUM_CONTRAST);

	OLED_set_command(SET_PRECHARGE_PERIOD);
	OLED_set_command(0x21);

	OLED_set_command(SET_MEMORY_ADDRESSING_MODE);
	OLED_set_command(0x00); // Horizontal addressing mode

	OLED_set_command(SET_VCOM_DESELECT_LEVEL);
	OLED_set_command(0x30);

	OLED_set_command(SELECT_IREF);
	OLED_set_command(0x00); // Iref external

	OLED_set_command(DISPLAY_ON_FOLLOW_RAM); // Out follows RAM content

	OLED_set_command(SET_NORMAL_DISPLAY);

	OLED_set_command(SET_DISPLAY_ON);
	
	OLED_reset();
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
	if(l < NUM_LINES) {
		OLED_set_command(SET_PAGE_ADDRESS);
		line = l;
		OLED_set_command(line);
		OLED_set_command(0x7);
	}
}

void OLED_goto_column(uint8_t col) {
	if(col < NUM_COLUMNS) {
		OLED_set_command(SET_COLUMN_ADDRESS);
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

void OLED_printf(const char* fmt, ...){
	va_list args;
	va_start(args, fmt);
	vfprintf(&oled_stdout, fmt, args);
	va_end(args);
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

void OLED_set_contrast(contrast_value value) {
	OLED_set_command(SET_CONTRAST_CONTROL);
	OLED_set_command(value);
}