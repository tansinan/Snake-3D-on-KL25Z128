/*
 * Timer.cpp
 *
 *  Created on: May 28, 2015
 *      Author: tansinan
 */

#include "Timer.h"
#include "derivative.h"

#define TIMER_MAX_AMOUNT 10

struct
{
	uint16 duration;
	uint16 currentTime;
	void (*handler)();
} Timer_data[TIMER_MAX_AMOUNT];


static int systemTime = 0;
/**
 * Timer_init������ʼ��ϵͳ��ʱ��
 * @param duration ���õ�ʱ�䣬��λΪ0.1ms
 * ��ע��ʵ����duration����ܳ���8000,��ΪSYST_RVRֻ��24λ��Ч
 */
void Timer_init(uint16 duration)
{
	//����ȫ���ж�
	asm("CPSIE i");
	//��Ϊϵͳ������20.97MHz��Ƶ���£����ÿ2097��ʱ��������0.1ms
	SYST_RVR = 2097*duration;
	SYST_CVR = 0x00;
	SYST_CSR = 0x07;
	for(int i=0;i<TIMER_MAX_AMOUNT;i++)
	{
		Timer_data[i].handler=nullptr;
	}
}

/**
 * Timer_set��������һ���µļ�ʱ��
 */
int8 Timer_set(uint16 frequency, void (*handler)())
{
	for(int i=0;i<TIMER_MAX_AMOUNT;i++)
	{
		if(Timer_data[i].handler==nullptr)
		{
			Timer_data[i].duration = frequency;
			Timer_data[i].handler = handler;
			Timer_data[i].currentTime = 0;
			return i;
		}
	}
	return -1;
}

void Timer_unset(int8 timerId)
{
	Timer_data[timerId].handler = nullptr;
}

void Timer_disable()
{
	
}

void SysTick_Handler(void)
{
	unsigned int i;
	for(int i=0;i<TIMER_MAX_AMOUNT;i++)
	{
		if(Timer_data[i].handler!=nullptr)
		{
			Timer_data[i].currentTime ++;
			if(Timer_data[i].currentTime == Timer_data[i].duration)
			{
				Timer_data[i].handler();
				Timer_data[i].currentTime = 0;
			}
		}
	}
	i = SYST_CSR;
	systemTime++;
}

uint32 Timer_getSystemTime()
{
	return systemTime;
}
