/*
 * ForecastDisplay_Client.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_INC_FORECASTDISPLAY_CLIENT_H_
#define APP_HAL_PATTERNS_CLIENT_INC_FORECASTDISPLAY_CLIENT_H_


struct ForecastDisplay{
    WeatherData_Queue_Element_Type *itsData;
};

void ForecastDisplay_Notify(void);

#endif /* APP_HAL_PATTERNS_CLIENT_INC_FORECASTDISPLAY_CLIENT_H_ */
