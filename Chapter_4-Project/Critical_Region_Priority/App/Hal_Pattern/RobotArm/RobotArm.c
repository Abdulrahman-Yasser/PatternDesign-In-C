/*
 * RobotArm.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "RobotArm.h"
#include <stdlib.h>

struct RobotArm* RobotArm_Create(void){
    struct RobotArm* me;
    me = (struct RobotArm*)malloc(sizeof(struct RobotArm));
    me->its_motor = Motor_HandlerCreate(0);
    return me;
}

uint8 RobotArm_moveTo(struct RobotArm* me, uint32 x, uint32 y, uint32 z){
    /*
     * it will only change the direction and the speed of the motor
     */
    Motor_Move(me->its_motor, x, y);
    return 1;
}
