/*
 * FireModelClient.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_FIREMODELCLIENT_FIREMODELCLIENT_H_
#define APP_HAL_PATTERN_FIREMODELCLIENT_FIREMODELCLIENT_H_

#include "../SmokeSensor/SmokeSensor.h"
#include "../TemperatureSensor/TemperatureSensor.h"
#include "../WaterSensor/WaterSensor.h"
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

typedef enum{
    FireIsBIIIG, FireIsNormal, FireNotHappened, FireIsEnded
}FireModeStates;


// Follows the singleton pattern .

void FireModeCreate(void);
void FireModeSetInterface(DigitalInterface_Type* me);
void FireModeSetTemperature(TemperatureSensor* me);
void FireModeSetSmoke(SmokeSensor* me);
void FireModeSetWater(WaterSensor* me);
void FireModeReadSensors(void);
void FireModeActionState(void);


#endif /* APP_HAL_PATTERN_FIREMODELCLIENT_FIREMODELCLIENT_H_ */
