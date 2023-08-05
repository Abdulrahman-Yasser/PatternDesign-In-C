/*
 * Testing_LCD_and_ADC.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_AND_ADC_TESTING_LCD_AND_ADC_H_
#define APP_TESTING_LCD_AND_ADC_TESTING_LCD_AND_ADC_H_


#include "../General_Mcal/PLL/Static/inc/PLL.h"
#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/ADC/Static/inc/ADC.h"
#include "../General_Mcal/I2C/Static/Inc/I2C.h"

#include "../General_HAL/LCD/Static/inc/LCD.h"
#include "../General_HAL/Sensor/Static/inc/Senosr.h"

void Testing_LCD_and_ADC_init(void);

void Testing_LCD_and_ADC_loop(void);


#endif /* APP_TESTING_LCD_AND_ADC_TESTING_LCD_AND_ADC_H_ */
