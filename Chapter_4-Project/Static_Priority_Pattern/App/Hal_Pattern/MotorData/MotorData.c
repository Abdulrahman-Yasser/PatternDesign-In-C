/*
 * MotorData.c
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#include "MotorData.h"
#include "../General_HAL/DC_Motor/Static/inc/Motor.h"


static uint32 commandSpeed = 0;
static uint32 measuredSpeed = 0;



uint32 getCmdSpd(void){
    return commandSpeed;
}

uint32 getMeasSpd(void){
    return measuredSpeed + (rand()%2);
}

void setCmdSpd(uint32 cmdSpd){
    commandSpeed = cmdSpd;

}

void setMeasSpd(uint32 MeasSpd){
    measuredSpeed = MeasSpd;
}



