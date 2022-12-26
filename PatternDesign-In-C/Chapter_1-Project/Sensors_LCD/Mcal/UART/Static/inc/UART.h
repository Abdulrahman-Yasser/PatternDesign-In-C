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

#define UART_TRANSMIT_RECEIVE_ONE_CHAR          1
#define UART_TRANSMIT_RECEIVE_MANY_CHAR         0

#define UART_BUFFER_MUST_BE_PUSHED      1
#define UART_BUFFER_MAY_NOT_BE_PUSHED   0

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void uart_init(void);

void Poke_to_transmit(UART_ChannelType my_uart, uint8 OnlyOneChar);
void Poke_to_receive(UART_ChannelType my_uart, uint8 OnlyOneChar);

void Push_to_Transmit(UART_ChannelType my_uart, uint8 x, uint8 must_be_pushed);

void Pop_the_Received(UART_ChannelType my_uart, uint8* data);



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

