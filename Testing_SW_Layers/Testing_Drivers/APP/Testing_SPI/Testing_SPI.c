/*
 * Testing_SPI.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Abdu
 */


#include "Testing_SPI.h"

#include "General_Mcal/PORT/Static/inc/PORT.h"
#include "General_Mcal/PLL/Static/inc/PLL.h"
#include "General_Mcal/SPI/Static/SPI.h"


static void Testing_Spi_Init(void){
    PLL_Init();
    Port_Init();
    Spi_Init(SPI_getConfig());
}
static void Testing_Spi_Loop(void){
    Spi_Transmit_one_package(SSI_Channel_0, 0x0f);
    Delay_ms(1000);
    Spi_Transmit_one_package(SSI_Channel_0, 0xf0);
    Delay_ms(1000);
    Spi_Transmit_one_package(SSI_Channel_0, 0xff);
    Delay_ms(1000);
    Spi_Transmit_one_package(SSI_Channel_0, 0xCC);
    Delay_ms(1000);
}

void Testing_Spi(void){
    Testing_Spi_Init();
    Testing_Spi_Loop();
}


