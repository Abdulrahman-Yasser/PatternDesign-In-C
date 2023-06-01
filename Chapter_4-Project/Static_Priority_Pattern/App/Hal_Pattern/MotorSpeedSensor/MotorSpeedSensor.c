/*
 * MotorSpeedSensor.c
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#include <App/Hal_Pattern/MotorSpeedSensor/MotorSpeedSensor.h>
#include "../MotorData/MotorData.h"

#include "FreeRTOS.h"
#include "task.h"

/* mss for Motor speed Sensor */
static int mss_priority = 5;
static int mss_stack = 128;

void MotorSpeedSensor_Init(void){
    TaskHandle_t SpeedSensorHandler;
    xTaskCreate(MotorSpeedSensor_run, "SpeedSensor", mss_stack, Null_Ptr, mss_priority, &SpeedSensorHandler);
}

void MotorSpeedSensor_Cleanup(void){

}

void MotorSpeedSensor_run(void){
    TickType_t os_pend_timer_id = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&os_pend_timer_id, 50);
        getSpeed();
    }
}

void getSpeed(void){
    uint32 x;
    x = rand();
    setMeasSpd(x);
}


void MotorSpeedSensor_initRelations(void){
    MotorSpeedSensor_Init();
}

