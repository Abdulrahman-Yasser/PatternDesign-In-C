/*
 * Motor_Observer.c
 *
 *  Created on: May 31, 2023
 *      Author: Abdu
 */

#include "Motor_Observer.h"

static struct Motor_Observer{
    DigitalObservableSensor_Type* my_Client;
    DigitalInterface_Type* my_Motor;
    uint8 data;
    Observer* my_observer;
}Motor_Observer;

struct Motor_Observer* Motor_Observer_Init(DigitalObservableSensor_Type* the_Client){
    Motor_Observer.my_Motor = Digital_Interface_Create(DIO_Channel0_F);
    Motor_Observer.my_observer = Observer_Create(Motor_Observer_Update);
    Motor_Observer.my_Client = the_Client;
    Motor_Observer.my_Client->my_observable->Subscribe(the_Client->my_observable, Motor_Observer.my_observer);
    return &Motor_Observer;
}

void Motor_Observer_Update(uint8 d){
    Motor_Observer.data = d;
    if(d > 0){
        Motor_Observer.my_Motor->Write_High(Motor_Observer.my_Motor);
    }else{
        Motor_Observer.my_Motor->Write_Low(Motor_Observer.my_Motor);
    }
}
