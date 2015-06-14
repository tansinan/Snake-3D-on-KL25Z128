/*
 * UART.c
 *
 *  Created on: May 7, 2015
 *      Author: leo
 */
#include "Includes.h"
void UART0_Init (void) {
	SIM_SOPT2 = SIM_SOPT2_UART0SRC(1);
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;//选择MCGFLLCLK
	SIM_SCGC4|=0x400;// 使能UART0的时钟
	SIM_SCGC5|=0x200;// 使能PORTA的时钟
	PORTA_PCR1=0x200; //配置端口PTA1为UART0复用端口
	PORTA_PCR2=0x200; //配置端口PTA1为UART0复用端口
	UART0_BDH = 0x00;
	UART0_BDL = 0x8F; //波特率9600
	UART0_C2 = 0x0C; //打开发送和接收器
	
	//just test
	UART0_Config();
	asm("CPSIE i");//确认开启全局中断
}



//made by zhujiao
void UART0_Config() {
  UART0_C2 &= ~(UART0_C2_TE_MASK| UART0_C2_RE_MASK);
  UART0_BDH = 0x00;
  UART0_BDL = 0x88;
  UART0_C4 = 0x0F;
  UART0_C1 = 0x00;
  UART0_C3 = 0x00;
  UART0_MA1 = 0x00;
  UART0_MA1 = 0x00;
  UART0_S1 |= 0x1F;
  UART0_S2 |= 0xC0;
  UART0_C2 |= UART0_C2_TE_MASK| UART0_C2_RE_MASK|UART0_C2_RIE_MASK;
}

unsigned char uart0_getchar (void) {
	/* Wait until character has been received */
	while (!(UART0_S1 & UART_S1_RDRF_MASK));
	/* Return the 8-bit data from the receiver */
	//if(UART0_S1 & UART_S1_RDRF_MASK){
		return UART0_D;
	 
}


void uart0_putchar (unsigned char data) {
	/* Wait until space is available in the FIFO */
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	/* Send the character */
	UART0_D = data;
}


/*单片机向上位机发送字符串*/
void urat0__TransmitArray (char *data) {
	int index = 0;
	while (data[index]!='\0')    //将字符串(即字符数组)拆分成单个字符,逐一发送
        {
		   uart0_putchar (data[index]);
           index++;
        }
}

/*将int型转化为字符串输出*/
void urat0_TransmitNumeral (int numeral) {
  int reversed = 0, length = 0;char _cflag;
  if (numeral < 0) { urat0__TransmitArray("-"); numeral = -numeral; }   //先对符号进行判断,如有符号,输出"-"
  while (numeral > 0) {
    reversed = reversed * 10 + (numeral % 10); 
    numeral /= 10; length++; }          //对数据的长度进行测量
  while (length > 0) {                  //根据测量的结果,逐一发出数据
    _cflag='0'+reversed % 10;
    uart0_putchar(_cflag);
    reversed /= 10; length--;
  } 
}

