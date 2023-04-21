/*
 * Observer.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_
#define APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_


typedef struct{
    Update_t UpdateFuncPtr;
}Observer;

#endif /* APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_ */
