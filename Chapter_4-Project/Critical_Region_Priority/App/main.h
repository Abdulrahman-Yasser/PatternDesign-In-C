/*
 * main.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../General_Mcal/DIO/Static/inc/DIO.h"
#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/PWM/Static/inc/PWM.h"

#include "../General_HAL/DC_Motor/Static/inc/Motor.h"
#include "../General_HAL/LCD/Static/inc/LCD.h"

#include "Hal_Pattern/CRRobotArmManager/CRRobotArmManager.h"
#include "Hal_Pattern/CRDisplay/CRDisplay.h"
#include "Hal_Pattern/RobotArm/RobotArm.h"
#include "Hal_Pattern/UserInput/UserInput.h"


#include "FreeRTOS.h"
#include "task.h"

void main_Init(void);

void main_Loop(void);


#endif /* APP_MAIN_H_ */
