/*
 * OLED.H
 *
 *  Created on: Jan 2, 2014
 *      Author: millin
 */

#ifndef OLED_H_
#define OLED_H_

#ifndef _GLOBAL_DECL_
#define _GLOBAL_DECL_ extern
#endif

/******************************************/
/*****              OLED Define        ****/
/******************************************/

#define SSD1325			1		//��һ���ͺ�OLED��TW28642270B��2.7��
#define SSD1306			2		//��ѧϵͳ������Ļ���ͺ�OLED_UG2864HSWEG01��0.97��

#define OLED_TYPE		SSD1306



//�����ʵ�����ӵ������޸����º궨��
#define OLED_DC_H     (GPIOD_PDOR|=BIT0)
#define OLED_RESET_H  (GPIOD_PDOR|=BIT3)

//�����ʵ�����ӵ������޸����º궨��
#define OLED_DC_L     (GPIOD_PDOR&=~BIT0)
#define OLED_RESET_L  (GPIOD_PDOR&=~BIT3)


#define DDR_OLED_DC     (GPIOD_PDDR|=BIT0)
#define DDR_OLED_RESET  (GPIOD_PDDR|=BIT3)

//////////////////////////////////////////////////////

_GLOBAL_DECL_ const unsigned char ASCII[];

void OLED_Init(void);//ϵͳ��ʼ��
void OLED_W_Ctl(unsigned char cw);
void OLED_W_Dat(unsigned char dw);
void OLED_Clr(void);
void OLED_W_Test(void);
void OLED_W_Ch(unsigned char lx,unsigned char ly,char ch);
void OLED_W_Str(unsigned char lx,unsigned char ly,char *sch);
void OLED_W_Dot(unsigned char lx,unsigned char ly,char val);
unsigned char dtoa(unsigned char c1);
void OLED_W_Numeral (unsigned char x,unsigned char y,int numeral);


#endif /* OLED_H_ */
