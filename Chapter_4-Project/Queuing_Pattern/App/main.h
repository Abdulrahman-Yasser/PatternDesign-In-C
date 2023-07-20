/*
 * main.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_


#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/ADC/Static/inc/ADC.h"
#include "../General_Mcal/DIO/Static/inc/DIO.h"

#include "Hal_Pattern/SensorThread/SensorThread.h"
#include "Hal_Pattern/SensorThread/LightSensor/LightSensor.h"
#include "Hal_Pattern/SensorThread/SmokeSensor/SmokeSensor.h"
#include "Hal_Pattern/SensorThread/TemperatureSensor/TempSensor.h"

#include "Hal_Pattern/WeatherStationData/WeatherStationData.h"

#include "Hal_Pattern/WeatherStationDataQueue/WeatherStationDataQueue.h"

#include "Hal_Pattern/WeatherStationProcessingThread/WeatherStationConstroller/WeatherStationConstroller.h"
#include "Hal_Pattern/WeatherStationProcessingThread/WeatherStationDisplay/WeatherStationDisplay.h"

void main_init(void);

void main_loop(void);



#endif /* APP_MAIN_H_ */
