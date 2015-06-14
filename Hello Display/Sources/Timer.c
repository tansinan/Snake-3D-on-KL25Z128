#include "derivative.h"
#include "Timer.h"

/**
 * Timer_enable初始化SysTick始终模块，duration的单位为0.1ms
 */
void Timer_init(int duration)
{
	SYST_RVR = 2097*duration;
	SYST_CVR = 0;
	SYST_CSR = 0x07;
}
