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
	int seed = 0;
	int number;
	int guess;
	for(;;)
	{
		UART_putString("\rPlease guess my number:");
		if(seed == 0)
		{
			while(!(UART0_S1 & 0x20)) seed++;
			srand(seed);
		}
		number = rand() % 10;
		for(;;)
		{
			char c = UART_getChar();
			if(c>='0' && c<='9')
			{
				UART_putChar(c);
				guess = c - '0';
				if( guess > number )
				{
					UART_putString("\r\nToo Large!\r\n");
				}
				else if( guess < number )
				{
					UART_putString("\r\nToo Small!\r\n");
				}
				else
				{
					UART_putString("\r\nYou are right!\r\n");
					break;
				}
			}
		}
		
	}
	for(;;);
	return 0;
}
