/*
 * LED_Driver.c
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */


#include "LED_Driver.h"

#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

typedef struct LED_Driver LED_Driver;

struct LED_Driver{
    DigitalInterface_Type LED;
};

void
