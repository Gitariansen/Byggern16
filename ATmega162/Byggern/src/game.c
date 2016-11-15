/*
 * game.c
 *
 * Created: 02.11.2016 13:32:10
 *  Author: lassehh
 */ 

#include "game.h"

const int max_lives = 3;
static int lives;

void GAME_new() {
	lives = max_lives;
}

void GAME_end() {
	printf("You lost!\n");
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