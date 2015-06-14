/*
 * Function.c
 *
 *  Created on: May 6, 2015
 *      Author: leo
 */

#include "Includes.h"

unsigned char lED1_light_flag;
unsigned char lED2_light_flag;
unsigned char lED3_light_flag;
unsigned char lED4_light_flag;

/*enable interrupt*/
void enable_irq(int irq) {

    //确定irq号为有效的irq号
    if (irq > 32)	irq=32;
    
    NVIC_ICPR |= (1<<(irq%32));
    NVIC_ISER |= (1<<(irq%32));   

}

/*enable initial*/
void EN_Init() {
	//enable_irq(12);  //UART0 interrupt
	enable_irq(22);  //PIT interrupt
}

/*delay function*/
void delayms(unsigned int number) {
  unsigned short i,j;
  for(i=0;i<number;i++)
  {
	  for(j=0;j<100;j++)
		  asm("nop");
  }
}

//按键
/*KEY initial*/
void KEY_Init()
{
	/*enable PORTB,PORTC,PORTE  clock*/
	SIM_SCGC5|=SIM_SCGC5_PORTB_MASK+SIM_SCGC5_PORTE_MASK;

	/*portB  set to GPIO,raising edge interrupt,no pull enable,passive filter enable*/	
	PORTB_PCR8=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;	
	PORTB_PCR9=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;			
	PORTB_PCR16=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;	
	PORTB_PCR17=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;	
	
	/*portE  set to GPIO,raising edge interrupt,no pull enable,passive filter enable*/
	PORTE_PCR2=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;	
	PORTE_PCR3=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;	
	PORTE_PCR4=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;	
	PORTE_PCR5=PORT_PCR_MUX(0X1)+PORT_PCR_IRQC(0X0A)+PORT_PCR_PE_MASK+PORT_PCR_PS_MASK;

}

static char keyRecord = 0;

void PORTB_Handler()
{
	//A KEY handler  all show 0
	if((GPIOB_PDIR&BIT8)!=BIT8)
	{
		if((keyRecord & BIT0)==0)
			OLED_MENU_onKeyPressed(KEY_RIGHT);
		keyRecord |= BIT0;
		//0x01--LED1_flag;0x02---LED2_flag;0x03---LED3_flag;0x04---LED4_flag;blue---0x10;green---0x20;red---0x30
		LED_light(0x01);
	}
	else
	{
		keyRecord &= ~BIT0;
	}
	//B KEY handler  all show 1
	if((GPIOB_PDIR&BIT9)!=BIT9)
	{
		if((keyRecord & BIT1)==0)
			OLED_MENU_onKeyPressed(KEY_DOWN);
		keyRecord |= (BIT1);
		LED_light(0x02);
	}
	else
	{
		keyRecord &= ~BIT1;
	}
	//C KEY handler  all show 2
	if((GPIOB_PDIR&BIT16)!=BIT16)
	{
		if((keyRecord & BIT2)==0)
			OLED_MENU_onKeyPressed(KEY_LEFT);
		keyRecord |= BIT2;
		LED_light(0x03);	
	}
	else
	{
		keyRecord &= ~BIT2;
	}
	//D KEY handler  all close
	if((GPIOB_PDIR&BIT17)!=BIT17)
	{
		if((keyRecord & BIT3)==0)
			OLED_MENU_onKeyPressed(KEY_UP);
		keyRecord |= BIT3;
		LED_light(0x04);
	}
	else
	{
		keyRecord &= ~BIT3;
	}
//	//clear interrupt flag
//	PORTB_ISFR |= 0xFFFFFFFF;  //Clear Port B  ISR flags
}

void PORTE_Handler()
{
	//L KEY handler
	if((GPIOE_PDIR&BIT2)!=BIT2)   
	{
		//do someting
		LED_light(0x01);
	}
	//DOWN KEY handler
	else if((GPIOE_PDIR&BIT3)!=BIT3)
	{
		//do something 
		LED_light(0x02);
	}
	else if((GPIOE_PDIR&BIT4)!=BIT4)
	{
		//do something
		LED_light(0x03);
	}
	else if((GPIOE_PDIR&BIT5)!=BIT5)
	{
		//do something
		LED_light(0x04);
	}
//	//clear interrupt flag
//	PORTE_ISFR |= 0x000000FF;  //Clear Port E  flags
}


