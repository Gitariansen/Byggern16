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
#include "drivers/oled.h"
#include "drivers/timer.h"

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
	uint16_t score = TIMER_time() - start_time;
	
	OLED_reset();
	OLED_printf("GAME OVER!\n");
	OLED_printf("You lasted %d seconds", score/1000);

	_delay_ms(2000);

	set_state(SAVE_USER);
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