/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "Includes.h"

unsigned char show[6];
unsigned int ADC_LightIntensity=0;
unsigned int ADC_Temperature=0;
unsigned int ADC_potentiometer=0;

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

Menu menuRoot;
Menu menuFunction1;
Menu menuFunction2;
Menu menuFunction3;

char* entriesRoot[] = {"Function 1", "Function 2", "Function 3"};
Menu* rootChildren[] = {&menuFunction1, &menuFunction2, &menuFunction3};
char* func1Root[] = {"1-1","1-2","1-3"};
char* func2Root[] = {"2-1","2-2","2-3"};
char* func3Root[] = {"3-1","3-2","3-3"};
Menu* funcChildren[] = {NULL, NULL, NULL};

void initMenu()
{
	OLED_MENU_buildMenu(&menuRoot, "root");
	OLED_MENU_setRoot(&menuRoot);
	menuRoot.entries = entriesRoot;
	menuRoot.entryCount = 3;
	menuRoot.children = rootChildren;
	
	OLED_MENU_buildMenu(&menuFunction1, "function 1");
	menuFunction1.entryCount = 3;
	menuFunction1.entries = func1Root;
	menuFunction1.parent = &menuRoot;
	menuFunction1.children = funcChildren;
	
	OLED_MENU_buildMenu(&menuFunction2, "function 2");
	menuFunction2.entryCount = 3;
	menuFunction2.entries = func2Root;
	menuFunction2.parent = &menuRoot;
	menuFunction2.children = funcChildren;
	
	
	OLED_MENU_buildMenu(&menuFunction3, "function 3");
	menuFunction3.entryCount = 3;
	menuFunction3.entries = func3Root;
	menuFunction3.parent = &menuRoot;
	menuFunction3.children = funcChildren;
}

int main(void)
{
	char str[20];
	int _i=0;
	int receiveNumber=0;
	int counter = 0;
	asm("CPSIE i");//确认开启全局中断
	
	PIT_init(0x01);  //1ms interval interrupt
	ADC_Init();
	EN_Init();
	UART0_Init();
	KEY_Init();
	LED_Init();
	MMA8451_Init();  //initial MMA8451 g sensor
	//MusicPlay();
	OLED_Init();
	OLED_Clr();//清屏
	
	initMenu();
	
	for(;;) {
		if(UART0_S1 & UART_S1_RDRF_MASK) {
			receiveNumber=UART0_D;
		}			
		
		//TODO : Add key polling to PIT/SysTick Interupt.
		PORTB_Handler();
		PORTE_Handler();
		
		
		
		counter++;
		//sprintf(str,"Count:");
		/*OLED_W_Str(0,1,"acc_x");
		OLED_W_Numeral(0,64,acc_x);
		OLED_W_Str(1,1,"acc_y");
		OLED_W_Numeral(1,64,acc_y);
		OLED_W_Str(5,1,"DEP");
		OLED_W_Str(6,1,"Tsinghua");
		OLED_W_Str(7,1,"Universityhahaha");*/
		OLED_MENU_drawMenu();
	
		if(counter>=30) {
			Demo_accMeasure();
			counter=0;
		 }
		
		ADC_channel_potentiometer();
		ADC_potentiometer=ADC0_TR_DATA();
		
		ADC_channel_temperature();
		ADC_Temperature=ADC0_TR_DATA(); //ADC之间会互相干扰
		
		ADC_channel_photosensor();
		ADC_LightIntensity=ADC0_TR_DATA();
	
		/*if(counter%100==0) {
			//data_to_array(receiveNumber,acc_x*0.001,show);
			uart0_putchar('1');	
			urat0__TransmitArray("Leo Ma is so cool!!");
			uart0_putchar('\n');	
			urat0__TransmitArray("Tempreture");
			urat0_TransmitNumeral(ADC_Temperature);
			urat0__TransmitArray("Light");
			urat0_TransmitNumeral(ADC_LightIntensity);
			urat0__TransmitArray("Potentiometer");
			urat0_TransmitNumeral(ADC_potentiometer);				
			uart0_putchar('\n');
			_i++;
		}*/
	}
	return 0;
}
