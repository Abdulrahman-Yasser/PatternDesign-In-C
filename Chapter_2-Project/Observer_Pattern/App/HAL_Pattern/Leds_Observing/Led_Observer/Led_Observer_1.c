/*
 * Led_Observer_1.c
 *
 *  Created on: May 31, 2023
 *      Author: Abdu
 */

#include <App/HAL_Pattern/Leds_Observing/Led_Observer/Led_Observer_1.h>

static struct Led_Observer{
    DigitalObservableSensor_Type* my_Client;
    DigitalInterface_Type* my_Led;
    uint8 data;
    Observer* my_observer;
}Led_Observer_1;

struct Led_Observer* Led_Observer_Init(DigitalObservableSensor_Type* the_Client){
    Led_Observer_1.my_Led = Digital_Interface_Create(DIO_Channel1_F);
    Led_Observer_1.my_observer = Observer_Create(Led_Observer_Update);
    Led_Observer_1.my_Client = the_Client;
    Led_Observer_1.my_Client->my_observable->Subscribe(the_Client->my_observable, Led_Observer_1.my_observer);
    return &Led_Observer_1;
}

void Led_Observer_Update(uint8 d){
    Led_Observer_1.data = d;
    if(d > 0){
        Led_Observer_1.my_Led->Write_High(Led_Observer_1.my_Led);
    }else{
        Led_Observer_1.my_Led->Write_Low(Led_Observer_1.my_Led);
    }
}
