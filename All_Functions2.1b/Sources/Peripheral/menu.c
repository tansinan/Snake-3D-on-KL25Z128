/*
 * menu.c
 *
 *  Created on: May 22, 2015
 *      Author: leo
 */

#include "Includes.h"
void (*current_operation_index)(); 

Menu* currentMenu = NULL;
App OLED_MENU_app;

void OLED_MENU_setRoot(Menu* menu)
{
	currentMenu = menu;
}

void OLED_MENU_buildMenu(Menu* menu, char* title)
{
	menu->parent = NULL;
	menu->entryCount = 0;
	menu->selectedEntry = 0;
	menu->title = title;
}

void OLED_MENU_drawMenu()
{
	if(currentMenu == NULL) return;
	OLED_W_Str(0, 0, "::");
	OLED_W_Str(0, 16, currentMenu->title);
	for(int i = 0; i < currentMenu->entryCount; i++)
	{
		OLED_W_Str(i + 1, 8, currentMenu->entries[i]);
		if( i == currentMenu->selectedEntry)
		{
			OLED_W_Str(i + 1, 0, "*");
		}
		else
		{
			OLED_W_Str(i + 1, 0, " ");
		}
	}
}

void OLED_MENU_onKeyPressed(char key)
{
	if(currentMenu == NULL) return;
	switch(key)
	{
	case KEY_UP:
		if(currentMenu->selectedEntry > 0)
		{
			currentMenu->selectedEntry --;
		}
		break;
	case KEY_DOWN:
		if(currentMenu->selectedEntry < currentMenu->entryCount-1)
		{
			currentMenu->selectedEntry ++;
		}
		break;
	case KEY_RIGHT:
		if(currentMenu->children[currentMenu->selectedEntry] != NULL)
		{
			OLED_Clr();
			currentMenu = currentMenu->children[currentMenu->selectedEntry];
		}
		else if(currentMenu->childrenApplication[currentMenu->selectedEntry] != NULL)
		{
			OLED_Clr();
			App_switchTo(currentMenu->childrenApplication[currentMenu->selectedEntry]);
			void* p = &AppSensorTest_app;
		}
		break;
	case KEY_LEFT:
		if(currentMenu->parent != NULL)
		{
			OLED_Clr();
			currentMenu = currentMenu->parent;
		}
	}
}

void OLED_MENU_init()
{
	App_create(&OLED_MENU_app, OLED_MENU_drawMenu, OLED_MENU_onKeyPressed);
}

App* OLED_MENU_getApp()
{
	return &OLED_MENU_app;
}

/*void main()  
{  
	OLED_Init();
	OLED_Clr();//清屏
	while(1)  
	{  
	if((keyup==0)||(keydown==0)||(keyenter==0)) 
	{ 
		delay(10);//消抖 
		if(keyup==0) 
		{ 
			func_index=table[func_index].up; //向上翻
			while(!keyup);//松手检测 
		 } 
		if(keydown==0) { 
			func_index=table[func_index].down; //向下翻 
			while(!keydown); 
		}
		
		if(keyenter==0) 
		{
			func_index=table[func_index].enter; //确认 
			while(!keyenter);
		}  
		
		OLED_Clr(); 
	}  
	
	 current_operation_index=table[func_index].current_operation; 
	(*current_operation_index)();//执行当前操作函数 
	}  
}*/
