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

#include "../../../../Common/Std_Types.h"
#include "../../Dynamic/inc/IntCtrl_Cfg.h"

#include "IntCtrl_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void IntCtrl_Init(const IntCtrl_Container_t* IntCtrl_config_var) ;

void IntCtrl_DisableInterrupt(IntCtrl_InterruptType_t InterruptID) ;

void IntCtrl_Enable_Interrupt(IntCtrl_InterruptType_t InterruptID) ;

void IntCtrl_ChangePriority(IntCtrl_InterruptType_t InterruptID, IntCtrl_Prio_t Interrupt_Priority) ;

#endif  /* INTCTRL_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.h
 *********************************************************************************************************************/
