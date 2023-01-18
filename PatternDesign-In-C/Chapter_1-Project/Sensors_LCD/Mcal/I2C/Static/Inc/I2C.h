/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C.h
 *       Module:  I2C
 *
 *  Description:  The file got all the global function we will use in the driver
 *
 *********************************************************************************************************************/


#ifndef MCAL_I2C_STATIC_INC_I2C_H_
#define MCAL_I2C_STATIC_INC_I2C_H_

#include "I2C_Types.h"


#define I2C_CONFIGURED_PREDEF_NUMBER  3

#define I2C_TRANSMIT_RECEIVE_ONE_CHAR          1
#define I2C_TRANSMIT_RECEIVE_MANY_CHAR         0

#define I2C_BUFFER_MUST_BE_PUSHED      1
#define I2C_BUFFER_MAY_NOT_BE_PUSHED   0

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void I2C_init(void);

uint16 I2C_MasterPoke_to_transmit(I2C_ChannelType my_I2C, uint8 slave_address, uint8 Bytes_Cnt);
uint16 I2C_MasterPoke_to_receive(I2C_ChannelType my_I2C, uint8 slave_address, uint8 Bytes_Cnt);

uint16 I2C_Push_to_Transmit(I2C_ChannelType my_I2C, uint8 x, uint8 must_be_pushed);

uint16 I2C_Pop_the_Received(I2C_ChannelType my_I2C, uint8* data);



void I2C0_handler(void);

void I2C1_handler(void);

void I2C2_handler(void);

void I2C3_handler(void);





#endif /* MCAL_I2C_STATIC_INC_I2C_H_ */

/**********************************************************************************************************************
 *  END OF FILE: I2C.h
 *********************************************************************************************************************/

