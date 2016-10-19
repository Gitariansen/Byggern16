/*
 * MCP2515.c
 *
 * Created: 05.10.2016 11:24:22
 *  Author: elsala
 */ 

#include <util/delay.h>

#include "MCP2551.h"
#include "spi.h"

uint8_t MCP2551_init(){
	volatile uint8_t value;
	
	SPI_master_init();
	
	MCP2551_reset();
	_delay_ms(10);
	
	// Self test
	value = MCP2551_read_data(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2551 is NOT in configuration mode after reset!\n");
		return 1;
	}
	return 0;
}

uint8_t MCP2551_read_data(uint8_t address) {
	uint8_t result;
	SPI_SS_low(); // Select CAN controller
	SPI_transcieve(MCP_READ);
	SPI_transcieve(address);
	result = SPI_transcieve(0);
	SPI_SS_high(); // Deselect CAN controller
	return result;
}

void MCP2551_write_data(uint8_t address, uint8_t* data, int data_size) {
	SPI_SS_low(); // Select CAN controller
	SPI_transcieve(MCP_WRITE);
	SPI_transcieve(address);
	for(int i = 0; i < data_size; i++) {
		SPI_transcieve(data[i]);
	}
	SPI_SS_high(); // Deselect CAN controller
}

void MCP2551_request_to_send(uint8_t command) {
	SPI_SS_low();
	SPI_transcieve(MCP_RTS | (command & 0x07));
	SPI_SS_high();
}

uint8_t MCP2551_read_status(uint8_t address) {
	uint8_t result;
	SPI_SS_low();
	SPI_transcieve(MCP_READ_STATUS);
	SPI_transcieve(address);
	result = SPI_transcieve(0);
	SPI_SS_high();
	return result;
}

void MCP2551_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	SPI_SS_low();
	SPI_transcieve(MCP_BITMOD);
	SPI_transcieve(address);
	SPI_transcieve(mask);
	SPI_transcieve(data);
	SPI_SS_high();
}

void MCP2551_reset() {
	SPI_SS_low(); // Select CAN controller
	SPI_transcieve(MCP_RESET);
	SPI_SS_high(); // Deselect CAN controller
}
