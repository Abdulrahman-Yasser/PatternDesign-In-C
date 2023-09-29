/*
 * Testing_PLL.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Abdu
 */

#include "Testing_PLL.h"


void SysTickIsr(void);
void TestingPLL_Loop(void);
void TestingPLL_Initializations(void);

void TestingPLL_Initializations(void){
    PLL_Init();
    Port_Init();
    IntCtrl_Init();
}

void Testing_PLL(void){
    TestingPLL_Initializations();
    TestingPLL_Loop();
}

void TestingPLL_Loop(void){
    while(1){
        Dio_FlipChannel(DIO_Channel1_F);
        Delay_ms(100);
    }
}



