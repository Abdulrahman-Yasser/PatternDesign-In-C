/*
 * Testing_PLL.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Abdu
 */

#include <APP/Testing_SysTick/Testing_SysTick.h>


void SysTickIsr(void);
void TestingSysTick_Loop(void);
void TestingSysTick_Initializations(void);

void TestingSysTick_Initializations(void){
    Port_Init();
    PLL_Init();
    SysTick_Init();
    IntCtrl_Init();
    SysTick_Reload_ms(500);
    SysTick_SetCallBack(SysTickIsr);
    SysTick_Start();
}

void Testing_SysTick(void){
    TestingSysTick_Initializations();
    TestingSysTick_Loop();
}

void TestingSysTick_Loop(void){
    while(1){
    }
}



void SysTickIsr(void){
    static uint8 i = 0;
    if(i == CPU_CLOCK){
        Dio_FlipChannel(DIO_Channel2_F);
        i = 0;
    }else{
        i++;
    }
}
