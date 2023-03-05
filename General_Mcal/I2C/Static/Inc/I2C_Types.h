/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_Types.h
 *       Module:  I2C
 *
 *  Description:  The file got all the special types that we used for the I2C module
 *
 *********************************************************************************************************************/

#ifndef General_Mcal_I2C_STATIC_INC_I2C_TYPES_H_
#define General_Mcal_I2C_STATIC_INC_I2C_TYPES_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../General_Common/Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/




#define I2C_ALLOWED_INTERRUPTS_NUMBER  3

#define I2C_RETURN_ERROR            (uint16)0x8000
#define I2C_RETURN_FINE             (uint16)0x0000

typedef enum{
    I2C_NUM_0, I2C_NUM_1, I2C_NUM_2, I2C_NUM_3
}I2C_ChannelType;

typedef enum{
    I2C_ModeMaster, I2C_ModeSlave
}I2C_ModeType;

/* Sys_freq */
typedef enum{
    I2cSpeed_SM_100Kbps, I2cSpeed_FM_400Kbps, I2cSpeed_FMP_1Mbps, I2cSpeed_HS_3Mbps
}I2c_SpeedType;

typedef enum{
    I2C_GlitchSuppression_ON, I2C_GlitchSuppression_OFF
}I2C_GlitchSuppressionType;

typedef enum{
    I2C_LoopBack_ON, I2C_LoopBack_OFF
}I2C_LoopBackType;

typedef enum{
    I2C_RepeatedStart_ON, I2C_RepeatedStart_OFF
}I2C_RepeatedStartType;

typedef enum{
    I2C_MasterModeTransmit, I2C_MasterModeReceive, I2C_MasterModeSTOP
}I2C_MasterModeType;

typedef enum{
    I2C_SlaveModeTransmit, I2C_SlaveModeReceive, I2C_SlaveModeSTOP
}I2C_SlaveModeType;

typedef enum{
    I2C_MasterISR_None,
    I2C_MasterISR_TransactionComplete, I2C_MasterISR_ArbitrationLost,
    I2C_MasterISR_TransactionError, I2C_MasterISR_BusTimeout
}I2C_MasterISRModeType;

typedef enum{
    I2C_SlaveISR_None,
    I2C_SlaveISR_TransactionReceived, I2C_SlaveISR_StartCondition,
    I2C_SlaveISR_TransactionRequested, I2C_SlaveISR_StopCondition
}I2C_SlaveISRModeType;

typedef enum{
    I2C0_PREDEF_enum,
    I2C1_PREDEF_enum
}I2C_PredefI2CType;

typedef struct{
    I2C_ChannelType I2C_num;
    I2C_ModeType I2C_Mode;
    I2c_SpeedType I2C_Speed;
    I2C_GlitchSuppressionType I2c_GlitchSupression;
    I2C_LoopBackType I2C_LoopBack;
    I2C_MasterISRModeType I2C_MasterISRMode[I2C_ALLOWED_INTERRUPTS_NUMBER];
    I2C_SlaveISRModeType I2C_SlaveISRMode[I2C_ALLOWED_INTERRUPTS_NUMBER];
    uint8 I2C_Clock_Low_Timeout_Count;
    uint8 I2C_GlitchFilterPulseWidth;
    uint8 I2C_SlaveAddress1;
    uint8 I2C_SlaveAddress2;
}I2C_ConfigType;

typedef struct{
    I2C_ChannelType I2C_num;
    uint8 Adderss;
}I2C_MasterConfigType;


#endif /* General_Mcal_I2C_STATIC_INC_I2C_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: I2C_Types.h
 *********************************************************************************************************************/

