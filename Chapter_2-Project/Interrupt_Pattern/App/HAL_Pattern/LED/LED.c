/*
 * LED.c
 *
 *  Created on: May 5, 2023
 *      Author: Abdu
 */

#include "LED.h"
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

struct DigitalInterface_struct *myLed;

void LED_Init(void){
    myLed = Digital_Interface_Create(DIO_Channel1_F);
}

void LED_ON(void){
    myLed->Write_High(myLed);
}

void LED_OFF(void){
    myLed->Write_Low(myLed);
}



