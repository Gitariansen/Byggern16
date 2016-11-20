/*
 * menu.c
 *
 * Created: 28.09.2016 07:41:30
 *  Author: elsala
 */ 


#include "menu.h"
#include "game.h"
#include "highscore.h"
#include "options.h"
#include "drivers/oled.h"

// Menus are statically allocated at compile time to avoid overflow issues
menu_t main_menu, play_menu, options_menu, highscore_menu, contrast_menu, contrast_high_menu, contrast_medium_menu, contrast_low_menu, clear_highscore_menu, ultrasound_menu, ultrasound_on_menu, ultrasound_off_menu;

menu_t* current_menu;
int selected_index = 0;

menu_t* main_menu_children[] = { &play_menu, &options_menu, &highscore_menu };
menu_t main_menu = {
	.name = "Main menu",
	.children = main_menu_children,
	.num_children = sizeof(main_menu_children)/sizeof(menu_t*),
};

menu_t play_menu = {
	.name = "Play game",
	.parent = &main_menu,
	.function_ptr = (&GAME_new),
};


menu_t highscore_menu = {
	.name = "Highscore",
	.parent = &main_menu,
	.function_ptr = &HIGHSCORE_print_to_oled,
};

menu_t* options_menu_children[] = { &contrast_menu, &clear_highscore_menu, &ultrasound_menu };
menu_t options_menu = {
	.name = "Options",
	.parent = &main_menu,
	.children = options_menu_children,
	.num_children = sizeof(options_menu_children)/sizeof(menu_t*),
};

menu_t* contrast_menu_children[] = { &contrast_high_menu, &contrast_medium_menu, &contrast_low_menu };
menu_t contrast_menu = {
	.name = "Set Contrast",
	.parent = &options_menu,
	.children = &contrast_menu_children,
	.num_children = sizeof(contrast_menu_children)/sizeof(menu_t*),
};

void contrast_high_handler() { OLED_set_contrast(HIGH_CONTRAST); }
menu_t contrast_high_menu = {
	.name = "High",
	.parent = &contrast_menu,
	.function_ptr = &contrast_high_handler
};

void contrast_medium_handler() { OLED_set_contrast(MEDIUM_CONTRAST); }
menu_t contrast_medium_menu = {
	.name = "Medium",
	.parent = &contrast_menu,
	.function_ptr = &contrast_medium_handler
};

void contrast_low_handler() { OLED_set_contrast(LOW_CONTRAST); }
menu_t contrast_low_menu = {
	.name = "Low",
	.parent = &contrast_menu,
	.function_ptr = &contrast_low_handler
};

menu_t clear_highscore_menu = {
	.name = "Clear Highscore",
	.parent = &options_menu,
	.function_ptr = &HIGHSCORE_clear
};

menu_t* ultrasound_menu_children[] = { &ultrasound_on_menu, &ultrasound_off_menu };
menu_t ultrasound_menu = {
	.name = "Ultrasound",
	.parent = &options_menu,
	.children = &ultrasound_menu_children,
	.num_children = sizeof(ultrasound_menu_children)/sizeof(menu_t*),
};

void ultrasound_on_handler() { OPTIONS_set_use_ultrasound(1); }
menu_t ultrasound_on_menu = {
	.name = "Ultrasound on",
	.parent = &ultrasound_menu,
	.function_ptr = &ultrasound_on_handler
};

void ultrasound_off_handler() { OPTIONS_set_use_ultrasound(0); }
menu_t ultrasound_off_menu = {
	.name = "Ultrasound off",
	.parent = &ultrasound_menu,
	.function_ptr = &ultrasound_off_handler
};

void MENU_init() {
	OLED_init();
	MENU_open_menu(&main_menu);
}

void MENU_open_menu(menu_t* menu) {
	if(menu == NULL) {
		return;
	}
	current_menu = menu;
	selected_index = 0;
	MENU_print_menu();
}

void MENU_print_menu() {
	OLED_reset();
	for(int i = 0; i < current_menu->num_children; i++) {
		if(i == selected_index) {
			OLED_printf("%s *\n", current_menu->children[i]->name);
		} else {
			OLED_printf("%s\n", current_menu->children[i]->name);
		}
	}
	if(current_menu->parent != NULL) {
		OLED_printf("<-\n");
	}
}

void MENU_increase_index() {
	selected_index = (selected_index + 1) % (current_menu->num_children);
	MENU_print_menu();
}

void MENU_decrease_index() {
	selected_index = (selected_index - 1) % (current_menu->num_children);
	if(selected_index < 0) {
		selected_index = current_menu->num_children + selected_index;
	}
	MENU_print_menu();
}

void MENU_perform_action() {
	menu_t* selected_menu = (current_menu->children[selected_index]);
	if(selected_menu->children != NULL) {
		MENU_open_menu(selected_menu);
	} else if(selected_menu->function_ptr != NULL) {
		selected_menu->function_ptr();
	}
}

void MENU_return_to_parent() {
	if(current_menu->parent != NULL) {
		MENU_open_menu(current_menu->parent);
	}
}