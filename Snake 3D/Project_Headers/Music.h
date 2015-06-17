/*
 * Music.h
 *
 *  Created on: Jun 16, 2015
 *      Author: tansinan
 */

#ifndef MUSIC_H_
#define MUSIC_H_

extern int frequencyTable[];

typedef struct
{
	const char* tune;
	const char* duration;
	int length;
	const char* name;
} Music;

void Music_play(Music* music, int loop);

void Music_stop();

#endif /* MUSIC_H_ */
