/*
 * Observable.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#include <App/HAL_Patterns/Observable/Observable.h>

#include "Common/Compiler.h"
#include "../ObserverPattern_Cfg.h"
#include <stdlib.h>

static void PrivateSubscribe(Observable_Type* me, Observer *o);
static void PrivateUnSubscribe(Observable_Type* me, Observer *o);
static void PrivaateNotify(Observable_Type* me, uint8 data);

Observable_Type* Observable_Create(void){
    Observable_Type *me;
    me = (Observable_Type*)malloc(sizeof(Observable_Type));
    if(me != Null_Ptr){
        me->itsNotificationHandler = Null_Ptr;
        me->nSubscribers = 0;
        me->Subscribe = PrivateSubscribe;
        me->unSubscribe = PrivateUnSubscribe;
        me->Notify = PrivaateNotify;
    }
    return me;
}

void Observable_Destroy(Observable_Type* me){
    free(me);
}


static void PrivaateNotify(Observable_Type* me, uint8 data){
    int i;
    if(me->itsNotificationHandler == Null_Ptr || me->nSubscribers == 0){
        return;
    }
    NotificationHandle* ptr = me->itsNotificationHandler;
    ptr->FunPtr(data);
    for(i = 0; i < me->nSubscribers - 1; i++){
        if(ptr->itsNotificationHandle != Null_Ptr){
            ptr = ptr->itsNotificationHandle;
        }
        ptr->FunPtr(data);
    }
}

static void PrivateSubscribe(Observable_Type* me, Observer *o){
    /* add the function in the notification handler */
    NotificationHandle *pNH;
    pNH = me->itsNotificationHandler;
    if(pNH == Null_Ptr){
        me->itsNotificationHandler = NotificationHandle_Create();
        pNH = me->itsNotificationHandler;
    }else{
        while(pNH->itsNotificationHandle != Null_Ptr){
            pNH = pNH->itsNotificationHandle;
        }
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }
    pNH->FunPtr = o->UpdateFuncPtr;
    ++me->nSubscribers;
}

static void PrivateUnSubscribe(Observable_Type* me, Observer *o){
    NotificationHandle *pNH, *pBack;
    pNH = pBack = me->itsNotificationHandler;

    if(pNH == Null_Ptr){
        return ;
    }else{
        if(pNH->FunPtr == o->UpdateFuncPtr){
            me->itsNotificationHandler = pNH->itsNotificationHandle;
            free(pNH);
            --me->nSubscribers;
        }else{
            while(pNH != Null_Ptr){
                pBack = pNH;
                pNH = pNH->itsNotificationHandle;
                if(pNH->FunPtr == o->UpdateFuncPtr){
                    pBack->itsNotificationHandle = pNH->itsNotificationHandle;
                    free(pNH);
                    --me->nSubscribers;
                    return;
                }
            }
        }
    }
}

