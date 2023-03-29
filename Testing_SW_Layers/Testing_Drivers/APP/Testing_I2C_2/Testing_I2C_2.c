/*
 * Testing_I2C_2.c
 *
 *  Created on: Mar 29, 2023
 *      Author: Abdu
 */

/*
 * Works fine, Tested
 */

#include <APP/Testing_I2C_2/Testing_I2C_2.h>

static void Testing_I2C_2_Init();
static void Testing_I2C_2_Write_1_byte(uint8 data, uint8 slave_mem_address);
static uint8 Testing_I2C_2_Read_1_byte(uint8 slave_mem_address);

static void Testing_I2C_2_Init(){
    I2C_init();
}

static void Testing_I2C_2_Write_1_byte(uint8 data, uint8 slave_mem_address){
    I2C_Push_to_Transmit(Testing_I2C_2_USED, data, 0);
    I2C_MasterPoke_to_transmit(Testing_I2C_2_USED, Testing_I2C_2_SLAVE_ADDRESS, slave_mem_address, 1);
}


static uint8 Testing_I2C_2_Read_1_byte(uint8 slave_mem_address){
    uint8 data[2];
    I2C_MasterPoke_to_receive(Testing_I2C_2_USED, Testing_I2C_2_SLAVE_ADDRESS, slave_mem_address, 1);
    I2C_Pop_the_Received(Testing_I2C_2_USED, data, 1);
    return data[0];
}


void Testing_I2C_2_Initialization(void){
    Port_Init();
    IntCtrl_Init();
    Testing_I2C_2_Init();
}

void Testing_I2C_2_Loop(void){
    uint8 data = 0;
    while(1){
        data = 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        data = data << 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        data = data << 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        data = data << 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        data = data << 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        data = data << 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        data = data << 1;
        Testing_I2C_2_Write_1_byte(data, data);
        Delay_ms(100);
        Testing_I2C_2_Write_1_byte(0xff, 0xff);
        Delay_ms(1000);
        Testing_I2C_2_Write_1_byte(0x00, 0x00);
        Delay_ms(1000);
    }
}
