#include "ADC.h"
#include "derivative.h"

void ADC_init()
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTE_PCR23 = 0x0000;
	//PORTB_PCR3 = 0x0000;
	
	//配置ADC模式
	ADC0_CFG1 = 0x14;
	
	//ADC配置
	ADC0_CFG2 = 0x0;
	
	ADC0_SC2 = 0x0;
	ADC0_SC2 = 0x8;
	
	//选择使用的ADC通道
	ADC0_SC1A = 0x07;
}

unsigned short ADC_readData()
{
	unsigned short ret;
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));
	ret = ADC0_RA;
	ADC0_SC1A &= ~ADC_SC1_COCO_MASK;
	return ret;
}
