/*
 * LightSensor.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SENSORTHREAD_LIGHTSENSOR_LIGHTSENSOR_H_
#define APP_HAL_PATTERN_SENSORTHREAD_LIGHTSENSOR_LIGHTSENSOR_H_

#include "../General_Common/Std_Types.h"
#include "../General_HAL/Sensor/Static/inc/Senosr.h"

typedef struct{
    uint8 LightValue;
}Light_sensor_thread;


void LightSensorThread_Init(Light_sensor_thread* me);
uint8 LightSensorThread_Read(Light_sensor_thread* me);

#endif /* APP_HAL_PATTERN_SENSORTHREAD_LIGHTSENSOR_LIGHTSENSOR_H_ */
