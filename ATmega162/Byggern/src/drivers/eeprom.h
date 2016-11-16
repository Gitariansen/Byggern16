/*
 * eeprom.h
 *
 * Created: 16.11.2016 15:32:18
 *  Author: elsala
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdio.h>

void EEPROM_write(uint8_t address, uint8_t data);
uint8_t EEPROM_read(uint8_t address);

#endif /* EEPROM_H_ */