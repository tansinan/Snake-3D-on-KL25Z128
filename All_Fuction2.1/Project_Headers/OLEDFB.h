#ifndef OLEDFB_H_
#define OLEDFB_H_

#define OLEDFB_MODE_SET_BLACK 0
#define OLEDFB_MODE_SET_WHITE 1

typedef unsigned char uint8;

//TODO : functions not implemented.

void OLEDFB_clear();
void OLEDFB_setPixel(uint8 x, uint8 y);
void OLEDFB_getPixel();
void OLEDFB_drawBitmap();
void OLEDFB_drawBitmapEx();
void OLEDFB_drawText();
void OLEDFB_drawTextEx();
void OLEDFB_drawLine();
void OLEDFB_drawCircle();

#endif //OLED_H_
