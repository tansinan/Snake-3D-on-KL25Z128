/*
 * Timer.h
 * Timer.h����SysTick����һ���̶�Ƶ�ʵ�ʱ�ӡ�֮�����������κ�ע��ص���������ϵͳʱ�ӵ�һ����Ƶ�ϡ�
 * SysTick�������Ŀ�ĺ��Ĺ��ܣ���Ϊ��ѯ�Ƿǳ����Ƽ��ģ����жϲ������ǿ��ã���˻���SysTick����ѯ�ƺ���
 * һ�����ԵĽ��������
 *
 *  Created on: May 28, 2015
 *      Author: tansinan
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Types.h"

void Timer_init(uint16 duration);
int8 Timer_set(uint16 frequency, void (*handler)());
void Timer_unset(int8 timerId);
void Timer_disable();
void SysTick_Handler();

#endif /* TIMER_H_ */
