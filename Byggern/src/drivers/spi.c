/*
 * spi.c
 *
 * Created: 05.10.2016 10:16:14
 *  Author: elsala
 */ 

#include "../byggern.h"
#include "spi.h"
#include <avr/io.h>

void SPI_master_init() {
	// Set MOSI and SCK output. All others input.
	DDR_SPI	= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
	// Enable SPI, set Master, set clock rate fck/16
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);	
}

uint8_t SPI_transcieve(uint8_t data) {
	// Start transmission
	SPDR = data;
	// Wait for transmission to complete
	while(!(SPSR & (1 << SPIF)));
	// Read data from slave
	return SPDR;
}

void SPI_SS_low() {
	PORTB &= ~(1 << DD_SS);
}

void SPI_SS_high() {
	PORTB |= (1 << DD_SS);
}