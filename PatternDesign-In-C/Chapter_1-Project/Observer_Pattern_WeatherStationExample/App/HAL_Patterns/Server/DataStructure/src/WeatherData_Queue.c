/*
 * WeatherData_Queue.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

/* The Server */

#include "../inc/WeatherData_Queue.h"

#include "../../../Observable/inc/Observable.h"



struct {
    Queue_uint8_DYNAMIC_Type* temp;
    Queue_uint8_DYNAMIC_Type* smoke;
    Queue_uint8_DYNAMIC_Type* light;
    Observable_Type *my_Observable;
}WeatherData_Queue;

void PrivateSubscribe(void(*FunPtr)(void));
void PrivateUnSubscribe(void(*FunPtr)(void));
void PrivaateNotify(void(*FunPtr)(void));

void PrivateSubscribe(void(*FunPtr)(void)){
    /* add the function in the notification handler */
    NotificationHandle *pNH;
    pNH = WeatherData_Queue.my_Observable->itsNotificationHandler;
    if(pNH == Null_Ptr){
        WeatherData_Queue.my_Observable->itsNotificationHandler = NotificationHandle_Create();
        pNH = WeatherData_Queue.my_Observable->itsNotificationHandler;
    }else{
        while(pNH->itsNotificationHandle != Null_Ptr){
            pNH = pNH->itsNotificationHandle;
        }
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }
    pNH->UpdateFunPtr = FunPtr;
    ++WeatherData_Queue.my_Observable->nSubscribers;
}

void PrivateUnSubscribe(void(*FunPtr)(void)){
    NotificationHandle *pNH, *pBack;
    pNH = pBack = WeatherData_Queue.my_Observable->itsNotificationHandler;

    if(pNH == Null_Ptr){
        return ;
    }else{
        if(pNH->UpdateFunPtr == FunPtr){
            WeatherData_Queue.my_Observable->itsNotificationHandler = pNH->itsNotificationHandle;
            free(pNH);
            --WeatherData_Queue.my_Observable->nSubscribers;
        }else{
            while(pNH != Null_Ptr){
                pBack = pNH;
                pNH = pNH->itsNotificationHandle;
                if(pNH->UpdateFunPtr == FunPtr){
                    pBack->itsNotificationHandle = pNH->itsNotificationHandle;
                    free(pNH);
                    --WeatherData_Queue.my_Observable->nSubscribers;
                    return;
                }
            }
        }
    }
}

void PrivaateNotify(void(*FunPtr)(void)){
    for(int i = 0; i < WeatherData_Queue.my_Observable->nSubscribers; i++){
        WeatherData_Queue.my_Observable->itsNotificationHandler->UpdateFunPtr();
    }
}


void weatherData_Queue_Create(void){
    WeatherData_Queue.light = Queue_Create_DYNAMIC_uint8(8);
    WeatherData_Queue.smoke =  Queue_Create_DYNAMIC_uint8(8);
    WeatherData_Queue.temp =  Queue_Create_DYNAMIC_uint8(8);
    WeatherData_Queue.my_Observable = Observable_Create();
    WeatherData_Queue.my_Observable->Subscribe = PrivateSubscribe;
    WeatherData_Queue.my_Observable->nSubscribers = PrivateUnSubscribe;
    WeatherData_Queue.my_Observable->Notify = PrivaateNotify;
}

void weatherData_Queue_Push(WeatherData_Queue_Element_Type* element){
    WeatherData_Queue.light->insert(WeatherData_Queue.light, element->light);
    WeatherData_Queue.smoke->insert(WeatherData_Queue.smoke, element->smoke);
    WeatherData_Queue.temp->insert(WeatherData_Queue.temp, element->temp);
    /*
     * Notify the Clients
     */
    /*
     * Notification functions
     */
}

WeatherData_Queue_Element_Type* weatherData_Queue_Pop(void){
    WeatherData_Queue_Element_Type* result;
    result = (WeatherData_Queue_Element_Type*)malloc(sizeof(WeatherData_Queue_Element_Type));
    result->light = WeatherData_Queue.light->remove(WeatherData_Queue.light);
    result->smoke = WeatherData_Queue.smoke->remove(WeatherData_Queue.smoke);
    result->temp = WeatherData_Queue.temp->remove(WeatherData_Queue.temp);
    return result;
}

uint8 WeatherData_Queue_GetSize(void){
    uint8 x, y, z;
    x = WeatherData_Queue.light->getSize(WeatherData_Queue.light);
    y = WeatherData_Queue.smoke->getSize(WeatherData_Queue.smoke);
    z = WeatherData_Queue.temp->getSize(WeatherData_Queue.temp);
    if(x != y || y != z || x != z){
        return 0;
    }else{
        return x;
    }
}

uint8 WeatherData_Queue_IsEmpty(void){
    uint8 x = 0;
    if(WeatherData_Queue.light->isEmpty(WeatherData_Queue.light)){
        x = 1;
    }
    if(WeatherData_Queue.smoke->isEmpty(WeatherData_Queue.smoke)){
        x = 1;
    }
    if(WeatherData_Queue.temp->isEmpty(WeatherData_Queue.temp)){
        x = 1;
    }
    return x;
}

uint8 WeatherData_Queue_IsFull(void){
    uint8 x = 0;
    if(WeatherData_Queue.light->isFull(WeatherData_Queue.light)){
        x = 1;
    }
    if(WeatherData_Queue.smoke->isFull(WeatherData_Queue.smoke)){
        x = 1;
    }
    if(WeatherData_Queue.temp->isFull(WeatherData_Queue.temp)){
        x = 1;
    }
    return x;
}

void weatherData_Queue_Destroy(void){
    Queue_Destroy_DYNAMIC_uint8 (WeatherData_Queue.light);
    Queue_Destroy_DYNAMIC_uint8 (WeatherData_Queue.smoke);
    Queue_Destroy_DYNAMIC_uint8 (WeatherData_Queue.temp);
}
