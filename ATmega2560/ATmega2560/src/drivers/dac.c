/*
 * dac.c
 *
 * Created: 02.11.2016 15:32:22
 *  Author: lassehh
 */ 

#include "dac.h"
#include "TWI_Master.h"

void DAC_init() {
	TWI_Master_Initialise();
}

void DAC_write(uint8_t value) {
	uint8_t twi_msg[3] = {
		MAX520_TWI_ADDRESS,
		0x00,
		value
	};
	TWI_Start_Transceiver_With_Data(twi_msg, 3);
}