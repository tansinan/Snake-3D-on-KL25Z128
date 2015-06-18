/*
 * AppAlarmClock.c
 *
 *  Created on: Jun 15, 2015
 *      Author: tansinan
 */

#include "Types.h"
#include "Button.h"
#include "AppFramework.h"
#include "OLEDFB.h"
#include "Music.h"
#include "MusicLibrary.h"

#define STATE_SET 0
#define STATE_RUNNING 2
#define STATE_PAUSE 3
#define STATE_TIMEOUT 4


typedef struct
{
	int hour;
	int minute;
	int second;
	int csec;
} Time;

static Time timeSet;
int currentSetPos = 0;
static Time timeCurrent;

static int animationCounter = 0;
static int animationTimerId;
static bool pause;

App AppAlarmClock_theApp;

void AppAlarmClock_init();

static void paintHandler();

static void eventHandler(int event, int data);

static void animationTimerHandler();

static void setState(int _state);

static uint8 state;

void AppAlarmClock_init()
{
	timeSet.hour = 0;
	timeSet.minute = 0;
	timeSet.second = 0;
	timeSet.csec = 0;
	App_create(&AppAlarmClock_theApp, paintHandler, eventHandler);
}

static void paintHandler()
{
	int setPosXMap[] = {0,15,45,60,90,105};
	char temp[20];
	switch(state)
	{
	case STATE_SET:
		OLEDFB_drawCharEx(0,10,15,15,timeSet.hour/10+'0');
		OLEDFB_drawCharEx(15,10,15,15,timeSet.hour%10+'0');
		OLEDFB_drawCharEx(30,10,15,15,':');
		OLEDFB_drawCharEx(45,10,15,15,timeSet.minute/10 + '0');
		OLEDFB_drawCharEx(60,10,15,15,timeSet.minute%10 + '0');
		OLEDFB_drawCharEx(75,10,15,15,':');
		OLEDFB_drawCharEx(90,10,15,15,timeSet.second/10+'0');
		OLEDFB_drawCharEx(105,10,15,15,timeSet.second%10 + '0');
		OLEDFB_drawRect(setPosXMap[currentSetPos],10,setPosXMap[currentSetPos]+15,25,OLEDFB_INVERTED);
		OLEDFB_drawText(0,48,"A->START");
		break;
	case STATE_RUNNING:
		OLEDFB_drawCharEx(0,10,15,15,timeCurrent.hour/10+'0');
		OLEDFB_drawCharEx(15,10,15,15,timeCurrent.hour%10+'0');
		OLEDFB_drawCharEx(30,10,15,15,':');
		OLEDFB_drawCharEx(45,10,15,15,timeCurrent.minute/10 + '0');
		OLEDFB_drawCharEx(60,10,15,15,timeCurrent.minute%10 + '0');
		OLEDFB_drawCharEx(75,10,15,15,':');
		OLEDFB_drawCharEx(90,10,15,15,timeCurrent.second/10+'0');
		OLEDFB_drawCharEx(105,10,15,15,timeCurrent.second%10 + '0');
		sprintf(temp,"%d%dcsec", timeCurrent.csec/10,timeCurrent.csec%10);
		OLEDFB_drawText(0,48,"A->PAUSE/RESUME");
		OLEDFB_drawText(0,56,"B->RESET");
		OLEDFB_drawText(60,30,temp);
		break;
	case STATE_TIMEOUT:
		if(animationCounter < 50)
		{
			OLEDFB_drawTextEx(0,10,15,15,"00:00:00");
			OLEDFB_drawText(60,30,"00csec");
		}
		OLEDFB_drawText(0,48,"A->DELAY");
		OLEDFB_drawText(0,56,"B->RESET");
		break;
	}
}

