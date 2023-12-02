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




static void PrivateSubscribe(Observer *o);
static void PrivateUnSubscribe(Observer *o);
static void PrivaateNotify(void);

static void PrivateSubscribe(Observer *o){
    /* add the function in the notification handler */
    NotificationHandle *pNH;
    struct Server_with_Observable_s* Server_with_Observable = get_my_server();
    pNH = Server_with_Observable->my_Observable->itsNotificationHandler;
    if(pNH == Null_Ptr){
        Server_with_Observable->my_Observable->itsNotificationHandler = NotificationHandle_Create();
        pNH = Server_with_Observable->my_Observable->itsNotificationHandler;
    }else{
        while(pNH->itsNotificationHandle != Null_Ptr){
            pNH = pNH->itsNotificationHandle;
        }
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }
    pNH->FunPtr = o->UpdateFuncPtr;
    ++Server_with_Observable->my_Observable->nSubscribers;
}

static void PrivateUnSubscribe(Observer *o){
    NotificationHandle *pNH, *pBack;
    struct Server_with_Observable_s* Server_with_Observable = get_my_server();
    pNH = pBack = Server_with_Observable->my_Observable->itsNotificationHandler;

    if(pNH == Null_Ptr){
        return ;
    }else{
        if(pNH->FunPtr == o->UpdateFuncPtr){
            Server_with_Observable->my_Observable->itsNotificationHandler = pNH->itsNotificationHandle;
            free(pNH);
            --Server_with_Observable->my_Observable->nSubscribers;
        }else{
            while(pNH != Null_Ptr){
                pBack = pNH;
                pNH = pNH->itsNotificationHandle;
                if(pNH->FunPtr == o->UpdateFuncPtr){
                    pBack->itsNotificationHandle = pNH->itsNotificationHandle;
                    free(pNH);
                    --Server_with_Observable->my_Observable->nSubscribers;
                    return;
                }
            }
        }
    }
}

static void PrivaateNotify(void){
    int i;
    uint8 status;
    struct Server_with_Observable_s* Server_with_Observable = get_my_server();
    status = Server_with_Observable_Pop(Server_with_Observable);
    if(Server_with_Observable->my_Observable->itsNotificationHandler == Null_Ptr || Server_with_Observable->my_Observable->nSubscribers == 0){
        return;
    }
    NotificationHandle* ptr = Server_with_Observable->my_Observable->itsNotificationHandler;
    ptr->FunPtr(status);
    for(i = 0; i < Server_with_Observable->my_Observable->nSubscribers - 1; i++){
        if(ptr->itsNotificationHandle != Null_Ptr){
            ptr = ptr->itsNotificationHandle;
        }
        ptr->FunPtr(status);
    }
}


void Server_with_Observable_UnSubscribe(struct Server_with_Observable_s* me, Observer *o){
    me->my_Observable->unSubscribe(o);
}


void Server_with_Observable_Subscribe(struct Server_with_Observable_s* me, Observer *o){
    me->my_Observable->Subscribe(o);
}

Observable_Type* Server_with_Observable_GetObservable(struct Server_with_Observable_s* me){
    return me->my_Observable;
}

void Server_with_Observable_Init(struct Server_with_Observable_s* me){
    me->my_button = Button_Create(0);
    me->my_Observable = Observable_Create();
    me->my_Observable->Subscribe = PrivateSubscribe;
    me->my_Observable->unSubscribe = PrivateUnSubscribe;
    me->my_Observable->Notify = PrivaateNotify;
}


void Server_with_Observable_Push(struct Server_with_Observable_s* me){
    g_status = me->my_button->Read(me->my_button);
    PrivaateNotify();
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

