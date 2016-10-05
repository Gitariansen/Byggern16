/*
 * IncFile1.h
 *
 * Created: 14.09.2016 16:22:46
 *  Author: elsala
 */ 


#ifndef ANALOG_H_
#define ANALOG_H_

typedef enum {LEFT, RIGHT, X_NEUTRAL} x_dirn_t;
typedef enum {UP, DOWN, Y_NEUTRAL} y_dirn_t;

typedef struct {
	int x;
	x_dirn_t x_dirn;
	int y;
	y_dirn_t y_dirn;
	int click;
} joystick_state_t;

void JOYSTICK_init(void);
joystick_state_t JOYSTICK_get_state();

#endif /* ANALOG_H_ */