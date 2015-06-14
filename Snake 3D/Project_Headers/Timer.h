/*
 * Timer.h
 * Timer.h利用SysTick设置一个固定频率的时钟。之后，它将允许任何注册回调函数到该系统时钟的一个分频上。
 * SysTick是这个项目的核心功能，因为轮询是非常不推荐的，而中断并不总是可用，因此基于SysTick的轮询似乎是
 * 一个折衷的解决方法。
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
