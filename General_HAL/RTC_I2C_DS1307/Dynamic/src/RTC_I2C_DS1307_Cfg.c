/*
 * RTC_I2C_DS1307_Cfg.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */


#include "../inc/RTC_I2C_DS1307_Cfg.h"

extern const RTC_DS1307_TimeFrame_Type RTC_DS1307_InitialTime_Config = {
                                                                                     .seconds = 9, .minutes = 33, .hours = 4, .AM_PM = 1
};
extern const RTC_DS1307_DateFrame_Type RTC_DS1307_InitialDate_Config = {
                                                                                        .day = 1, .month = 4, .year = 23, .date = 1
};
