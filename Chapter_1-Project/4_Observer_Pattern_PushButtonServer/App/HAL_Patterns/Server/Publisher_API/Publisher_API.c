/*
 * WeatherStation_Server.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */


#include "../Server_with_Observable/Server_with_Observable.h"
#include "Publisher_API.h"

void ButtonStatus_Publish(struct Server_with_Observable_s* me){
    uint8 myButtonStatus;
    Server_with_Observable_Push(me);
}

uint8 Button_IsEmpty(struct Server_with_Observable_s* me){
    return 0;
}

