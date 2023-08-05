/*
 * Testing_HAL_1.h
 *
 *  Created on: Aug 4, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_HAL_TEMP_SMOKE_WATER_HUMANITY_LCD_BUZZER_LED_TESTING_HAL_1_H_
#define APP_TESTING_HAL_TEMP_SMOKE_WATER_HUMANITY_LCD_BUZZER_LED_TESTING_HAL_1_H_


#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include "../../General_Mcal/I2C/Static/inc/I2C.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/ADC/Static/Inc/ADC.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"
#include "../../General_Mcal/PLL/Static/inc/PLL.h"

#include "../../General_HAL/LCD/Static/inc/LCD.h"
#include "../../General_HAL/Sensor/Static/inc/Senosr.h"
#include "../../General_HAL/TempratureSensor_HAL/Static/inc/TempratureSensor_HAL.h"
#include "../../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"


void Testing_HAL1_Init(void);

void Testing_HAL1_Loop(void);



#endif /* APP_TESTING_HAL_TEMP_SMOKE_WATER_HUMANITY_LCD_BUZZER_LED_TESTING_HAL_1_H_ */
