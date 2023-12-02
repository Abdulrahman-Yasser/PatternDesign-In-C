/*
 * LED_1.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */
#include <App/HAL_Patterns/Client/LED_1/LED_1.h>
#include <App/HAL_Patterns/Server/Server_with_Observable/Server_with_Observable.h>
#include <stdlib.h>

#include "../../Observer/Observer.h"
#include "../../Observable/Observable.h"

#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"

static struct LED_1_s{
    DigitalInterface_Type* my_led;
    Observer *my_Observer;
}my_LED_1;

static void LED_1_updateLED(uint8 status);


void my_LED_1_Init(struct LED_1_s* const me, Observable_Type* my_observable){
    me->my_led = Digital_Interface_Create(DIO_Channel1_F);

    me->my_Observer = Observer_Create(LED_1_updateLED);
    my_observable->Subscribe(my_observable, me->my_Observer);
}



/*
 * The update function that will be passed through the observer to the observable.
 * Here in FireDisplay it's responsible of writing "FIRE" on LCD, set LED and Buzzer HIGH
   if there is a fire only. Other wise it will do nothing.
 * It will write it over the display and it will not free the LCD's semaphore, because
   if it set the semaphore free then the HistogramDisplay will easily write over it .
 */
static void LED_1_updateLED(uint8 status){
    /* Put what you need to update */
    if(status == 1){
        my_LED_1.my_led->Write_High(my_LED_1.my_led);
    }else if(status == 0){
        my_LED_1.my_led->Write_Low(my_LED_1.my_led);
    }
}



void LED_1_setItsLED(struct LED_1_s* const me, DigitalInterface_Type* p_LED_Handler){
    me->my_led = p_LED_Handler;
}

struct LED_1_s * LED_1_GetHandler(void){
    return &my_LED_1;
}

