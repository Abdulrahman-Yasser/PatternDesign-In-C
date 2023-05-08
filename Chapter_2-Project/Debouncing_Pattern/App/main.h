/*
 * main.h
 *
 *  Created on: May 7, 2023
 *      Author: Abdu
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../General_Mcal/PORT/Static/inc/PORT.h"

#include "HAL_Pattern/ButtonDriver/ButtonDriver.h"
#include "HAL_Pattern/LedEmitter/LedEmitter.h"

#define DEBOUNCE_BUTTON_DIO_ID  0

void Debouncing_Pattern_Iint(void);
void Debouncing_Pattern_Loop(void);



#endif /* APP_MAIN_H_ */
