/*
 * Button.h
 *
 *  Created on: Apr 21, 2023
 *      Author: Abdu
 */

#ifndef BUTTON_INTERFACE_STATIC_INC_BUTTON_H_
#define BUTTON_INTERFACE_STATIC_INC_BUTTON_H_


#include "../General_Mcal/DIO/Static/inc/DIO_Types.h"

typedef struct Button_Struct Button_Type;

struct Button_Struct{
    DIO_ChannelType Dio_Ch;
    DIO_LevelType (*Read)(Button_Type* const me);
};

Button_Type* Button_Create(uint8 DIO_ID);
void Button_Destroy(Button_Type* me);

Std_ReturnType Button_Set_CallBackFuncISR(Button_Type* me, void (*ptr_fun)(void));

uint8 Button_Check_Isr(Button_Type* me);

void Button_Remove_Isr(Button_Type* me);

#endif /* BUTTON_INTERFACE_STATIC_INC_BUTTON_H_ */
