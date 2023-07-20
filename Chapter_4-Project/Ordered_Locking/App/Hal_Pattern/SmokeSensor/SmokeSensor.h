/*
 * SmokeSensor.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SMOKESENSOR_SMOKESENSOR_H_
#define APP_HAL_PATTERN_SMOKESENSOR_SMOKESENSOR_H_

#include "../ResourceList/ResourceList.h"
#include "../General_SpecificDrivers/SmokeDriver_WeatherStation/SmokeDriver_WeatherStation.h"
typedef struct{
    uint8 resourceID;
    Sensor_Type* itsSmkHandler;
    SemaphoreHandle_t itsMutex;
    ResourceList *itsResourceList;
}SmokeSensor;


void SmokeSensor_Init(SmokeSensor* const me);
void SmokeSensor_Cleanup(SmokeSensor* const me);

/* Operations */

Sensor_Type* SmokeSensor_getSmoke(SmokeSensor* const me);
int SmokeSensor_lockDyadic(SmokeSensor* const me);
void SmokeSensor_releaseDyadic(SmokeSensor* const me);
void SmokeSensor_setSmoke(SmokeSensor* const me, Sensor_Type* Smk_handelr);
SemaphoreHandle_t SmokeSensor_getItsMutex(const SmokeSensor* const me);
void SmokeSensor_setItsMutex(SmokeSensor* const me, SemaphoreHandle_t p_Mutex);
ResourceList* SmokeSensor_getItsResourceList(const SmokeSensor* const me);
void SmokeSensor_setItsResourceList(SmokeSensor* const me, ResourceList* p_ResourceList);
SmokeSensor * SmokeSensor_Create(void);
void SmokeSensor_Destroy(SmokeSensor* const me);


#endif /* APP_HAL_PATTERN_SMOKESENSOR_SMOKESENSOR_H_ */
