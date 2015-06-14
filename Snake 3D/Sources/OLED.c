/*
 * OLED.C
 *
 *  Created on: Jan 2, 2014
 *      Author: millin
 */


#include "derivative.h" /* include peripheral declarations */
#include "OLED.H"


void OLED_SPI0_Init(void)
{
	  unsigned short i;
	  
	/* enable PORTD clock */
	SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;	//PORTD0-3对应OLED控制
	
	SIM_SCGC4|=SIM_SCGC4_SPI0_MASK;
	
	/*portD set to GPIO*/	    
	PORTD_PCR0=PORT_PCR_MUX(0X1); //OLED D/C
	PORTD_PCR3=PORT_PCR_MUX(0X1); //OLED RESET
	
	PORTD_PCR1=PORT_PCR_MUX(0X2); //OLED SPI SCK
	PORTD_PCR2=PORT_PCR_MUX(0X2); //OLED SPI MOSI
	
	//Init SPI0
	SPI0_C1 |= 0x5C; //SPOL=1,CPHA=1,LSBFE=0
	SPI0_BR = 0x10; //Bus Clock 再2分频	
	
	//set as output
	DDR_OLED_DC;
	DDR_OLED_RESET; 
	
	OLED_DC_H;
	
	//产生硬件RESET信号
	OLED_RESET_L;
	for(i=0;i<30000;i++) {
		asm("nop");
	}
	OLED_RESET_H;
}

void OLED_Init(void) //系统初始化调用这个
{

  OLED_SPI0_Init();
  
  if (OLED_TYPE==SSD1325) {
		OLED_W_Ctl(0xae); //OLED off
		OLED_W_Ctl(0xb3); //Clock div
		OLED_W_Ctl(0x91); 
		OLED_W_Ctl(0xa8); //设置为64行
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0xa2); //offset = 76？
		OLED_W_Ctl(0x4C); 
		OLED_W_Ctl(0xa1); //从0开始
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0xa0); //remap，A[6]=1 A[4]=1
		OLED_W_Ctl(0x50);
		OLED_W_Ctl(0xad); //启用外来VCC
		OLED_W_Ctl(0x02); 
		OLED_W_Ctl(0x81); //对比度
		OLED_W_Ctl(0x40); 
		OLED_W_Ctl(0x86); //Current Range
		OLED_W_Ctl(0xbe); //Vcomh设置
		OLED_W_Ctl(0x02);
		OLED_W_Ctl(0xbf); //Set Seg Low Voltage
		OLED_W_Ctl(0x0e); 
		OLED_W_Ctl(0xa4); //Normal Mode
		OLED_W_Ctl(0x23); //Graphic 加速设置，启用了Rect绘制
		OLED_W_Ctl(0x01); 
		OLED_W_Ctl(0x24); //设置Rect范围
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0xaf); //OLED on
  }
  
  if (OLED_TYPE==SSD1306) {
		OLED_W_Ctl(0xae); //OLED off
		OLED_W_Ctl(0xd5); //Set Clock
		OLED_W_Ctl(0x80); 
		OLED_W_Ctl(0xa8); //行数
		OLED_W_Ctl(0x3f); 
		OLED_W_Ctl(0xd3); //行offset
		OLED_W_Ctl(0x00); 
		OLED_W_Ctl(0x40); //Start Line
		OLED_W_Ctl(0x8D); //电荷泵
		OLED_W_Ctl(0x14); 
		OLED_W_Ctl(0xa1); //设置方向 127对应Seg0
		OLED_W_Ctl(0xc8); //Com[n-1] -> Com0
		OLED_W_Ctl(0xda); //无Left/Right Remap，Alter Com Pin，A[5]=0 A[4]=1
		OLED_W_Ctl(0x12); 
		OLED_W_Ctl(0x81); //对比度
		OLED_W_Ctl(0xcf); 
		OLED_W_Ctl(0xd9); //PreCharge
		OLED_W_Ctl(0xf1); 
		OLED_W_Ctl(0xdb); //Vcom
		OLED_W_Ctl(0x40); 
		OLED_W_Ctl(0xa4); //显示
		OLED_W_Ctl(0xa6); //1对应像素on
		OLED_W_Ctl(0xaf); //OLED on
  }
  
  OLED_Clr();
  
}



//write a control word 'cw' to OLED 'cs'(CSA/CSB)
void OLED_W_Ctl(unsigned char cw) {
	unsigned char i;
	
	OLED_DC_L;//write ctl

	while ((SPI0_S & 0x20) == 0); //SPTEF发送不为空
	
	SPI0_D = cw;
		
	while ((SPI0_S & 0x80) == 0); //SPRF接收未满
	
	i=SPI0_D;
	  
	OLED_DC_H;
 
}

//write a data word 'dw' to OLED 'cs'(CSA/CSB)
void OLED_W_Dat(unsigned char dw) {
	unsigned char i;
	
	OLED_DC_H;//write data
	
	while ((SPI0_S & 0x20) == 0); //SPTEF发送不为空
	
	SPI0_D = dw;
		
	while ((SPI0_S & 0x80) == 0); //SPRF接收未满
	
	i=SPI0_D;
	
	OLED_DC_H;
	
}


//clear OLED screen
void OLED_Clr(void) {
	unsigned char i,j;
	
	if (OLED_TYPE==SSD1325) {
		OLED_W_Ctl(0x75); /* set row address */
		OLED_W_Ctl(0x00); /* set row start address */
		OLED_W_Ctl(0x4f); /* set row end address */
		OLED_W_Ctl(0x15); /* set column address */
		OLED_W_Ctl(0x00); /* set column start address */
		OLED_W_Ctl(0x3f); /* set column end address */
		for(i=0;i<64;i++) {
			for(j=0;j<80;j++) {
				OLED_W_Dat(0x00);
			}
		}
	}

	if (OLED_TYPE==SSD1306) {
		for(i=0;i<8;i++) {
			OLED_W_Ctl(0xB0+i);	//选择行
			OLED_W_Ctl(0x00);	//选择列（0-127的Low）
			OLED_W_Ctl(0x10);	//选择列（0-127的High）
			for(j=0;j<128;j++) {
				OLED_W_Dat(0x00);
			}
		}
	}
}
