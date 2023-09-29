/*
 * Buutton.c
 *
 *  Created on: Apr 21, 2023
 *      Author: Abdu
 */

#include "../inc/Button.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"

#include <stdlib.h>

static DIO_LevelType read_Button(Button_Type* me);

Button_Type* Button_Create(uint8 DIO_ID){
    Button_Type* me;
    me = (Button_Type*)malloc(sizeof(Button_Type));
    if(me != Null_Ptr){
        me->Dio_Ch = Dio_GetChannelId(DIO_ID);
        me->Read = read_Button;
    }
    return me;
}

void Button_Destroy(Button_Type* me){
    if(me != Null_Ptr){
        free(me);
    }
}

Std_ReturnType Button_Set_CallBackFuncISR(Button_Type* me, void(*ptr_fun)(void)){
    if(me != Null_Ptr){
        Dio_Set_CallBackFun(me->Dio_Ch, ptr_fun);
        return E_OK;
    }
    return E_NOK;
}

uint8 Button_Check_Isr(Button_Type* me){
    return Dio_Check_Isr(me->Dio_Ch);
}

void Button_Remove_Isr(Button_Type* me){
    Dio_Remove_Isr(me->Dio_Ch);
}

static DIO_LevelType read_Button(Button_Type* me){
    me->Last_State = Dio_ReadChannel(me->Dio_Ch);
    return me->Last_State;
}


