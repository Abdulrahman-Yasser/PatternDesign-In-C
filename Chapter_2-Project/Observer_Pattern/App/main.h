/*
 * main.h
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_


#include "../General_Mcal/PORT/Static/inc/PORT.h"
#include "../General_Mcal/DIO/Static/inc/DIO.h"

#include "HAL_Pattern/HAL_DigitalSensorObservable/Digital_SensorServer.h"

#include "HAL_Pattern/Leds_Observing/Buzzer_Observer/Buzzer_Observer.h"
#include "HAL_Pattern/Leds_Observing/Led_Observer/Led_Observer_1.h"
#include "HAL_Pattern/Leds_Observing/Motor_Observer/Motor_Observer.h"

void main_init(void);
void main_loop(void);



#endif /* APP_MAIN_H_ */
