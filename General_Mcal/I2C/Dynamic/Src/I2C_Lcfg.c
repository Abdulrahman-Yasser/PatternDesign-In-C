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

#include "../inc/I2C_Cfg.h"


const I2C_ConfigType I2C_Container[I2C_CONFIGURED_NUMBER] = {
    {I2C_NUM_2, I2C_ModeMaster, I2cSpeed_SM_100Kbps, I2C_GlitchSuppression_OFF, I2C_LoopBack_OFF,
     {I2C_MasterISR_None, I2C_MasterISR_None, I2C_MasterISR_None},
     {I2C_SlaveISR_None, I2C_SlaveISR_None, I2C_SlaveISR_None}, 0x00, 0x00, 0x7B, 0xF1
    }
};

