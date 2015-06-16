/*
 * AppMusicGame.c
 *
 *  Created on: Jun 15, 2015
 *      Author: tansinan
 */

#include "AppMusicGame.h"
#include "AppFramework.h"
#include "Button.h"
#include "OLEDFB.h"
#include "Timer.h"

#define STATE_SPLASH  0
#define STATE_SELECT_MUSIC 1
#define STATE_COUNT_DOWN 2
#define STATE_GAME 3
#define STATE_GAMEOVER 4

App AppMusicGame_theApp;

static void paintHandler();

static void eventHandler(int event, int data);

static void animationTimerHandler();

static void setState(int _state);

static uint8 state;

static uint8 animationTimerId;

static uint16 animationCounter;

static int8 speed = 10;
static int8 correctKey = -1;
static int8 pressedKey = -1;
static uint8 mistakeFlag = 0;

static struct
{
	uint16 correctCount;
	uint16 wrongCount;
	uint16 missCount;
} playStat;

static bool lastResult;

static bool currentResult;

static int historyBest = 0x0FFFFFFF;

void AppMusicGame_init()
{
	App_create(&AppMusicGame_theApp, paintHandler, eventHandler);
}

static void paintHandler()
{
	switch(state)
	{
	case STATE_SPLASH:
		if(animationCounter < 50)
		{
			OLEDFB_drawTextEx(100 - 2 * animationCounter, 10, 16, 16, "Music~");
			break;
		}
		OLEDFB_drawTextEx(0, 10, 16, 16, "Music~");
		if(animationCounter > 50 && animationCounter < 150)
		{
			if(animationCounter < 100)
			{
				OLEDFB_drawCircle(50,50,(animationCounter - 50)* 10 / 50,OLEDFB_INVERTED);
			}
			else
			{
				OLEDFB_drawCircle(50,50,10,OLEDFB_INVERTED);
				OLEDFB_drawCircle(90,50,(animationCounter - 100)* 10 / 50,OLEDFB_INVERTED);
			}
			break;
		}
		else if(animationCounter < 200)
		{
			OLEDFB_drawRect(50,0,100,10, OLEDFB_INVERTED);
			OLEDFB_drawRect(50,50,60,10 + (200 - animationCounter),OLEDFB_INVERTED);
			OLEDFB_drawRect(90,50,100,10 + (200 - animationCounter),OLEDFB_INVERTED);
			OLEDFB_drawCircle(50,50,10,OLEDFB_WHITE);
			OLEDFB_drawCircle(90,50,10,OLEDFB_WHITE);
		}
		else
		{
			OLEDFB_drawText(4, 45, "ANYKEY=CONTINUE");
			OLEDFB_drawRect(50,0,100,10, OLEDFB_INVERTED);
			OLEDFB_drawRect(50,50,60,10,OLEDFB_INVERTED);
			OLEDFB_drawRect(90,50,100,10,OLEDFB_INVERTED);
			OLEDFB_drawCircle(50,50,10,OLEDFB_WHITE);
			OLEDFB_drawCircle(90,50,10,OLEDFB_WHITE);
		}
		break;
	case STATE_GAME:
		{
			const char keyToChar[] = {'U','D','L','R','A','B','C','D'};
			
			if(pressedKey!=-1)
			{
				if(correctKey == pressedKey)
				{
					OLEDFB_drawCharEx(64,4,12,12,keyToChar[correctKey]);
				}
				else
				{
					OLEDFB_drawCharEx(64,4,12,12,'X');
				}
			}
			
			int size = animationCounter % 10 <= 5 ?
					(animationCounter % 10 + 3) : ((10 - animationCounter% 10) + 3);
			if(correctKey == KEY_LEFT && pressedKey==-1)
			{
				OLEDFB_drawCharEx(12, 22, 20, 20, 'L');
				OLEDFB_drawRect(12, 22, 32, 42, OLEDFB_INVERTED);
			}
			else OLEDFB_drawRect(12+size, 22+size, 32-size, 42-size, OLEDFB_INVERTED);
			
			if(correctKey == KEY_RIGHT && pressedKey==-1)
			{
				OLEDFB_drawCharEx(32, 22, 20, 20, 'R');
				OLEDFB_drawRect(32, 22, 52, 42, OLEDFB_INVERTED);
			}
			else OLEDFB_drawRect(32 + size, 22 + size, 52 - size, 42 - size, OLEDFB_INVERTED);
			
			if(correctKey == KEY_UP && pressedKey==-1)
			{
				OLEDFB_drawCharEx(22, 2, 20, 20, 'U');
				OLEDFB_drawRect(22, 2, 42, 22, OLEDFB_INVERTED);
			}
			else OLEDFB_drawRect(22 + size, 2 + size, 42 - size, 22 - size, OLEDFB_INVERTED);
			
			if(correctKey == KEY_DOWN && pressedKey==-1)
			{
				OLEDFB_drawCharEx(22, 42, 20, 20, 'D');
				OLEDFB_drawRect(22, 42, 42, 62, OLEDFB_INVERTED);
			}
			else OLEDFB_drawRect(22 + size, 42 + size, 42 - size, 62 - size, OLEDFB_INVERTED);
			
			if(correctKey == KEY_A && pressedKey==-1)
			{
				OLEDFB_drawCharEx(76, 12, 20, 20, 'A');
				OLEDFB_drawCircle(86,22,10,OLEDFB_INVERTED);
			}
			else
			{
				OLEDFB_drawCircle(86,22,size,OLEDFB_INVERTED);
			}
			
			if(correctKey == KEY_C && pressedKey==-1)
			{
				OLEDFB_drawCharEx(76, 34, 20, 20, 'C');
				OLEDFB_drawCircle(86,44,10,OLEDFB_INVERTED);
			}
			else
			{
				OLEDFB_drawCircle(86,44,size,OLEDFB_INVERTED);
			}
			
			if(correctKey == KEY_B && pressedKey==-1)
			{
				OLEDFB_drawCharEx(96, 12, 20, 20, 'B');
				OLEDFB_drawCircle(106,22,10,OLEDFB_INVERTED);
			}
			else
			{
				OLEDFB_drawCircle(106,22,size,OLEDFB_INVERTED);
			}
			
			if(correctKey == KEY_D && pressedKey==-1)
			{
				OLEDFB_drawCharEx(96, 34, 20, 20, 'D');
				OLEDFB_drawCircle(106,44,10,OLEDFB_INVERTED);
			}
			else
			{
				OLEDFB_drawCircle(106,44,size,OLEDFB_INVERTED);
			}
			if(mistakeFlag == 2)
			{
				OLEDFB_drawTextEx(50,48,8,8,"MISS");
			}
			OLEDFB_drawRect(0,60,animationCounter*128/(speed*10),64,OLEDFB_INVERTED);
		}
		case STATE_GAMEOVER:
			break;
	}
}

