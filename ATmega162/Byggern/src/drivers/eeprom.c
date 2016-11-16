/*
 * eeprom.c
 *
 * Created: 16.11.2016 15:32:09
 *  Author: elsala
 */ 

#include <avr/interrupt.h>

void EEPROM_write(uint8_t address, uint8_t data) {
	cli();
	// Wait for completion of previous write
	while(EECR & (1 << EEWE));
	// Set up address and data registers
	EEAR = address;
	EEDR = data;
	// Write logical one to EEMWE
	EECR |= (1 << EEMWE);
	// Start eeprom write by setting EEWE
	EECR |= (1 << EEWE);
	sei();
}

uint8_t EEPROM_read(uint8_t address) {
	// Wait for completion of previous write
	while(EECR & (1 << EEWE));
	// Set up address and data registers
	EEAR = address;
	// Start eeprom read by writing EERE
	EECR |= (1 << EERE);
	/// Return data from data register
	return EEDR;
}