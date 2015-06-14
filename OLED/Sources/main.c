/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "OLED.H"

unsigned char dtoa(unsigned char c1)
{
  return (c1>=10)? (c1+'A'-10):(c1+'0');
  //此处使用了问号表达式，相当于if/else
}

//give some delay~~
void delay()
{
   unsigned short i,j;
   for(i=0;i<3000;i++)
	{
   		for(j=0;j<100;j++)
      		asm("nop");
	}
}


int main(void) {
	char str[20];
	unsigned short nCnt;
	
	// 启用模块PORTC时钟
	SIM_SCGC5  = SIM_SCGC5 | (1<<11);
	
	// 指定用作GPIO
	PORTC_PCR0 = 0x0100;
	PORTC_PCR3 = 0x0100;
	
	GPIOC_PDDR |= 0x09;
	GPIOC_PDOR &= (~0x09);
	
	
	OLED_Init();
	// 包含PORT的初始化和方向
	
	OLED_Clr();//清屏
	
	nCnt = 0;
	
	//OLED_W_Test();
	
	for(;;)
	{
		delay();
		
		nCnt++;
		
		//闪灯
		GPIOC_PDOR = ~ GPIOC_PDOR;

	    sprintf(str,"Count:    ");
	    str[9]=dtoa(nCnt%10);
	    str[8]=dtoa((nCnt/10)%10);
	    str[7]=dtoa((nCnt/100)%10);
	    OLED_W_Str(0,1,str);
	    
	    OLED_W_Str(2,1,"DEP");
	    OLED_W_Str(4,1,"Tsinghua");
	    OLED_W_Str(6,1,"University");
	}
}
