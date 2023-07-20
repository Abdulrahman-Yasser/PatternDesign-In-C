/*
 * SmokeSensor.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "SmokeSensor.h"
#include <stdlib.h>

static void cleanUpRelations(SmokeSensor* me);
static void cleanUpRelations(SmokeSensor* me){

}


void SmokeSensor_Init(SmokeSensor* const me){
    me->resourceID = 2;
    me->itsSmkHandler = SmokeHandler;
    {
        SmokeDriver_WeatherStation_Init();
    }
    me->itsMutex = xSemaphoreCreateMutex();
    me->itsResourceList = Null_Ptr;
}
void SmokeSensor_Cleanup(SmokeSensor* const me){
    cleanUpRelations(me);
}

/* Operations */

Sensor_Type* SmokeSensor_getSmoke(SmokeSensor* const me){
    return me->itsSmkHandler;
}

int SmokeSensor_lockDyadic(SmokeSensor* const me){
    uint8 ok;
    xSemaphoreTake(me->itsMutex, 0);
    ok = ResourceList_addLock(me->itsResourceList, me->resourceID);
    if(ok != 0){
        xSemaphoreGive(me->itsMutex);
    }
    return ok;
}

void SmokeSensor_releaseDyadic(SmokeSensor* const me){
    ResourceList_removeLock(me->itsResourceList, me->resourceID);
    xSemaphoreGive(me->itsMutex);
}

void SmokeSensor_setSmoke(SmokeSensor* const me, Sensor_Type* Smk_handelr){
    me->itsSmkHandler = Smk_handelr;
}

SemaphoreHandle_t SmokeSensor_getItsMutex(const SmokeSensor* const me){
    return me->itsMutex;
}

void SmokeSensor_setItsMutex(SmokeSensor* const me, SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

ResourceList* SmokeSensor_getItsResourceList(const SmokeSensor* const me){
    return me->itsResourceList;
}

void SmokeSensor_setItsResourceList(SmokeSensor* const me, ResourceList* p_ResourceList){
    me->itsResourceList = p_ResourceList;
}

SmokeSensor* SmokeSensor_Create(void){
    SmokeSensor* me;
    me = (SmokeSensor*)malloc(sizeof(SmokeSensor));
    if(me != Null_Ptr){
        SmokeSensor_Init(me);
    }
    return me;
}

void SmokeSensor_Destroy(SmokeSensor* const me){
    SmokeSensor_Cleanup(me);
    free(me);
}

