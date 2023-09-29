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

#include "../../Static/inc/UART_Types.h"

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/
#define UART_CONFIGURED_NUMBER 2


#define UART0_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, No ISR
#define UART1_PREDEF_MACRO        Disable   //Disable EOT, Enable FIFO frequent, No ISR
#define UART5_PREDEF_MACRO        Disable   //Enable EOT, Disable FIFO, Interrupt Rx, Tx


/* CallBack Functions from APP layer to MCAL_Layer layer*/
#define UART0_TX_ISR_CALLBACK        App_Uart0_Tx_CallBack
#define UART0_RX_ISR_CALLBACK        App_Uart0_Rx_CallBack
#define UART1_TX_ISR_CALLBACK        App_Uart1_Tx_CallBack
#define UART1_RX_ISR_CALLBACK        App_Uart1_Rx_CallBack
#define UART2_TX_ISR_CALLBACK        App_Uart2_Tx_CallBack
#define UART2_RX_ISR_CALLBACK        App_Uart2_Rx_CallBack
#define UART3_TX_ISR_CALLBACK        App_Uart3_Tx_CallBack
#define UART3_RX_ISR_CALLBACK        App_Uart3_Rx_CallBack
#define UART4_TX_ISR_CALLBACK        App_Uart4_Tx_CallBack
#define UART4_RX_ISR_CALLBACK        App_Uart4_Rx_CallBack
#define UART5_TX_ISR_CALLBACK        App_Uart5_Tx_CallBack
#define UART5_RX_ISR_CALLBACK        App_Uart5_Rx_CallBack
#define UART6_TX_ISR_CALLBACK        App_Uart6_Tx_CallBack
#define UART6_RX_ISR_CALLBACK        App_Uart6_Rx_CallBack
#define UART7_TX_ISR_CALLBACK        App_Uart7_Tx_CallBack
#define UART7_RX_ISR_CALLBACK        App_Uart7_Rx_CallBack





extern const UART_ConfigType UART_Container[UART_CONFIGURED_NUMBER];


#endif  /* UART_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: UART_Cfg.h
 *********************************************************************************************************************/

