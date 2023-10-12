/*
 * SPI.c
 *
 *  Created on: Sep 30, 2023
 *      Author: Abdu
 */

#include "SPI.h"
#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "CPU_resources.h"


uint32 SSI_bases[] = {
                                SSI0_BASE_ADDERSS,
                                SSI1_BASE_ADDERSS,
                                SSI2_BASE_ADDERSS,
                                SSI3_BASE_ADDERSS
};

extern void SPI_0_handler(void);
extern void SPI_1_handler(void);
extern void SPI_2_handler(void);
extern void SPI_3_handler(void);

void (*SPI_Tx_n_handler[])(void) = {
                                 SPI_0_handler,
                                 SPI_1_handler,
                                 SPI_2_handler,
                                 SPI_3_handler
};

void (*SPI_Rx_n_handler[])(void) = {
                                 SPI_0_handler,
                                 SPI_1_handler,
                                 SPI_2_handler,
                                 SPI_3_handler
};


void Spi_Init(SsiConfig_t const* const Config){
    uint8 i;
    /**
     * to help calculating the baud rate
     * */
    uint8 SCR_Value, CPSDVSR, myClock;

    /**
     * iterate through the static configured SPI
     * */
    for(i = 0; i < SSI_CONFIGURED_NUMBER; i++){

        /**
         * 1 - Enable the clock for the corresponding SSI channel
         */
        REG_ORING_ONE_BIT_NO_CASTING(SYSCTL_RCGCSSI, Config[i].channelNumber);

        /**
         * 2 - disable the channel before reprogramming by clearing the bit SSE.
         */
        REG_CLEAR_ONE_BIT_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CR1_OFFSET, SSI_CR1_SSE_bitOFFSET);

        /**
         * 3 - Select whether the channel is master or slave.
         */
        REG_ORING_ONE_BIT_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CR1_OFFSET, Config[i].SlaveOrMaster);

        /**
         * 4 - Select Clock source.
         */
        REG_ORING_ONE_BIT_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CC_OFFSET, Config[i].ClkSrc);

        /**
         * 5 - calculate the baudRate.
         */
        if(Config[i].ClkSrc == SSI_SysClk){
            myClock = CPU_CLOCK;

        }else{
            myClock = CPU_PIOSC_CLOCK;
            REG_ORING_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CC_OFFSET, 0x5);
        }
        myClock = (myClock*1000) / Config[i].BaudRate;
        SCR_Value = 1;
        do{
            SCR_Value++;
            CPSDVSR = myClock / SCR_Value;
        }while(((CPSDVSR * SCR_Value != myClock )) && SCR_Value != 255);
        if(SCR_Value == 255){
            while(1);
        }
        REG_ORING_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CR0_OFFSET, (CPSDVSR - 1) << 8);
        REG_ORING_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CPSR_OFFSET, SCR_Value );

        /**
         * 6 - configure the clockPhase, ProtocolMode and DataSize
         */
        REG_ORING_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CR0_OFFSET, Config[i].ClockPolarity << SSI_SerialClockPolarity_Offset
                                                                                     | Config[i].protocolMode << SSI_ProtocolMode_Offset
                                                                                     | (Config[i].DataSize - 1) << SSI_DataSize_Offset);
        if(Config[i].ClockPolarity == E_TRUE){
            /*
             * Need to set GPIO SSInclk pin into pull-up register
             */
        }

        /**
         * 7 - did you use DMA ?
         * configure it here
         */

        /**
         * 8 - interrupt masks you will use
         */
        REG_ORING_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_IM_OFFSET, Config[i].InterruptMask );


        /**
         * 9 - Enable the channel
         */
        REG_ORING_ONE_BIT_CASTING_POINTED(SSI_bases[Config[i].channelNumber] + SSI_CR1_OFFSET, SSI_CR1_SSE_bitOFFSET);
    }
}

