/**********************************************************************************************************************

  *  FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  SysTick_Types.h
  *       Module:  SysTick timer Driver
  *
  *  Description:  The file contains all the types of the Systick Driver
  *  
  *********************************************************************************************************************/
#ifndef SYSTICK_TYPES_H
#define SYSTICK_TYPES_H

 /**********************************************************************************************************************
  * INCLUDES
  *********************************************************************************************************************/
#include "../../General_Common/Std_Types.h"



 /**********************************************************************************************************************
  *  GLOBAL DATA TYPES AND STRUCTURES
  *********************************************************************************************************************/
typedef enum {
    SysTick_Interrupt_Disable, SysTick_Interrupt_Enable
}SysTick_InterruptType;

typedef enum {
    SysTick_ClkSrc_PIOSC, SysTick_ClkSrc_SysClk
}SysTick_ClkSrcType;

typedef uint32 SysTick_ReLoadType;

typedef struct{
    SysTick_InterruptType Interrupt;
    SysTick_ClkSrcType Clock;
    SysTick_ReLoadType ReLoad;
}SysTick_Config;

#endif
