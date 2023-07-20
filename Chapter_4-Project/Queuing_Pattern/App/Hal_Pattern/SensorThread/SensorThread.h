/*
 * SensorThread.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SENSORTHREAD_SENSORTHREAD_H_
#define APP_HAL_PATTERN_SENSORTHREAD_SENSORTHREAD_H_

#include "../General_HAL/Sensor/Static/inc/Senosr.h"
#include "../WeatherStationData/WeatherStationData.h"
#include "../WeatherStationDataQueue/WeatherStationDataQueue.h"

#include "LightSensor/LightSensor.h"
#include "SmokeSensor/SmokeSensor.h"
#include "TemperatureSensor/TempSensor.h"


typedef struct SensorThread SensorThread;


struct SensorThread {
    WeatherStationDataQueue* my_data_queue;
    Light_sensor_thread my_light;
    Smoke_sensor_thread my_smoke;
    Temp_sensor_thread my_temp;
};

void SensorThread_setItsDataQueue(SensorThread* me, WeatherStationDataQueue* const dataQueuePtr);
SensorThread* SensorThread_create(void);
void SensorThread_init(SensorThread* const me);
void SensorThread_updateData(SensorThread* const me);

#endif /* APP_HAL_PATTERN_SENSORTHREAD_SENSORTHREAD_H_ */
