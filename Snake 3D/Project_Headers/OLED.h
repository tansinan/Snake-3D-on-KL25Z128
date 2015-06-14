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


/******************************************/
//��Ӧ��־λ��ֵ���⹦��
/******************************************/
#define BIT0  0x01
#define BIT1  0x02
#define BIT2  0x04
#define BIT3  0x08
#define BIT4  0x10
#define BIT5  0x20
#define BIT6  0x40
#define BIT7  0x80
#define BIT8  0x100
#define BIT9  0x200
#define BIT10  0x400
#define BIT11  0x800
#define BIT12  0x1000
#define BIT13  0x2000
#define BIT14  0x4000
#define BIT15  0x8000


//�����ʵ�����ӵ������޸����º궨��
#define OLED_DC_H     (GPIOD_PDOR|=BIT0)
#define OLED_RESET_H  (GPIOD_PDOR|=BIT3)

//�����ʵ�����ӵ������޸����º궨��
#define OLED_DC_L     (GPIOD_PDOR&=~BIT0)
#define OLED_RESET_L  (GPIOD_PDOR&=~BIT3)


#define DDR_OLED_DC     (GPIOD_PDDR|=BIT0)
#define DDR_OLED_RESET  (GPIOD_PDDR|=BIT3)

//////////////////////////////////////////////////////

void OLED_Init(void);//ϵͳ��ʼ��
void OLED_W_Ctl(unsigned char cw);
void OLED_W_Dat(unsigned char dw);
void OLED_Clr(void);

#endif /* OLED_H_ */
