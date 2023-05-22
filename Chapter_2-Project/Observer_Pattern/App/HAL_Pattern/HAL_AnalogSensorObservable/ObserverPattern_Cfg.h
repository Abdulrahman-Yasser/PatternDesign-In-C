/*
 * ObserverPattern_Cfg.h
 *
 *  Created on: Mar 5, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVERPATTERN_CFG_H_
#define APP_HAL_PATTERNS_OBSERVERPATTERN_CFG_H_

#include "Std_Types.h"
#include "Server/TimeMarkedData/TimeMarkedData_DataType.h"

// to update temperature, date and time
typedef void (*Update_t)(struct TimeMarkedData*);

#endif /* APP_HAL_PATTERNS_OBSERVERPATTERN_CFG_H_ */