static void eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		animationTimerId = Timer_set(10, animationTimerHandler);
		setState(STATE_SET);
		break;
	case EVENT_APP_QUIT:
		Timer_unset(animationTimerId);
		break;
	case EVENT_KEY_DOWN:
		if(state == STATE_SET)
		{
			switch(data)
			{
			case KEY_RIGHT:
				if(currentSetPos<5) currentSetPos++;
				break;
			case KEY_LEFT:
				if(currentSetPos>0) currentSetPos--;
				break;
			case KEY_UP:
				if(currentSetPos == 0)
				{
					timeSet.hour += 10;
					timeSet.hour %= 100;
				}
				else if(currentSetPos == 1)
				{
					timeSet.hour += 1;
					timeSet.hour %= 100;
				}
				else if(currentSetPos == 2)
				{
					timeSet.minute += 10;
					timeSet.minute %= 60;
				}
				else if(currentSetPos == 3)
				{
					timeSet.minute += 1;
					timeSet.minute %= 60;
				}
				else if(currentSetPos == 4)
				{
					timeSet.second += 10;
					timeSet.second %= 60;
				}
				else if(currentSetPos == 5)
				{
					timeSet.second += 1;
					timeSet.second %= 60;
				}
				break;
			case KEY_DOWN:
				if(currentSetPos == 0)
				{
					timeSet.hour += 90;
					timeSet.hour %= 100;
				}
				else if(currentSetPos == 1)
				{
					timeSet.hour += 99;
					timeSet.hour %= 100;
				}
				else if(currentSetPos == 2)
				{
					timeSet.minute += 50;
					timeSet.minute %= 60;
				}
				else if(currentSetPos == 3)
				{
					timeSet.minute += 59;
					timeSet.minute %= 60;
				}
				else if(currentSetPos == 4)
				{
					timeSet.second += 50;
					timeSet.second %= 60;
				}
				else if(currentSetPos == 5)
				{
					timeSet.second += 59;
					timeSet.second %= 60;
				}
				break;
			case KEY_A:
				if(timeSet.second==0 && timeSet.hour==0 && timeSet.minute ==0) break;
				timeCurrent = timeSet;
				setState(STATE_RUNNING);
				break;
			}
		}
		else if(state == STATE_RUNNING)
		{
			if(data == KEY_B) setState(STATE_SET);
			else if(data == KEY_A) pause = !pause;
		}
		else if(state == STATE_TIMEOUT)
		{
			if(data == KEY_B) setState(STATE_SET);
			else if(data == KEY_A)
			{
				timeCurrent.minute = 5;
				setState(STATE_RUNNING);
			}
		}
		break;
	}
}

static void animationTimerHandler()
{
	if(state == STATE_RUNNING)
	{
		if(pause) return;
		/*if(animationCounter < 100)
		{
			animationCounter++;
		}
		if(animationCounter == 100)
		{*/
			timeCurrent.csec--;
			if(timeCurrent.csec < 0)
			{
				timeCurrent.csec += 100;
				timeCurrent.second--;
			}
			if(timeCurrent.second < 0)
			{
				timeCurrent.second += 60;
				timeCurrent.minute--;
			}
			if(timeCurrent.minute < 0)
			{
				timeCurrent.minute += 60;
				timeCurrent.hour--;
			}
			if(timeCurrent.hour == 0 && timeCurrent.minute == 0&& timeCurrent.second==0 && timeCurrent.csec==0)
			{
				Music_play(&MusicLibrary_rainbow,-1);
				setState(STATE_TIMEOUT);
			}
		//}
	}
	else if(state == STATE_PAUSE)
	{
		if(animationCounter < 100)
		{
			animationCounter++;
		}
		else
		{
			animationCounter =0;
		}
	}
}

static void setState(int _state)
{
	switch(_state)
	{
	case STATE_SET:
		Music_stop();
		animationCounter = 0;
		break;
	case STATE_RUNNING:
		Music_stop();
		pause = false;
		animationCounter = 0;
		break;
	case STATE_TIMEOUT:
		animationCounter = 0;
		break;
	}
	state = _state;
}
