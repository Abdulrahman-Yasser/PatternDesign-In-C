/*
 * HistogramDisplay.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_LED_2_LED_2_H_
#define APP_HAL_PATTERNS_CLIENT_LED_2_LED_2_H_

#include "../../Server/Server_with_Observable/Server_with_Observable.h"
#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "../../Observable/Observable.h"

struct LED_2_s;

void my_LED_2_Init(struct LED_2_s* const me, Observable_Type* my_observable);
void LED_2_setItsLED(struct LED_2_s* const me, DigitalInterface_Type* p_LED_Handler);
struct LED_2_s * LED_2_GetHandler(void);

#endif /* APP_HAL_PATTERNS_CLIENT_LED_2_LED_2_H_ */
