#include "derivative.h"
#include "DigitalTube.h"

//6������ܵ���ʾ����
char DigitalTube_content[6];
const char DigitalTube_numberContent[10] = 
{
	~0xA0, ~0xBE, ~0x62, 0xD5, 0xC3, 0xD6 ,0xDE, 0x45, 0xDF, 0xD7
};

void DigitalTube_init()
{
	//����Port Aʹ��
	SIM_SCGC5 |= 0x200;
	
	//����Port Dʹ��
	SIM_SCGC5 |= 0x1000;
	
	//Port A��pin 12-17��Ϊ����ܿ������������ΪGPIO
	for(int i=12;i<18;i++)
	{
		PORT_PCR_REG(PORTA_BASE_PTR,i) = 0x100;
	}
	
	//Port D��pin 0-7��Ϊ�������ʾ���������ΪGPIO
	for(int i=0;i<8;i++)
	{
		PORT_PCR_REG(PORTD_BASE_PTR,i) = 0x100;
	}
	
	//�������������Ϊoutput
	GPIOA_PDDR |= 0x3F000;
	GPIOD_PDDR |= 0xFF;
	
	//��ʼ�����ر���������ܵ�����������������ܵ���ʾ����
	GPIOA_PDOR |= 0x3F000;
	GPIOD_PDOR |= 0xFF;
}


/**
 * �����ˢ����ʾ�Ĵ���ص�������1ms���ҵ���һ�ν�Ϊ���ʡ�
 */
void DigitalTube_handler()
{
	//��ǰ������ʾ�������
	static int currentTube = 0;
	
	//�������
	GPIOA_PDOR |= 0x3F000;
	GPIOD_PDOR |= 0xFF;
	
	//ֻ��ʾ��ǰ������ʾ�������
	GPIOA_PDOR &= ~(1 << (12+currentTube));
	GPIOD_PDOR &= ~DigitalTube_content[currentTube];
	
	//������Ҫ��ʾ������ܣ�׼����һ�ε���
	currentTube++;
	if(currentTube >= 6) currentTube = 0;
}
