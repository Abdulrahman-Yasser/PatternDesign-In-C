/*
 * WeatherStationDataQueue.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_WEATHERSTATIONDATAQUEUE_WEATHERSTATIONDATAQUEUE_H_
#define APP_HAL_PATTERN_WEATHERSTATIONDATAQUEUE_WEATHERSTATIONDATAQUEUE_H_

#include "../WeatherStationData/WeatherStationData.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "../General_HAL/LCD/Static/inc/LCD.h"

#define WEATHER_QUEUE_SIZE 10


typedef struct {
    uint8 head;
    uint8 size;
    uint8 tail;
    SemaphoreHandle_t *sema;
    WeatherStationData itsWeatherStationData[WEATHER_QUEUE_SIZE];
    LCD_Handler_Type *WeatherLCD;
}WeatherStationDataQueue;

/* Constructors and destructors:*/

void WeatherStationDataQueue_Init(WeatherStationDataQueue* const me);
void WeatherStationDataQueue_Cleanup(WeatherStationDataQueue* const me);

/* Operations */

int WeatherStationDataQueue_insert(WeatherStationDataQueue* const me, WeatherStationData w);
WeatherStationData * WeatherStationDataQueue_remove(WeatherStationDataQueue* const me);
void WeatherStationDataQueue_setItsLCD(WeatherStationDataQueue* const me, LCD_Handler_Type *the_lcd);
int WeatherStationDataQueue_getItsWeatherStationData(const WeatherStationDataQueue* const me);
WeatherStationDataQueue * WeatherStationDataQueue_Create(void);
void WeatherStationDataQueue_Destroy(WeatherStationDataQueue* const me);

#endif /* APP_HAL_PATTERN_WEATHERSTATIONDATAQUEUE_WEATHERSTATIONDATAQUEUE_H_ */
