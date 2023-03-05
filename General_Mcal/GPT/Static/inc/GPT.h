/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT.h
 *       Module:  Global Timer Module Driver (GPT)
 *
 *  Description:  The File contain all the global function prototypes and
 *                all the constant definitions in the GPT Driver
 *
 *********************************************************************************************************************/
#ifndef GPT_H
#define GPT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "GPT_Types.h"
#include "../../General_Common/Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void Gpt_Init(void);

void Gpt_DisableNotification(Gpt_ChannelType Channel);

void Gpt_EnableNotification(Gpt_ChannelType Channel);

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);

void Gpt_StopTimer(Gpt_ChannelType Channel);

Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);

Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr);



#endif
