/*
 * SPI_Types.h
 *
 *  Created on: Sep 30, 2023
 *      Author: Abdu
 */

#ifndef SPI_STATIC_SPI_TYPES_H_
#define SPI_STATIC_SPI_TYPES_H_

#include "General_Common/Std_Types.h"

#define SSI_IM_TX   (1 << 3)
#define SSI_IM_RX   (1 << 2)
#define SSI_IM_RT   (1 << 1)
#define SSI_IM_POR  (1 << 0)

#define SSI_BSY_FLAGG 4
#define SSI_RFF_FLAGG 3
#define SSI_RNE_FLAGG 2
#define SSI_TNF_FLAGG 1
#define SSI_TFE_FLAGG 0
#define SSI_CR1_SSE_bitOFFSET 1

/* CR0 register */
#define SSI_SerialClockPolarity_Offset 6
#define SSI_ProtocolMode_Offset 4
#define SSI_DataSize_Offset 0


typedef enum{
    SSI_Channel_0,
    SSI_Channel_1,
    SSI_Channel_2,
    SSI_Channel_3,
    SSI_Channel_NotUsed
}SSI_Channel_t;

typedef enum{
    Tx_IM, Rx_IM, Rx_TimeOut, Rx_OverRun
}SSI_Interrupt_Type;

typedef enum{
    SSI_Protocol_SPI,
    SSI_Protocol_TISS,
    SSI_Protocol_MicroWire,
    SSI_Protocol_not_available
}SSI_ProtocolMode_t;

typedef enum{
    SSI_Master, SSI_SLAVE_OUTPUT_EN = 4, SSI_SLAVE_OUTPUT_DIS = 0xc
}SSI_SlaveMaster_t;


typedef enum{
    SSI_EOT, SSI_HALF_FIFO
}SSI_InterruptMode_t;

typedef enum{
    SSI_SysClk, SSI_PIOSC
}SSI_ClockSrc_t;

typedef enum{
    SSI_DMA_NotAvailable,
    SSI_DMA_Receive, SSI_DMA_Transmit,
    SSI_DMA_ReceiveTransmit
}SSI_DMA_t;

typedef struct{
    SSI_Channel_t channelNumber;
    Std_BoolReturnType ClockPolarity;
    uint8 DataSize;
    SSI_ProtocolMode_t protocolMode;
    SSI_InterruptMode_t Interrupt;
    SSI_ClockSrc_t ClkSrc;
    uint32 BaudRate;
    SSI_DMA_t DMA_State;
    SSI_SlaveMaster_t SlaveOrMaster;
    uint8 InterruptMask;
}SsiConfig_t;



#endif /* SPI_STATIC_SPI_TYPES_H_ */
