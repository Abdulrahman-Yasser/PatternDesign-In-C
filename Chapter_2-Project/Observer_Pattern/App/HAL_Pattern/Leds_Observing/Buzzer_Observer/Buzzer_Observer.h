/*
 * Buzzer_Observer.h
 *
 *  Created on: May 31, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_LEDS_OBSERVING_LED_OBSERVER_1_BUZZER_OBSERVER_1_H_
#define APP_HAL_PATTERN_LEDS_OBSERVING_LED_OBSERVER_1_BUZZER_OBSERVER_1_H_


#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "../../Observer/Observer.h"
#include "../../Observable/Observable.h"
#include "../../HAL_DigitalSensorObservable/Digital_SensorServer.h"



struct Buzzer_Observer* Buzzer_Observer_Init(DigitalObservableSensor_Type* the_Client);

void Buzzer_Observer_Update(uint8 d);



#endif /* APP_HAL_PATTERN_LEDS_OBSERVING_LED_OBSERVER_1_LED_OBSERVER_1_H_ */
