/*
 * FireDisplay.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_CLIENT_1_INC_FIREDISPLAY_H_
#define APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_CLIENT_1_INC_FIREDISPLAY_H_

#include "../General_HAL/LCD/Static/inc/LCD.h"
#include "../General_HAL/LCD/Dynamic/inc/LCD_Cfg.h"

LCD_Handler_Type *FireDisplay_LcdHandler;

void FireDisplay_Init(void);

void FireDisplay_update(void);


#endif /* APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_CLIENT_1_INC_FIREDISPLAY_H_ */
