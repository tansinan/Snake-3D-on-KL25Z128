/*
 * UART.h
 *
 *  Created on: May 7, 2015
 *      Author: leo
 */

#ifndef UART_H_
#define UART_H_

void UART0_Init (void);

unsigned char uart0_getchar (void);

void uart0_putchar (unsigned char data);


/*单片机向上位机发送字符串*/
void urat0__TransmitArray (char *data);

/*将int型转化为字符串输出*/
void urat0_TransmitNumeral (int numeral) ;


#endif /* UART_H_ */
