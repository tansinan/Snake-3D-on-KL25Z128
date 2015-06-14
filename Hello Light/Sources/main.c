/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

int displayMode = 0;
int lastButtonStatus = 0;
int buttonPressed = 0;

int currentCycle = 0;
int currentTime = 0;

void delay()
{
	for(int i=0;i<50;i++)
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
	SIM_SCGC5 |= 0x0A00;
	SIM_SCGC5 |= 0x0C00;
	/*PORTC_PCR0 = 0x100;
	PORTC_PCR1 = 0x100;
	PORTC_PCR2 = 0x100;
	PORTC_PCR3 = 0x100;
	PORTC_PCR4 = 0x100;
	PORTC_PCR5 = 0x100;*/
	for(int i=0;i<12;i++)
	{
		PORT_PCR_REG(PORTC_BASE_PTR,i) = 0x100;
	}
	//enable global interrupt
	asm("CPSIE i");
	
	//Enable port A interrupt in NVIC
	NVIC_ISER |= (1<<30);
	
	//A for Interrupt,2 for pulling-up resistor
	PORTA_PCR2 |= 0x00A0102;
	
	//0x102, where 0x002 enables the built-in pull up resistor.
	PORTB_PCR17 = 0x102;
	
	GPIOC_PDDR = 0xFFF;
	GPIOB_PDDR &= ~(1<<17);
	GPIOC_PDOR = ~0;
	int temp = GPIOB_PDIR;
	for(int counter=0;;counter++)
	{
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
				if(currentTime < brightness*10)
				{
					GPIOC_PDOR &= ~1;
				}
			}
			else if(displayMode == 1)
			{
				if(currentTime < brightness*10)
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
	return 0;
}

void PORTA_IRQHandler(void)
{
	if(GPIOA_PDIR & (1<<2))
	{
		if(buttonPressed == 0)
		{
			displayMode++;
			if(displayMode>1) displayMode = 0;
			buttonPressed = 1;
		}
		/*if(mode == 0)
		{
			GPIOC_PDOR = 0;
		}
		else
		{
			GPIOC_PDOR = ~0;
		}*/
		PORTA_PCR2 |= (1<<24);
	}
}

