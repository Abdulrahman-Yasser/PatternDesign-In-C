/*
 * Buzzer.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */
#include <App/HAL_Patterns/Client/Buzzer/Buzzer.h>
#include <App/HAL_Patterns/Server/Server_with_Observable/Server_with_Observable.h>
#include <stdlib.h>

#include "../../Observer/Observer.h"
#include "../../Observable/Observable.h"

#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"

static struct Buzzer_s{
    DigitalInterface_Type* my_buzzer;
    Observer *my_Observer;
}my_Buzzer;

static void Buzzer_update(uint8 status);


void my_Buzzer_Init(struct Buzzer_s* const me, Observable_Type* my_observable){
    me->my_buzzer = Digital_Interface_Create(DIO_Channel1_B);

    me->my_Observer = Observer_Create(Buzzer_update);
    my_observable->Subscribe(me->my_Observer);
}



/*
 * The update function that will be passed through the observer to the observable.
 * Here in FireDisplay it's responsible of writing "FIRE" on LCD, set LED and Buzzer HIGH
   if there is a fire only. Other wise it will do nothing.
 * It will write it over the display and it will not free the LCD's semaphore, because
   if it set the semaphore free then the HistogramDisplay will easily write over it .
 */
static void Buzzer_update(uint8 status){
    /* Put what you need to update */
    if(status == 1){
        my_Buzzer.my_buzzer->Write_High(my_Buzzer.my_buzzer);
    }else if(status == 0){
        my_Buzzer.my_buzzer->Write_Low(my_Buzzer.my_buzzer);
    }
}



void Buzzer_setItsLED(struct Buzzer_s* const me, DigitalInterface_Type* p_Buzzer_Handler){
    me->my_buzzer = p_Buzzer_Handler;
}

struct Buzzer_s * Buzzer_GetHandler(void){
    return &(my_Buzzer);
}

