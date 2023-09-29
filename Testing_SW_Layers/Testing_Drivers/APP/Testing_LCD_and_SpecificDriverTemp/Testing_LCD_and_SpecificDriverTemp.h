/*
 * Testing_LCD_and_SpecificDriverTemp.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_H_
#define APP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_H_


#include "MCAL_Layer/PLL/Static/inc/PLL.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/ADC/Static/inc/ADC.h"
#include "MCAL_Layer/I2C/Static/inc/I2C.h"

#include "HAL_Layer/LCD/Static/inc/LCD.h"
#include "HAL_Layer/Sensor/Static/inc/Senosr.h"

#include "APP_Layer/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"
#include "APP_Layer/SmokeDriver_WeatherStation/SmokeDriver_WeatherStation.h"
#include "APP_Layer/WaterDriver_WeatherStation/WaterDriver_WeatherStation.h"

void Testing_LCD_and_SpecificDriverTemp_loop(void);
void Testing_LCD_and_SpecificDriverTempInit(void);



#endif /* APP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_H_ */
