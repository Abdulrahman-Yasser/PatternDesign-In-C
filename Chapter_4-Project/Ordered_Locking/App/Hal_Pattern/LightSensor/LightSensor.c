/*
 * LightSensor.c
 *
 *  Created on: Jul 8, 2023
 *      Author: Abdu
 */

#include "LightSensor.h"
#include <stdlib.h>

static void cleanUpRelations(LightSensor* me);
static void cleanUpRelations(LightSensor* me){

}


void LightSensor_Init(LightSensor* const me){
    me->resourceID = 2;
    me->itsLightHandler = LightHandler;
    {
        LightDriver_WeatherStation_Init();
    }
    me->itsMutex = xSemaphoreCreateMutex();
    me->itsResourceList = Null_Ptr;
}
void LightSensor_Cleanup(LightSensor* const me){
    cleanUpRelations(me);
}

/* Operations */

Sensor_Type* LightSensor_getLight(LightSensor* const me){
    return me->itsLightHandler;
}

int LightSensor_lockDyadic(LightSensor* const me){
    uint8 ok;
    xSemaphoreTake(me->itsMutex, 0);
    ok = ResourceList_addLock(me->itsResourceList, me->resourceID);
    if(ok != 0){
        xSemaphoreGive(me->itsMutex);
    }
    return ok;
}

void LightSensor_releaseDyadic(LightSensor* const me){
    ResourceList_removeLock(me->itsResourceList, me->resourceID);
    xSemaphoreGive(me->itsMutex);
}

void LightSensor_setLight(LightSensor* const me, Sensor_Type* light_handelr){
    me->itsLightHandler = light_handelr;
}

SemaphoreHandle_t LightSensor_getItsMutex(const LightSensor* const me){
    return me->itsMutex;
}

void LightSensor_setItsMutex(LightSensor* const me, SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

ResourceList* LightSensor_getItsResourceList(const LightSensor* const me){
    return me->itsResourceList;
}

void LightSensor_setItsResourceList(LightSensor* const me, ResourceList* p_ResourceList){
    me->itsResourceList = p_ResourceList;
}

LightSensor* LightSensor_Create(void){
    LightSensor* me;
    me = (LightSensor*)malloc(sizeof(LightSensor));
    if(me != Null_Ptr){
        LightSensor_Init(me);
    }
    return me;
}

void LightSensor_Destroy(LightSensor* const me){
    LightSensor_Cleanup(me);
    free(me);
}
