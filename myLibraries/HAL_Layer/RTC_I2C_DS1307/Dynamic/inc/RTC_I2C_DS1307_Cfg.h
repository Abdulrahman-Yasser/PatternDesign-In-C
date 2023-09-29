/*
 * RTC_I2C_DS1307_Cfg.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS1307_DYNAMIC_INC_RTC_I2C_DS1307_CFG_H_
#define RTC_I2C_DS1307_DYNAMIC_INC_RTC_I2C_DS1307_CFG_H_


#include "../../Static/inc/RTC_I2C_DS1307_Types.h"
#include "MCAL_Layer/I2C/Dynamic/inc/I2C_Cfg.h"

#define RTC_DS1307_I2C_Channel              I2C_RTC_CHANNEL_NUMBER

#define RTC_12_vs_24_USER_CFG          RTC_DS1307_USED_12_MODE

extern const RTC_DS1307_TimeFrame_Type RTC_DS1307_InitialTime_Config;
extern const RTC_DS1307_DateFrame_Type RTC_DS1307_InitialDate_Config;


#endif /* RTC_I2C_DS1307_DYNAMIC_INC_RTC_I2C_DS1307_CFG_H_ */
