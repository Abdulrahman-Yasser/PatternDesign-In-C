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
#include "../../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"
#include "../../General_Common/DataStructure/Queue/static/inc/Queue.h"


#include <stdlib.h>


struct TMDQueue_with_Observable_s{
    TMDQueue* my_TMDQueue_server;
    Observable_Type *my_Observable;
}TMDQueue_with_Observable;

static void PrivateSubscribe(Observer *o);
static void PrivateUnSubscribe(Observer *o);
static void PrivaateNotify(void);

static void PrivateSubscribe(Observer *o){
    /* add the function in the notification handler */
    NotificationHandle *pNH;
    pNH = TMDQueue_with_Observable.my_Observable->itsNotificationHandler;
    if(pNH == Null_Ptr){
        TMDQueue_with_Observable.my_Observable->itsNotificationHandler = NotificationHandle_Create();
        pNH = TMDQueue_with_Observable.my_Observable->itsNotificationHandler;
    }else{
        while(pNH->itsNotificationHandle != Null_Ptr){
            pNH = pNH->itsNotificationHandle;
        }
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }
    pNH->FunPtr = o->UpdateFuncPtr;
    ++TMDQueue_with_Observable.my_Observable->nSubscribers;
}

static void PrivateUnSubscribe(Observer *o){
    NotificationHandle *pNH, *pBack;
    pNH = pBack = TMDQueue_with_Observable.my_Observable->itsNotificationHandler;

    if(pNH == Null_Ptr){
        return ;
    }else{
        if(pNH->FunPtr == o->UpdateFuncPtr){
            TMDQueue_with_Observable.my_Observable->itsNotificationHandler = pNH->itsNotificationHandle;
            free(pNH);
            --TMDQueue_with_Observable.my_Observable->nSubscribers;
        }else{
            while(pNH != Null_Ptr){
                pBack = pNH;
                pNH = pNH->itsNotificationHandle;
                if(pNH->FunPtr == o->UpdateFuncPtr){
                    pBack->itsNotificationHandle = pNH->itsNotificationHandle;
                    free(pNH);
                    --TMDQueue_with_Observable.my_Observable->nSubscribers;
                    return;
                }
            }
        }
    }
}

static void PrivaateNotify(void){
    int i;
    struct TimeMarkedData tmd;
    tmd = TMDQueue_with_Observable_Pop(&TMDQueue_with_Observable);
    for(i = 0; i < TMDQueue_with_Observable.my_Observable->nSubscribers; i++){
        TMDQueue_with_Observable.my_Observable->itsNotificationHandler->FunPtr(&tmd);
    }
}


void TMDQueue_with_Observable_UnSubscribe(struct TMDQueue_with_Observable_s* me, Observer *o){
    me->my_Observable->unSubscribe(o);
}


void TMDQueue_with_Observable_Subscribe(struct TMDQueue_with_Observable_s* me, Observer *o){
    me->my_Observable->Subscribe(o);
}

void TMDQueue_with_Observable_Init(struct TMDQueue_with_Observable_s* me){
    me->my_TMDQueue_server = TMDQueue_Create();
    me->my_Observable = Observable_Create();
    me->my_Observable->Subscribe = PrivateSubscribe;
    me->my_Observable->unSubscribe = PrivateUnSubscribe;
    me->my_Observable->Notify = PrivaateNotify;
}

struct TMDQueue_with_Observable_s* TMDQueue_with_Observable_GetHandler(void){
    return &TMDQueue_with_Observable;
}

void TMDQueue_with_Observable_Push(struct TMDQueue_with_Observable_s* me, struct TimeMarkedData* tmd){
    TMDQueue_Insert(me->my_TMDQueue_server, *(tmd));
    PrivaateNotify();
}

struct TimeMarkedData TMDQueue_with_Observable_Pop(struct TMDQueue_with_Observable_s* me){
    struct TimeMarkedData tmd;
    uint8 i;
    i = TMDQueue_getLastIndex(me->my_TMDQueue_server);
    tmd = TMDQueue_remove(me->my_TMDQueue_server, i);
    return tmd;
}

uint8 TMDQueue_with_Observable_IsEmpty(struct TMDQueue_with_Observable_s* me){
    if(TMDQueue_IsEmpty(me->my_TMDQueue_server)){
        return 1;
    }else{
        return 0;
    }
}

uint8 TMDQueue_with_Observable_IsFull(struct TMDQueue_with_Observable_s* me){
    return 1;
    /*
     * it doesn't decrease any way ..
     */
}

void TMDQueue_with_Observable_Destroy(struct TMDQueue_with_Observable_s* me){
    Observable_Destroy(me->my_Observable);
    TMDQueue_Destroy(me->my_TMDQueue_server);
}

