/*
 * Testing_HAL_1.h
 *
 *  Created on: Aug 4, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_HAL_TEMP_SMOKE_WATER_HUMANITY_LCD_BUZZER_LED_TESTING_HAL_1_H_
#define APP_TESTING_HAL_TEMP_SMOKE_WATER_HUMANITY_LCD_BUZZER_LED_TESTING_HAL_1_H_


#include "MCAL_Layer/DIO/Static/inc/DIO.h"
#include "MCAL_Layer/I2C/Static/inc/I2C.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/ADC/Static/inc/ADC.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"
#include "MCAL_Layer/PLL/Static/inc/PLL.h"

#include "HAL_Layer/LCD/Static/inc/LCD.h"
#include "HAL_Layer/Sensor/Static/inc/Senosr.h"
#include "HAL_Layer/TempratureSensor_HAL/Static/inc/TempratureSensor_HAL.h"
#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"


void Testing_HAL1_Init(void);

void Testing_HAL1_Loop(void);



#endif /* APP_TESTING_HAL_TEMP_SMOKE_WATER_HUMANITY_LCD_BUZZER_LED_TESTING_HAL_1_H_ */
