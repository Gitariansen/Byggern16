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
// config commands
#define SET_LOWER_COLUMN_START_ADDRESS	0x00 // 00~0F
#define SET_HIGHER_COLUMN_START_ADDRESS	0x10 // 10~1F
#define SET_MEMORY_ADDRESSING_MODE		0x20
#define ADDRESSING_MODE_HORIZONTAL		0x00
#define ADDRESSING_MODE_VERTICAL		0x01
#define ADDRESSING_MODE_PAGE			0x02
#define SET_MEMORY_ADDRESSING_MODE		0x20
#define SET_COLUMN_ADDRESS				0x21 // range: 0-127
#define SET_PAGE_ADDRESS				0x22 // range: 0-7
#define SET_DISPLAY_START_LINE			0x40 // 40~7F
#define SET_CONSTART_CONTROL			0x81 // select one of 256 contrast steps
#define SET_SEGMENT_REMAP				0xA1 // alternative: A0
#define DISPLAY_ON_FOLLOW_RAM			0xA4
#define DISPLAY_ON_IGNORE_RAM			0xA5
#define SET_NORMAL_DISPLAY				0xA6 // 1 indicates "ON" pixel
#define SET_INVERSE_DISPLAY				0xA7 // 0 indicates "ON" pixel
#define SET_MULTIPLEX_RATIO				0xA8 // range: 16-63
#define SELECT_IREF						0xAD
#define SET_DISPLAY_OFF					0xAE
#define SET_DISPLAY_ON					0xAF
#define SET_PAGE_START_ADDRESS			0xB0 // B0~B7
#define SET_COM_OUTPUT_SCAN_DIR_NORMAL	0xC0
#define SET_COM_OUTPUT_SCAN_DIR_REMAP	0xC8
#define SET_DISPLAY_OFFSET				0xD3
#define SET_CLCK_DIV_RATIO_OSC_FREQ		0xD5
//	upper nibble (osc. freq)	0-16
//	lower nibble (divide ratio)	0-15
#define SET_PRECHARGE_PERIOD			0xD9
#define SET_COM_PIN_HARDWARE_CONF		0xDA
#define SET_VCOM_DESELECT_LEVEL			0xDB

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