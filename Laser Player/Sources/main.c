/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */
#include "UART.h"

void UART_printHex(unsigned char c)
{
	if(c>=0 && c<=9)
		UART_putChar(c+'0');
	else
		UART_putChar((c-10)+'A');
}

void UART_printCharHex(unsigned char c)
{
	UART_printHex(c/16);
	UART_printHex(c%16);
	UART_putChar('\r');
	UART_putChar('\n');
}


int main(void)
{
	UART_init();
	
	//Init
	SIM_SCGC5 |= 0x2400;
	
	//0x102, where 0x002 enables the built-in pull up resistor.
	PORTB_PCR17 = 0x102;
	PORTB_PCR16 = 0x102;
	PORTB_PCR11 = 0x102;
	PORTB_PCR10 = 0x102;
	
	PORTE_PCR2 = 0x102;
	PORTE_PCR3 = 0x102;
	PORTE_PCR4 = 0x102;
	PORTE_PCR5 = 0x102;
	
	GPIOB_PDDR &= ~(1<<17);
	GPIOB_PDDR &= ~(1<<16);
	GPIOB_PDDR &= ~(1<<11);
	GPIOB_PDDR &= ~(1<<10);
	GPIOE_PDDR &= ~(1<<2);
	GPIOE_PDDR &= ~(1<<3);
	GPIOE_PDDR &= ~(1<<4);
	GPIOE_PDDR &= ~(1<<5);
	
	char lastChar = '\0';
	
	for(;;)
	{
		int var = GPIOB_PDIR;
		if((GPIOB_PDIR&(1<<17))==0&& lastChar!= 'a')
		{
			lastChar = 'a';
			UART_putChar('a');
		}
		if((GPIOB_PDIR&(1<<16))==0&& lastChar!= 'b')
		{
			lastChar = 'b';
			UART_putChar('b');
		}
		/*if((GPIOB_PDIR&(1<<11))==0&& lastChar!= 'c')
		{
			lastChar = 'c';
			UART_putChar('c');
		}
		if((GPIOB_PDIR&(1<<10))==0&& lastChar!= 'd')
		{
			lastChar = 'd';
			UART_putChar('d');
		}*/
		if((GPIOE_PDIR&(1<<2))==0 && lastChar!= 'e')
		{
			lastChar = 'e';
			UART_putChar('e');
		}
		if((GPIOE_PDIR&(1<<3))==0 && lastChar!= 'f')
		{
			lastChar = 'f';
			UART_putChar('f');
		}
		if((GPIOE_PDIR&(1<<4))==0 && lastChar!= 'g')
		{
			lastChar = 'g';
			UART_putChar('g');
		}
		if((GPIOE_PDIR&(1<<5))==0 && lastChar!= 'h')
		{
			lastChar = 'h';
			UART_putChar('h');
		}
		/*else if((GPIOB_PDIR&(1<<10))==0&& lastChar!= 'd')
		{
			lastChar = 'd';
			UART_putChar('d');
		}*/
	}
	
	for(;;);
	return 0;
}
