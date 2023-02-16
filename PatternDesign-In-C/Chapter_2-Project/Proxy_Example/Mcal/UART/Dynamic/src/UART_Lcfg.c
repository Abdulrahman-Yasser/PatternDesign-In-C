/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  UART_Lcfg.c
  *        \brief  Digital Input Output Driver
  *
  *      \details  This file contains all the needed Linkning time configuration
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <Mcal/UART/Dynamic/inc/UART_Cfg.h>


const UART_ConfigType UART_Container[UART_CONFIGURED_NUMBER] = {
    {
    .uart_n = UART_NUM_5,.Uart_Mode = UARTMode_Transmit_Receive,
    .Data_Size = UARTSize_EIGHT_BITS, .parity = UARTParity_NO_PARITY,
    .StopBits_Num = UARTSTOPBIT_ONE,
    .Uart_ISRMode = {UARTISRMode_Transmit,UARTISRMode_Receive,UARTISRMode_None,UARTISRMode_None},
    .BaudRate = 9600,.endOfTransmission = 1,
    .fifo_size_rx = UART_FIFO_NOTUSED,.fifo_size_tx = UART_FIFO_NOTUSED
    },
    {
    .uart_n = UART_NUM_7,.Uart_Mode = UARTMode_Transmit_Receive,
    .Data_Size = UARTSize_EIGHT_BITS, .parity = UARTParity_NO_PARITY,
    .StopBits_Num = UARTSTOPBIT_ONE,
    .Uart_ISRMode = {UARTISRMode_Transmit,UARTISRMode_Receive,UARTISRMode_None,UARTISRMode_None},
    .BaudRate = 9600,.endOfTransmission = 0,
    .fifo_size_rx = UART_FIFO_NOTUSED,.fifo_size_tx = UART_FIFO_7_8
    }
};

/* To trigger ISR in case of UART_FIFO_7_8 we should full the FIFO at least with 4 bytes,
 * it will trigger TxMIS after it sends the 4 bytes */

/* To trigger ISR in case of UART_FIFO_6_8 we should full the FIFO at least with 6 bytes,
 * it will trigger TxMIS after it sends the 16 bytes */

/* To trigger ISR in case of UART_FIFO_4_8 we should full the FIFO at least with 10 bytes,
 * it will trigger TxMIS after it sends the 16 bytes */

/* To trigger ISR in case of UART_FIFO_2_8 we should full the FIFO at least with 14 bytes,
 * it will trigger TxMIS after it sends the 16 bytes */

/* To trigger ISR in case of UART_FIFO_1_8 we should full the FIFO at least with 16 bytes,
 * it will trigger TxMIS after it sends the 16 bytes */

/**********************************************************************************************************************
 *  END OF FILE: UART_Lcfg.c
 *********************************************************************************************************************/
