/*
 * IncFile1.h
 *
 * Created: 14.09.2016 16:22:46
 *  Author: elsala
 */ 


#ifndef ANALOG_H_
#define ANALOG_H_

typedef struct {
	int x;
	int y;
} joystick_position;

void JOYSTICK_init(void);
joystick_position JOYSTICK_get_position();

#endif /* ANALOG_H_ */