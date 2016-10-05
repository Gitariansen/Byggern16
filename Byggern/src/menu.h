/*
 * menu.h
 *
 * Created: 28.09.2016 07:41:46
 *  Author: elsala
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef struct menu_t {
	char			* name;
	struct menu_t	* parent;
	struct menu_t	** children;
	int				num_children;
	void			* (*function_ptr)(void);
} menu_t;

//const char* const menu_names[] = {"Main menu", "Play game", "Options", "Highscore", "Set Contrast"};
const menu_t main_menu, play_menu, options_menu, highscore_menu, contrast_menu;

void MENU_init();
void MENU_open_menu(menu_t* menu);
void MENU_print_menu();
void MENU_increase_index();
void MENU_decrease_index();
void MENU_perform_action();
void MENU_return_to_parent();

#endif /* MENU_H_ */