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

#define STATE_SPLASH  0
#define STATE_READY  1
#define STATE_COUNT_DOWN 2
#define STATE_GAME 3
#define STATE_GAMEOVER 4

static const char* startText1 = "Are you?";
static const char* startText2 = "QUICK?";
static void animationHandler();
static uint8 animationTimerId;


static void paintHandler();

static void eventHandler();

static struct
{
	uint8 state;
	int startAnimationStage;
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
		OLEDFB_drawTextEx(0, 0, 12, 12, startText1);
		OLEDFB_drawTextEx(20, 20, 12, 12, startText2);
		break;
	}
}
static void eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		gameData.state = STATE_SPLASH;
		animationTimerId = Timer_set(50);
		break;
	case EVENT_APP_QUIT:
		Timer_unset(animationTimerId);
		break;
	}
}

static void animationTimerHandler();
