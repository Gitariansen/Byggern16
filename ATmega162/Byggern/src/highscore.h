/*
 * highscore.h
 *
 * Created: 16.11.2016 14:12:31
 *  Author: elsala
 */ 


#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <stdio.h>

#define USERNAME_LENGTH	3
#define MAX_NUM_USERS	10

typedef struct user_t {
	char		name[USERNAME_LENGTH + 1];
	uint8_t		score;
} user_t;

void HIGHSCORE_add_user(user_t user);
user_t* HIGHSCORE_get_users();

int compare(const void* a, const void* b);

#endif /* HIGHSCORE_H_ */