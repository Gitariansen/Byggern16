/*
 * options.h
 *
 * Created: 16.11.2016 12:22:23
 *  Author: elsala
 */ 


#ifndef OPTIONS_H_
#define OPTIONS_H_

typedef enum {
	INITIAL,
	MENU,
	IN_GAME,
	SAVE_USER
} state_t;

void OPTIONS_set_state(state_t new_state);
state_t OPTIONS_get_state();

void OPTIONS_set_use_ultrasound(int value);
int OPTIONS_use_ultrasound();

#endif /* OPTIONS_H_ */