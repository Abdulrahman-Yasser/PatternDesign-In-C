/*
 * LightSensor.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SENSORTHREAD_SMOKESENSOR_SMOKESENSOR_H_
#define APP_HAL_PATTERN_SENSORTHREAD_SMOKESENSOR_SMOKESENSOR_H_


#include "../General_Common/Std_Types.h"
#include "../General_HAL/Sensor/Static/inc/Senosr.h"

typedef struct{
    uint8 SmokeValue;
}Smoke_sensor_thread;


void SmokeSensorThread_Init(Smoke_sensor_thread* me);
uint8 SmokeSensorThread_Read(Smoke_sensor_thread* me);


#endif /* APP_HAL_PATTERN_SENSORTHREAD_LIGHTSENSOR_LIGHTSENSOR_H_ */
