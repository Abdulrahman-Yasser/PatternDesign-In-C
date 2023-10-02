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

typedef enum{
    SSI_Mode_not_available, SSI_Mode_SPI,
    SSI_Mode_TISS, SSI_Mode_MicroWire
}SSI_Mode_t;

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
    uint8 ClkLevelInIdleState;
    uint8 DataSize;
    SSI_Mode_t Mode;
    SSI_InterruptMode_t Interrupt;
    SSI_ClockSrc_t ClkSrc;
    uint8 BaudRate;
    SSI_DMA_t DMA_State;
    uint8 InterruptMask;
}SpiConfig_t;



#endif /* SPI_STATIC_SPI_TYPES_H_ */
