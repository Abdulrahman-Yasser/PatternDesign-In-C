/*
 * Server_with_Observable.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

/* The Server */

#include <App/HAL_Patterns/Observable/Observable.h>
#include <App/HAL_Patterns/Server/Server_with_Observable/Server_with_Observable.h>

#include "HAL_Layer/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"
#include "Common/DataStructure/Queue/static/inc/Queue.h"

#include "Server_with_Observable.h"

#include "HAL_Layer/Button_Interface/Static/inc/Button.h"

#include <stdlib.h>

uint8 g_status = 0;


static struct Server_with_Observable_s{
    Button_Type* my_button;
    Observable_Type *my_Observable;
}Server_with_Observable;


struct Server_with_Observable_s* get_my_server(void){
    return &(Server_with_Observable);
}



void Server_with_Observable_UnSubscribe(struct Server_with_Observable_s* me, Observer *o){
    me->my_Observable->unSubscribe(me->my_Observable, o);
}


void Server_with_Observable_Subscribe(struct Server_with_Observable_s* me, Observer *o){
    me->my_Observable->Subscribe(me->my_Observable, o);
}

Observable_Type* Server_with_Observable_GetObservable(struct Server_with_Observable_s* me){
    return me->my_Observable;
}

void Server_with_Observable_Init(struct Server_with_Observable_s* me){
    me->my_button = Button_Create(0);
    me->my_Observable = Observable_Create();
}


void Server_with_Observable_Push(struct Server_with_Observable_s* me){
    g_status = me->my_button->Read(me->my_button);
    me->my_Observable->Notify(me->my_Observable, g_status);
}

uint8 Server_with_Observable_Pop(struct Server_with_Observable_s* me){
    return g_status;
}

uint8 Server_with_Observable_IsEmpty(struct Server_with_Observable_s* me){
        return 0;
}

uint8 Server_with_Observable_IsFull(struct Server_with_Observable_s* me){
    return 1;
    /*
     * it doesn't decrease any way ..
     */
}

void Server_with_Observable_Destroy(struct Server_with_Observable_s* me){
    Observable_Destroy(me->my_Observable);
    Button_Destroy(me->my_button);
}

