

/**
 * main.c
 */
#include "main.h"

int main(void)
{
    main_Init();
    main_Loop();

}


void main_Init(void){
    Port_Init();
    pwm_init();
    I2C_init();
}

void main_Loop(void){
    struct kinematicData* my_kinematicData;
    my_kinematicData = kinematicData_Create();

    struct SpeedController* mySpeedController;
    mySpeedController = SpeedController_Create();
    SpeedController_setItsKinematicData(mySpeedController, my_kinematicData);

    struct DirectionController* myDirectionController;
    myDirectionController = DirectionController_Create();
    DirectionController_setItsKinematicData(myDirectionController, my_kinematicData);

    struct FlightDataDisplay* myDisplay;
    myDisplay = FlightDataDisplay_Create();
    FlightDataDisplay_setItsKinematicData(myDisplay, my_kinematicData);

    TaskHandle_t DC_Handler, SC_Handler, DisplayHandler;
    xTaskCreate(DirectionController_run, "DC_Task", 128, myDirectionController, 1, &DC_Handler);
    xTaskCreate(SpeedController_run, "SC_Task", 128, mySpeedController, 1, &SC_Handler);
    xTaskCreate(FlightDataDisplay_run, "Display", 128, myDisplay, 1, &DisplayHandler);

    vTaskStartScheduler();
    while(1);
}
