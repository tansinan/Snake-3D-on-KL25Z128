/*
 * Function.h
 *
 *  Created on: May 6, 2015
 *      Author: leo
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_


/*enable interrupt*/
void enable_irq(int irq);

/*enable initial*/
void EN_Init();

/*delay function*/
void delayms(unsigned int number);

void  KEY_Init();
void PORTB_Handler();
void PORTE_Handler();


/*LED inital*/
void LED_Init();

//input parameter number:0x01--LED1;0x02----LED2;0x03----LED3;0x04---LED4
void LED_light(unsigned char number);
//0x01--LED1_flag;0x02---LED2_flag;0x03---LED3_flag;0x04---LED4_flag;blue---0x10;green---0x20;red---0x30
void LED_color(unsigned char LED1_flag,unsigned char LED2_flag,unsigned char LED3_flag,unsigned char LED4_flag,unsigned char color);

#define BIT0 0x01
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)
#define BIT8 (1<<8)
#define BIT9 (1<<9)
#define BIT10 (1<<10)
#define BIT11 (1<<11)
#define BIT12 (1<<12)
#define BIT13 (1<<13)
#define BIT14 (1<<14)
#define BIT15 (1<<15)
#define BIT16 (1<<16)
#define BIT17 (1<<17)
#define BIT18 (1<<18)
#define BIT19 (1<<19)
#define BIT20 (1<<20)
#define BIT21 (1<<21)
#define BIT22 (1<<22)
#define BIT23 (1<<23)
#define BIT24 (1<<24)
#define BIT25 (1<<25)
#define BIT26 (1<<26)
#define BIT27 (1<<27)
#define BIT28 (1<<28)
#define BIT29 (1<<29)
#define BIT30 (1<<30)
#define BIT31 (1<<31)

#define NULL 0

#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_A 4
#define KEY_B 5
#define KEY_C 6
#define KEY_D 7


#define GPIO_PIN_MASK     0x3Fu
#define GPIO_PIN(x)   (((1)<<(x&GPIO_PIN_MASK)))

#endif /* FUNCTION_H_ */
