/*
 * dac.h
 *
 * Created: 02.11.2016 15:32:12
 *  Author: lassehh
 */ 


#ifndef DAC_H_
#define DAC_H_

#include <stdio.h>

#define MAX520_TWI_ADDRESS 0x50

void DAC_init();
void DAC_write(uint8_t value);

#endif /* DAC_H_ */