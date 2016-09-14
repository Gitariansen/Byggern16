/*
 * IncFile1.h
 *
 * Created: 14.09.2016 16:22:46
 *  Author: elsala
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

typedef struct {
	int x_pos;
	int y_pos;
} joystick;

typedef struct {
	int left;
	int right;
} slider;

void ANALOG_init(void);
joystick ANALOG_get_joystick();
slider ANALOG_get_slider();

#endif /* INCFILE1_H_ */