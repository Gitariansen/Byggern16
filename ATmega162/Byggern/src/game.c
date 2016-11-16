/*
 * game.c
 *
 * Created: 02.11.2016 13:32:10
 *  Author: lassehh
 */ 

#include "game.h"
#include "options.h"

const int max_lives = 3;
static int lives;

void GAME_new() {
	lives = max_lives;
	set_state(IN_GAME);
}

void GAME_end() {
	printf("Game over!\n");
	set_state(MENU);
}

void GAME_hit() {
	lives -= 1;
	if(lives == 0) {
		GAME_end();
	}
}

int GAME_get_lives() {
	return lives;
}