/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl.h
 *       Module:  Nested Vector Interrupt Controller Driver (NVIC)
 *
 *  Description:  The File contain all the Functions prototype used in the NVIC driver
 *
 *********************************************************************************************************************/

#ifndef INTCTRL_H
#define INTCTRL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "../../Dynamic/inc/IntCtrl_Cfg.h"

#include "IntCtrl_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define Enable_Interrupts()     __asm("  CPSIE I")

#define Disable_Interrupts()     __asm("  CPSID I")

#define Wait_For_Interrupt()   __asm("WFI ")


void IntCtrl_Init(void) ;

void IntCtrl_DisableInterrupt(IntCtrl_InterruptType_t InterruptID) ;

void IntCtrl_Enable_Interrupt(IntCtrl_InterruptType_t InterruptID) ;

void IntCtrl_ChangePriority(IntCtrl_InterruptType_t InterruptID, IntCtrl_Prio_t Interrupt_Priority) ;

#endif  /* INTCTRL_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.h
 *********************************************************************************************************************/
