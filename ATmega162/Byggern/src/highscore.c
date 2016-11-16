/*
 * highscore.c
 *
 * Created: 16.11.2016 14:12:52
 *  Author: elsala
 */ 

#include "highscore.h"
#include "drivers/eeprom.h"

int num_users = 0;

void HIGHSCORE_add_user(user_t user) {
	// Get existing highscore list and add new user
	user_t* old_users = HIGHSCORE_get_users();
	user_t users[num_users];
	for(int i = 0; i < num_users; i++) {
		users[i] = old_users[i];
	}
	users[num_users] = user;
	num_users++;
	
	// Sort highscore list
	qsort(users, num_users, sizeof(user_t), compare);
	
	// Store users in EEPROM
	for(int i = 0; i < num_users; i++) {
		for(int j = 0; j < USERNAME_LENGTH; j++) {
			printf("Writing %c\n", users[i].name[j]);
			EEPROM_write(i + j, users[i].name[j]);
		}
		EEPROM_write(i + USERNAME_LENGTH, users[i].score);
	}
}

user_t* HIGHSCORE_get_users() {
	user_t users[num_users];

	for(int i = 0; i < num_users; i++) {
		// Read name
		for(int j = 0; j < USERNAME_LENGTH; j++) {
			users[i].name[j] = EEPROM_read(i + j);
		}
		users[i].name[USERNAME_LENGTH] = '\0';
		// Read score
		users[i].score = EEPROM_read(i + USERNAME_LENGTH);
	}
	return users;
}

int HIGHSCORE_num_users() {
	return num_users;
}

// Implement compare on users for quicksort
int compare(const void* a, const void* b) {
	user_t *user_a = (user_t *)a;
	user_t *user_b = (user_t *)b;
	
	return (user_b->score - user_a->score);
}