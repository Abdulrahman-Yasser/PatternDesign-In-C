/*
 * KinematicData.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_KINEMATICDATA_KINEMATICDATA_H_
#define APP_HAL_PATTERN_KINEMATICDATA_KINEMATICDATA_H_

#include "../Speed/Speed.h"
#include "../Direction/Direction.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

struct kinematicData{
    struct speed my_Speed;
    struct Direction my_Direction;
    SemaphoreHandle_t sema;
};

struct kinematicData* kinematicData_Create(void);


struct speed kinematicData_getSpeed(struct kinematicData* me);
void kinematicData_setSpeed(struct kinematicData* me, struct speed arg_Speed);

struct Direction kinematicData_getDirection(struct kinematicData* me);
void kinematicData_setDirection(struct kinematicData* me, struct Direction arg_Direction);


#endif /* APP_HAL_PATTERN_KINEMATICDATA_KINEMATICDATA_H_ */
