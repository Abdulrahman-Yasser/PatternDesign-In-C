/*
 * Testing_ADC.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#include "Testing_ADC.h"

static void Testing_I2C_Initialization(void);
static void Testing_I2C_Loop(void);

static void Testing_I2C_Initialization(void){
    Port_Init();
    ADC_Init();
}
static void Testing_I2C_Loop(void){

}


void Testing_ADC_Test(void){
    Testing_I2C_Initialization();
    Testing_I2C_Loop();
}

