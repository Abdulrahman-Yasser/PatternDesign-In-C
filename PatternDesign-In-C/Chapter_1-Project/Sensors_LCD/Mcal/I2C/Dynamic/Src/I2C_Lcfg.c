/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  I2C_Lcfg.c
  *        \brief  Digital Input Output Driver
  *
  *      \details  This file contains all the needed Linkning time configuration
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <Mcal/I2C/Dynamic/inc/I2C_Cfg.h>


const I2C_ConfigType I2C_Container[I2C_CONFIGURED_NUMBER] = {
    {I2C_NUM_0, I2C_ModeMaster, I2cSpeed_SM_100Kbps, I2C_GlitchSuppression_OFF, I2C_LoopBack_OFF,
     {I2C_MasterISR_TransactionComplete, I2C_MasterISR_None, I2C_MasterISR_None},
     {I2C_SlaveISR_None, I2C_SlaveISR_None, I2C_SlaveISR_None}, 0x00, 0x00, 0x7B, 0xF1
    }
};

extern const I2C_MasterConfigType I2C_MasterContainer[I2C_MASTER_CONFIGURED_NUMBER] = {
    {
     I2C_NUM_1, I2cSpeed_SM_100Kbps, I2C_GlitchSuppression_OFF, I2C_LoopBack_OFF,
     {I2C_MasterISR_None, I2C_MasterISR_None, I2C_MasterISR_None}, 0, 0
    }
}
extern const I2C_SlaveConfigType I2C_SlaveContainer[I2C_SLAVE_CONFIGURED_NUMBER] = {
    {
     I2C_NUM_2,
     {I2C_SlaveISR_None, I2C_SlaveISR_None, I2C_SlaveISR_None}, 0x7B, 0xF1
    }
}
