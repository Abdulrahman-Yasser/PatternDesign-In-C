/*
 * RobotArm.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "RobotArm.h"


struct RobotArm* RobotArm_Create(void){
    struct RobotArm* me;
    me = (struct RobotArm*)malloc(sizeof(struct RobotArm));
    me->its_motor = Motor_HandlerCreate(0);
}

void RobotArm_moveTo(struct RobotArm* me, uint8 x, uint8 y, uint8 z){
    /*
     * it will only change the direction and the speed of the motor
     */
    Motor_Move(me->its_motor, x, y);
}
