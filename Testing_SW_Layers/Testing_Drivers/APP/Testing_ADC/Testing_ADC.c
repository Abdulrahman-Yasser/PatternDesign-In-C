/*
 * Testing_ADC.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#include "Testing_ADC.h"

static void Testing_ADC_Initialization(void);
static void Testing_ADC_Loop(void);

static void Testing_ADC_Initialization(void){
    Port_Init();
    ADC_Init();
}

static void Testing_ADC_Loop(void){
    uint16 x;
    ADC_ValueGroup_Type* my_ADCBuffer;
    my_ADCBuffer = NormalQueue_Create_STATIC_uint(Normal_Queue_uint16);
    ADC_SetupResultBuffer(TESTING_ADC_Channel, TESTING_ADC_SS_NUM, my_ADCBuffer);
    while(1){
        ADC_ReadingOperation(TESTING_ADC_Channel, TESTING_ADC_SS_NUM);
        ADC_ReadGroup(TESTING_ADC_Channel, TESTING_ADC_SS_NUM, my_ADCBuffer);
        x = ADC_ReadOneValue(TESTING_ADC_Channel, TESTING_ADC_SS_NUM);
    }
}


void Testing_ADC_Test(void){
    Testing_ADC_Initialization();
    Testing_ADC_Loop();
}

