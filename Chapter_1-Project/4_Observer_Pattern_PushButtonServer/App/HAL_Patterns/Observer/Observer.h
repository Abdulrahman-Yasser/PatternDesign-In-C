/*
 * Observer.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_
#define APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_



#include "Observer_datatype.h"



Observer* Observer_Create(Update_t fun);
void Observer_Destroy(Observer* me);

void Observer_SetFunction(Observer* me, Update_t func);

#endif /* APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_ */
