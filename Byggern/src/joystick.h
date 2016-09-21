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
	int click;
} joystick_state;

void JOYSTICK_init(void);
joystick_state JOYSTICK_get_state();

#endif /* ANALOG_H_ */