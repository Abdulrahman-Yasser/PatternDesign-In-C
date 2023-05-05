/*
 * Testing_DIO.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#include "Testing_DIO.h"

static void Testing_DIO_Init(void);
static void Testing_DIO_Loop(void);
static void Testing_DIO_Isr_But_1(void);

static void Testing_DIO_Isr_But_1(void){
    uint8 registerChecker;
    registerChecker = Dio_Check_Isr(TESTING_DIO_Button_1_Channel);
    if(registerChecker == 1){
        Dio_WriteChannel(TESTING_DIO_LED_1_Channel, DIO_Level_HIGH);
        Dio_WriteChannel(TESTING_DIO_LED_2_Channel, DIO_Level_LOW);
        Dio_Remove_Isr(TESTING_DIO_Button_1_Channel);
    }
}

static void Testing_DIO_Loop(void){
    DIO_LevelType data , old_data ;
    while(1){
        Delay_ms(50);
        data = Dio_ReadChannel(TESTING_DIO_Button_2_Channel);

        if(data == old_data){
            Dio_WriteChannel(TESTING_DIO_LED_2_Channel, data);
            Dio_WriteChannel(TESTING_DIO_LED_1_Channel, !data);
        }else{
            old_data = data;
        }

    }
}


static void Testing_DIO_Init(void){
    Enable_Interrupts();

    Port_Init();
    Dio_Init();
    Dio_Set_CallBackFun(TESTING_DIO_Button_1_Channel, Testing_DIO_Isr_But_1);
    IntCtrl_Init();
}

void Testing_DIO(void){
    Testing_DIO_Init();
    Testing_DIO_Loop();
}


