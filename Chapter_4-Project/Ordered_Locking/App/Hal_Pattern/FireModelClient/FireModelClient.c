/*
 * FireModelClient.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "FireModelClient.h"

typedef struct FireContainer_s{
    SmokeSensor* mySmokeSensor;
    TemperatureSensor* myTempSensor;
    WaterSensor* myWaterSensor;
    FireModeStates myState;
    DigitalInterface_Type myFanInterface;
    DigitalInterface_Type myBuzzerInterface;
    DigitalInterface_Type myLedInterface;
}FireContainer_t;

FireContainer_t *my_FireContainer;


void FireModeCreate(void){
    if(my_FireContainer == Null_Ptr){
        my_FireContainer = (FireContainer_t*)malloc(sizeof(FireContainer_t));
        my_FireContainer->myState = FireNotHappened;
    }
}

void FireModeSetInterface(DigitalInterface_Type* led, DigitalInterface_Type* fan, DigitalInterface_Type* buzzer){
    if(led != Null_Ptr || my_FireContainer != Null_Ptr || fan == Null_Ptr || buzzer == Null_Ptr){
        return;
    }
    my_FireContainer->myFanInterface = fan;
    my_FireContainer->myLedInterface = led;
    my_FireContainer->myBuzzerInterface = buzzer;
}
void FireModeSetTemperature(TemperatureSensor* me){
    if(me != Null_Ptr && my_FireContainer != Null_Ptr){
        my_FireContainer->myTempSensor = me;
    }
}
void FireModeSetSmoke(SmokeSensor* me){
    if(me != Null_Ptr && my_FireContainer != Null_Ptr){
        my_FireContainer->mySmokeSensor = me;
    }
}
void FireModeSetWater(WaterSensor* me){
    if(me != Null_Ptr && my_FireContainer != Null_Ptr){
        my_FireContainer->myWaterSensor = me;
    }
}
void FireModeReadSensors(void){
    uint32 temperature, smoke, water;
    TickType_t DC_Delay;
    while(1){
        DC_Delay = xTaskGetTickCount();
        vTaskDelayUntil(&DC_Delay, 4000);
        if(my_FanContainer == Null_Ptr){
            continue;
        }
        temperature = TemperatureSensor_getTemperature(my_FanContainer->myTempSensor);
        smoke = SmokeSensor_getSmoke(my_FireContainer->mySmokeSensor);
        water = WaterSensor_getWater(my_FireContainer->myWaterSensor);
        if(temperature > 60 && smoke > 30 && water > 20){
            // Smoke and Water and high temperature ... the fire is Big
            my_FireContainer->myState = FireIsBIIIG;
        }else if(temperature > 60 && smoke > 30 && water < 20){
            // High temperature and a lot of smoke, the fire can be handled
            my_FireContainer->myState = FireIsNormal;
        }else if(temperature < 60 && smoke > 30 && water < 20){
            // Just smoke, there is no water or heat .. the fire is ended
            my_FireContainer->myState = FireIsEnded;
        }else{
            my_FireContainer->myState = FireNotHappened;
        }
        FireModeActionState();
    }
}


void FireModeActionState(void){
    switch(my_FireContainer->myState){
    case FireIsBIIIG:
        my_FireContainer->myFanInterface->Write_High(my_FireContainer->myFanInterface);
        my_FireContainer->myLedInterface->Write_High(my_FireContainer->myLedInterface);
        my_FireContainer->myBuzzerInterface->Write_High(my_FireContainer->myBuzzerInterface);
        break;
    case FireIsNormal:
        my_FireContainer->myFanInterface->Write_Low(my_FireContainer->myFanInterface);
        my_FireContainer->myLedInterface->Write_High(my_FireContainer->myLedInterface);
        my_FireContainer->myBuzzerInterface->Write_High(my_FireContainer->myBuzzerInterface);
        break;
    case FireIsEnded:
        my_FireContainer->myFanInterface->Write_Low(my_FireContainer->myFanInterface);
        my_FireContainer->myBuzzerInterface->Write_Low(my_FireContainer->myBuzzerInterface);
        my_FireContainer->myLedInterface->Write_High(my_FireContainer->myLedInterface);
        break;
    case FireNotHappened:
        my_FireContainer->myFanInterface->Write_Low(my_FireContainer->myFanInterface);
        my_FireContainer->myLedInterface->Write_Low(my_FireContainer->myLedInterface);
        my_FireContainer->myBuzzerInterface->Write_Low(my_FireContainer->myBuzzerInterface);
        break;
    default :
        break;
    }
}

