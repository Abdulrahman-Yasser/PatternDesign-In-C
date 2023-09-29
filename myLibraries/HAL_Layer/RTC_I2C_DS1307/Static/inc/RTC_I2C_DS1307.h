/*
 * RTC_I2C_DS1307.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_H_
#define RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_H_

#include "RTC_I2C_DS1307_Types.h"

void RTC_DS1307_Init(void);



RTC_DS1307_TimeFrame_Type RTC_DS1307_getTime(void);

RTC_DS1307_DateFrame_Type RTC_DS1307_getDate(void);

void RTC_DS1307_setTime(RTC_DS1307_TimeFrame_Type*  my_time);

void RTC_DS1307_setDate(RTC_DS1307_DateFrame_Type* my_date);

Std_ReturnType RTC_DS1307_get_state(void);

#endif /* RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_H_ */
