/*
 * main.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/DIO/Static/inc/DIO.h"
#include "../General_Mcal/PWM/Static/inc/PWM.h"

#include "../General_HAL/DC_Motor/Static/inc/Motor.h"

#include "Hal_Pattern/MotorController/MotorController.h"
#include "Hal_Pattern/MotorData/MotorData.h"
#include "Hal_Pattern/MotorDisplay/MotorDisplay.h"
#include "Hal_Pattern/MotorSpeedSensor/MotorSpeedSensor.h"

void main_Init(void);

void main_Loop(void);


#endif /* APP_MAIN_H_ */
