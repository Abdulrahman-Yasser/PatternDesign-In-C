/*
 * FanModeClient.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "FanModeClient.h"


typedef struct FanContainer_s{
    SmokeSensor* mySmokeSensor;
    TemperatureSensor* myTempSensor;
    WaterSensor* myWaterSensor;
    FanModeStates myState;
    DigitalInterface_Type myFanInterface;
}FanContainer_t;

FanContainer_t *my_FanContainer;

void FanModeCreate(void){
    if(my_FanContainer == Null_Ptr){
        my_FanContainer = (FanContainer_t*)malloc(sizeof(FanContainer_t*));
        my_FanContainer->myState = FanIsNotNeeded;
    }
}

void FanModeSetInterface(DigitalInterface_Type* me){
    if(my_FanContainer != Null_Ptr && me != Null_Ptr){
        my_FanContainer->myFanInterface = me;
    }
}

void FanModeSetTemperature(TemperatureSensor* me){
    if(my_FanContainer != Null_Ptr && me != Null_Ptr){
        my_FanContainer->myTempSensor = me;
    }
}
void FanModeSetSmoke(SmokeSensor* me){
    if(my_FanContainer != Null_Ptr && me != Null_Ptr){
        my_FanContainer->mySmokeSensor = me;
    }
}
void FanModeSetWater(WaterSensor* me){
    if(my_FanContainer != Null_Ptr && me != Null_Ptr){
        my_FanContainer->myWaterSensor = me;
    }
}


void FanModeReadSensors(void){
    uint32 temperature, smoke, water;
    TickType_t DC_Delay;
    while(1){
        DC_Delay = xTaskGetTickCount();
        vTaskDelayUntil(&DC_Delay, 8000);
        if(my_FanContainer == Null_Ptr){
            continue;
        }
        temperature = TemperatureSensor_getTemperature(my_FanContainer->myTempSensor);
        smoke = SmokeSensor_getSmoke(my_FanContainer->mySmokeSensor);
        water = WaterSensor_getWater(my_FanContainer->myWaterSensor);
        if(temperature > 60 && smoke < 30 && water < 20){
            // Just cooling the air
            my_FanContainer->myState = FanIsNeeded;
        }else{
            my_FanContainer->myState = FanIsNotNeeded;
        }
        FanModeActionState();
    }
}

void FanModeActionState(void){
    if(my_FanContainer->myState == FanIsNeeded){
        my_FanContainer->myFanInterface->Write_High(my_FanContainer->myFanInterface);
    }else if(my_FanContainer->myState == FanIsNotNeeded){
        my_FanContainer->myFanInterface->Write_Low(my_FanContainer->myFanInterface);
    }
}

