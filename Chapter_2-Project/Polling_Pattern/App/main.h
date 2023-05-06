/*
 * main.h
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"
#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "../General_Mcal/ADC/Static/inc/ADC.h"

#include "../General_HAL/Sensor/Dynamic/inc/Sensor_Cfg.h"

#include "HAL_Pattern/FCPeriodicPoller/FCPeriodicPoller.h"
#include "HAL_Pattern/FCTimer/FCTimer.h"
#include "HAL_Pattern/FireCircuitSensor/FireCircuitSensor.h"
#include "HAL_Pattern/FireDisplay/FireDisplay.h"


void main_init(void);

void Pattern_Creation(void);


#endif /* APP_MAIN_H_ */
