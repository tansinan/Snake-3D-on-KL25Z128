/*
 * AppSensorTest.c
 *
 *  Created on: May 23, 2015
 *      Author: tansinan
 */

#ifndef APPSENSORTEST_H_
#define APPSENSORTEST_H_

#include "Includes.h"

App AppSensorTest_app;

void AppSensorTest_reportData(char type, int data)
{
	uart0_putchar(0xFF);
	uart0_putchar(type);
	uart0_putchar(data/256);
	uart0_putchar(data%256);
}

void AppSensorTest_drawHandler()
{
	static int counter  = 0;
	static unsigned int ADC_LightIntensity=0;
	static unsigned int ADC_Temperature=0;
	static unsigned int ADC_potentiometer=0;
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
	counter ++ ;
	OLED_W_Str(0,1,"Temperature");
	OLED_W_Numeral(0,64,sizeof(short));
	OLED_W_Str(1,1,"acc_y");
	OLED_W_Numeral(1,64,acc_y);
	OLED_W_Str(5,1,"DEP");
	OLED_W_Str(6,1,"Tsinghua");
	OLED_W_Str(7,1,"Universityhahaha");
}

void AppSensorTest_onKeyPressed(char key)
{
	if(key == KEY_LEFT)
	{
		App_switchTo(OLED_MENU_getApp());		
	}
	else
	{
		//srand(16723);
		/*uart0_putchar('1');	
		urat0__TransmitArray("Leo Ma is so cool!!");
		uart0_putchar('\n');	
		urat0__TransmitArray("Tempreture");
		//urat0_TransmitNumeral(ADC_Temperature);
		urat0__TransmitArray("Light");
		//urat0_TransmitNumeral(ADC_LightIntensity);
		urat0__TransmitArray("Potentiometer");
		//urat0_TransmitNumeral(ADC_potentiometer);				
		uart0_putchar('\n');*/
		AppSensorTest_reportData(0, rand()%100);
		AppSensorTest_reportData(1, rand()%100);
	}
}
void AppSensorTest_init()
{
	App_create(&AppSensorTest_app, AppSensorTest_drawHandler, AppSensorTest_onKeyPressed);
}

App* AppSensorTest_getApp()
{
	return &AppSensorTest_app;
}

#endif /* APPSENSORTTEST_H_ */