void Spi_Transmit_polling(SSI_Channel_t const ssi_channel, uint16 const *data, uint8 dataLength){
    volatile uint8 status;
    uint16 dataFrame = 1;
    uint8 i;
    REG_READ_CASTING_POINTED(status, SSI_bases[ssi_channel] + SSI_CR0_OFFSET);
    status = status & 0x0f;
    while(status--){
        dataFrame = ( dataFrame << 1 ) | 1;
    }
    for(i = 0; i < dataLength; i++){
        Spi_Transmit_one_package(ssi_channel, data[i] & dataFrame);
    }
}


void Spi_Transmit_one_package(SSI_Channel_t const ssi_channel, uint16 const data){
    volatile uint8 status;
    do{
        REG_READ_CASTING_POINTED(status, SSI_bases[ssi_channel] + SSI_SR_OFFSET);
    }while( (status & (1 << SSI_BSY_FLAGG)) & !(status & (1 << SSI_TNF_FLAGG) ) );
    /* if the transmit FIFO is not full and the flag is not busy, break the loop */
    REG_WRITE_CASTING_POINTED(SSI_bases[ssi_channel] + SSI_DR_OFFSET, data );
}

uint16 Spi_RegisterReceive(SSI_Channel_t const ssi_channel){
    volatile uint8 status;
    do{
        REG_READ_CASTING_POINTED(status, SSI_bases[ssi_channel] + SSI_SR_OFFSET);
    }while(status & (1 << SSI_RNE_FLAGG));

    REG_READ_CASTING_POINTED(status, SSI_bases[ssi_channel] + SSI_DR_OFFSET);
    return status;
}


void Spi_Set_Callback(SSI_Channel_t ssi_channel, SSI_Interrupt_Type SSI_Interrupt_event, void (*DioCallBackFun)(void)){
    if(DioCallBackFun != Null_Ptr){
        if(SSI_Interrupt_event == Tx_IM){
            SPI_Tx_n_handler[ssi_channel] = DioCallBackFun;
        }else if(SSI_Interrupt_event == Rx_IM){
            SPI_Rx_n_handler[ssi_channel] = DioCallBackFun;
        }
    }
}


extern void SPI_0_handler(void){
    volatile uint8 status;
    REG_READ_CASTING_POINTED(status, SSI_bases[0] + SSI_MIS_OFFSET);
    switch(status){
    case SSI_IM_TX:
        SPI_Tx_n_handler[0]();
        break;
    case SSI_IM_RX:
        SPI_Rx_n_handler[0]();
        break;
    case SSI_IM_RT:
        break;
    case SSI_IM_POR:
        break;
    default:
        break;
    }

}

extern void SPI_1_handler(void){
    volatile uint8 status;
    REG_READ_CASTING_POINTED(status, SSI_bases[1] + SSI_MIS_OFFSET);
    switch(status){
    case SSI_IM_TX:
        SPI_Tx_n_handler[1]();
        break;
    case SSI_IM_RX:
        SPI_Rx_n_handler[1]();
        break;
    case SSI_IM_RT:
        break;
    case SSI_IM_POR:
        break;
    default:

    }

}

extern void SPI_2_handler(void){
    volatile uint8 status;
    REG_READ_CASTING_POINTED(status, SSI_bases[2] + SSI_MIS_OFFSET);
    switch(status){
    case SSI_IM_TX:
        SPI_Tx_n_handler[2]();
        break;
    case SSI_IM_RX:
        SPI_Rx_n_handler[2]();
        break;
    case SSI_IM_RT:
        break;
    case SSI_IM_POR:
        break;
    default:

    }

}

extern void SPI_3_handler(void){
    volatile uint8 status;
    REG_READ_CASTING_POINTED(status, SSI_bases[3] + SSI_MIS_OFFSET);
    switch(status){
    case SSI_IM_TX:
        SPI_Tx_n_handler[3]();
        break;
    case SSI_IM_RX:
        SPI_Rx_n_handler[3]();
        break;
    case SSI_IM_RT:
        break;
    case SSI_IM_POR:
        break;
    default:

    }

}
