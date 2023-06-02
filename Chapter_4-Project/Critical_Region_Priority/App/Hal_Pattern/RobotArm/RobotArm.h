/*
 * RobotArm.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_ROBOTARM_ROBOTARM_H_
#define APP_HAL_PATTERN_ROBOTARM_ROBOTARM_H_

#include "../../General_Common/Std_Types.h"
#include "../../General_HAL/DC_Motor/Static/inc/Motor.h"

struct RobotArm{
    Motor_HandlerType* its_motor;
};

struct RobotArm* RobotArm_Create(void);

uint8 RobotArm_moveTo(struct RobotArm* me, uint32 x, uint32 y, uint32 z);


#endif /* APP_HAL_PATTERN_ROBOTARM_ROBOTARM_H_ */
