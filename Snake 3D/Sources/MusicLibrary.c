/*
 * MusicLibrary.c
 *
 *  Created on: Jun 16, 2015
 *      Author: tansinan
 */

#include "MusicLibrary.h"
#include "Types.h"

Music MusicLibrary_rainbow;
Music MusicLibrary_test1;
Music MusicLibrary_test2;

static const int8 tune1[] = {7,7,5,4,2,7,4,4,5,4,-1,0,2,4,2,0,4,5,4};
static const int8 duration1[] = {4,1,1,2,2,6,4,2,1,9,4,2,1,1,4,2,1,1,6};

void MusicLibrary_init()
{
	MusicLibrary_rainbow.tune = &tune1;
	MusicLibrary_rainbow.duration = &duration1;
	MusicLibrary_rainbow.length = sizeof(tune1);
	
	MusicLibrary_test1.tune = &tune1;
	MusicLibrary_test1.duration = &duration1;
	MusicLibrary_test1.length = sizeof(tune1);
	
	MusicLibrary_test2.tune = &tune1;
	MusicLibrary_test2.duration = &duration1;
	MusicLibrary_test2.length = sizeof(tune1);
}
