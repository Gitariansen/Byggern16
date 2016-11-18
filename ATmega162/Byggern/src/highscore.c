/*
 * highscore.c
 *
 * Created: 16.11.2016 14:12:52
 *  Author: elsala
 */ 

#include "ATmega162.h"
#include <util/delay.h>

#include "highscore.h"
#include "menu.h"
#include "drivers/eeprom.h"
#include "drivers/oled.h"

int		num_users;
user_t	user_array[MAX_NUM_USERS];

void HIGHSCORE_load_from_EEPROM() {
	num_users = EEPROM_read(NUM_USERS_ADDRESS);
	
	for(int i = 0; i < num_users; i++) {
		int user_index = i*sizeof(user_t);
		// Read name
		for(int c = 0; c < USERNAME_LENGTH; c++) {
			user_array[i].name[c] = EEPROM_read(USER_START_ADDRESS + user_index + c);
		}
		// Read score
		user_array[i].score = EEPROM_read(USER_START_ADDRESS + user_index + USERNAME_LENGTH);
	}
}

void HIGHSCORE_store_to_EEPROM() {
	EEPROM_write(NUM_USERS_ADDRESS, num_users);
	
	for(int i = 0; i < num_users; i++) {
		int user_index = i*sizeof(user_t);
		for(int c = 0; c < USERNAME_LENGTH; c++) {
			EEPROM_write(USER_START_ADDRESS + c + user_index, user_array[i].name[c]);
		}
		EEPROM_write(USER_START_ADDRESS + user_index + USERNAME_LENGTH, user_array[i].score);
	}
}

void HIGHSCORE_clear() {
	for(int i = 0; i < num_users; i++) {
		int user_index = i*sizeof(user_t);
		
		for(int c = 0; c < USERNAME_LENGTH; c++) {
			EEPROM_write(USER_START_ADDRESS + user_index + c, 0);
		}
		EEPROM_write(USER_START_ADDRESS + user_index + USERNAME_LENGTH, 0);
		num_users--;
	}
	
	if(num_users == 0) {
		printf("Clear succeeded\n");
		EEPROM_write(NUM_USERS_ADDRESS, 0);
	} else {
		printf("Clear failed\n");
	}
}

void HIGHSCORE_add_user(user_t user) {
	if(num_users < MAX_NUM_USERS) {
		num_users++;
	}
	user_array[num_users - 1] = user;

	qsort(user_array, num_users, sizeof(user_t), compare);
}

void HIGHSCORE_print_to_oled() {
	OLED_reset();
	OLED_printf("Nr    Name  Time\n");
	for(int i = 0; i < MAX_NUM_USERS; i++) {
		if(i < num_users) {
			OLED_printf("%d.    ", i + 1);
			OLED_printf("%c%c%c   ", user_array[i].name[0], user_array[i].name[1], user_array[i].name[2]);
			OLED_printf("%d\n", user_array[i].score);
		} else {
			OLED_printf("%d.\n", i + 1);
		}
	}
	_delay_ms(2000);
	MENU_print_menu();
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