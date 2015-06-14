/*
 * SMG.h
 *
 *  Created on: May 6, 2015
 *      Author: leo
 */

#ifndef SMG_H_
#define SMG_H_

//delay n ms
void PIT_init(unsigned int number_ms);

void SMG_Init();
void SMG_show_data(unsigned char show_data[],unsigned char number);

//PIT interrupt handle
void PIT_IRQHandler(void);

//data1 forward,data2 backward
//void data_to_array(unsigned int data1,unsigned int data2,unsigned char array[]);
void data_to_array(int data1,int data2,unsigned char array[]);

#endif /* SMG_H_ */
