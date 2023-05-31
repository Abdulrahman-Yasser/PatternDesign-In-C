/*
 * Buzzer_Observer.c
 *
 *  Created on: May 31, 2023
 *      Author: Abdu
 */

#include "Buzzer_Observer.h"

static struct Buzzer_Observer{
    DigitalObservableSensor_Type* my_Client;
    DigitalInterface_Type* my_Buzzer;
    uint8 data;
    Observer* my_observer;
}Buzzer_Observer;

struct Buzzer_Observer* Buzzer_Observer_Init(DigitalObservableSensor_Type* the_Client){
    Buzzer_Observer.my_Buzzer = Digital_Interface_Create(DIO_Channel0_F);
    Buzzer_Observer.my_observer = Observer_Create(Buzzer_Observer_Update);
    Buzzer_Observer.my_Client = the_Client;
    Buzzer_Observer.my_Client->my_observable->Subscribe(the_Client->my_observable, Buzzer_Observer.my_observer);
    return &Buzzer_Observer;
}

void Buzzer_Observer_Update(uint8 d){
    Buzzer_Observer.data = d;
    if(d > 0){
        Buzzer_Observer.my_Buzzer->Write_High(Buzzer_Observer.my_Buzzer);
    }else{
        Buzzer_Observer.my_Buzzer->Write_Low(Buzzer_Observer.my_Buzzer);
    }
}
