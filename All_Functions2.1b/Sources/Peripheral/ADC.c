/*
 * ADC_Init.c
 *
 *  Created on: Aug 16, 2013
 *      Author: renpf
 */

#include "Includes.h"



void ADC0_initial()
{
	    //ADC0 initial
	    SIM_SCGC5|=SIM_SCGC5_PORTB_MASK+SIM_SCGC5_PORTE_MASK;
	    SIM_SCGC6|=SIM_SCGC6_ADC0_MASK;
	    
	    PORTB_PCR3=PORT_PCR_MUX(0X0);
	    
	    PORTE_PCR21=PORT_PCR_MUX(0X0);//ADC0_SE4A
	    PORTE_PCR23=PORT_PCR_MUX(0X0);//ADC0_SE7A
	    
		ADC0_CFG1=ADC_CFG1_ADLSMP_MASK+ADC_CFG1_MODE(1);	
		ADC0_SC3=ADC_SC3_ADCO_MASK; 
		ADC0_SC1A=ADC_SC1_ADCH(13);		 //potentiometers sensor path acquire	
}



void ADC_Init()
{
	ADC0_initial();
}


//anolog convert to digital
unsigned int ADC0_TR_DATA()
{
	unsigned int ADC_Result;
	//check convert complete flag 
	while((ADC0_SC1A&ADC_SC1_COCO_MASK)!=ADC_SC1_COCO_MASK);
	  	
	ADC_Result=ADC0_RA;
	
	//clear flag	   	
   	ADC0_SC1A&=~ADC_SC1_COCO_MASK;
   	
   	return ADC_Result;
}

//change ADC channel
void ADC_channel_temperature()
{
	ADC0_SC1A=ADC_SC1_ADCH(4);		    //PTE1----temperature sensor	
}


//change ADC channel
void ADC_channel_potentiometer()
{
	ADC0_SC1A=ADC_SC1_ADCH(7);		    //potentiometers sensor path acquire
}



void ADC_channel_photosensor()
{
	ADC0_SC1A=ADC_SC1_ADCH(13);		    //photosensor sensor path acquire
}



