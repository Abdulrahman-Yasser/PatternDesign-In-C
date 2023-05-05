/*
 * main.h
 *
 *  Created on: May 5, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"
#include "Button_Handler/Button_Handler.h"
#include "HAL_Pattern/LED/LED.h"
#include "HAL_Pattern/Robot_Interrupt_VectorTable/RobotInterruptVectorTable.h"


void InterruptPattern(void);

#endif /* APP_MAIN_H_ */
