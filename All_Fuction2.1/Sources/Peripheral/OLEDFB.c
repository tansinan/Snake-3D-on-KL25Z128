#include "OLEDFB.h"

//8x128 bytes frame buffer
uint8 OLEDFB_frameBuffer[1024];

void OLEDFB_setPixel(uint8 x, uint8 y)
{
	//Prevent illegal pixel operation that is out of range(128x64).
	if (x >= 128 || y >= 64) return;

	//if (value == 0)
		OLEDFB_frameBuffer[y / 8 * 128 + x] &= ~(1 << (y % 8));
	//else
	//	OLEDFB_frameBuffer[y / 8 * 128 + x] |= (1 << (y % 8));
}

void OLEDFB_setPixelEx(int x, int y, uint8 mode)
{
	//Prevent illegal pixel operation that is out of range(128x64).
	if (x >= 128 || y >= 64) return;
	
	//TODO : not finished.
}
