/*
 * RTC_I2C_DS3231.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS3231_STATIC_INC_RTC_I2C_DS3231_H_
#define RTC_I2C_DS3231_STATIC_INC_RTC_I2C_DS3231_H_

#include "RTC_I2C_DS3231_Types.h"

void RTC_DS3231_Init(void);


uint16 RTC_DS3231_ReadTemperature(void );

uint8 RTC_DS3231_AlarmSet(RTC_DS3231_TimeAlarmFrame* time, RTC_DS3231_Alarm_Type Alarm_Mode, uint8 alarm_num);

RTC_DS3231_TimeFrame RTC_DS3231_ReadTime_and_Date(void);

RTC_DS3231_TimeFrame RTC_DS3231_ReadTime(void);

RTC_DS3231_TimeFrame RTC_DS3231_ReadDate(void);

#endif /* RTC_I2C_DS3231_STATIC_INC_RTC_I2C_DS3231_H_ */
