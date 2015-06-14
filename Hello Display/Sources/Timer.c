#include "derivative.h"
#include "Timer.h"

/**
 * Timer_enable��ʼ��SysTickʼ��ģ�飬duration�ĵ�λΪ0.1ms
 */
void Timer_init(int duration)
{
	SYST_RVR = 2097*duration;
	SYST_CVR = 0;
	SYST_CSR = 0x07;
}
