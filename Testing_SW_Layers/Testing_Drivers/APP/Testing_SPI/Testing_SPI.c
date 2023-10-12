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
    char* const my_char = "o k ,   b u t   i   w i l l   b e   t h e r e ";
    while(1){
        Spi_Transmit_one_package(SSI_Channel_2, 0x01);
        Delay_ms(5);
        Spi_Transmit_one_package(SSI_Channel_2, 0x02);
        Delay_ms(5);
        Spi_Transmit_one_package(SSI_Channel_2, 0x03);
        Delay_ms(5);
        Spi_Transmit_one_package(SSI_Channel_2, 0xff);
        Delay_ms(5);
        Spi_Transmit_one_package(SSI_Channel_2, 0x00);
        Delay_ms(5);
        Spi_Transmit_one_package(SSI_Channel_2, 0xf0);
        Delay_ms(5);
        Spi_Transmit_one_package(SSI_Channel_2, 0x0f);
        Delay_ms(5);
        Spi_Transmit_polling(SSI_Channel_2, (uint16*)my_char, 23);
    }
}

void Testing_Spi(void){
    Testing_Spi_Init();
    Testing_Spi_Loop();
}


