/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_Cfg.h
 *       Module:  I2C
 *
 *  Description:  The file got all the USER configurations and all the constant values
 *
 *********************************************************************************************************************/
#ifndef I2C_CFG_H
#define I2C_CFG_H

#include "../../Static/Inc/I2C_Types.h"
#include "../../Static/Inc/I2C.h"

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/
#define I2C_CONFIGURED_NUMBER 2


#define I2C0_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, No ISR
#define I2C1_PREDEF_MACRO        Disable   //Disable EOT, Enable FIFO frequent, No ISR
#define I2C5_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, Interrupt Rx, Tx


/* CallBack Functions from APP layer to General_Mcal layer*/
#define I2C0_TX_ISR_CALLBACK        App_I2C0_Tx_CallBack
#define I2C0_RX_ISR_CALLBACK        App_I2C0_Rx_CallBack
#define I2C1_TX_ISR_CALLBACK        App_I2C1_Tx_CallBack
#define I2C1_RX_ISR_CALLBACK        App_I2C1_Rx_CallBack
#define I2C2_TX_ISR_CALLBACK        App_I2C2_Tx_CallBack
#define I2C2_RX_ISR_CALLBACK        App_I2C2_Rx_CallBack
#define I2C3_TX_ISR_CALLBACK        App_I2C3_Tx_CallBack
#define I2C3_RX_ISR_CALLBACK        App_I2C3_Rx_CallBack



#define I2C_LCD_CHANNEL_NUMBER      I2C_NUM_3
#define I2C_RTC_CHANNEL_NUMBER      I2C_NUM_1


extern const I2C_ConfigType I2C_Container[I2C_CONFIGURED_NUMBER];


#endif  /* I2C_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: I2C_Cfg.h
 *********************************************************************************************************************/
