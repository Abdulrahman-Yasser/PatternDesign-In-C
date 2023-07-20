/*
 * TemperatureSensor.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "TemperatureSensor.h"
#include <stdlib.h>

static void cleanUpRelations(TemperatureSensor* me);
static void cleanUpRelations(TemperatureSensor* me){

}


void TemperatureSensor_Init(TemperatureSensor* const me){
    me->resourceID = 2;
    me->itsTempHandler = TempHandler;
    {
        TempDriver_WeatherStation_Init();
    }
    me->itsMutex = xSemaphoreCreateMutex();
    me->itsResourceList = Null_Ptr;
}
void TemperatureSensor_Cleanup(TemperatureSensor* const me){
    cleanUpRelations(me);
}

/* Operations */

Sensor_Type* TemperatureSensor_getTemperature(TemperatureSensor* const me){
    return me->itsTempHandler;
}

int TemperatureSensor_lockDyadic(TemperatureSensor* const me){
    uint8 ok;
    xSemaphoreTake(me->itsMutex, 0);
    ok = ResourceList_addLock(me->itsResourceList, me->resourceID);
    if(ok != 0){
        xSemaphoreGive(me->itsMutex);
    }
    return ok;
}

void TemperatureSensor_releaseDyadic(TemperatureSensor* const me){
    ResourceList_removeLock(me->itsResourceList, me->resourceID);
    xSemaphoreGive(me->itsMutex);
}

void TemperatureSensor_setTemperature(TemperatureSensor* const me, Sensor_Type* temp_handelr){
    me->itsTempHandler = temp_handelr;
}

SemaphoreHandle_t TemperatureSensor_getItsMutex(const TemperatureSensor* const me){
    return me->itsMutex;
}

void TemperatureSensor_setItsMutex(TemperatureSensor* const me, SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

ResourceList* TemperatureSensor_getItsResourceList(const TemperatureSensor* const me){
    return me->itsResourceList;
}

void TemperatureSensor_setItsResourceList(TemperatureSensor* const me, ResourceList* p_ResourceList){
    me->itsResourceList = p_ResourceList;
}

TemperatureSensor* TemperatureSensor_Create(void){
    TemperatureSensor* me;
    me = (TemperatureSensor*)malloc(sizeof(TemperatureSensor));
    if(me != Null_Ptr){
        TemperatureSensor_Init(me);
    }
    return me;
}

void TemperatureSensor_Destroy(TemperatureSensor* const me){
    TemperatureSensor_Cleanup(me);
    free(me);
}

