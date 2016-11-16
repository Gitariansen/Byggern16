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
	IN_GAME
} state_t;

void set_state(state_t new_state);
state_t get_state();

#endif /* OPTIONS_H_ */