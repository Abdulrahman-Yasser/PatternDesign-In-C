/*
 * Observer_datatype.h
 *
 *  Created on: Dec 1, 2023
 *      Author: abduy
 */

#ifndef APP_HAL_PATTERNS_OBSERVER_OBSERVER_DATATYPE_H_
#define APP_HAL_PATTERNS_OBSERVER_OBSERVER_DATATYPE_H_

#include "../ObserverPattern_Cfg.h"

typedef struct{
    Update_t UpdateFuncPtr;
}Observer;




#endif /* APP_HAL_PATTERNS_OBSERVER_OBSERVER_DATATYPE_H_ */
