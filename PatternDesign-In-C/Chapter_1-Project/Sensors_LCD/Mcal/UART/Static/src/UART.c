/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO.c
  *        \brief  Digital Input Output Driver
  *
  *      \details  This file contains the static implementation of the driver
  *                  it contains all the function implementation logic
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <Mcal/UART/Static/inc/UART.h>
#include "../../../../Common/Std_Types.h"


#include "../../../../Common/Mcu_Hw.h"

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/

UART_Config uart_cinfigs[8];

#define UART_BUFFER_SIZE 16

uint8 UART0_TX_buffer[UART_BUFFER_SIZE];
uint8 UART1_TX_buffer[UART_BUFFER_SIZE];
uint8 UART2_TX_buffer[UART_BUFFER_SIZE];
uint8 UART3_TX_buffer[UART_BUFFER_SIZE];
uint8 UART4_TX_buffer[UART_BUFFER_SIZE];
uint8 UART5_TX_buffer[UART_BUFFER_SIZE];
uint8 UART6_TX_buffer[UART_BUFFER_SIZE];
uint8 UART7_TX_buffer[UART_BUFFER_SIZE];

uint8 UART0_RX_buffer[UART_BUFFER_SIZE];
uint8 UART1_RX_buffer[UART_BUFFER_SIZE];
uint8 UART2_RX_buffer[UART_BUFFER_SIZE];
uint8 UART3_RX_buffer[UART_BUFFER_SIZE];
uint8 UART4_RX_buffer[UART_BUFFER_SIZE];
uint8 UART5_RX_buffer[UART_BUFFER_SIZE];
uint8 UART6_RX_buffer[UART_BUFFER_SIZE];
uint8 UART7_RX_buffer[UART_BUFFER_SIZE];


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/



