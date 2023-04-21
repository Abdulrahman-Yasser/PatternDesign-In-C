/*
 * WeatherStation_Server.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */


#include <App/HAL_Patterns/Server/WeatherStation/WeatherStation_Server.h>

void WeatherStation_Push(void){
    uint8 smokeValue = SmokeHandler->GetValue(SmokeHandler);
    uint8 lightValue = LightHandler->GetValue(LightHandler);
    uint8 tepmValue = TempHandler->GetValue(TempHandler);

    WeatherData_Queue_Element_Type WeatherData_Single_Element = {
                                                                5, smokeValue, lightValue
    };
    if(WeatherData_Queue_IsFull()){
        WeatherData_Queue_Pop();
    }
    weatherData_Queue_Push(&WeatherData_Single_Element);
}

uint8 WeatherStation_IsEmpty(void){
    uint8 x = WeatherData_Queue_IsEmpty();
    return x;
}

