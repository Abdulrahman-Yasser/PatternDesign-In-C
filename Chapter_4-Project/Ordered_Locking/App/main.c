

/**
 * main.c
 */


#include "main.h"

int main(void)
{
    Port_Init();
    pwm_init();
    I2C_init();


    ResourceList* AllMyResources = ResourceList_Create();
    SemaphoreHandle_t MainMutexForResourceList;
    ResourceList_setItsMutex(AllMyResources, MainMutexForResourceList);


    /***************** Setting up my sensors (resources) *****************/
    /*
     * water sensor
     */

    Sensor_Type *BaseWaterSensor;
    BaseWaterSensor = Sensor_Create(0, Sensor_Interface_Digital);
    SemaphoreHandle_t WaterMutex;

    WaterSensor* myMain_WaterSensor;
    myMain_WaterSensor = WaterSensor_Create();

    WaterSensor_setWater(myMain_WaterSensor, BaseWaterSensor);
    WaterkeSensor_setItsMutex(myMain_WaterSensor, WaterMutex);
    WaterSensor_setItsResourceList(myMain_WaterSensor, AllMyResources);

    /*
     * Smoke sensor
     */

    Sensor_Type *BaseSmokeSensor;
    BaseSmokeSensor = Sensor_Create(1, Sensor_Interface_Analog);
    SemaphoreHandle_t SmokeMutex;

    SmokeSensor* myMain_SmokeSensor;
    myMain_SmokeSensor = SmokeSensor_Create();

    SmokeSensor_setSmoke(myMain_SmokeSensor, BaseSmokeSensor);
    SmokeSensor_setItsMutex(myMain_SmokeSensor, SmokeMutex);
    SmokeSensor_setItsResourceList(myMain_SmokeSensor, AllMyResources);

    /*
     * Temperature sensor
     */

    Sensor_Type *BaseTemperatureSensor;
    BaseTemperatureSensor = Sensor_Create(2, Sensor_Interface_Analog);
    SemaphoreHandle_t TemperatureMutex;

    TemperatureSensor* myMain_tempSensor;
    myMain_tempSensor = TemperatureSensor_Create();

    TemperatureSensor_setTemperature(myMain_tempSensor, BaseTemperatureSensor);
    TemperatureSensor_setItsMutex(myMain_tempSensor, TemperatureMutex);
    TemperatureSensor_setItsResourceList(myMain_tempSensor, AllMyResources);


    /***************** Setting up my Interfaces *****************/
    DigitalInterface_Type *myMain_Buzzer;
    myMain_Buzzer = Digital_Interface_Create(DIO_Channel2_A);

    DigitalInterface_Type *myMain_Led;
    myMain_Led = Digital_Interface_Create(DIO_Channel3_A);

    DigitalInterface_Type *myMain_Fan;
    myMain_Fan = Digital_Interface_Create(DIO_Channel4_A);

    /***************** Setting up my Clients *****************/
    FanModeCreate();
    FanModeSetSmoke(myMain_SmokeSensor);
    FanModeSetTemperature(myMain_tempSensor);
    FanModeSetWater(myMain_WaterSensor);
    FanModeSetInterface(myMain_Fan);

    FireModeCreate();
    FireModeSetSmoke(myMain_SmokeSensor);
    FireModeSetTemperature(myMain_tempSensor);
    FireModeSetWater(myMain_WaterSensor);
    FireModeSetInterface(myMain_Led, myMain_Fan, myMain_Buzzer);

    TaskHandle_t Fire_Handler, Fan_Handler;

    xTaskCreate(FanModeReadSensors, "Fan_Task", 128, Null_Ptr, 2, &Fan_Handler);
    xTaskCreate(FireModeReadSensors, "Fire_Task", 128, Null_Ptr, 1, &Fire_Handler);

    vTaskStartScheduler();
    while(1);

}
