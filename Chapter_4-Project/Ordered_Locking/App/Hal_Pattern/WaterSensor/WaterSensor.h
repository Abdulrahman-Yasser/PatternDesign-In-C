/*
 * RTC_Device.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_WATERSENSOR_RTC_DEVICE_H_
#define APP_HAL_PATTERN_WATERSENSOR_RTC_DEVICE_H_


#include "../ResourceList/ResourceList.h"
#include "../General_SpecificDrivers/WaterDriver_WeatherStation/WaterDriver_WeatherStation.h"

typedef struct{
    uint8 resourceID;
    Sensor_Type* itsWaterHandler;
    SemaphoreHandle_t itsMutex;
    ResourceList *itsResourceList;
}WaterSensor;


void WaterSensor_Init(WaterSensor* const me);
void WaterSensor_Cleanup(WaterSensor* const me);

/* Operations */

Sensor_Type* WaterSensor_getWater(WaterSensor* const me);
int WaterSensor_lockDyadic(WaterSensor* const me);
void WaterSensor_releaseDyadic(WaterSensor* const me);
void WaterSensor_setWater(WaterSensor* const me, Sensor_Type* water_handelr);
SemaphoreHandle_t WaterSensor_getItsMutex(const WaterSensor* const me);
void WaterkeSensor_setItsMutex(WaterSensor* const me, SemaphoreHandle_t p_Mutex);
ResourceList* WaterSensor_getItsResourceList(const WaterSensor* const me);
void WaterSensor_setItsResourceList(WaterSensor* const me, ResourceList* p_ResourceList);
WaterSensor * WaterSensor_Create(void);
void WaterSensor_Destroy(WaterSensor* const me);




#endif /* APP_HAL_PATTERN_WATERSENSOR_RTC_DEVICE_H_ */
