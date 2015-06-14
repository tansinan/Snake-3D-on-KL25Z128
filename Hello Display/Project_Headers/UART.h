/*
 * UART.h
 *
 *  Created on: Apr 16, 2015
 *      Author: tansinan
 */

#ifndef UART_H_
#define UART_H_

#include "derivative.h"

void UART_init()
{
	SIM_SOPT2 = SIM_SOPT2_UART0SRC(1);
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SCGC5 |= 0x0200;
	SIM_SCGC4 |= 0x0400;
	PORTA_PCR1 = 0x200;
	PORTA_PCR2 = 0x200;
	UART0_BDH = 0x00;
	UART0_BDL = 0x8F;
	UART0_C2 = 0x0C;
}

void UART_putChar(unsigned char data)
{
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	UART0_D = data;
}

void UART_putString(unsigned char* str)
{
	for(int i=0;;i++)
	{
		if(str[i]!='\0')
		{
			UART_putChar(str[i]);
		}
		else return;
	}
}

unsigned char UART_getChar()
{
	while(!(UART0_S1 & 0x20));
	return UART0_D;
}

#endif /* UART_H_ */
