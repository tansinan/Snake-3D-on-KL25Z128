/*
 * Menu.h
 *
 *  Created on: May 22, 2015
 *      Author: tansinan
 */

#ifndef MENU_H_
#define MENU_H_

#include "AppFramework.h"

typedef struct Menu
{
	struct Menu* parent;
	char* title;
	char entryCount;
	char selectedEntry;
	char** entries;
	struct Menu** children;
	App** childrenApplication;
} Menu;

void OLED_MENU_buildMenu(Menu* menu, char* title);
void OLED_MENU_setRoot(Menu* menu);
void OLED_MENU_drawMenu();
void OLED_MENU_onKeyPressed(char key);
void OLED_MENU_init();
App* OLED_MENU_getApp();

#endif /* MENU_H_ */
