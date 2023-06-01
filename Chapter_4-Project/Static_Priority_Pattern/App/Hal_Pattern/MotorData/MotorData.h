/*
 * MotorData.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_MOTORDATA_MOTORDATA_H_
#define APP_HAL_PATTERN_MOTORDATA_MOTORDATA_H_

#include "../General_Common/Std_Types.h"


uint32 getCmdSpd(void);

uint32 getMeasSpd(void);

void setCmdSpd(uint32 cmdSpd);

void setMeasSpd(uint32 MeasSpd);



#endif /* APP_HAL_PATTERN_MOTORDATA_MOTORDATA_H_ */
