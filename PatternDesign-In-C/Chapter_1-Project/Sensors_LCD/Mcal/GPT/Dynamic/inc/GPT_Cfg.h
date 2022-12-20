/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Cfg.h
 *       Module:  Global Timer Module Driver (GPT)
 *
 *  Description:  The File contain all the User Configuration that will be used in the GPT driver
 *
 *********************************************************************************************************************/
#ifndef GPT_CFG_H
#define GPT_CFG_H

 /**********************************************************************************************************************
  * INCLUDES
  *********************************************************************************************************************/
#include "../../../../Common/Std_Types.h"

#include "../../Static/inc/GPT_Types.h"

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/
#define TIMERS_NUMBERS      11
#define WIDE_TIMER_RANGE_PRIVATE 6

#define GPT_PREDEF_TIMER_NUMBERS        4



#define MY_TIMER0_CHANNEL               (Gpt_ChannelType)Gpt_Channel_Normal_0
#define MY_TIMER0_FREQUENCY             (uint32)15       //15us
#define MY_TIMER0_PRESCALING_TYPE       Gpt_Prescale_Hardware
#define MY_TIMER0_WAIT_PERIOD           (Gpt_ValueType)60000
#define MY_TIMER0_MODE                  (Gpt_ModeType)Gpt_Mode_Periodic_A
#define MY_TIMER0_INTERRUPT             ((1 << Gpt_InterruptOverFlow))
#define MY_TIMER0_ISR_CALLBACK          App_Function

#define MY_DEFAULT_CHANNEL              Gpt_Channel_Normal_0
#define MY_DEFAULT_FREQUENCY            0
#define MY_DEFAULT_PRESCALING_TYPE      Gpt_Prescale_NotUsed
#define MY_DEFAULT_WAIT_PERIOD          0
#define MY_DEFAULT_MODE                 Gpt_Mode_NotUsed
#define MY_DEFAULT_INTERRUPT            Gpt_Interrupt_NotUsed
#define MY_DEFAULT_ISR_CALLBACK         (void*)0



#define GPT_PREDEF_TIMER_100US_32BIT        Disable
#define GPT_PREDEF_TIMER_60US_16BIT         Disable
#define GPT_PREDEF_TIMER_40US_24BIT         Disable
#define GPT_PREDEF_TIMER_20US_32BIT         Disable



#if GPT_PREDEF_TIMER_100US_32BIT == Enable
#define GPT_PREDEF_TIMER_100US_32BIT_FUN_OVERFLOW           App_Function
#define GPT_PREDEF_TIMER_100US_32BIT_FUN_MATCH              App_Function
#endif

#if GPT_PREDEF_TIMER_60US_16BIT == Enable
#define GPT_PREDEF_TIMER_60US_16BIT_FUN_OVERFLOW             App_Function
#define GPT_PREDEF_TIMER_60US_16BIT_FUN_MATCH                App_Function
#endif

#if GPT_PREDEF_TIMER_40US_24BIT == Enable
#define GPT_PREDEF_TIMER_40US_24BIT_FUN_OVERFLOW             App_Function
#define GPT_PREDEF_TIMER_40US_24BIT_FUN_MATCH                App_Function
#endif

#if GPT_PREDEF_TIMER_20US_32BIT == Enable
#define GPT_PREDEF_TIMER_20US_32BIT_FUN_OVERFLOW             App_Function
#define GPT_PREDEF_TIMER_20US_32BIT_FUN_MATCH                App_Function
#endif

/**********************************************************************************************************************
  *  GLOBAL DATA PROTOTYPES
  *********************************************************************************************************************/
extern void App_Function(void);

#endif

/**********************************************************************************************************************
 *  END OF FILE: GPT_Cfg.h
 *********************************************************************************************************************/
