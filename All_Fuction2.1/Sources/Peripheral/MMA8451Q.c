/*
 * MMA8451Q.c
 *
 *  Created on: Mar 21, 2014
 *      Author: renpf
 */

/*
 * File:        k60_i2c.c
 * Purpose:     Code for initializing and using I2C
 *
 * Notes:
 *
 */

#include "Includes.h"



unsigned char MMA8451_data[6];
unsigned char MasterTransmission;
unsigned char SlaveID;


float acc_x=0;
int acc_y=0;
int acc_z=0;

//just for test
int acc_0=0;
int _acc=0;


/*******************************************************************/
/*!
 * I2C Initialization
 * Set Baud Rate and turn on I2C0
 */
void MMA8451_init_I2C(void)
{
    SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK; //Turn on clock to I2C0 module
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;//Turn on clock to PORTB module
    
    
    /* configure GPIO for I2C0 function */
    PORTB_PCR0 = PORT_PCR_MUX(2);
    PORTB_PCR1 = PORT_PCR_MUX(2);
    I2C0_F  = 0x14;       /* set MULT and ICR */
    I2C0_C1 = I2C_C1_IICEN_MASK;       /* enable IIC */
}

/*******************************************************************/
/*!
 * Start I2C Transmision
 * @param SlaveID is the 7 bit Slave Address
 * @param Mode sets Read or Write Mode
 */

void MMA8451_IIC_StartTransmission (unsigned char SlaveID, unsigned char Mode)
{
  if(Mode == MWSR)
  {
    /* set transmission mode */
    MasterTransmission = MWSR;
  }
  else
  {
    /* set transmission mode */
    MasterTransmission = MRSW;
  }

  /* shift ID in right possition */
  SlaveID = (unsigned char) MMA8451_I2C_ADDRESS << 1;

  /* Set R/W bit at end of Slave Address */
  SlaveID |= (unsigned char)MasterTransmission;

  /* send start signal */
  MMA8451_i2c_Start();

  /* send ID with W/R bit */
  MMA8451_i2c_write_byte(SlaveID);
}

/*******************************************************************/
/*!
 * Pause Routine
 */
void Pause(void){
    int n;
    for(n=1;n<50;n++) {
      asm("nop");
    }
}

/*******************************************************************/
/*!
 * Read a register from the MPR084
 * @param u8RegisterAddress is Register Address
 * @return Data stored in Register
 */
unsigned char MMA8451_ReadRegister(unsigned char u8RegisterAddress)
{
  unsigned char result;
  unsigned int j;

  /* Send Slave Address */
  MMA8451_IIC_StartTransmission(SlaveID,MWSR);
  MMA8451_i2c_Wait();

  /* Write Register Address */
  I2C0_D = u8RegisterAddress;
  MMA8451_i2c_Wait();

  /* Do a repeated start */
  I2C0_C1 |= I2C_C1_RSTA_MASK;

  /* Send Slave Address */
  I2C0_D = (MMA8451_I2C_ADDRESS << 1) | 0x01; //read address
  MMA8451_i2c_Wait();

  /* Put in Rx Mode */
  I2C0_C1 &= (~I2C_C1_TX_MASK);

  /* Turn off ACK */
  I2C0_C1 |= I2C_C1_TXAK_MASK;

  /* Dummy read */
  result = I2C0_D ;
  for (j=0; j<5000; j++){};
  MMA8451_i2c_Wait();

  /* Send stop */
  MMA8451_i2c_Stop();
  result = I2C0_D ;
  Pause();
  return result;
}

/*******************************************************************/
/*!
 * Write a byte of Data to specified register on MPR084
 * @param u8RegisterAddress is Register Address
 * @param u8Data is Data to write
 */
void MMA8451_WriteRegister(unsigned char u8RegisterAddress, unsigned char u8Data)
{
  /* send data to slave */
  MMA8451_IIC_StartTransmission(SlaveID,MWSR);
  MMA8451_i2c_Wait();

  I2C0_D = u8RegisterAddress;
  MMA8451_i2c_Wait();

  I2C0_D = u8Data;
  MMA8451_i2c_Wait();

  MMA8451_i2c_Stop();

  Pause();
}

//MMA8451 initial
void MMA8451_Init()
{
	MMA8451_init_I2C();
	//MMA8451_ID=MMA8451_ReadRegister(0x0D);  //read device ID
	MMA8451_WriteRegister(0x2A, 0x01);	
}

/***************************************************************************//*!
 * @brief   UART0 read data register full interrupt service routine.
 ******************************************************************************/
void UART0_IRQHandler(void)
{  
	//ADC_TR_DATA();	
	unsigned int c=0;
	
  if (UART0_S1&UART_S1_RDRF_MASK)  
  {
	  c = UART0_D;	              	  
    if (UART0_S1&UART_S1_TDRE_MASK)
    {           
    	MMA8451_data[0]=MMA8451_ReadRegister(0x01);
    	MMA8451_data[1]=MMA8451_ReadRegister(0x02);
		
    	MMA8451_data[2]=MMA8451_ReadRegister(0x03);
    	MMA8451_data[3]=MMA8451_ReadRegister(0x04);
		
    	MMA8451_data[4]=MMA8451_ReadRegister(0x05);
    	MMA8451_data[5]=MMA8451_ReadRegister(0x06);

    	acc_0=MMA8451_data[0];
    }
  }    
}

void Demo_accMeasure() {
	    MMA8451_data[0]=MMA8451_ReadRegister(0x01);  //x
    	MMA8451_data[1]=MMA8451_ReadRegister(0x02);
		
    	MMA8451_data[2]=MMA8451_ReadRegister(0x03);  //y
    	MMA8451_data[3]=MMA8451_ReadRegister(0x04);
		
    	MMA8451_data[4]=MMA8451_ReadRegister(0x05);  //z
    	MMA8451_data[5]=MMA8451_ReadRegister(0x06);

    	//acc_0=MMA8451_data[0];
    	//_acc=(MMA8451_data[1] | (MMA8451_data[0]<<8) )*0.01;
    	
    	//if(MMA8451_data[0]>0X7F) {
    		acc_x=(float) ( (signed short int)( (MMA8451_data[1] | (MMA8451_data[0]<<8))) );
    		//gyro_x = -(float)((int16)( ( Fpt -> acclAndgyro[3] ) | ( ( Fpt -> acclAndgyro[4] ) << 8 ) ) );
    	//} else {
    	//	acc_x=(MMA8451_data[1] | (MMA8451_data[0]<<8) );
    	//}
    	acc_x *=-0.1;
 
    	/*
    	acc_x=((MMA8451_data[1] | (MMA8451_data[0]<<8)));
    	if(acc_x>=32768) {
    		acc_x=(acc_x-65536);
    	}
    	*/
    	
    	if(MMA8451_data[2]>0X7F) {
    	    acc_y=-(~((MMA8451_data[3] | (MMA8451_data[2]<<8))) + 1 );
    	} else {
    	    acc_y=(MMA8451_data[3] | (MMA8451_data[2]<<8) );
    	}
    	
    	
    	if(MMA8451_data[4]>0X7F) {
    	    acc_z=-(~((MMA8451_data[5] | (MMA8451_data[4]<<8))) + 1 );
    	 } else {
    	    acc_z=(MMA8451_data[5] | (MMA8451_data[4]<<8) );
    	 }    	
}
