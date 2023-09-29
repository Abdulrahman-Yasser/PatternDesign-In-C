/*
 * Testing_LCD.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_TESTING_LCD_H_
#define APP_TESTING_LCD_TESTING_LCD_H_

#include "HAL_Layer/LCD/Dynamic/inc/LCD_Cfg.h"
#include "HAL_Layer/LCD/Static/inc/LCD.h"

#include "MCAL_Layer/DIO/Static/inc/DIO.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/I2C/Static/inc/I2C.h"
#include "MCAL_Layer/GPT/Static/inc/GPT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"


void TestingLCD_Initializations(void);
void TestingLCD_Loop(void);



#endif /* APP_TESTING_LCD_TESTING_LCD_H_ */
