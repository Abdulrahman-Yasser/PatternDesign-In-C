/*
 * LightSensor.h
 *
 *  Created on: Jul 8, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_LIGHTSENSOR_LIGHTSENSOR_H_
#define APP_HAL_PATTERN_LIGHTSENSOR_LIGHTSENSOR_H_

#include "../ResourceList/ResourceList.h"
#include "../General_SpecificDrivers/LightDriver_WeatherStation/LightDriver_WeatherStation.h"

typedef struct{
    uint8 resourceID;
    Sensor_Type* itsLightHandler;
    SemaphoreHandle_t itsMutex;
    ResourceList *itsResourceList;
}LightSensor;


void LightSensor_Init(LightSensor* const me);
void LightSensor_Cleanup(LightSensor* const me);

/* Operations */

Sensor_Type* LightSensor_getLight(LightSensor* const me);
int LightSensor_lockDyadic(LightSensor* const me);
void LightSensor_releaseDyadic(LightSensor* const me);
void LightSensor_setLight(LightSensor* const me, Sensor_Type* light_handelr);
SemaphoreHandle_t LightSensor_getItsMutex(const LightSensor* const me);
void LightSensor_setItsMutex(LightSensor* const me, SemaphoreHandle_t p_Mutex);
ResourceList* LightSensor_getItsResourceList(const LightSensor* const me);
void LightSensor_setItsResourceList(LightSensor* const me, ResourceList* p_ResourceList);
LightSensor * LightSensor_Create(void);
void LightSensor_Destroy(LightSensor* const me);


#endif /* APP_HAL_PATTERN_LIGHTSENSOR_LIGHTSENSOR_H_ */
