/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

#include "DigitalTube.h"
#include "Timer.h"
#include "ADC.h"
#include "Music.h"
#include "UART.h"

int displayMode = 0;
int lastButtonStatus = 0;
int buttonPressed = 0;

int currentCycle = 0;
int currentTime = 0;

int speed = 1;

void delay()
{
	for(int i=0;i<1000*speed;i++)
	{
		if(!GPIOB_PDIR&&(1<<17))
		{
			if(lastButtonStatus == 0)
			{
				lastButtonStatus = 1;
				displayMode++;
				if(displayMode>=4)
				{
					displayMode = 0;
				}
			}
		}
		else
		{
			lastButtonStatus = 0;
		}
	}
	currentTime+=10;
	if(currentTime>1000)
	{
		currentCycle++;
		currentTime = 0;
	}
}

int main(void)
{
	DigitalTube_init();
	Timer_init(10);
	UART_init();
	ADC_init();
	Music_init();
	for(int i=0;i<6;i++)
	{
		DigitalTube_content[i] = DigitalTube_numberContent[0];//DigitalTube_numberContent[0];
	}
	
	//µÆµÄÊ¹ÄÜ
	SIM_SCGC5 |= 0x0A00;
	SIM_SCGC5 |= 0x0C00;
	for(int i=0;i<12;i++)
	{
		PORT_PCR_REG(PORTC_BASE_PTR,i) = 0x100;
	}
	
	//Enable port A interrupt in NVIC
	//NVIC_ISER |= (1<<30);
	
	//A for Interrupt,2 for pulling-up resistor
	//PORTA_PCR2 |= 0x00A0102;
	
	//0x102, where 0x002 enables the built-in pull up resistor.
	//PORTB_PCR17 = 0x102;
	
	//GPIOC_PDDR = 0xFFF;
	//GPIOB_PDDR &= ~(1<<17);
	//GPIOC_PDOR = ~0;
	//int temp = GPIOB_PDIR;
	int counter = 0;
	for(int i=0;i<6;i++)
	{
		DigitalTube_content[i] = DigitalTube_numberContent[0];
	}
	for(;;)
	{
		unsigned short ADCValue = ADC_readData();
		//Music_playFrequency(ADCValue/5 + 440);
		//char c = UART_getChar();
		//if(c>='0' && c<= '9')
		{
			/*for(int i=6;i>0;i--)
			{
				DigitalTube_content[i] = DigitalTube_content[i-1];
			}*/
			//UART_putChar(c);
			//DigitalTube_content[0] = DigitalTube_numberContent[c-'0'];
			DigitalTube_content[0] = DigitalTube_numberContent[ADCValue % 10];
			DigitalTube_content[1] = DigitalTube_numberContent[(ADCValue / 10) % 10];
			DigitalTube_content[2] = DigitalTube_numberContent[(ADCValue / 100) % 10];
			DigitalTube_content[3] = DigitalTube_numberContent[(ADCValue / 1000)];
		}
		speed = ADCValue/1000+1;
		delay();
		for(int i=0;i<8;i++)
		{
			int brightness = currentCycle%200;
			if(brightness>100)
			{
				brightness = 200-brightness;
			}
			brightness-=30;
			if(brightness==0) brightness = 0;
			GPIOC_PDOR = ~0;
			if(displayMode == 0)
			{
				if(currentTime < 500)
				{
					GPIOC_PDOR &= ~1;
				}
			}
			else if(displayMode == 1)
			{
				if(currentTime < 500)
				{
					GPIOC_PDOR &= ~(1<<4);
				}
			}
			else if(displayMode == 2)
			{
				if(currentTime < brightness*10)
				{
					GPIOC_PDOR &= ~(1<<8);
				}
			}
			else if(displayMode == 3)
			{
				if(currentTime < brightness*10)
				{
					GPIOC_PDOR &= ~(7<<9);
				}
			}
		}
	}
	for(;;);
	return 0;
}

void SysTick_Handler()
{
	static int i = 0;
	DigitalTube_handler();
	int temp;
	temp = SYST_CSR;
}
