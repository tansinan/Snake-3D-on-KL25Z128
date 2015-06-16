/*
 * Music.h
 *
 *  Created on: Jun 16, 2015
 *      Author: tansinan
 */

#ifndef MUSIC_H_
#define MUSIC_H_

extern int Music_frequencyTable[];

typedef struct
{
	const char* tune;
	const char* duration;
	int length;
} Music;

void Music_play(Music* music, int loop);

void Music_stop();

#endif /* MUSIC_H_ */