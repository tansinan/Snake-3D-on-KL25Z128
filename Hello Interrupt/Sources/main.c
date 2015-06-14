/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

int mode = 0;
int buttonPressed = 0;


void delay()
{
	int i,j;
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			asm("nop");
		}
	}
	buttonPressed = 0;
}

void PORTA_IRQHandler(void)
{
	if(GPIOA_PDIR & (1<<2))
	{
		if(buttonPressed == 0)
		{
			mode++;
			if(mode>1) mode = 0;
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

int main(void)
{
	int i;
	SIM_SCGC5 |= 0x0A00;
	
	//enable global interrupt
	asm("CPSIE i");
	
	//Enable port A interrupt in NVIC
	NVIC_ISER |= (1<<30);
	
	//A for Interrupt,2 for pulling-up resistor
	PORTA_PCR2 |= 0x00A0102;
	
	for(i=0;i<12;i++)
	{
		PORT_PCR_REG(PORTC_BASE_PTR,i) = 0x100;
	}
	GPIOC_PDDR = 0xFFF;
	GPIOC_PDOR = ~0;
	
	int time = 0;
	for(;;)
	{
		time++;
		time%=2;
		delay();
		GPIOC_PDOR = ~0;
		if(mode == 0)
		{
			if(time==0)
			{
				GPIOC_PDOR &= ~(1<<4);
				GPIOC_PDOR &= ~(1<<0);
			}
		}
		else
		{
			if(time==0)
			{
				GPIOC_PDOR &= ~(1<<4);
			}
			else
			{
				GPIOC_PDOR &= ~(1<<0);
			}
		}
	}
	return 0;
}
