/*
 * LED_1.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_LED_1_LED_1_H_
#define APP_HAL_PATTERNS_CLIENT_LED_1_LED_1_H_

#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "../../Server/Server_with_Observable/Server_with_Observable.h"
#include "../../Observable/Observable.h"

struct LED_1_s;

void my_LED_1_Init(struct LED_1_s* const me, Observable_Type* my_observable);
void LED_1_setItsLED(struct LED_1_s* const me, DigitalInterface_Type* p_LED_Handler);
struct LED_1_s * LED_1_GetHandler(void);

#endif /* APP_HAL_PATTERNS_CLIENT_LED_1_LED_1_H_ */
