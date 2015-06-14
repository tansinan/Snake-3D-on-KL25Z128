/*
 * UART.c
 *
 *  Created on: May 7, 2015
 *      Author: leo
 */
#include "Includes.h"
void UART0_Init (void) {
	SIM_SOPT2 = SIM_SOPT2_UART0SRC(1);
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;//ѡ��MCGFLLCLK
	SIM_SCGC4|=0x400;// ʹ��UART0��ʱ��
	SIM_SCGC5|=0x200;// ʹ��PORTA��ʱ��
	PORTA_PCR1=0x200; //���ö˿�PTA1ΪUART0���ö˿�
	PORTA_PCR2=0x200; //���ö˿�PTA1ΪUART0���ö˿�
	UART0_BDH = 0x00;
	UART0_BDL = 0x8F; //������9600
	UART0_C2 = 0x0C; //�򿪷��ͺͽ�����
	
	//just test
	UART0_Config();
	asm("CPSIE i");//ȷ�Ͽ���ȫ���ж�
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


/*��Ƭ������λ�������ַ���*/
void urat0__TransmitArray (char *data) {
	int index = 0;
	while (data[index]!='\0')    //���ַ���(���ַ�����)��ֳɵ����ַ�,��һ����
        {
		   uart0_putchar (data[index]);
           index++;
        }
}

/*��int��ת��Ϊ�ַ������*/
void urat0_TransmitNumeral (int numeral) {
  int reversed = 0, length = 0;char _cflag;
  if (numeral < 0) { urat0__TransmitArray("-"); numeral = -numeral; }   //�ȶԷ��Ž����ж�,���з���,���"-"
  while (numeral > 0) {
    reversed = reversed * 10 + (numeral % 10); 
    numeral /= 10; length++; }          //�����ݵĳ��Ƚ��в���
  while (length > 0) {                  //���ݲ����Ľ��,��һ��������
    _cflag='0'+reversed % 10;
    uart0_putchar(_cflag);
    reversed /= 10; length--;
  } 
}

