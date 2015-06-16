/*
 * Music.c
 *
 *  Created on: Jun 16, 2015
 *      Author: tansinan
 */

#include "Buzzer.h"
#include "Music.h"
#include "Timer.h"
#include "Types.h"

int frequencyTable[] = {523,554,587,622,659,698,740,784,831,880,932,988};

static Music* currentMusic = NULL;

static int tuneCounter = 0;
static int currentTune = 0;
static int loopCount = 0;
static int loopTotal = 0;
static uint8 timerId = 0xFF;


static void timerHandler();

void Music_play(Music* music, int loop)
{
	if(currentMusic != NULL)
	{
		return;
	}
	currentMusic = music;
	loopTotal = loop;
	
	timerId = Timer_set(10, timerHandler);
	tuneCounter = currentTune = loopCount = 0;
	Buzzer_set(frequencyTable[currentMusic->tune[0]], 50);
}

void Music_stop()
{
	if(timerId != 0xFF)
	{
		Buzzer_set(0,0);
		currentMusic = NULL;
		Timer_unset(timerId);
	}
}

static void timerHandler()
{
	if(currentTune >= currentMusic->length) return;
	tuneCounter ++ ;
	if(tuneCounter >= currentMusic->duration[currentTune] * 20)
	{
		tuneCounter = 0;
		currentTune++;
		if(currentTune < currentMusic->length && currentMusic->tune[currentTune] >= 0)
		{
			Buzzer_set(frequencyTable[currentMusic->tune[currentTune]], 50);
		}
		else 
		{
			if(loopTotal == -1)
			{
				currentTune = 0;
			}
			else if(loopCount < loopTotal - 1)
			{
				loopCount++;
				currentTune = 0;
			}
			else
			{
				Music_stop();
			}
		}
	}
}
