/*
 * Testing_Keypad_LCD.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_KEYPAD_LCD_TESTING_KEYPAD_LCD_H_
#define APP_TESTING_KEYPAD_LCD_TESTING_KEYPAD_LCD_H_

#include "../../General_Mcal/PLL/Static/inc/PLL.h"
#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/I2C/Static/inc/I2C.h"
#include "../../General_Mcal/GPT/Static/inc/GPT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"


#include "../General_HAL/Keypad/Static/inc/keypad.h"
#include "../General_HAL/LCD/Static/inc/LCD.h"

void Testing_Keypad_LCD_Init(void);
void Testing_Keypad_LCD_Loop(void);




#endif /* APP_TESTING_KEYPAD_LCD_TESTING_KEYPAD_LCD_H_ */
