/*
 * WeatherStation_Server.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_

#include "../Server_with_Observable/Server_with_Observable.h"



void ButtonStatus_Publish(struct Server_with_Observable_s* me);

uint8 Button_IsEmpty(struct Server_with_Observable_s* me);


#endif /* APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_ */
