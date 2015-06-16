/*
 * OLEDFB.c
 *
 *  Created on: May 28, 2015
 *      Author: tansinan
 */

#include "OLED.h"
#include "OLEDFB.h"
#include "OLEDFONT.h"

//8x128 bytes frame buffer
uint8 OLEDFB_frameBuffer[1024];

void OLEDFB_init()
{
	OLEDFB_clear();
	OLEDFB_flush();
}

void OLEDFB_clear()
{
	uint32* tmp = OLEDFB_frameBuffer;
	for(uint16 i = 0;i<=0xFF;i++)
	{
		tmp[i] = 0;
	}
}

void OLEDFB_flush()
{
	for(uint16 i=0;i<8;i++)
	{
		//制定写入的行
		OLED_W_Ctl(0xB0 + i);
		
		//分两次指定写入的列的低字节和高字节
		OLED_W_Ctl(0x00);
		OLED_W_Ctl(0x10);	
		for(uint16 j=i*128;j<i*128+128;j++)
		{
			OLED_W_Dat(OLEDFB_frameBuffer[j]);
		}
	}
}

void OLEDFB_setPixelBlack(uint8 x, uint8 y)
{
	//Prevent illegal pixel operation that is out of range(128x64).
	if (x >= 128 || y >= 64) return;
	
	//Set corresponding bit to 1
	OLEDFB_frameBuffer[y / 8 * 128 + x] &= ~(1 << (y % 8));
}

void OLEDFB_setPixelWhite(uint8 x, uint8 y)
{
	//Prevent illegal pixel operation that is out of range(128x64).
	if (x >= 128 || y >= 64) return;
	
	//Set corresponding bit to 0
	OLEDFB_frameBuffer[y / 8 * 128 + x] |= (1 << (y % 8));
}

void OLEDFB_setPixelInverted(uint8 x, uint8 y)
{
	//Prevent illegal pixel operation that is out of range(128x64).
	if (x >= 128 || y >= 64) return;
	
	//Set corresponding bit inverted
	OLEDFB_frameBuffer[y / 8 * 128 + x] ^= (1 << (y % 8));
}

//TODO : not finished
void OLEDFB_setPixelColumn(uint8 x, uint8 y, uint8 data)
{
	if (x >= 128 || y >= 8) return;
	//OLEDFB_frameBuffer[y / 8 * 128 + x] |
}

void OLEDFB_drawPixel(uint8 x, uint8 y, uint8 mode)
{
	switch(mode)
	{
		case OLEDFB_BLACK:
			OLEDFB_setPixelBlack(x,y);
			break;
		case OLEDFB_WHITE:
			OLEDFB_setPixelWhite(x,y);
			break;
		case OLEDFB_INVERTED:
			OLEDFB_setPixelInverted(x,y);
			break;
	}
}

/**
 * OLEDFB_drawBitmap paint a bitmap on the frame buffer.
 * @param x The x coordinate of top-left corner of bit map ranging from 0 to 127
 * @param y The y coordinate of top-left corner of bit map ranging from 0 to 63
 * @param bitmap The bitmap to paint. Note that and must be encoded in column-major.
 * @param srcWidth The width of bitmap.
 * @param srcHeight The height of bitmap.
 * Please note that based on the feature of the OLED, The operation can be accelerated in the following conditions:
 * y%8 == 0 and srcHeight % 8 ==0.
 * But TODO: This is not implemented.
 */
void OLEDFB_drawBitmap(uint8 x, uint8 y, uint8* bitmap, uint8 srcWidth, uint8 srcHeight)
{
	for(uint16 i=0;i<srcWidth;i++)
	{
		for(uint16 j=0;j<srcHeight;j++)
		{
			uint16 pixelPos = i*srcHeight + j;
			if(bitmap[pixelPos/8] & ( 1 << ( pixelPos % 8 ) ) )
			{
				OLEDFB_setPixelWhite(i+x,j+y);
			}
			else
			{
				OLEDFB_setPixelBlack(i+x,j+y);
			}
		}
	}
}

