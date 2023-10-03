/*
 * SPI_Lcfg.c
 *
 *  Created on: Sep 30, 2023
 *      Author: Abdu
 */
#include "SPI_Cfg.h"


static SsiConfig_t Ssi_Container[SSI_CONFIGURED_NUMBER] = {
            {.BaudRate = 1000, .ClkSrc = SSI_SysClk, .ClockPolarity = E_FALSE,
            .DMA_State = SSI_DMA_NotAvailable, .DataSize = 8, .Interrupt = SSI_HALF_FIFO,
            .SlaveOrMaster = SSI_Master, .channelNumber = SSI_Channel_2, .protocolMode = SSI_Protocol_SPI
            }
};

SsiConfig_t* SPI_getConfig(void){
    return &Ssi_Container[0];
}
