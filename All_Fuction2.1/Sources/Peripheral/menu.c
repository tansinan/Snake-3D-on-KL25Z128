/*
 * menu.c
 *
 *  Created on: May 22, 2015
 *      Author: leo
 */

#include "Includes.h"



 

#define uchar unsigned char 

 

uchar func_index=0; 

void (*current_operation_index)(); 

Menu* currentMenu = NULL;

typedef struct { 
uchar current; 
uchar up;//���Ϸ������� 
uchar down;//���·������� 
uchar enter;//ȷ�������� 
void (*current_operation)(); 
} key_table; 


/*key_table table[]= {  
{0,2,1,3,(*fun1)},//��һ�㪤��ʾ���廪��ѧ��.������ѧ,���� 
{1,0,2,2,(*fun2)},//��һ�㪤��ʾ�廪��ѧ����������ѧ��,����
{2,1,0,3,(*fun4)},//��һ�㪤��ʾ�廪��ѧ��������ѧ,�����ء� 
{3,7,3,3,(*fun5)},//�ڶ��㪤�廪��ѧ������ʾ���ص㡿������ʱ�䡢��顢����  

}; */

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
		if(&currentMenu->children[currentMenu->selectedEntry] != NULL)
		{
			OLED_Clr();
			currentMenu = currentMenu->children[currentMenu->selectedEntry];
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

/*void main()  
{  
	OLED_Init();
	OLED_Clr();//����
	while(1)  
	{  
	if((keyup==0)||(keydown==0)||(keyenter==0)) 
	{ 
		delay(10);//���� 
		if(keyup==0) 
		{ 
			func_index=table[func_index].up; //���Ϸ�
			while(!keyup);//���ּ�� 
		 } 
		if(keydown==0) { 
			func_index=table[func_index].down; //���·� 
			while(!keydown); 
		}
		
		if(keyenter==0) 
		{
			func_index=table[func_index].enter; //ȷ�� 
			while(!keyenter);
		}  
		
		OLED_Clr(); 
	}  
	
	 current_operation_index=table[func_index].current_operation; 
	(*current_operation_index)();//ִ�е�ǰ�������� 
	}  
}*/
