/*
 * Testing_DS1307.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Abdu
 */

/*
 * do not forget to edit PORT_Cfg, I2c_Cfg and DIO_Cfg to your own configuration
 */

#include "Testing_DS1307.h"
#include <stdio.h>


static void Testing_DS1307_InitBoard(void);
static void Testing_DS1307_LoopApp(void);



void Testing_DS1307(void){
    Testing_DS1307_InitBoard();
    Testing_DS1307_LoopApp();
}

static void Testing_DS1307_InitBoard(void){
    Port_Init();
    I2C_init();
    IntCtrl_Init();

    RTC_DS1307_Init();
}


static void Testing_DS1307_LoopApp(void){
    volatile RTC_DS1307_TimeFrame_Type my_TimeContainer;
    volatile RTC_DS1307_DateFrame_Type my_DateContainer;
    Std_BoolReturnType my_bool;
    while(1){
        my_bool = RTC_DS1307_get_state();
        my_TimeContainer = RTC_DS1307_getTime();
        my_DateContainer = RTC_DS1307_getDate();
//        printf("hours : %d / min : %d / sec : %d \n", my_TimeContainer.hours, my_TimeContainer.minutes, my_TimeContainer.seconds);
//        printf("year : %d / month : %d / day : %d \n", my_DateContainer.year, my_DateContainer.month, my_DateContainer.day);
        Delay_ms(1000);
    }
}


