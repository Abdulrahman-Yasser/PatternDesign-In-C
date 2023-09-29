/*
 * Testing_Keypad_LCD.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_KEYPAD_LCD_TESTING_KEYPAD_LCD_H_
#define APP_TESTING_KEYPAD_LCD_TESTING_KEYPAD_LCD_H_

#include "MCAL_Layer/PLL/Static/inc/PLL.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/I2C/Static/inc/I2C.h"
#include "MCAL_Layer/GPT/Static/inc/GPT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"


#include "HAL_Layer/Keypad/Static/inc/keypad.h"
#include "HAL_Layer/LCD/Static/inc/LCD.h"

void Testing_Keypad_LCD_Init(void);
void Testing_Keypad_LCD_Loop(void);




#endif /* APP_TESTING_KEYPAD_LCD_TESTING_KEYPAD_LCD_H_ */
