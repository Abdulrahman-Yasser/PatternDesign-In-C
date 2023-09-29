/*
 * RTC_I2C_DS3231.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */


#include "../inc/RTC_I2C_DS3231.h"
#include "MCAL_Layer/I2C/Static/inc/I2C_Types.h"
#include "MCAL_Layer/I2C/Static/inc/I2C.h"

#define RTC_DS3231_I2C_Channel              (I2C_ChannelType)I2C_NUM_0
#define RTC_DS3231_I2C_Slave_Address        0x0e

#define RTC_DS3231_Seconds_Register         0x00
#define RTC_DS3231_Minutes_Register         0x01
#define RTC_DS3231_Hours_Register           0x02
#define RTC_DS3231_Days_Register            0x03
#define RTC_DS3231_Date_Register            0x04
#define RTC_DS3231_Months_Register          0x05
#define RTC_DS3231_Years_Register           0x06
#define RTC_DS3231_Alarm1_Second_Register   0x07
#define RTC_DS3231_Alarm1_Minutes_Register  0x08
#define RTC_DS3231_Alarm1_Hour_Register     0x09
#define RTC_DS3231_Alarm1_Day_Date_Register 0x0A
#define RTC_DS3231_Alarm2_Minutes_Register  0x0B
#define RTC_DS3231_Alarm2_Hour_Register     0x0C
#define RTC_DS3231_Alarm2_Day_Date_Register 0x0D
#define RTC_DS3231_Control_Register         0x0e
#define RTC_DS3231_Status_Register          0x0f
#define RTC_DS3231_Aging_Register           0x10
#define RTC_DS3231_TempMSB_Register         0x11
#define RTC_DS3231_TempLSB_Register         0x12

#define I2C_Bit_12_24_Mode_Offset           6

//static uint8 RTC_DS3231_Read(uint8 my_register);
static uint8 BCD_to_DECI(uint8 value);
static uint8 DECI_to_BCD(uint8 value);

//static uint8 RTC_DS3231_Read(uint8 my_register){
//    uint8 data;
//    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, my_register, 1);
//    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, &data, 1) ;
//    return data;
//}


static uint8 BCD_to_DECI(uint8 value){
    return value;
}


static uint8 DECI_to_BCD(uint8 value){
    return value;
}


void RTC_DS3231_Init(void){
    uint8 data;
    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Control_Register, 1, 0);
    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, &data, 1) ;
    if(data & 0x80 ){
        /* OSC is stopped */
        return;
    }
    /* Enable INTCN and disable the SQW */
    data |= 0x04;
    I2C_Push_to_Transmit(RTC_DS3231_I2C_Channel, data, 1);
    I2C_MasterPoke_to_transmit(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Control_Register, 1);
}


uint16 RTC_DS3231_ReadTemperature(void ){
    uint8 data, Temperature[2];
    uint16 FullTemperature;
    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Control_Register, 1, 0);
    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, &data, 1) ;
    if(data & 0x80 ){
        /* OSC is stopped */
        return 0;
    }
    /* Enable CONV bit to read the temperature */
    data |= 0x20;
    I2C_Push_to_Transmit(RTC_DS3231_I2C_Channel, data, 1);
    I2C_MasterPoke_to_transmit(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Control_Register, 1);
    Delay_ms(2);
    /* Receive the temperature then pop it */
    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_TempMSB_Register, 2, 0);
    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, Temperature, 2) ;
    FullTemperature = ((uint16)Temperature[0] << 8) | Temperature[1];
    return FullTemperature;
}


