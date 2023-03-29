/*
 * RTC_I2C_DS1307_Cfg.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */


#include "../inc/RTC_I2C_DS1307_Cfg.h"

const RTC_DS1307_TimeFrame_Type RTC_DS1307_Time_Config = {
                                                                                     .seconds = 22, .minutes = 40, .hours = 24
};
const RTC_DS1307_DateFrame_Type RTC_DS1307_Date_Config = {
                                                                                        .day = RTC_Days_SUNDAY, .month = RTC_Month_MAR, .year = 23
};
