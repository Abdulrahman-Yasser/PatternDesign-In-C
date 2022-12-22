/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_Cfg.h
 *       Module:  UART
 *
 *  Description:  The file got all the USER configurations and all the constant values
 *
 *********************************************************************************************************************/
#ifndef UART_CFG_H
#define UART_CFG_H

#include <Mcal/UART/Static/inc/UART_Types.h>

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/
#define UART_CONFIGURED_NUMBER 1


#define UART0_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, No ISR
#define UART1_PREDEF_MACRO        Disable   //Disable EOT, Enable FIFO frequent, No ISR
#define UART5_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, Interrupt Rx, Tx

extern const UART_ConfigType UART_Container[UART_CONFIGURED_NUMBER];

#endif  /* UART_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: UART_Cfg.h
 *********************************************************************************************************************/

