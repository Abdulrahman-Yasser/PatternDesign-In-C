/*
 * RTC_I2C_DS1307.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */


#include "../General_Mcal/I2C/Static/Inc/I2C_Types.h"
#include "../General_Mcal/I2C/Static/Inc/I2C.h"
#include "../inc/RTC_I2C_DS1307.h"
#include "../../Dynamic/inc/RTC_I2C_DS1307_Cfg.h"

#define RTC_DS1307_I2C_Slave_Address        0x68

#define RTC_DS1307_Seconds_Register         0x00
#define RTC_DS1307_Minutes_Register         0x01
#define RTC_DS1307_Hours_Register           0x02
#define RTC_DS1307_Days_Register            0x03
#define RTC_DS1307_Date_Register            0x04
#define RTC_DS1307_Months_Register          0x05
#define RTC_DS1307_Years_Register           0x06
#define RTC_DS1307_Control_Register         0x07

#define RTC_DS1307_Bit_12_24_Mode_OFFSET           6

#define RTC_DS1307_Bit_12_24_Mode_MASK             0x40
#define RTC_DS1307_Bit_CH_MASK                     0x80



//static uint8 RTC_DS1307_Read(uint8 my_register);
static uint8 BCD_to_DECI(uint8 value);
static uint8 DECI_to_BCD(uint8 value);
static char* get_day(uint8 i);
static char* get_month(uint8 i);



static uint8 BCD_to_DECI(uint8 value){
    uint8 a, b;
    a = value & 0x0f;
    b = (value >> 4) & 0x0f;
    b = b * 10;
    return a + b;
}


static uint8 DECI_to_BCD(uint8 value){
    uint8 ones, tens, result;
    tens = value / 10;
    ones = value % 10;
    result = ones | (tens << 4);
    return result;
}

static char* get_day(uint8 i){
    char* RTD_DS1307_Days[7] = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATERDAY" };
    return RTD_DS1307_Days[i-1];

}

static char* get_month(uint8 i){
    char* RTD_DS1307_Months[12] = { "January" , "February", "March", "April", "MAY", "June", "July", "August", "September", "October", "November", "December"};
    return RTD_DS1307_Months[i-1];
}


void RTC_DS1307_Init(void){
    /* it will only be initialized once */
    uint8 data;
    static uint8 Only_Initialise_Once = 0;
    if(Only_Initialise_Once){
        return;
    }
    Only_Initialise_Once = 1;

    /* Set values of 12_24_mode and CLEAR CH Bit to stop the clock halt */
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, 0, 0);
    I2C_MasterPoke_to_transmit(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Seconds_Register, 1);
    data = RTC_12_vs_24_USER_CFG << RTC_DS1307_Bit_12_24_Mode_OFFSET;
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data, 0);
    I2C_MasterPoke_to_transmit(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Hours_Register, 1);
    /* Clears the CH Bit before writing the seconds value */
    data = 0;
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data, 0);
    I2C_MasterPoke_to_transmit(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Seconds_Register, 1);

    /* Send the Initialized time the first time */
    RTC_DS1307_setTime(&RTC_DS1307_InitialTime_Config);
    RTC_DS1307_setDate(&RTC_DS1307_InitialDate_Config);

    if(RTC_DS1307_get_state()){
        return;
    }else{
        while(1);
    }
}

RTC_DS1307_TimeFrame_Type RTC_DS1307_getTime(void){
    uint8 data[3];
    RTC_DS1307_TimeFrame_Type result;
    I2C_MasterPoke_to_receive(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Seconds_Register, 3, 0);
    I2C_Pop_the_Received(RTC_DS1307_I2C_Channel, data, 3);

    data[0] &= ~RTC_DS1307_Bit_CH_MASK;
    if(data[2] & RTC_DS1307_Bit_12_24_Mode_MASK){
        result.AM_PM = (data[2] >> 5) & 1;
        data[2] &= ~(1 << 5);
    }else{
        result.AM_PM = 0xff;
    }
    data[2] &= ~RTC_DS1307_Bit_12_24_Mode_MASK;

    result.seconds = BCD_to_DECI(data[0]);
    result.minutes = BCD_to_DECI(data[1]);
    result.hours = BCD_to_DECI(data[2]);
    return result;
}

RTC_DS1307_DateFrame_Type RTC_DS1307_getDate(void){
    uint8 data[4] ;
    RTC_DS1307_DateFrame_Type result;
    I2C_MasterPoke_to_receive(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Days_Register, 4, 0);
    I2C_Pop_the_Received(RTC_DS1307_I2C_Channel, data, 4);

    result.day = BCD_to_DECI(data[0]);
    result.date = BCD_to_DECI(data[1]);
    result.month = BCD_to_DECI(data[2]);
    result.year = BCD_to_DECI(data[3]);
    return result;
}

Std_ReturnType RTC_DS1307_get_state(void){
    uint8 data;
    I2C_MasterPoke_to_receive(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Seconds_Register, 1, 0);
    I2C_Pop_the_Received(RTC_DS1307_I2C_Channel, &data, 1);
    if((data & (1 << 7)) == 1){
        /* Failed */
        return E_NOK;
    }else{
        /* Succeed */
        return E_OK;
    }
}

void RTC_DS1307_setTime(RTC_DS1307_TimeFrame_Type* my_time){
    uint8 data[3];

    I2C_MasterPoke_to_receive(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Seconds_Register, 3, 0);
    I2C_Pop_the_Received(RTC_DS1307_I2C_Channel, data, 3);

    /* Keep the CH and 12_24 bit values as it is */
    data[0] &= RTC_DS1307_Bit_CH_MASK;
    data[2] &= RTC_DS1307_Bit_12_24_Mode_MASK;
    if(data[2]){
        /* 12-hour mode */
        data[2] |= (my_time->AM_PM & 0x01) << 5;
    }
    data[0] |= DECI_to_BCD(my_time->seconds);
    data[1] = DECI_to_BCD(my_time->minutes);
    data[2] |= DECI_to_BCD(my_time->hours);

    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[0], 0);
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[1], 0);
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[2], 0);
    I2C_MasterPoke_to_transmit(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Seconds_Register, 3);
}

void RTC_DS1307_setDate(RTC_DS1307_DateFrame_Type* my_date){
    uint8 data[4];
    data[0] = DECI_to_BCD(my_date->day);
    data[1] = DECI_to_BCD(my_date->date);
    data[2] = DECI_to_BCD(my_date->month);
    data[3] = DECI_to_BCD(my_date->year);

    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[0] , 0);
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[1] , 0);
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[2] , 0);
    I2C_Push_to_Transmit(RTC_DS1307_I2C_Channel, data[3] , 0);
    I2C_MasterPoke_to_transmit(RTC_DS1307_I2C_Channel, RTC_DS1307_I2C_Slave_Address, RTC_DS1307_Days_Register, 4);

}
