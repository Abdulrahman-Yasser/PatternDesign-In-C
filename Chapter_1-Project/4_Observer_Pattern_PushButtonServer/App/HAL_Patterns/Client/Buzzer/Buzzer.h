/*
 * LED_1.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_LED_1_BUZZER_H_
#define APP_HAL_PATTERNS_CLIENT_LED_1_BUZZER_H_

#include "HAL_Layer/Digital_Intrface/Static/inc/Digital_Interface.h"
#include "../../Server/Server_with_Observable/Server_with_Observable.h"
#include "../../Observable/Observable.h"

struct Buzzer_s;

void my_Buzzer_Init(struct Buzzer_s* const me, Observable_Type* my_observable);
void Buzzer_setItsLED(struct Buzzer_s* const me, DigitalInterface_Type* p_Buzzer_Handler);
struct Buzzer_s * Buzzer_GetHandler(void);




#endif /* APP_HAL_PATTERNS_CLIENT_LED_1_LED_1_H_ */
