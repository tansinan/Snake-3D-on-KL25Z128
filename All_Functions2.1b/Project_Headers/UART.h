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


/*��Ƭ������λ�������ַ���*/
void urat0__TransmitArray (char *data);

/*��int��ת��Ϊ�ַ������*/
void urat0_TransmitNumeral (int numeral) ;


#endif /* UART_H_ */
