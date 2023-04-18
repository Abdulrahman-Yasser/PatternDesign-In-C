/*
 * StatisticsDisplay.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_STATISTICSDISPLAY_CLIENT_2_INC_STATISTICSDISPLAY_H_
#define APP_HAL_PATTERNS_CLIENT_STATISTICSDISPLAY_CLIENT_2_INC_STATISTICSDISPLAY_H_


#include "../General_HAL/LCD/Static/inc/LCD.h"

LCD_Handler_Type *StatisticsDisplay_LcdHandler;

void StatisticsDisplay_Init(void);

void StatisticsDisplay_update(void);


#endif /* APP_HAL_PATTERNS_CLIENT_STATISTICSDISPLAY_CLIENT_2_INC_STATISTICSDISPLAY_H_ */
