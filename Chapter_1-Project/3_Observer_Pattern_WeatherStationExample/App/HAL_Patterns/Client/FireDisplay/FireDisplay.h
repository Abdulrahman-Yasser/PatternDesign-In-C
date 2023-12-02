/*
 * FireDisplay.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_FIREDISPLAY_H_
#define APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_FIREDISPLAY_H_

#include "APP_WS_Layer/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"
#include "HAL_Layer/LCD/Static/inc/LCD.h"
#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"

#include "../../Observer/Observer.h"
#include "../../Server/TimeMarkedData/TimeMarkedData_DataType.h"

struct TMDQueue_with_Observable_s;
struct FireDisplay;


void FireDisplay_Init(struct FireDisplay* const me);

void FireDisplay_Cleanup(struct FireDisplay* const me);

/* Operations */

void FireDisplay_setItsLCD(struct FireDisplay* const me, LCD_Handler_Type *p_LCD_Handler);

void FireDisplay_setItsBUZZER(struct FireDisplay* const me, DigitalInterface_Type* p_BUZZER_Handler);

void FireDisplay_setItsLED(struct FireDisplay* const me, DigitalInterface_Type* p_LED_Handler);

Observer* FireDisplay_getObserver(void);

struct FireDisplay * FireDisplay_GetHandler(void);






#endif /* APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_FIREDISPLAY_H_ */
