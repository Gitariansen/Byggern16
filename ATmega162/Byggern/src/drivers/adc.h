/*
 * adc.h
 *
 * Created: 14.09.2016 10:30:29
 *  Author: elsala
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

// Constants
// ADC channels
#define X_JOYSTICK_CHANNEL		0
#define Y_JOYSTICK_CHANNEL		1
#define LEFT_SLIDER_CHANNEL		2
#define RIGHT_SLIDER_CHANNEL	3

int ADC_init(void);
uint8_t ADC_read(uint8_t chan);

#endif /* ADC_H_ */