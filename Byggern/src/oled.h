/*
 * oled.h
 *
 * Created: 21.09.2016 10:25:12
 *  Author: elsala
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdio.h>

// Constants
#define NUM_LINES	8
#define NUM_COLUMNS	128
// TODO: this
/*
// config commands
#define SET_LOWER_COLUMN_START_ADDRESS	0x00 // 00~0F
#define SET_HIGHER_COLUMN_START_ADDRESS	0x10 // 10~1F
#define SET_MEMORY_ADDRESSING_MODE		0x20
#define ADDRESSING_MODE_HORIZONTAL		0x00
#define ADDRESSING_MODE_VERTICAL		0x01
#define ADDRESSING_MODE_PAGE			0x02
#define SET_COLUMN_ADDRESS				0x21 // range: 0-127
#define SET_PAGE_ADDRESS				0x22 // range: 0-7
#define SET_DISPLAY_START_LINE			0x40 // 40~7F
#define SET_CONSTART_CONTROL			0x81 // select one of 256 constrast steps
#define SET_SEGMENT_REMAP				0xA1 // alternative: A0
#define DISPLAY_ON						0xA4
#define
*/

void OLED_init();
void OLED_reset();

void OLED_set_command(uint8_t cmd);
void OLED_write_data(uint8_t data);

void OLED_print_char(char c);
void OLED_printf(const char* fmt, ...);
void OLED_clear();

void OLED_home();

void OLED_goto_line(uint8_t line);
void OLED_goto_column(uint8_t col);
void OLED_pos(uint8_t line, uint8_t col);

#endif /* OLED_H_ */