uint8 RTC_DS3231_AlarmSet(RTC_DS3231_TimeAlarmFrame* time, RTC_DS3231_Alarm_Type Alarm_Mode, uint8 alarm_num){
    uint8 data[4], temp, i, error;
    time->seconds = DECI_to_BCD(time->seconds);
    time->minutes = DECI_to_BCD(time->minutes);
    time->hours = DECI_to_BCD(time->hours);
    time->day_date = DECI_to_BCD(time->day_date);
    if(alarm_num == 1){
        temp = (Alarm_Mode >> 0) & 0x01;
        data[0] = (temp << 7) | time->seconds;
        temp = (Alarm_Mode >> 1) & 0x01;
        data[1] = (temp << 7) | time->minutes;
        temp = (Alarm_Mode >> 2) & 0x01;
        data[2] = (temp << 7) | time->hours | (1 << I2C_Bit_12_24_Mode_Offset);
        temp = (Alarm_Mode >> 3) & 0x01;
        data[3] = (temp << 7);
        temp = (Alarm_Mode >> 4) & 0x01;
        data[3] = (((data[3]) | (temp << 6)) | time->day_date);
        for(i = 0; i < 4; i++){
            error = I2C_Push_to_Transmit(RTC_DS3231_I2C_Channel, data[i], 1);
            if(!error){
                return error;
            }
        }
        error = I2C_MasterPoke_to_transmit(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Alarm1_Second_Register, 4);
        if(!error){
            return error;
        }
    }else if(alarm_num == 2){
        temp = (Alarm_Mode >> 0) & 0x01;
        data[0] = (temp << 7) | time->minutes;
        temp = (Alarm_Mode >> 1) & 0x01;
        data[1] = (temp << 7) | time->hours | (1 << I2C_Bit_12_24_Mode_Offset);
        temp = (Alarm_Mode >> 2) & 0x01;
        data[2] = (temp << 7);
        temp = (Alarm_Mode >> 3) & 0x01;
        data[2] = (((data[2]) | (temp << 6)) | time->day_date);
        for(i = 0; i < 3; i++){
            error = I2C_Push_to_Transmit(RTC_DS3231_I2C_Channel, data[i], 1);
            if(!error){
                return error;
            }
        }
        error = I2C_MasterPoke_to_transmit(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Alarm2_Minutes_Register, 3);
        if(!error){
            return error;
        }
    }
    return error;
}


RTC_DS3231_TimeFrame RTC_DS3231_ReadTime_and_Date(void){
    uint8 data[7], i;
    RTC_DS3231_TimeFrame result;
    do{
        I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Seconds_Register, 1, 0);
        data[0] = I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, data, 1);
        data[0] = BCD_to_DECI(data[0]);
    }while(data[0] == 59);
    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Seconds_Register, 6, 0);
    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, data, 6);
    for(i = 0; i < 7; i++){
        data[i] = BCD_to_DECI(data[i]);
    }
    result.seconds = data[0];
    result.minutes = data[1];
    result.hours = data[2];
    result.day = data[3];
    result.date = data[4];
    result.month = data[5];
    result.year = data[6];
    return result;
}


RTC_DS3231_TimeFrame RTC_DS3231_ReadTime(void){
    uint8 data[3], i;
    RTC_DS3231_TimeFrame result;
    do{
        I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Seconds_Register, 1, 0);
        data[0] = I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, data, 1);
        data[0] = BCD_to_DECI(data[0]);
    }while(data[0] == 59);
    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Seconds_Register, 3, 0);
    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, data, 3);
    for(i = 0; i < 3; i++){
        data[i] = BCD_to_DECI(data[i]);
    }
    result.seconds = data[0];
    result.minutes = data[1];
    result.hours = data[2];
    return result;
}


RTC_DS3231_TimeFrame RTC_DS3231_ReadDate(void){
    uint8 data[4] , i;
    RTC_DS3231_TimeFrame result;
    do{
        I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Seconds_Register, 1, 0);
        data[0] = I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, data, 1);
        data[0] = BCD_to_DECI(data[0]);
    }while(data[0] == 59);
    I2C_MasterPoke_to_receive(RTC_DS3231_I2C_Channel, RTC_DS3231_I2C_Slave_Address, RTC_DS3231_Date_Register, 4, 0);
    I2C_Pop_the_Received(RTC_DS3231_I2C_Channel, data, 4);
    for(i = 0; i < 4; i++){
        data[i] = BCD_to_DECI(data[i]);
    }
    result.day = data[0];
    result.date = data[1];
    result.month = data[2];
    result.year = data[3];
    return result;
}



