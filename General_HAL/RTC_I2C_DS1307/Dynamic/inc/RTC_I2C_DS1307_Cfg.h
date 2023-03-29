/*
 * RTC_I2C_DS1307_Cfg.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS1307_DYNAMIC_INC_RTC_I2C_DS1307_CFG_H_
#define RTC_I2C_DS1307_DYNAMIC_INC_RTC_I2C_DS1307_CFG_H_


#include "../../Static/inc/RTC_I2C_DS1307_Types.h"


#define RTC_12_vs_24_USER_CFG          RTC_DS1307_USED_12_MODE

extern const RTC_DS1307_TimeFrame_Type RTC_DS1307_Time_Config;
extern const RTC_DS1307_DateFrame_Type RTC_DS1307_Date_Config;


#endif /* RTC_I2C_DS1307_DYNAMIC_INC_RTC_I2C_DS1307_CFG_H_ */
