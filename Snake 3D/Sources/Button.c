/*
 * Button.c
 *
 *  Created on: Jun 11, 2015
 *      Author: tansinan
 */

#include "derivative.h"
#include "Button.h"
#include "Timer.h"
#include "Types.h"
#include "AppFramework.h"

uint8 keyStatus[8];

void Button_init()
{
	// Port B和Port E使能
	SIM_SCGC5 |= 0x2400;
	
	//配置相关引脚为GPIO并启用上拉电阻
	PORTB_PCR17 = 0x102;
	PORTB_PCR16 = 0x102;
	PORTB_PCR9 = 0x102;
	PORTB_PCR8 = 0x102;
	PORTE_PCR2 = 0x102;
	PORTE_PCR3 = 0x102;
	PORTE_PCR4 = 0x102;
	PORTE_PCR5 = 0x102;
	
	GPIOB_PDDR &= ~(1<<17);
	GPIOB_PDDR &= ~(1<<16);
	GPIOB_PDDR &= ~(1<<9);
	GPIOB_PDDR &= ~(1<<8);
	GPIOE_PDDR &= ~(1<<2);
	GPIOE_PDDR &= ~(1<<3);
	GPIOE_PDDR &= ~(1<<4);
	GPIOE_PDDR &= ~(1<<5);
	
	Timer_set(5, Button_onTimer);
	
	for(int i=0;i<8;i++)
	{
		keyStatus[i] = 0;
	}
}

void Button_onTimer()
{
	if((GPIOB_PDIR&(1<<17))==0)
	{
		if(keyStatus[KEY_UP] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+17771));
			App_sendMessage(EVENT_KEY_DOWN, KEY_UP);
		}
		keyStatus[KEY_UP] = 1;
	}
	else
	{
		keyStatus[KEY_UP] = 0;
	}
	
	if((GPIOB_PDIR&(1<<16))==0)
	{
		if(keyStatus[KEY_LEFT] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+41991));
			App_sendMessage(EVENT_KEY_DOWN, KEY_LEFT);
		}
		keyStatus[KEY_LEFT] = 1;
	}
	else
	{
		keyStatus[KEY_LEFT] = 0;
	}
	
	if((GPIOB_PDIR&(1<<9))==0)
	{
		if(keyStatus[KEY_DOWN] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+17991));
			App_sendMessage(EVENT_KEY_DOWN, KEY_DOWN);
		}
		keyStatus[KEY_DOWN] = 1;
	}
	else
	{
		keyStatus[KEY_DOWN] = 0;
	}
	
	if((GPIOB_PDIR&(1<<8))==0)
	{
		if(keyStatus[KEY_RIGHT] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+14891));
			App_sendMessage(EVENT_KEY_DOWN, KEY_RIGHT);
		}
		keyStatus[KEY_RIGHT] = 1;
	}
	else
	{
		keyStatus[KEY_RIGHT] = 0;
	}
	
	if((GPIOE_PDIR&(1<<2))==0)
	{
		if(keyStatus[KEY_A] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+17291));
			App_sendMessage(EVENT_KEY_DOWN, KEY_A);
		}
		keyStatus[KEY_A] = 1;
	}
	else
	{
		keyStatus[KEY_A] = 0;
	}
	
	if((GPIOE_PDIR&(1<<3))==0)
	{
		if(keyStatus[KEY_B] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+60991));
			App_sendMessage(EVENT_KEY_DOWN, KEY_B);
		}
		keyStatus[KEY_B] = 1;
	}
	else
	{
		keyStatus[KEY_B] = 0;
	}
	
	if((GPIOE_PDIR&(1<<4))==0)
	{
		if(keyStatus[KEY_C] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+33413));
			App_sendMessage(EVENT_KEY_DOWN, KEY_C);
		}
		keyStatus[KEY_C] = 1;
	}
	else
	{
		keyStatus[KEY_C] = 0;
	}
	
	if((GPIOE_PDIR&(1<<5))==0)
	{
		if(keyStatus[KEY_D] == 0)
		{
			srand(rand()&(Timer_getSystemTime()+17991));
			App_sendMessage(EVENT_KEY_DOWN, KEY_D);
		}
		keyStatus[KEY_D] = 1;
	}
	else
	{
		keyStatus[KEY_D] = 0;
	}
}
