/*
 * menu.c
 *
 * Created: 28.09.2016 07:41:30
 *  Author: elsala
 */ 


#include "menu.h"
#include "oled.h"
#include "joystick.h"


menu_t* current_menu;
int selected_index = 0;

const menu_t* const main_menu_children[] = { &play_menu, &options_menu, &highscore_menu };
menu_t main_menu = {
	.name = "Main menu",// menu_names[0]
	.children = main_menu_children,
	.num_children = sizeof(main_menu_children)/sizeof(menu_t*),
};

menu_t play_menu = {
	.name = "Play game",//&menu_names[1]
	.parent = &main_menu,
};

menu_t* options_menu_children[] = { &contrast_menu, &return_menu };
menu_t options_menu = {
	.name = "Options",//&menu_names[2]
	.parent = &main_menu,
	.children = options_menu_children,
	.num_children = sizeof(options_menu_children)/sizeof(menu_t*),
};

menu_t highscore_menu = {
	.name = "Highscore",//&menu_names[3]
	.parent = &main_menu,
};

menu_t contrast_menu = {
	.name = "Set Contrast",//&menu_names[4],
	.parent = &options_menu,
};

menu_t return_menu = {
	.name = "Return",//&menu_names[5],
	.parent = &options_menu,
	.function_ptr = MENU_return_to_parent,
};

void MENU_init() {
	MENU_open_menu(&main_menu);
}

void MENU_open_menu(menu_t* menu) {
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
}

void MENU_increase_index() {
	selected_index = (selected_index + 1) % (current_menu->num_children);
	printf("%d\n%d\n", selected_index, current_menu->num_children);
	MENU_print_menu();
}

void MENU_decrease_index() {
	selected_index = (selected_index - 1) % (current_menu->num_children);
	if(selected_index < 0) {
		selected_index = current_menu->num_children + selected_index;
	}
	printf("%d\n%d\n", selected_index, current_menu->num_children);
	MENU_print_menu();
}

void MENU_perform_action() {
	menu_t* selected_menu = (current_menu->children[selected_index]);
	printf("\n\n%s\n\n",selected_menu->name);
	if(selected_menu->children != NULL) {
		printf("HELLO!");
		MENU_open_menu(selected_menu);
		return;
	}
	selected_menu->function_ptr();
}

void MENU_return_to_parent() {
	printf("FJEOWAJWAO");
	MENU_open_menu(current_menu->parent);
}