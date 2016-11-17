/*
 * highscore.c
 *
 * Created: 16.11.2016 14:12:52
 *  Author: elsala
 */ 

#include "highscore.h"
#include "drivers/eeprom.h"

int		num_users;
user_t	user_array[MAX_NUM_USERS];

void HIGHSCORE_load_from_EEPROM() {
	num_users = EEPROM_read(NUM_USERS_ADDRESS);
	
	for(int i = 0; i < num_users; i++) {
		int user_index = i*(sizeof(user_t) - 1);
		// Read name
		for(int c = 0; c < USERNAME_LENGTH; c++) {
			user_array[i].name[c] = EEPROM_read(USER_START_ADDRESS + user_index + c);
		}
		user_array[i].name[USERNAME_LENGTH] = '\0';
		// Read score
		user_array[i].score = EEPROM_read(USER_START_ADDRESS + user_index + USERNAME_LENGTH);
	}
}

void HIGHSCORE_store_to_EEPROM() {
	EEPROM_write(USER_START_ADDRESS, num_users);
	
	for(int i = 0; i < num_users; i++) {
		int user_index = i*4;
		for(int c = 0; c < USERNAME_LENGTH; c++) {
			EEPROM_write(USER_START_ADDRESS + c + user_index, user_array[i].name[c]);
		}
		EEPROM_write(USER_START_ADDRESS + user_index + USERNAME_LENGTH, user_array[i].score);
	}
}

void HIGHSCORE_clear() {
	for(int i = 0; i < num_users; i++) {
		int user_index = i*(sizeof(user_t) - 1);
		
		for(int c = 0; c < USERNAME_LENGTH; c++) {
			EEPROM_write(USER_START_ADDRESS + user_index + c, 0);
		}
		EEPROM_write(USER_START_ADDRESS + user_index + USERNAME_LENGTH, 0);
		num_users--;
	}
	
	if(num_users == 0) {
		printf("Clear succeeded\n");
		EEPROM_write(USER_START_ADDRESS, 0);
	} else {
		printf("Clear failed\n");
	}
}

void HIGHSCORE_add_user(user_t user) {
	user_array[num_users] = user;
	if(num_users < MAX_NUM_USERS) {
		num_users++;
	}
	qsort(user_array, num_users, sizeof(user_t), compare);
}

user_t* HIGHSCORE_get_users() {
	return user_array;
}

int HIGHSCORE_get_num_users() {
	return num_users;
}

// Implement compare on users for quicksort
int compare(const void* a, const void* b) {
	user_t *user_a = (user_t *)a;
	user_t *user_b = (user_t *)b;
	
	return (user_b->score - user_a->score);
}