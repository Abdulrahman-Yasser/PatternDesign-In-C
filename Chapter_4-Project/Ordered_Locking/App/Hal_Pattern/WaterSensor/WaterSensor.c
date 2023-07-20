/*
 * RTC_Device.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */


#include "WaterSensor.h"

#include <stdlib.h>

static void cleanUpRelations(WaterSensor* me);
static void cleanUpRelations(WaterSensor* me){

}


void WaterSensor_Init(WaterSensor* const me){
    me->resourceID = 2;
    me->itsWaterHandler = WaterS_Handler;
    {
        WaterDriver_WeatherStation_Init();
    }
    me->itsMutex = xSemaphoreCreateMutex();
    me->itsResourceList = Null_Ptr;
}
void WaterSensor_Cleanup(WaterSensor* const me){
    cleanUpRelations(me);
}

/* Operations */

Sensor_Type* WaterSensor_getWater(WaterSensor* const me){
    return me->itsWaterHandler;
}

int WaterSensor_lockDyadic(WaterSensor* const me){
    uint8 ok;
    xSemaphoreTake(me->itsMutex, 0);
    ok = ResourceList_addLock(me->itsResourceList, me->resourceID);
    if(ok != 0){
        xSemaphoreGive(me->itsMutex);
    }
    return ok;
}

void WaterSensor_releaseDyadic(WaterSensor* const me){
    ResourceList_removeLock(me->itsResourceList, me->resourceID);
    xSemaphoreGive(me->itsMutex);
}

void WaterSensor_setWater(WaterSensor* const me, Sensor_Type* water_handelr){
    me->itsWaterHandler = water_handelr;
}

SemaphoreHandle_t WaterSensor_getItsMutex(const WaterSensor* const me){
    return me->itsMutex;
}

void WaterSensor_setItsMutex(WaterSensor* const me, SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

ResourceList* WaterSensor_getItsResourceList(const WaterSensor* const me){
    return me->itsResourceList;
}

void WaterSensor_setItsResourceList(WaterSensor* const me, ResourceList* p_ResourceList){
    me->itsResourceList = p_ResourceList;
}

WaterSensor* WaterSensor_Create(void){
    WaterSensor* me;
    me = (WaterSensor*)malloc(sizeof(WaterSensor));
    if(me != Null_Ptr){
        WaterSensor_Init(me);
    }
    return me;
}

void WaterSensor_Destroy(WaterSensor* const me){
    WaterSensor_Cleanup(me);
    free(me);
}
