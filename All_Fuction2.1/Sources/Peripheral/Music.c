/*
 * Music.c
 *
 *  Created on: May 7, 2015
 *      Author: leo
 */

#include "Includes.h"

#define PWM0_CLK_FREQ 50000*3.28
#define L1M 1*2 
//�Ͱ˶�
#define L2M 2*2
#define L3M 3*2
#define L4M 4*2
#define L5M 5*2
#define L6M 6*2
#define L7M 7*2

#define M1  (unsigned short)(PWM0_CLK_FREQ/523)
#define M2  (unsigned short)(PWM0_CLK_FREQ/587)
#define M3  (unsigned short)(PWM0_CLK_FREQ/659)
#define M4  (unsigned short)(PWM0_CLK_FREQ/698)
#define M5  (unsigned short)(PWM0_CLK_FREQ/784)
#define M6  (unsigned short)(PWM0_CLK_FREQ/880)
#define M7  (unsigned short)(PWM0_CLK_FREQ/988)

#define H1M 1/2 
//�߰˶�
#define H2M 2/2
#define H3M 3/2
#define H4M 4/2
#define H5M 5/2
#define H6M 6/2
#define H7M 7/2
#define NN 0 
//��ֹ��



//������С��
//��¼����
const unsigned short note[50] 
       = {M3, M2, M1, M2,
		M3, M3, M3,
		M2, M2, M2,
		M3, M5, M5,
		M3, M2, M1, M2,
		M3, M3, M3,
		M2, M2, M3, M2, M1,
		NN, 0xff};
const unsigned short duration[50] //��¼����
		= {0x03,0x01,0x02,0x02,
		0x02,0x02,0x04,
		0x02,0x02,0x04,
		0x02,0x02,0x04,
		0x03,0x01,0x02,0x02,
		0x02,0x02,0x04,
		0x02,0x02,0x02,0x02,0x06,
		0x50, 0};

unsigned short pNote=0,nDuration=0;
//��¼���ŵ�������ʣ������

//PWM��ʼ��
void TPM2_Init(void) {
	//SIM Init
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	
	SIM_SCGC5|=BIT10; //ʹ��PORTBʱ��
	SIM_SCGC6 |= BIT26;
	//PORT Init
	PORTB_PCR18 |= BIT8+BIT9;
	//PWM Init
	TPM2_CNT = 0;
	TPM2_MOD = 0x00;
	TPM2_SC = (0x0008 | 0x0007); // ����PWMʱ��
	TPM2_C0SC = (0x0020 | 0x0008); //����PEMģʽ
	TPM2_C0V = 0x00;
}

//����PWMƵ��
void TPM2_Set(unsigned short period) {
	TPM2_MOD = period;
	TPM2_C0V = period/2; //ռ�ձȣ��ɵ�������
}


void SYSTICK_Init(void) {
	SYST_RVR = 2621250; //1/8 sec @ 20.97MHz
	SYST_CVR = 0x00; //Clear Value
	SYST_CSR = 0x07; //Enable Clock
}

void SysTick_Handler(void) {
	unsigned int i;
	if(nDuration==0) {
	if(note[pNote]==0xff) pNote=0;
		//���ò����µ���
		TPM2_Set ((unsigned short)( note[pNote]));
		nDuration= duration[pNote];
		pNote++;
	}
	nDuration--;
	i= SYST_CSR; //�����������־λ
}

void MusicPlay(void) {
		asm("CPSIE i");//ȷ�Ͽ���ȫ���ж�
		TPM2_Init();
		SYSTICK_Init();
		  
}

