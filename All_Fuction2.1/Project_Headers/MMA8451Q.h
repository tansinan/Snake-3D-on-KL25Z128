/*
 * MMA8451Q.h
 *
 *  Created on: Mar 21, 2014
 *      Author: renpf
 */

#ifndef MMA8451Q_H_
#define MMA8451Q_H_

#define MMA8451_I2C_ADDRESS                         0x1D


#define MMA8451_i2c_DisableAck()       I2C0_C1 |= I2C_C1_TXAK_MASK

#define MMA8451_i2c_RepeatedStart()    I2C0_C1     |= 0x04;

#define MMA8451_i2c_Start()            I2C0_C1     |= 0x10;\
                                       I2C0_C1     |= I2C_C1_MST_MASK

#define MMA8451_i2c_Stop()             I2C0_C1  &= ~I2C_C1_MST_MASK;\
                                       I2C0_C1  &= ~I2C_C1_TX_MASK

#define MMA8451_i2c_EnterRxMode()      I2C0_C1   &= ~I2C_C1_TX_MASK;\
                                       I2C0_C1   &= ~I2C_C1_TXAK_MASK

#define MMA8451_i2c_Wait()             while((I2C0_S & I2C_S_IICIF_MASK)==0) {} \
                                              I2C0_S |= I2C_S_IICIF_MASK;

#define MMA8451_i2c_write_byte(data)   I2C0_D = data

#define MWSR                   0x00  /* Master write  */
#define MRSW                   0x01  /* Master read */

void MMA8451_init_I2C(void);
void MMA8451_IIC_StartTransmission (unsigned char SlaveID, unsigned char Mode);
void MMA8451_WriteRegister(unsigned char u8RegisterAddress, unsigned char u8Data);
unsigned char MMA8451_ReadRegister(unsigned char u8RegisterAddress);
void Pause(void);
//MMA8451 initial
void MMA8451_Init();

void UART0_IRQHandler(void);

 void Demo_accMeasure();

#endif /* MMA8451Q_H_ */
