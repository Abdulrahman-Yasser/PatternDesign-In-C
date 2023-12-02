/*
 * TMDQueue_with_Observable.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

/* The Server */

#include <App/HAL_Patterns/Observable/Observable.h>
#include "TMDQueue_with_Observable.h"
#include "../TMDQueue/TMDQueue.h"
#include "HAL_Layer/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"
#include "Common/DataStructure/Queue/static/inc/Queue.h"


#include <stdlib.h>


struct TMDQueue_with_Observable_s{
    TMDQueue* my_TMDQueue_server;
    Observable_Type *my_Observable;
}TMDQueue_with_Observable;


Observable_Type *TMDQueue_with_Observable_GetObservable(void){
    return TMDQueue_with_Observable.my_Observable;
}

void TMDQueue_with_Observable_UnSubscribe(struct TMDQueue_with_Observable_s* me, Observer *o){
    me->my_Observable->unSubscribe(me->my_Observable, o);
}


void TMDQueue_with_Observable_Subscribe(struct TMDQueue_with_Observable_s* me, Observer *o){
    me->my_Observable->Subscribe(me->my_Observable, o);
}

void TMDQueue_with_Observable_Init(struct TMDQueue_with_Observable_s* me){
    me->my_TMDQueue_server = TMDQueue_Create();
    me->my_Observable = Observable_Create();
}

struct TMDQueue_with_Observable_s* TMDQueue_with_Observable_GetHandler(void){
    return &TMDQueue_with_Observable;
}

void TMDQueue_with_Observable_Push(struct TMDQueue_with_Observable_s* me, struct TimeMarkedData* tmd){
    TMDQueue_Insert(me->my_TMDQueue_server, *(tmd));
    me->my_Observable->Notify(me->my_Observable, tmd);
}

struct TimeMarkedData TMDQueue_with_Observable_Pop(struct TMDQueue_with_Observable_s* me){
    struct TimeMarkedData tmd;
    uint8 i;
    i = TMDQueue_getLastIndex(me->my_TMDQueue_server);
    tmd = TMDQueue_remove(me->my_TMDQueue_server, i);
    return tmd;
}

uint8 TMDQueue_with_Observable_IsEmpty(struct TMDQueue_with_Observable_s* me){
    return TMDQueue_IsEmpty(me->my_TMDQueue_server);
}

uint8 TMDQueue_with_Observable_IsFull(struct TMDQueue_with_Observable_s* me){
    return TMDQueue_isFull(me->my_TMDQueue_server);
}

void TMDQueue_with_Observable_Destroy(struct TMDQueue_with_Observable_s* me){
    Observable_Destroy(me->my_Observable);
    TMDQueue_Destroy(me->my_TMDQueue_server);
}

