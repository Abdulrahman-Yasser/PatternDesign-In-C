
/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PWM_Cfg.h
 *       Module:  PWM
 *
 *  Description:  The file got all the USER configurations and all the constant values
 *
 *********************************************************************************************************************/

#ifndef MCAL_PWM_DYNAMIC_INC_PWM_CFG_H_
#define MCAL_PWM_DYNAMIC_INC_PWM_CFG_H_

#include "../../Static/Inc/PWM_Types.h"
#include "../../Static/Inc/PWM.h"

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/
#define PWM_CONFIGURED_NUMBER 1


#define PWM0_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, No ISR
#define PWM1_PREDEF_MACRO        Disable   //Disable EOT, Enable FIFO frequent, No ISR
#define PWM5_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, Interrupt Rx, Tx


/* CallBack Functions from APP layer to MCAL layer*/
#define PWM0_TX_ISR_CALLBACK        App_PWM0_Tx_CallBack
#define PWM0_RX_ISR_CALLBACK        App_PWM0_Rx_CallBack
#define PWM1_TX_ISR_CALLBACK        App_PWM1_Tx_CallBack
#define PWM1_RX_ISR_CALLBACK        App_PWM1_Rx_CallBack
#define PWM2_TX_ISR_CALLBACK        App_PWM2_Tx_CallBack
#define PWM2_RX_ISR_CALLBACK        App_PWM2_Rx_CallBack
#define PWM3_TX_ISR_CALLBACK        App_PWM3_Tx_CallBack
#define PWM3_RX_ISR_CALLBACK        App_PWM3_Rx_CallBack





extern const PWM_ConfigType PWM_Container[PWM_CONFIGURED_NUMBER];



#endif /* MCAL_PWM_DYNAMIC_INC_PWM_CFG_H_ */

/**********************************************************************************************************************
 *  END OF FILE: PWM_Cfg.h
 *********************************************************************************************************************/
