/*
 * AppReactionTime.c
 *
 *  Created on: Jun 14, 2015
 *      Author: tansinan
 */

#include <stdio.h>

#include "AppReactionTime.h"
#include "AppFramework.h"
#include "Button.h"
#include "OLEDFB.h"
#include "Timer.h"

#define STATE_SPLASH  0
#define STATE_READY  1
#define STATE_COUNT_DOWN 2
#define STATE_GAME 3
#define STATE_GAMEOVER 4

static const char* startText1 = "Are you?";
static const char* startText2 = "QUICK?";
static const char* startText3 = "ANYKEY=CONTINUE";
static const char* readyText1 = "READY?";
static const char* readyText2 = "A = GO!";
static const char* readyText3 = "D = EXIT";

static void animationTimerHandler();

static void setState(int _state);

static uint8 animationTimerId;

static int gameBeginTime;

static int keyPressedTime;

static int historyBest = 0x0FFFFFFF;

static void paintHandler();

static void eventHandler(int event, int data);

static struct
{
	uint8 state;
	uint8 splashAnimationCounter;
	int countDownNumber;
	int gameTimer;
} gameData;

void AppReactionTime_init()
{
	App_create(&AppReactionTime_theApp, paintHandler, eventHandler);
}

static void paintHandler()
{
	switch(gameData.state)
	{
	case STATE_SPLASH:
		if(gameData.splashAnimationCounter < 50)
		{
			OLEDFB_drawTextEx(100 - 2 * gameData.splashAnimationCounter, 10, 12, 12, startText1);
		}
		else if(gameData.splashAnimationCounter < 100)
		{
			OLEDFB_drawTextEx(0, 10, 12, 12, startText1);
			OLEDFB_drawTextEx(gameData.splashAnimationCounter - 50, 30, 12, 12, startText2);
		}
		else
		{
			OLEDFB_drawTextEx(0, 10, 12, 12, startText1);
			OLEDFB_drawTextEx(50, 30, 12, 12, startText2);
			OLEDFB_drawText(4, 45, startText3);
		}
		OLEDFB_drawCircle(64,32,31,OLEDFB_INVERTED);
		break;
	case STATE_READY:
		OLEDFB_drawTextEx(10, 10, 12, 12, readyText1);
		OLEDFB_drawText(35,44, readyText2);
		OLEDFB_drawText(35,54, readyText3);
		for(int i = 0;i < 5;i++)
		{
			OLEDFB_drawRect(12*i+12*(i+1), 27, 12*(i+1)+12*(i+1), 39, OLEDFB_WHITE);
		}
		if(gameData.splashAnimationCounter == 0)
		{
			gameData.splashAnimationCounter = 0;
		}
		break;
	case STATE_COUNT_DOWN:
		OLEDFB_drawCharEx(32, 0, 64, 64, '0' + gameData.countDownNumber);
		OLEDFB_drawCircle(64,32,gameData.splashAnimationCounter,OLEDFB_INVERTED);
		if(gameData.splashAnimationCounter >= 50)
		{
			gameData.splashAnimationCounter = 0;
			if(gameData.countDownNumber > 0)
			{
				gameData.countDownNumber--;
			}
			if(gameData.countDownNumber == 0)
			{
				setState(STATE_GAME);
			}
		}
		break;
	case STATE_GAME:
		OLEDFB_drawTextEx(4, 12, 40, 40, "GO!");
		if(gameBeginTime == 0)
		{
			OLEDFB_flush();
			gameBeginTime = Timer_getSystemTime();
		}
		break;
	case STATE_GAMEOVER:
		{
			char temp[30];
			int duration = keyPressedTime - gameBeginTime;
			OLEDFB_drawTextEx(4,4, 16,16, "TIME:");
			sprintf(temp, "%d.%d%d%d", duration/1000, (duration/100)%10, (duration/10)%10, duration%10);
			if(keyPressedTime!=0)
			{
				OLEDFB_drawTextEx(20,20, 16,16, temp);
				if(duration < historyBest)
				{
					OLEDFB_drawText(20,48,"New Record!");
				}
				else
				{
					sprintf(temp, "History Best:");
					OLEDFB_drawText(20,48,temp);
					sprintf(temp, "%d.%d%d%d", historyBest/1000, (historyBest/100)%10, (historyBest/10)%10, historyBest%10);
					OLEDFB_drawText(28,56,temp);
				}
			}
			else
			{
				OLEDFB_drawTextEx(4,4, 16,16, "TIME:");
				OLEDFB_drawTextEx(20,20, 16,16, "+INF...");
				/*sprintf(temp, "History Best:");
				OLEDFB_drawText(20,48,temp);
				sprintf(temp, "%d.%d%d%d", historyBest/1000, (historyBest/100)%10, (historyBest/10)%10, historyBest%10);
				OLEDFB_drawText(28,56,temp);*/
			}
			break;
		}
	}
}

static void eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		animationTimerId = Timer_set(20, animationTimerHandler);
		setState(STATE_SPLASH);
		break;
	case EVENT_APP_QUIT:
		Timer_unset(animationTimerId);
		break;
	case EVENT_KEY_DOWN:
		switch(gameData.state)
		{
		case STATE_SPLASH:
			setState(STATE_READY);
			break;
		case STATE_READY:
			if(data == KEY_A) setState(STATE_COUNT_DOWN);
			//TODO : Implement return to menu.
			else if(data == KEY_D);
			break;
		case STATE_COUNT_DOWN:
			//TODO : Implement return to menu.
			if(data == KEY_D);
			keyPressedTime = gameBeginTime = 0;
			setState(STATE_GAMEOVER);
			break;
		case STATE_GAME:
			if(keyPressedTime == 0) keyPressedTime = Timer_getSystemTime();
			setState(STATE_GAMEOVER);
			break;
		case STATE_GAMEOVER:
			if(keyPressedTime - gameBeginTime < historyBest)
			{
				historyBest = keyPressedTime - gameBeginTime;
			}
			if(data == KEY_A) setState(STATE_READY);
			//TODO : Implement return to menu.
			else if(data == KEY_D);
			break;
		}
		break;
	}
}

static void animationTimerHandler()
{
	if(gameData.splashAnimationCounter < 100)
	{
		gameData.splashAnimationCounter++;
	}
}

static void setState(int _state)
{
	switch(_state)
	{
	case STATE_SPLASH:
		gameData.splashAnimationCounter = 0;
		break;
	case STATE_READY:
		gameData.splashAnimationCounter = 0;
		break;
	case STATE_COUNT_DOWN:
		gameData.splashAnimationCounter = 0;
		gameData.countDownNumber = 3;
		break;
	case STATE_GAME:
		gameBeginTime = 0;
		keyPressedTime = 0;
		break;
	case STATE_GAMEOVER:
		break;
	}
	gameData.state = _state;
}
