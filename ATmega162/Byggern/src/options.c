/*
 * options.c
 *
 * Created: 16.11.2016 12:22:34
 *  Author: elsala
 */ 

#include "options.h"

static state_t state = INITIAL;

void set_state(state_t new_state) {
	if(new_state == MENU) {
		MENU_init();
	}
	state = new_state;
}

state_t get_state() {
	return state;
}