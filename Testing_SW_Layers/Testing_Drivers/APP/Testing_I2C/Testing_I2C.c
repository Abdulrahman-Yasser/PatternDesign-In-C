/*
 * Testing_I2C.c
 *
 *  Created on: Mar 29, 2023
 *      Author: Abdu
 */

/*
 * Works fine, Tested
 */

#include "Testing_I2C.h"

static void Testing_I2C_Init();
static void Testing_I2C_Write_1_byte(uint8 data, uint8 slave_mem_address);
static uint8 Testing_I2C_Read_1_byte(uint8 slave_mem_address);

static void Testing_I2C_Init(){
    I2C_init();
}

static void Testing_I2C_Write_1_byte(uint8 data, uint8 slave_mem_address){
    I2C_Push_to_Transmit(TESTING_I2C_USED, data, 0);
    I2C_MasterPoke_to_transmit(TESTING_I2C_USED, TESTING_I2C_SLAVE_ADDRESS, slave_mem_address, 1);
}


static uint8 Testing_I2C_Read_1_byte(uint8 slave_mem_address){
    uint8 data[2];
    I2C_MasterPoke_to_receive(TESTING_I2C_USED, TESTING_I2C_SLAVE_ADDRESS, slave_mem_address, 1, 0);
    I2C_Pop_the_Received(TESTING_I2C_USED, data, 1);
    return data[0];
}


void Testing_I2C_Initialization(void){
    Port_Init();
    IntCtrl_Init();
    Testing_I2C_Init();
}

void Testing_I2C_Loop(void){
    while(1){
        Testing_I2C_Write_1_byte(0xff, 0xff);
        Delay_ms(1000);
        Testing_I2C_Write_1_byte(0x00, 0x00);
        Delay_ms(1000);
    }
}