static void animationTimerHandler()
{
	switch(state)
	{
	case STATE_SPLASH:
		if(animationCounter < 200)
		{
			animationCounter++;
		}
		break;
	case STATE_GAME:
		if(animationCounter < 10 * speed)
		{
			animationCounter++;
		}
		else
		{
			if(pressedKey == -1)
			{
				playStat.missCount++;
				mistakeFlag = 2;
			}
			else mistakeFlag = 3;
			animationCounter = 0;
			correctKey = rand()%8;
			pressedKey = -1;
		}
		break;
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
		switch(state)
		{
		case STATE_SPLASH:
			setState(STATE_GAME);
			break;
		case STATE_GAME:
			if(pressedKey!=-1) break;
			pressedKey = data;
			if(pressedKey == correctKey)
			{
				playStat.correctCount++;
				mistakeFlag = 0;
			}
			else
			{
				playStat.wrongCount++;
				mistakeFlag = 1;
			}
			break;
		}
		break;
	}
}

static void setState(int _state)
{
	switch(_state)
	{
	case STATE_SPLASH:
		animationCounter = 0;
		break;
	case STATE_GAME:
		speed = 10;
		pressedKey = -1;
		correctKey = rand()%7;
		mistakeFlag = 3;
		playStat.correctCount = 0;
		playStat.missCount = 0;
		playStat.wrongCount = 0;
		/*case STATE_READY:
		animationCounter = 0;
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
		break;*/
	}
	state = _state;
}
