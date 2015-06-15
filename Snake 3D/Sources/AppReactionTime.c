/*
 * AppReactionTime.c
 *
 *  Created on: Jun 14, 2015
 *      Author: tansinan
 */

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


static void paintHandler();

static void eventHandler();

static struct
{
	uint8 state;
	uint8 splashAnimationCounter;
	int countDownNumber;
	int countDownDuration;
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
	}
}
static void eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		gameData.state = STATE_SPLASH;
		gameData.splashAnimationCounter = 0;
		animationTimerId = Timer_set(20, animationTimerHandler);
		break;
	case EVENT_APP_QUIT:
		Timer_unset(animationTimerId);
		break;
	case EVENT_KEY_DOWN:
		if(gameData.state == STATE_SPLASH) setState(STATE_READY);
		break;
	}
}

static void animationTimerHandler()
{
	if(gameData.state == STATE_SPLASH && gameData.splashAnimationCounter < 100)
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
	}
	gameData.state = _state;
}
