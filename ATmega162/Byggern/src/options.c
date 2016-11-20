/*
 * options.c
 *
 * Created: 16.11.2016 12:22:34
 *  Author: elsala
 */ 

#include "options.h"
#include "menu.h"

state_t state = INITIAL;
int use_ultrasound = 0;

void OPTIONS_set_state(state_t new_state) {
	if(new_state == MENU) {
		MENU_init();
	}
	state = new_state;
}

state_t OPTIONS_get_state() {
	return state;
}

void OPTIONS_set_use_ultrasound(int value) {
	use_ultrasound = value;
}

int OPTIONS_use_ultrasound() {
	return use_ultrasound;
}