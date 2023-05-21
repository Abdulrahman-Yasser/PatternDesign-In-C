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

#include <stdlib.h>


struct TMDQueue_with_Observable_s{
    TMDQueue* my_TMDQueue_server;
    Observable_Type *my_Observable;
}TMDQueue_with_Observable;

void PrivateSubscribe(Observer *o);
void PrivateUnSubscribe(Observer *o);
void PrivaateNotify(void);

void PrivateSubscribe(Observer *o){
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

void PrivateUnSubscribe(Observer *o){
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

void PrivaateNotify(void){
    int i;
    struct TimeMarkedData tmd;
    tmd = weatherData_Queue_Pop();
    for(i = 0; i < TMDQueue_with_Observable.my_Observable->nSubscribers; i++){
        TMDQueue_with_Observable.my_Observable->itsNotificationHandler->FunPtr(&tmd);
    }
}


struct TMDQueue_with_Observable_s* weatherData_Queue_Create(void){
    TMDQueue_with_Observable.my_TMDQueue_server = TMDQueue_Create();
    TMDQueue_with_Observable.my_Observable = Observable_Create();
    TMDQueue_with_Observable.my_Observable->Subscribe = PrivateSubscribe;
    TMDQueue_with_Observable.my_Observable->unSubscribe = PrivateUnSubscribe;
    TMDQueue_with_Observable.my_Observable->Notify = PrivaateNotify;
    return &TMDQueue_with_Observable;
}

void WeatherData_Queue_Push(struct TimeMarkedData* tmd){
    TMDQueue_Insert(TMDQueue_with_Observable.my_TMDQueue_server, *(tmd));
    PrivaateNotify();
}

struct TimeMarkedData weatherData_Queue_Pop(void){
    struct TimeMarkedData tmd;
    uint8 i;
    i = TMDQueue_getLastIndex(TMDQueue_with_Observable.my_TMDQueue_server);
    tmd = TMDQueue_remove(TMDQueue_with_Observable.my_TMDQueue_server, i);
    return tmd;
}

uint8 WeatherData_Queue_IsEmpty(void){
    if(TMDQueue_IsEmpty(TMDQueue_with_Observable.my_TMDQueue_server)){
        return 1;
    }else{
        return 0;
    }
}

uint8 WeatherData_Queue_IsFull(void){
    return 1;
    /*
     * it doesn't decrease any way ..
     */
}

void weatherData_Queue_Destroy(void){
    Observable_Destroy(TMDQueue_with_Observable.my_Observable);
    TMDQueue_Destroy(TMDQueue_with_Observable.my_TMDQueue_server);
}

