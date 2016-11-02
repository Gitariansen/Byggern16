/*
 * adc.h
 *
 * Created: 02.11.2016 10:48:11
 *  Author: lassehh
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdio.h>

#define IR_CHANNEL 0x00

void ADC_init();
uint8_t ADC_read(uint8_t ch);

#endif /* ADC_H_ */