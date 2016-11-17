/*
 * game.c
 *
 * Created: 02.11.2016 13:32:10
 *  Author: lassehh
 */ 

#include "ATmega162.h"
#include <util/delay.h>
#include "game.h"
#include "options.h"
#include "highscore.h"
#include "drivers/oled.h"
#include "drivers/timer.h"
#include "drivers/joystick.h"

const int max_lives = 3;
static int lives;

static uint16_t start_time;
static uint16_t hit_time;

void GAME_new() {
	lives = max_lives;

	OLED_reset();
	OLED_printf("Lives: %d/%d", lives, max_lives);

	// Start timer
	start_time = TIMER_time();
	
	set_state(IN_GAME);
}

void GAME_end() {
	uint16_t time_in_ms = TIMER_time() - start_time;
	
	OLED_reset();
	OLED_printf("GAME OVER!\n");
	OLED_printf("You lasted %d seconds", time_in_ms/1000);

	_delay_ms(2000);

	GAME_save_score(time_in_ms / 1000);
	
	set_state(INITIAL);
}

void GAME_save_score(int score) {
	OLED_reset();
	OLED_printf("Save you score\n");

	user_t user ;
	user.score = score;

	for(int i = 0; i < USERNAME_LENGTH; i++) {
		char c = 'A';

		joystick_state_t joystick_state = JOYSTICK_get_state();
		joystick_state_t old_joystick_state = joystick_state;

		while(1) {
			joystick_state = JOYSTICK_get_state();
			if(JOYSTICK_compare(joystick_state, old_joystick_state)) {
				continue;
			}

			if(joystick_state.y_dirn != old_joystick_state.y_dirn) {
				if(joystick_state.y_dirn == UP) {
					if(c - 1 < 'A') {
						c = 'Z';
						} else {
						c--;
					}
					} if(joystick_state.y_dirn == DOWN) {
					if(c + 1 > 'Z') {
						c = 'A';
						} else {
						c++;
					}
				}
				old_joystick_state.y_dirn = joystick_state.y_dirn;
			}

			OLED_pos(1, i*5);
			OLED_print_char(c);
			
			if(joystick_state.click != old_joystick_state.click && joystick_state.click) {
				old_joystick_state.click = joystick_state.click;
				user.name[i] = c;
				break;
			}

			old_joystick_state = joystick_state;

			_delay_ms(10);
		}
	}
	HIGHSCORE_add_user(user);
	HIGHSCORE_store_to_EEPROM();
}

void GAME_hit() {
	if(hit_time - TIMER_time() < 1000) {
		// Invincible for one second after hit
		return;
	}
	hit_time = TIMER_time();

	lives -= 1;

	OLED_reset();
	OLED_printf("Lives: %d/%d", lives, max_lives);

	if(lives == 0) {
		GAME_end();
	}
}

int GAME_get_lives() {
	return lives;
}