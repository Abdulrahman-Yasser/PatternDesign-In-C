/*
 * Testing_LCD.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_TESTING_LCD_H_
#define APP_TESTING_LCD_TESTING_LCD_H_

#include "../../General_HAL/LCD/Dynamic/inc/LCD_Cfg.h"
#include "../../General_HAL/LCD/Static/inc/LCD.h"

#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/I2C/Static/inc/I2C.h"
#include "../../General_Mcal/GPT/Static/inc/GPT.h"


void App_Initializations(void);
void LCD_Initializations(void);



#endif /* APP_TESTING_LCD_TESTING_LCD_H_ */
