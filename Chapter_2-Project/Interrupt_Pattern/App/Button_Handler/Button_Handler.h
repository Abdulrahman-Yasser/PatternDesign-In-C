/*
 * Button_Handler.h
 *
 *  Created on: May 5, 2023
 *      Author: Abdu
 */

#ifndef APP_BUTTON_HANDLER_BUTTON_HANDLER_H_
#define APP_BUTTON_HANDLER_BUTTON_HANDLER_H_

#include "../HAL_Pattern/Robot_Interrupt_VectorTable/RobotInterruptVectorTable.h"

ButtonVectorPtr oldVectors[10];

void ButtonInit(void);

void install(void);

void deinstall(void);

void handleButtonRemoveISR(void);

void handleButtonPushInterrupt(void);

void handleButtonReleaseInterrupt(void);

#endif /* APP_BUTTON_HANDLER_BUTTON_HANDLER_H_ */
