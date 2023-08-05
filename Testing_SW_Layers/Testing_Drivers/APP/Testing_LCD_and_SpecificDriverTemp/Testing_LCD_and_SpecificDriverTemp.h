/*
 * Testing_LCD_and_SpecificDriverTemp.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_H_
#define APP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_H_


#include "../General_Mcal/PLL/Static/inc/PLL.h"
#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/ADC/Static/inc/ADC.h"
#include "../General_Mcal/I2C/Static/Inc/I2C.h"

#include "../General_HAL/LCD/Static/inc/LCD.h"
#include "../General_HAL/Sensor/Static/inc/Senosr.h"

#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"
#include "../General_SpecificDrivers/SmokeDriver_WeatherStation/SmokeDriver_WeatherStation.h"
#include "../General_SpecificDrivers/WaterDriver_WeatherStation/WaterDriver_WeatherStation.h"

void Testing_LCD_and_SpecificDriverTemp_loop(void);
void Testing_LCD_and_SpecificDriverTempInit(void);



#endif /* APP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_TESTING_LCD_AND_SPECIFICDRIVERTEMP_H_ */
