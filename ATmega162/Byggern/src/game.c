/*
 * game.c
 *
 * Created: 02.11.2016 13:32:10
 *  Author: lassehh
 */ 

#include "game.h"

static int goals;

void GAME_new() {
	goals = 0;
}

void GAME_score() {
	goals += 1;
}

int GAME_get_goals() {
	return goals;
}