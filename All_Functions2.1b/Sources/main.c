/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "Includes.h"
#include "AppSensorTest.h"

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

void initMenu()
{
	static char* entriesRoot[] = {"Function 1", "Function 2", "Function 3"};
	static Menu* rootChildren[] = {&menuFunction1, &menuFunction2, &menuFunction3};
	static char* func1Root[] = {"SensorDemo","1-2","1-3"};
	static char* func2Root[] = {"2-1","2-2","2-3"};
	static char* func3Root[] = {"3-1","3-2","3-3"};
	static Menu* funcChildrenMenu[] = {NULL, NULL, NULL};
	static App* func1ChildrenApplication[] = {&AppSensorTest_app, NULL, NULL};
	static App* funcChildrenApplication[] = {NULL, NULL, NULL};
	OLED_MENU_buildMenu(&menuRoot, "root");
	OLED_MENU_setRoot(&menuRoot);
	menuRoot.entries = entriesRoot;
	menuRoot.entryCount = 3;
	menuRoot.children = rootChildren;
	
	OLED_MENU_buildMenu(&menuFunction1, "function 1");
	menuFunction1.entryCount = 3;
	menuFunction1.entries = func1Root;
	menuFunction1.parent = &menuRoot;
	menuFunction1.children = funcChildrenMenu;
	menuFunction1.childrenApplication = func1ChildrenApplication;
	
	OLED_MENU_buildMenu(&menuFunction2, "function 2");
	menuFunction2.entryCount = 3;
	menuFunction2.entries = func2Root;
	menuFunction2.parent = &menuRoot;
	menuFunction2.children = funcChildrenMenu;
	menuFunction2.childrenApplication = funcChildrenApplication;
	
	
	OLED_MENU_buildMenu(&menuFunction3, "function 3");
	menuFunction3.entryCount = 3;
	menuFunction3.entries = func3Root;
	menuFunction3.parent = &menuRoot;
	menuFunction3.children = funcChildrenMenu;
	menuFunction3.childrenApplication = funcChildrenApplication;
}

int main(void)
{
	App* currentApp;
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
	
	//Initialise the "Main Menu" Application
	OLED_MENU_init();
	//Initialise the "Sensor Test" Application
	AppSensorTest_init();
	
	//Initialise menu data for the "Main Menu Application"
	//Note: this must be called after all application intialized!!!
	initMenu();
	App_switchTo(OLED_MENU_getApp());
	
	for(;;) {
		if(UART0_S1 & UART_S1_RDRF_MASK) {
			receiveNumber=UART0_D;
		}			
		
		//TODO : Add key polling to PIT/SysTick Interupt.
		PORTB_Handler();
		PORTE_Handler();
		currentApp = App_getCurrentApp();
		if(currentApp != NULL)
		{
			currentApp->onDraw();
		}
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
