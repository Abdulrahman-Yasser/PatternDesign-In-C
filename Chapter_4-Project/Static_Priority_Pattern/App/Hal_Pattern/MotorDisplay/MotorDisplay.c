/*
 * MotorDisplay.c
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#include "MotorDisplay.h"
#include "../MotorData/MotorData.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

static int md_priority = 10;
static int md_stack = 128;

void MotorDisplay_Init(void){
    TaskHandle_t MotorDisplayHandler;
    xTaskCreate(MotorDisplay_run, "MotorDisplay", md_stack, NULL, md_priority, &MotorDisplayHandler);
}

void MotorDisplay_Cleanup(void){

}

void MotorDisplay_run(void){
    TickType_t DisplayDelay = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&DisplayDelay, 500);
        display();
    }
}

void display(void){
//    printf("Command Speed : %d - ",getCmdSpd());
//    printf("Measured Speed : %d/n",getMeasSpd());
}

void MotorDisplay_initRelations(void){

}



