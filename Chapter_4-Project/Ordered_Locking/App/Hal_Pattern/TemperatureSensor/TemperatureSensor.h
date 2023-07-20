/*
 * TemperatureSensor.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_TEMPERATURESENSOR_TEMPERATURESENSOR_H_
#define APP_HAL_PATTERN_TEMPERATURESENSOR_TEMPERATURESENSOR_H_

#include "../ResourceList/ResourceList.h"
#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"
typedef struct{
    uint8 resourceID;
    Sensor_Type* itsTempHandler;
    SemaphoreHandle_t itsMutex;
    ResourceList *itsResourceList;
}TemperatureSensor;


void TemperatureSensor_Init(TemperatureSensor* const me);
void TemperatureSensor_Cleanup(TemperatureSensor* const me);

/* Operations */

Sensor_Type* TemperatureSensor_getTemperature(TemperatureSensor* const me);
int TemperatureSensor_lockDyadic(TemperatureSensor* const me);
void TemperatureSensor_releaseDyadic(TemperatureSensor* const me);
void TemperatureSensor_setTemperature(TemperatureSensor* const me, Sensor_Type* temp_handelr);
SemaphoreHandle_t TemperatureSensor_getItsMutex(const TemperatureSensor* const me);
void TemperatureSensor_setItsMutex(TemperatureSensor* const me, SemaphoreHandle_t p_Mutex);
ResourceList* TemperatureSensor_getItsResourceList(const TemperatureSensor* const me);
void TemperatureSensor_setItsResourceList(TemperatureSensor* const me, ResourceList* p_ResourceList);
TemperatureSensor * TemperatureSensor_Create(void);
void TemperatureSensor_Destroy(TemperatureSensor* const me);


#endif /* APP_HAL_PATTERN_TEMPERATURESENSOR_TEMPERATURESENSOR_H_ */