/*LED inital*/
void LED_Init()
{
	/*enable PORTB and PORTD  clock*/
	SIM_SCGC5|=SIM_SCGC5_PORTC_MASK;
	
	/*portC0---11 was set to GPIO*/	
	PORTC_PCR0=PORT_PCR_MUX(0X1);	
	PORTC_PCR1=PORT_PCR_MUX(0X1);
	PORTC_PCR2=PORT_PCR_MUX(0X1);	
	PORTC_PCR3=PORT_PCR_MUX(0X1);
	PORTC_PCR4=PORT_PCR_MUX(0X1);	
	PORTC_PCR5=PORT_PCR_MUX(0X1);
	PORTC_PCR6=PORT_PCR_MUX(0X1);	
	PORTC_PCR7=PORT_PCR_MUX(0X1);	
	PORTC_PCR8=PORT_PCR_MUX(0X1);	
	PORTC_PCR9=PORT_PCR_MUX(0X1);
	PORTC_PCR10=PORT_PCR_MUX(0X1);	
	PORTC_PCR11=PORT_PCR_MUX(0X1);
	    
	/*port set to out*/
	GPIOC_PDDR|=0XFFF;
	/*port out set to high*/
	GPIOC_PDOR=0XFFF;
	
}

//input parameter number:0x01--LED1;0x02----LED2;0x03----LED3;0x04---LED4
void LED_light(unsigned char number)
{
	switch(number)
	{
	     case 1:
	    		/*port out set to high*/
	    		GPIOC_PDOR=0XFFF;      //all dim
	    	    GPIOC_PDOR&=~(BIT0|BIT1|BIT2);   //GPIOC0--1--2  light
	    	    break;
	     case 2:
	    		/*port out set to high*/
	    		GPIOC_PDOR=0XFFF;      //all dim
	    	    GPIOC_PDOR&=~(BIT3|BIT4|BIT5);   //GPIOC0--3--5  light
	    	    break;
	     case 3:
	    		/*port out set to high*/
	    		GPIOC_PDOR=0XFFF;      //all dim
	    	    GPIOC_PDOR&=~(BIT6|BIT7|BIT8);   //GPIOC0--6--8  light
	    	    break;
	     case 4:
	    		/*port out set to high*/
	    		GPIOC_PDOR=0XFFF;      //all dim
	    	    GPIOC_PDOR&=~(BIT9|BIT10|BIT11);  //GPIOC0--9--11  light
	    	    break;
	     default: 
	    	    GPIOC_PDOR&=~0xFFF;              //GPIOC0--1--2  light
	    	    break;
	}
}

//0x01--LED1_flag;0x02---LED2_flag;0x03---LED3_flag;0x04---LED4_flag;white---0x00;blue---0x10;green---0x20;red---0x30
void LED_color(unsigned char LED1_flag,unsigned char LED2_flag,unsigned char LED3_flag,unsigned char LED4_flag,unsigned char color)
{
	unsigned char led_light_flag;
	led_light_flag=LED1_flag|LED2_flag|LED3_flag|LED4_flag|color;
	switch(led_light_flag)
	{
        case 0x01:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT0|BIT1|BIT2);  //GPIOC0--9--11  light	    	
    	         break;
        case 0x02:
	             GPIOC_PDOR=0XFFF;      //all dim
                 GPIOC_PDOR&=~(BIT3|BIT4|BIT5);  //GPIOC0--9--11  light	    	
    	         break;
        case 0x03:
	             GPIOC_PDOR=0XFFF;      //all dim
                 GPIOC_PDOR&=~(BIT6|BIT7|BIT8);  //GPIOC0--9--11  light	    	
    	         break;
        case 0x04:
	             GPIOC_PDOR=0XFFF;      //all dim
                 GPIOC_PDOR&=~(BIT9|BIT10|BIT11);  //GPIOC0--9--11  light	    	
    	         break;
	    case 0x11:
    		     GPIOC_PDOR=0XFFF;      //all dim
    	         GPIOC_PDOR&=~(BIT0);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x12:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT3);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x13:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT6);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x14:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT9);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x21:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT1);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x22:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT4);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x23:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT7);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x24:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT10);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x31:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT2);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x32:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT5);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x33:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT8);  //GPIOC0--9--11  light	    	
	    	     break;
	    case 0x34:
		         GPIOC_PDOR=0XFFF;      //all dim
	             GPIOC_PDOR&=~(BIT11);  //GPIOC0--9--11  light	    	
	    	     break;
	    default: 
	    	     break;
	}
}
