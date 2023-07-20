/*
 * main.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/I2C/Static/Inc/I2C.h"
#include "../General_Mcal/PWM/Static/inc/PWM.h"

#include "../General_HAL/LCD/Static/inc/LCD.h"
#include "../General_HAL/DC_Motor/Static/inc/Motor.h"


#include "Hal_Pattern/kinematicData/kinematicData.h"
#include "Hal_Pattern/Direction/Direction.h"
#include "Hal_Pattern/DirectionController/DirectionController.h"
#include "Hal_Pattern/MotorDataDisplay/MotorDataDisplay.h"
#include "Hal_Pattern/Speed/Speed.h"
#include "Hal_Pattern/SpeedController/SpeedController.h"

void main_Init(void);

void main_Loop(void);


#endif /* APP_MAIN_H_ */
