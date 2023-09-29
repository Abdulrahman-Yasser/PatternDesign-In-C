/*
 * Testing_LCD_and_ADC.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_AND_ADC_TESTING_LCD_AND_ADC_H_
#define APP_TESTING_LCD_AND_ADC_TESTING_LCD_AND_ADC_H_


#include "MCAL_Layer/PLL/Static/inc/PLL.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/ADC/Static/inc/ADC.h"
#include "MCAL_Layer/I2C/Static/inc/I2C.h"

#include "HAL_Layer/LCD/Static/inc/LCD.h"
#include "HAL_Layer/Sensor/Static/inc/Senosr.h"

void Testing_LCD_and_ADC_init(void);

void Testing_LCD_and_ADC_loop(void);


#endif /* APP_TESTING_LCD_AND_ADC_TESTING_LCD_AND_ADC_H_ */
