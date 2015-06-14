/*
 * SMG.c
 *
 *  Created on: May 6, 2015
 *      Author: leo
 */

//SMG init
#include "Includes.h"

unsigned char  Num[12]={0xA0,0xBE,0x62,0x2A,0x3C,0x29,0x21,0xBA,0x20,0x28,0xFF,~BIT7};
unsigned long int led[6]={BIT12,BIT13,BIT14,BIT15,BIT16,BIT17};



unsigned int flag_100ms=0;

unsigned int number=0;


void PIT_init(unsigned int number_ms)
{
	/*Trun on PIT clocks*/
	SIM_SCGC6|=SIM_SCGC6_PIT_MASK;
	
    /*Enable PIT Module*/
	PIT_MCR&=~(PIT_MCR_MDIS_MASK);
	
	/*Setup the channel0 of PIT*/
	PIT_LDVAL0=20000*number_ms;
	
	/*Enable the IRQ of channel0,PIT*/
	PIT_TCTRL0|=PIT_TCTRL_TIE_MASK;
	
	/*Running channel0,PIT*/
	PIT_TCTRL0|=PIT_TCTRL_TEN_MASK;	
}



void SMG_Init()
{
	    /* PORTA and PORTD clock have already enabled*/
		SIM_SCGC5|=SIM_SCGC5_PORTA_MASK+SIM_SCGC5_PORTD_MASK;		   
	    
		/*portA  set to GPIO*/	    
	    PORTA_PCR12=PORT_PCR_MUX(0X1);
	    PORTA_PCR13=PORT_PCR_MUX(0X1);
	    PORTA_PCR14=PORT_PCR_MUX(0X1);
	    PORTA_PCR15=PORT_PCR_MUX(0X1);
	    PORTA_PCR16=PORT_PCR_MUX(0X1);
	    PORTA_PCR17=PORT_PCR_MUX(0X1);
	    
		/*portD  set to GPIO*/	    
	    PORTD_PCR0=PORT_PCR_MUX(0X1);
	    PORTD_PCR1=PORT_PCR_MUX(0X1);
	    PORTD_PCR2=PORT_PCR_MUX(0X1);
	    PORTD_PCR3=PORT_PCR_MUX(0X1);
	    PORTD_PCR4=PORT_PCR_MUX(0X1);
	    PORTD_PCR5=PORT_PCR_MUX(0X1);
	    PORTD_PCR6=PORT_PCR_MUX(0X1);
	    PORTD_PCR7=PORT_PCR_MUX(0X1); 
	    
	    /*LED control pin set to out*/	    
	    GPIOA_PDDR|=GPIO_PDDR_PDD(GPIO_PIN(12)|GPIO_PIN(13)|GPIO_PIN(14)|GPIO_PIN(15)|GPIO_PIN(16)|GPIO_PIN(17));
	    
	    /*LED bit pin set to out*/	  
	    GPIOD_PDDR|=0x000000FF;	    
	    
	    /*LED control pin set to high ,LEDs are closed*/
	    GPIOA_PDOR|=GPIO_PDDR_PDD(GPIO_PIN(12)|GPIO_PIN(13)|GPIO_PIN(14)|GPIO_PIN(15)|GPIO_PIN(16)|GPIO_PIN(17));	    
	    
	    /*LED bit pin set to low ,LED bit are all lighted,change GPIOC_PDOR register can change the number it shows*/
		GPIOD_PDOR=0x00;		
		
		/*LED control pin set to low ,LEDs are all open*/
		GPIOA_PDOR&=~GPIO_PDDR_PDD(GPIO_PIN(12)|GPIO_PIN(13)|GPIO_PIN(14)|GPIO_PIN(15)|GPIO_PIN(16)|GPIO_PIN(17));
}

//SMG show data in show_data[]:0---5
void SMG_show_data(unsigned char show_data[],unsigned char number)
{
	/*
	unsigned char i;
	for(i=0;i<6;i++)
	{
		 GPIOA_PDOR|=0xFF000; 
		 GPIOD_PDOR=Num[show_data[i]];
		 GPIOA_PDOR&=~(led[i%6]);		
		 //GPIOA_PDOR=0x00;
	}*/
	
	 GPIOA_PDOR|=0xFF000; 
	 GPIOD_PDOR=Num[show_data[number]];
	 GPIOA_PDOR&=~(led[number%6]);	
}

//PIT interrupt handle
void PIT_IRQHandler(void)
{
	//do something
	/*Clear the flag of channel0,PIT*/
	PIT_TFLG0|=PIT_TFLG_TIF_MASK;
}



//data1 forward,data2 backward
//void data_to_array(unsigned int data1,unsigned int data2,unsigned char array[]){
void data_to_array(int data1,int data2,unsigned char array[]){
	int _flag1=0;
	int _flag2=0;
	unsigned char i;
	
	if(data1<0) {
		_flag1=1;
		data1=-data1;
	}
	if(data2<0) {
		_flag2=1;
		data2=-data2;
	}
	
	//data1=data1&0xFF;
	//data2>>=4;

	
	if(!_flag1) {
		for(i=0;i<3;i++) {		
			array[i]=data1%10;
			data1/=10;
		}
	} else {
		array[2]=11;
		for(i=0;i<2;i++) {		
			array[i]=data1%10;
			data1/=10;
		}
	}
	/*
	for(i=3;i<6;i++)
	{		
		array[i]=data2%10;
		data2/=10;
	}
	*/
	
	if(!_flag2) {
		for(i=3;i<6;i++)
			{		
				array[i]=data2%10;
				data2/=10;
			}
		} else {
			array[5]=11;
			for(i=3;i<5;i++) {		
				array[i]=data2%10;
				data2/=10;
			}
		}
	
}
