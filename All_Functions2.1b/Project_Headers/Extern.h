/*
 * Extern.h
 *
 *  Created on: May 6, 2015
 *      Author: leo
 */

#ifndef EXTERN_H_
#define EXTERN_H_

#include "AppFramework.h"

typedef signed short int   int16;

extern unsigned int number;
extern unsigned int flag_100ms;
extern unsigned char show[6];
extern unsigned char MMA8451_data[6];
extern unsigned char lED1_light_flag;
extern unsigned char lED2_light_flag;
extern unsigned char lED3_light_flag;
extern unsigned char lED4_light_flag;
extern int acc_0;
extern unsigned int ADC_Result;


//MMA8451Q.c
extern float  acc_x;
extern int acc_y;
extern int acc_z;





/*just for test*/
//from:MMA8451Q.c
extern int acc_0;
extern int _acc;

//Applications
extern App OLED_MENU_app;
extern App AppSensorTest_app;

#endif /* EXTERN_H_ */
