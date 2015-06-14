#include "derivative.h"
#include "DigitalTube.h"

//6个数码管的显示内容
char DigitalTube_content[6];
const char DigitalTube_numberContent[10] = 
{
	~0xA0, ~0xBE, ~0x62, 0xD5, 0xC3, 0xD6 ,0xDE, 0x45, 0xDF, 0xD7
};

void DigitalTube_init()
{
	//设置Port A使能
	SIM_SCGC5 |= 0x200;
	
	//设置Port D使能
	SIM_SCGC5 |= 0x1000;
	
	//Port A的pin 12-17均为数码管控制输出，配置为GPIO
	for(int i=12;i<18;i++)
	{
		PORT_PCR_REG(PORTA_BASE_PTR,i) = 0x100;
	}
	
	//Port D的pin 0-7均为数码管显示输出，配置为GPIO
	for(int i=0;i<8;i++)
	{
		PORT_PCR_REG(PORTD_BASE_PTR,i) = 0x100;
	}
	
	//将相关引脚配置为output
	GPIOA_PDDR |= 0x3F000;
	GPIOD_PDDR |= 0xFF;
	
	//初始化：关闭所有数码管的输出，清空所有数码管的显示内容
	GPIOA_PDOR |= 0x3F000;
	GPIOD_PDOR |= 0xFF;
}


/**
 * 数码管刷新显示的处理回调函数，1ms左右调用一次较为合适。
 */
void DigitalTube_handler()
{
	//当前正在显示的数码管
	static int currentTube = 0;
	
	//清除数据
	GPIOA_PDOR |= 0x3F000;
	GPIOD_PDOR |= 0xFF;
	
	//只显示当前正在显示的数码管
	GPIOA_PDOR &= ~(1 << (12+currentTube));
	GPIOD_PDOR &= ~DigitalTube_content[currentTube];
	
	//更新需要显示的数码管，准备下一次调用
	currentTube++;
	if(currentTube >= 6) currentTube = 0;
}
