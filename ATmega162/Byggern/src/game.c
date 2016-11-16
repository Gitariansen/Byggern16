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

const int max_lives = 3;
static int lives;

void GAME_new() {
	lives = max_lives;

	OLED_reset();
	OLED_printf("Lives: %d/%d", lives, max_lives);

	set_state(IN_GAME);
}

void GAME_end() {
	OLED_reset();
	OLED_center();
	OLED_printf("GAME OVER!");
	_delay_ms(2000);
	set_state(MENU);
}

void GAME_hit() {
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