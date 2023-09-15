/*
 * Testing_SevenSegment.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Abdu
 */

#include "Testing_SevenSegment.h"

void Testing_SevenSegment_Init(void){
    PLL_Init();
    Port_Init();
}

void Testing_SevenSegment_loop(void){
    uint8 c = 0;
    while(1){
        SeventSegment_WriteSpecificOne(0, c);
        c++;
        c = c % 10;
        Delay_ms(1000);
    }
}

