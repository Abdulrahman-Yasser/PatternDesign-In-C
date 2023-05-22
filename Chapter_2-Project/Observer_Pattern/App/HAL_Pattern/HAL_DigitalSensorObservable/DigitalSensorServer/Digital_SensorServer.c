/*
 * SensorObserver.c
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#include <App/HAL_Pattern/HAL_DigitalSensorObservable/Digital_SensorServer.h>




#include "Digital_SensorServer.h"

#include "../../General_Common/Std_Types.h"
#include "../../General_Mcal/DIO/Static/inc/DIO.h"

#include <stdlib.h>

static void DigSens_PrivateSubscribe(Observable_Type* my_Observable,Observer* o);
static void DigSens_PrivateUnSubscribe(Observable_Type* my_Observable,Observer* o);
static void DigSens_PrivateNotify(Observable_Type* my_Observable);
static uint8 getLastValue_byObservable(Observable_Type* my_Observable);
static void DigitalObservableSensor_InitRelations(DigitalObservableSensor_Type* me);


static uint8 getLastValue_byObservable(Observable_Type* my_Observable){

}


static void DigitalObservableSensor_InitRelations(DigitalObservableSensor_Type* me){
    me->GetValue = GetValueFunction_Digital;
    me->my_observable = Observable_Create();
    me->my_observable->Subscribe = DigSens_PrivateSubscribe;
    me->my_observable->unSubscribe = DigSens_PrivateUnSubscribe;
    me->my_observable->Notify = DigSens_PrivateNotify;
}

static void DigSens_PrivateSubscribe(Observable_Type* my_Observable, Observer* o){
    NotificationHandle *pNH;
    pNH = my_Observable->itsNotificationHandler;
    if(pNH == Null_Ptr){
        my_Observable->itsNotificationHandler = NotificationHandle_Create();
        pNH = my_Observable->itsNotificationHandler;
    }else{
        while(pNH->itsNotificationHandle != Null_Ptr){
            pNH = pNH->itsNotificationHandle;
        }
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }
    pNH->FunPtr = o->UpdateFuncPtr;
    ++my_Observable->nSubscribers;
}

static void DigSens_PrivateUnSubscribe(Observable_Type* my_Observable, Observer* o){
    NotificationHandle *pNH, *pBack;
    pNH = pBack = my_Observable->itsNotificationHandler;

    if(pNH == Null_Ptr){
        return ;
    }else{
        if(pNH->FunPtr == o->UpdateFuncPtr){
            my_Observable->itsNotificationHandler = pNH->itsNotificationHandle;
            free(pNH);
            --my_Observable->nSubscribers;
        }else{
            while(pNH != Null_Ptr){
                pBack = pNH;
                pNH = pNH->itsNotificationHandle;
                if(pNH->FunPtr == o->UpdateFuncPtr){
                    pBack->itsNotificationHandle = pNH->itsNotificationHandle;
                    free(pNH);
                    --my_Observable->nSubscribers;
                    return;
                }
            }
        }
    }
}

static void DigSens_PrivateNotify(Observable_Type* my_Observable){
    int i;
    uint8 data;
    data = getLastValue_byObservable(my_Observable);
    for(i = 0; i < my_Observable->nSubscribers; i++){
        my_Observable->itsNotificationHandler->FunPtr();
    }
}


DigitalObservableSensor_Type* DigitalObservableSensor_Create(DIO_ChannelType Sensor_Data_Pins){
    DigitalObservableSensor_Type* me = (DigitalObservableSensor_Type*)malloc(sizeof(DigitalObservableSensor_Type));
    if(me != Null_Ptr){
        me->Sensor_Data_Pins = Sensor_Data_Pins;
        DigitalObservableSensor_InitRelations(me);
    }
    return me;
}

void DigitalObservableSensor_Destroy( DigitalObservableSensor_Type* const me){
    free(me);
}


static SENSOR_READ_TYPE GetValueFunction_Digital(Sensor_Type* const me){
    return Dio_ReadChannel(me->Sensor_ID);
}