void OLEDFB_drawBitmapEx(uint8 x, uint8 y, uint8 width, uint8 height, uint8* bitmap, uint8 srcWidth, uint8 srcHeight)
{
	for(uint16 i=0;i<width;i++)
	{
		uint16 xPos = i*srcWidth/width;
		for(uint16 j=0;j<height;j++)
		{
			uint16 pixelPos = xPos*srcWidth + j*srcHeight/height;
			if(bitmap[pixelPos/8] & ( 1 << ( pixelPos % 8 ) ) )
			{
				OLEDFB_setPixelWhite(i+x,j+y);
			}
			else
			{
				OLEDFB_setPixelBlack(i+x,j+y);
			}
		}
	}
}

void OLEDFB_drawChar(uint8 x, uint8 y, const uchar c)
{
	if(c<0x20||x>=0x80) return;
	OLEDFB_drawBitmap(x, y, &OLEDFONT[(c-0x20)*8], 8, 8);
}

void OLEDFB_drawText(uint8 x, uint8 y, const uchar* str)
{
	while((*str)!='\0')
	{
		OLEDFB_drawChar(x,y,*str);
		str++;
		x+=8;
	}
}

void OLEDFB_drawCharEx(uint8 x, uint8 y, uint8 charWidth, uint8 charHeight, const uchar c)
{
	if(c<0x20||x>=0x80) return;
	OLEDFB_drawBitmapEx(x, y, charWidth, charHeight, &OLEDFONT[(c-0x20)*8], 8, 8);
}

void OLEDFB_drawTextEx(uint8 x, uint8 y, uint8 charWidth, uint8 charHeight, const uchar* str)
{
	while((*str)!='\0')
	{
		OLEDFB_drawCharEx(x,y, charWidth, charHeight,*str);
		str++;
		x+=charWidth;
	}
}

void OLEDFB_drawLine(int16 x1, int16 y1, int16 x2, int16 y2)
{
    int16 deltaX = abs(x1 - x2);
    int16 deltaY = abs(y1 - y2);
    if (deltaX > deltaY)
    {
        if(x1 > x2)
        {
        	uint16 temp;
        	temp = x1;
        	x1 = x2;
        	x2 = temp;
        	temp = y1;
        	y1 = y2;
        	y2 = temp;
        }
        deltaX = x2 - x1;
        deltaY = y2 - y1;
		int16 error = deltaX > 0 ? deltaY/2 : -deltaY/2;
		for(int16 x = x1, y = y1; x <= x2 && x<128/* && y >= 0 && y<64*/; x++, error-=deltaY)
        {
            if(error<0&&deltaY>0)
            {
                y++;
                error+=deltaX;
            }
            else if(error>0&&deltaY<0)
            {
                y--;
                error-=deltaX;
            }
            OLEDFB_setPixelWhite(x, y);
        }
    }
    else
    {
        if(y1 > y2)
        {
        	uint16 temp;
        	temp = x1;
        	x1 = x2;
        	x2 = temp;
        	temp = y1;
        	y1 = y2;
        	y2 = temp;
        }
        deltaX = x2 - x1;
        deltaY = y2 - y1;
		int16 error = deltaY > 0 ? deltaX/2 : -deltaX/2;
		for(int16 y = y1, x = x1; y <= y2 && y <64/* && x>=0 && x<128*/; y++, error-=deltaX)
        {
            if(error<0&&deltaX>0)
            {
                x++;
                error+=deltaY;
            }
			else if(error>0&&deltaX<0)
            {
                x--;
                error-=deltaY;
			}
            OLEDFB_setPixelWhite(x, y);
        }
	}
}

void OLEDFB_drawRect(int16 x1, int16 y1, int16 x2, int16 y2, uint16 mode)
{
	int16 temp;
    if(x1 > x2)
    {
    	temp = x1;
    	x1 = x2;
    	x2 = temp;
    }
    if(y1>y2)
    {
    	temp = y1;
    	y1 = y2;
    	y2 = temp;
    }
	for(int16 i = x1;i<=x2;i++)
	{
		for(int16 j = y1;j<=y2;j++)
		{
			OLEDFB_drawPixel(i, j, mode);
		}
	}
}

void OLEDFB_drawCircle(int8 x, int8 y, int8 r, uint8 mode)
{
	uint16 mid = r/sqrt(2);
	for(int16 i = -mid;i<=mid;i++)
	{
		int16 l = round(sqrt(r*r- i*i));
		OLEDFB_drawRect(x+i,y-l,x+i,y+l,mode);
		OLEDFB_drawRect(x-l,y+i,x-mid-1,y+i,mode);
		OLEDFB_drawRect(x+mid+1,y+i,x+l,y+i,mode);
	}
}
