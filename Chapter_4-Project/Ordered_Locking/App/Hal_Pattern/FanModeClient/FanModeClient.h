/*
 * FanModeClient.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_FANMODECLIENT_FANMODECLIENT_H_
#define APP_HAL_PATTERN_FANMODECLIENT_FANMODECLIENT_H_

#include "../SmokeSensor/SmokeSensor.h"
#include "../TemperatureSensor/TemperatureSensor.h"
#include "../WaterSensor/WaterSensor.h"
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

typedef enum{
    FanIsNotNeeded, FanIsNeeded
}FanModeStates;


// Follows the singleton pattern .

void FanModeCreate(void);
void FanModeSetInterface(DigitalInterface_Type* me);
void FanModeSetTemperature(TemperatureSensor* me);
void FanModeSetSmoke(SmokeSensor* me);
void FanModeSetWater(WaterSensor* me);
void FanModeReadSensors(void);
void FanModeActionState(void);


#endif /* APP_HAL_PATTERN_FANMODECLIENT_FANMODECLIENT_H_ */
