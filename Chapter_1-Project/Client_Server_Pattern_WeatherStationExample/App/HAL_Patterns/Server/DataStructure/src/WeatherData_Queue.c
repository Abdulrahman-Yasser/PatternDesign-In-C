/*
 * WeatherData_Queue.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */


#include "../inc/WeatherData_Queue.h"

void weatherData_Queue_Create(void){
    WeatherData_Queue.light = Queue_Create_DYNAMIC_uint8(8);
    WeatherData_Queue.smoke =  Queue_Create_DYNAMIC_uint8(8);
    WeatherData_Queue.temp =  Queue_Create_DYNAMIC_uint8(8);
}

void weatherData_Queue_Push(WeatherData_Queue_Element_Type* element){
    WeatherData_Queue.light->insert(WeatherData_Queue.light, element->light);
    WeatherData_Queue.smoke->insert(WeatherData_Queue.smoke, element->smoke);
    WeatherData_Queue.temp->insert(WeatherData_Queue.temp, element->temp);
}

WeatherData_Queue_Element_Type* weatherData_Queue_Pop(void){
    WeatherData_Queue_Element_Type* result;
    result = (WeatherData_Queue_Element_Type*)malloc(sizeof(WeatherData_Queue_Element_Type));
    result->light = WeatherData_Queue.light->remove(WeatherData_Queue.light);
    result->smoke = WeatherData_Queue.smoke->remove(WeatherData_Queue.smoke);
    result->temp = WeatherData_Queue.temp->remove(WeatherData_Queue.temp);
    return result;
}

uint8 WeatherData_Queue_GetSize(void){
    uint8 x, y, z;
    x = WeatherData_Queue.light->getSize(WeatherData_Queue.light);
    y = WeatherData_Queue.smoke->getSize(WeatherData_Queue.smoke);
    z = WeatherData_Queue.temp->getSize(WeatherData_Queue.temp);
    if(x != y || y != z || x != z){
        return 0;
    }else{
        return x;
    }
}

uint8 WeatherData_Queue_IsEmpty(void){
    uint8 x = 0;
    if(WeatherData_Queue.light->isEmpty(WeatherData_Queue.light)){
        x = 1;
    }
    if(WeatherData_Queue.smoke->isEmpty(WeatherData_Queue.smoke)){
        x = 1;
    }
    if(WeatherData_Queue.temp->isEmpty(WeatherData_Queue.temp)){
        x = 1;
    }
    return x;
}

uint8 WeatherData_Queue_IsFull(void){
    uint8 x = 0;
    if(WeatherData_Queue.light->isFull(WeatherData_Queue.light)){
        x = 1;
    }
    if(WeatherData_Queue.smoke->isFull(WeatherData_Queue.smoke)){
        x = 1;
    }
    if(WeatherData_Queue.temp->isFull(WeatherData_Queue.temp)){
        x = 1;
    }
    return x;
}

void weatherData_Queue_Destroy(void){
    Queue_Destroy_DYNAMIC_uint8 (WeatherData_Queue.light);
    Queue_Destroy_DYNAMIC_uint8 (WeatherData_Queue.smoke);
    Queue_Destroy_DYNAMIC_uint8 (WeatherData_Queue.temp);
}
