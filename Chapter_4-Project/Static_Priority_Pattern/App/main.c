

/**
 * main.c
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
int main(void)
{
    main_Init();
    main_Loop();
}



void main_Init(void){
    Port_Init();
    Dio_Init();
    pwm_init();
}

void main_Loop(void){
    MotorController_Init();
    MotorDisplay_Init();
    MotorSpeedSensor_Init();
    vTaskStartScheduler();
    while(1){

    }
}
