/*
 * Button_Handler.c
 *
 *  Created on: May 5, 2023
 *      Author: Abdu
 */

#include "Button_Handler.h"
#include "DIO/Static/inc/DIO.h"
#include "../HAL_Pattern/LED/LED.h"

void ButtonInit(void){
    int i = 0;
    for(i = 0; i < 9; i++){
        oldVectors[i] = Null_Ptr;
        ISR_Address[i] = Null_Ptr;
    }
    Dio_Init_ISR(DIO_Channel0_F, DIO_ChannelISR_edges_both);
}

void install(void){
    oldVectors[0] = ISR_Address[0];
    oldVectors[1] = ISR_Address[1];
    oldVectors[2] = ISR_Address[2];
    ISR_Address[0] = handleButtonPushInterrupt;
    ISR_Address[1] = handleButtonReleaseInterrupt;
    ISR_Address[2] = handleButtonRemoveISR;
    Dio_Set_CallBackFun(DIO_Channel0_F, ISR_Address[0]);
    Dio_Set_CallBackFun(DIO_Channel0_F, ISR_Address[1]);
    Dio_Set_CallBackFun(DIO_Channel0_F, ISR_Address[2]);
}


void deinstall(void){
    Dio_Remove_CallBackFun(DIO_Channel0_F, ISR_Address[0]);
    Dio_Remove_CallBackFun(DIO_Channel0_F, ISR_Address[1]);
    Dio_Remove_CallBackFun(DIO_Channel0_F, ISR_Address[2]);
    ISR_Address[0] = oldVectors[0];
    ISR_Address[1] = oldVectors[1];
    ISR_Address[2] = oldVectors[2];
    Dio_Set_CallBackFun(DIO_Channel0_F, ISR_Address[0]);
    Dio_Set_CallBackFun(DIO_Channel0_F, ISR_Address[1]);
    Dio_Set_CallBackFun(DIO_Channel0_F, ISR_Address[2]);
}

void handleButtonRemoveISR(void){
    if(Dio_Check_Isr(DIO_Channel0_F) ){
        Dio_Remove_Isr(DIO_Channel0_F);
    }
}

void handleButtonPushInterrupt(void){
    uint8 data;
    if(Dio_Check_Isr(DIO_Channel0_F) ){
        data = Dio_ReadChannel(DIO_Channel0_F);
        if(data == DIO_Level_LOW){
            LED_ON();
        }
    }
}

void handleButtonReleaseInterrupt(void){
    uint8 data;
    if(Dio_Check_Isr(DIO_Channel0_F) ){
        data = Dio_ReadChannel(DIO_Channel0_F);
        if(data == DIO_Level_HIGH){
            LED_OFF();
        }
    }
}




