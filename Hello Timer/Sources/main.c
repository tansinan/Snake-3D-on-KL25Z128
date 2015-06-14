/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */
#include "UART.h"
int sec = 0;
int min = 0;
int hrs = 0;
void SysTick_init()
{
	SYST_RVR = 0x9FFD07;
	SYST_CVR = 0x00;
	SYST_CSR = 0x07;
}

void SysTick_Handler(void)
{
	unsigned int i;
	static int count = 0;
	count++;
	if(count%2 == 0)
	{
		return;
	}
	sec++;
	if( sec == 60)
	{
		sec = 0;
		min ++;
	}
	if(min == 60)
	{
		min = 0;
		hrs++;
	}
	if(hrs == 24)
	{
		hrs = 0;
	}
	UART_putChar('\r');
	if(hrs>10) UART_putChar(hrs/10+'0');
	UART_putChar(hrs%10+'0');
	UART_putChar(':');
	UART_putChar(min/10+'0');
	UART_putChar(min%10+'0');
	UART_putChar(':');
	UART_putChar(sec/10+'0');
	UART_putChar(sec%10+'0');
	i = SYST_CSR;
}

int main(void)
{
	int counter = 0;
	asm("CPSIE i");
	UART_init();
	SysTick_init();
	return 0;
}
