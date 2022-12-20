/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_Types.h
 *       Module:  UART
 *
 *  Description:  The file got all the special types that we used for the UART module
 *
 *********************************************************************************************************************/

#ifndef UART_TYPES_H
#define UART_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../../../Common/Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint32 UART_BaudRateType;

typedef uint8 UART_EOF_FlagType;


typedef enum{
         UART_NUM_0, UART_NUM_1, UART_NUM_2, UART_NUM_3, UART_NUM_4, UART_NUM_5, UART_NUM_6, UART_NUM_7
}UART_ChannelType;

typedef enum{
    UARTSize_FIVE_BITS, UARTSize_SIX_BITS, UARTSize_SEVEN_BITS, UARTSize_EIGHT_BITS
}UART_SizeType;

typedef enum{
    UARTParity_NO_PARITY, UARTParity_ODD, UARTParity_EVEN = 3
}UART_ParityType;

/* Enumeration to define the number of stop bits */
typedef enum{
    UARTSTOPBIT_ONE, UARTSTOPBIT_TWO
}UART_StopBitsType;

typedef enum{
    UARTISRMode_POLLING, UARTISRMode_INTERRUPT
}UART_ISRModeType;

typedef enum{
    UARTMode_Transmit, UARTMode_Receive, UARTMode_Transmit_Receive
}UART_ModeType;

typedef enum{
    UART_FIFO_NOTUSED, UART_FIFO_1_8, UART_FIFO_2_8, UART_FIFO_4_8, UART_FIFO_6_8, UART_FIFO_7_8
}UART_FIFOType;

typedef enum{
    UART_PREDEF_8_1S_18Rx_18Tx,         // 8 Data-bit, 1 Stop bit, No Priority, FIFO 1/8 Rx, FIFO 1/8 Tx, No ISR
    UART_PREDEF_8_1S_18Rx_18Tx_ISR_EOT, // 8 Data-bit, 1 Stop bit, No Priority, FIFO 1/8 Rx, FIFO 1/8 Tx, End-Of-Transmission ISR
    UART_PREDEF_8_1S_18Rx_18Tx_ISR_FIFO,// 8 Data-bit, 1 Stop bit, No Priority, FIFO 1/8 Rx, FIFO 1/8 Tx, FIFO Memory ISR
    UART_PREDEF_8_1S_Rx_ISR             // 8 Data-bit, 1 Stop bit, No Priority, No FIFO Rx, ISR When ever it receives
}UART_PredefUARTType;

typedef struct{
    UART_ChannelType uart_n;
    UART_ModeType Uart_Mode;
    UART_SizeType Data_Size;
    UART_ParityType parity;
    UART_StopBitsType StopBits_Num;
    UART_ISRModeType Uart_ISRMode;
    UART_BaudRateType BaudRate;
    UART_EOF_FlagType endOfTransmission;
    UART_FIFOType fifo_size_rx;
    UART_FIFOType fifo_size_tx;
    uint8 front_pointer_tx;
    uint8 rear_pointer_tx;
    uint8 front_pointer_rx;
    uint8 rear_pointer_rx;
}UART_ConfigType;


#endif    /* UART_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: UART_Types.h
 *********************************************************************************************************************/

