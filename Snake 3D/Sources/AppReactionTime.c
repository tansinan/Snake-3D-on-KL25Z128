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

static const startText1 = "Are you?";
static const startText2 = "QUICK?";

static struct
{
	int state;
	int startAnimationStage;
	int countDownNumber;
	int countDownDuration;
	int gameTimer;
} gameData;


void AppReactionTime_init()
{
	
}

void AppReactionTime_onDrawHandler()
{
	OLEDFB_drawTextEx(0, 0, 12, 12, "Are you swift?");
	OLEDFB_draw
}
void AppReactionTime_eventHandler(int event, int data)
{
	switch(event)
	{
	case EVENT_APP_INIT:
		break;
	case EVENT_APP_QUIT:
		break;
	}
}
