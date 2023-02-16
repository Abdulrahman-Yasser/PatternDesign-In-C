/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Types.h
 *       Module:  Global Timer Module Driver (GPT)
 *
 *  Description:  The File contain all the standard types that used in the GPT Driver
 *
 *********************************************************************************************************************/
#ifndef GPT_TYPES_H
#define GPT_TYPES_H

#include "../../../../Common/Std_Types.h"

#define Gpt_InterruptOverFlow       0
#define Gpt_InterruptCaptureMatch   1
#define Gpt_InterruptCaptureEvent   2
#define Gpt_InterruptRTC            3
#define Gpt_InterruptMatch          4
#define Gpt_Interrupt_NotUsed       5


 /**********************************************************************************************************************
  *  GLOBAL DATA TYPES AND STRUCTURES
  *********************************************************************************************************************/

typedef enum{
    Gpt_Channel_Normal_0, Gpt_Channel_Normal_1, Gpt_Channel_Normal_2,
    Gpt_Channel_Normal_3, Gpt_Channel_Normal_4, Gpt_Channel_Normal_5,
    Gpt_Channel_Wide_0, Gpt_Channel_Wide_1, Gpt_Channel_Wide_2,
    Gpt_Channel_Wide_3, Gpt_Channel_Wide_4, Gpt_Channel_Wide_5
}Gpt_ChannelType;


typedef enum{
    Gpt_Mode_NotUsed, Gpt_Mode_OneShot_Concatenate, Gpt_Mode_Periodic_Concatenate,
    Gpt_Mode_OneShot_A, Gpt_Mode_Periodic_A,
    Gpt_Mode_OneShot_B, Gpt_Mode_Periodic_B,
    Gpt_Mode_RTC, Gpt_Mode_EdgeCount, Gpt_Mode_EdgeTime, Gpt_Mode_PWM
}Gpt_ModeType;


typedef uint32 Gpt_ValueType;

typedef enum{
GPT_PREDEF_TIMERType_100US_32BIT,
GPT_PREDEF_TIMERType_60US_16BIT,
GPT_PREDEF_TIMERType_40US_24BIT,
GPT_PREDEF_TIMERType_20US_32BIT
}Gpt_PredefTimerType;

typedef enum{
    Gpt_Prescale_Software, Gpt_Prescale_Hardware, Gpt_Prescale_NotUsed
}Gpt_PrescaleType;

typedef uint32 Gpt_InterruptType;

typedef struct{
    Gpt_ChannelType GptChannelId;
    Gpt_PrescaleType PreScalingType;
    uint32 GptChannelTickFrequency;
    Gpt_ValueType GptChannelTickValueMax;
    Gpt_ModeType ChannelMode;
    Gpt_InterruptType Interrupt_Type;
    void (*GptNotificationCallBack_OverFlowEvent)(void);
    void (*GptNotificationCallBack_Match)(void);
}Gpt_ConfigType;



#endif

/**********************************************************************************************************************
 *  END OF FILE: GPT_Types.h
 *********************************************************************************************************************/
