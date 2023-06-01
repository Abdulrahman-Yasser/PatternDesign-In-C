/*
 * MotorController.c
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */


#include "MotorController.h"

#include "../MotorData/MotorData.h"

#include "../General_HAL/DC_Motor/Static/inc/Motor.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>

/* mc for Motor controller
 */

static int mc_priority = 8;
static int mc_stack = 128;

static Motor_HandlerType* my_motor;


int motor1Spd;

void MotorController_Init(void){
    my_motor = Motor_HandlerCreate(0);
    TaskHandle_t MC_Handler;
    xTaskCreate( MotorController_run, "MotorControl", mc_stack, NULL, mc_priority, &MC_Handler);
}

void MotorController_Cleanup(void){

}

void MotorController_run(void){
    TickType_t last_delay_MC = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&last_delay_MC, 100);
        move();
    }
}

void move(void){
    uint32 m1Spd;
    /* this function would read the instrument
    panel to set the motor movement settings
    to set the position of the motors.
    Note that if you want to set only one
    of the motors, then set a negative value
    for the commanded position of the other
    */
    /* to make it from 0 to 90 */
    m1Spd = (((rand()%100) / 10 ) * 10);

    motor1Spd = m1Spd;
    Motor_ChangeSpeed(my_motor, (Motor_Speed_Type)motor1Spd);
    setCmdSpd( motor1Spd );
}

void zero(void){
    motor1Spd = 0;
    setCmdSpd(0);
}

void MotorController_initRelations(void){
    MotorController_Init();
}

