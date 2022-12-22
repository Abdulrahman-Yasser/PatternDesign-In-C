/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART.h
 *       Module:  UART
 *
 *  Description:  The file got all the global function we will use in the driver
 *
 *********************************************************************************************************************/
#ifndef UART_H
#define UART_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <Mcal/UART/Static/inc/UART_Types.h>
#include "../../../../Common/Std_Types.h"

#define UART_CONFIGURED_PREDEF_NUMBER  3


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void uart_init(void);

void Poke_to_transmit(UART_ChannelType my_uart);

void Push_to_Transmit(UART_ChannelType my_uart, uint8 x);
void Pop_the_Received(UART_ChannelType my_uart, uint8* data);

void Push_to_Transmit_predef(UART_PredefUARTType uart_predef_arg, uint8 x);
void Pop_the_Received_predef(UART_PredefUARTType uart_predef_arg, uint8* data);


void uart0_handler(void);

void uart1_handler(void);

void uart2_handler(void);

void uart3_handler(void);

void uart4_handler(void);

void uart5_handler(void);

void uart6_handler(void);

void uart7_handler(void);


#endif    /* UART_H */

/**********************************************************************************************************************
 *  END OF FILE: UART.h
 *********************************************************************************************************************/

