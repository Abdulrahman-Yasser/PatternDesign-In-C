/*
 * LED_Cfg.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Abdu
 */

#ifndef HAL_LED_DYNAMIC_INC_SENSOR_CFG_H_
#define HAL_LED_DYNAMIC_INC_SENSOR_CFG_H_

#include "../../Static/inc/Sensor_Types.h"


#define SENSOR_DIGITAL_CONFIGURED_NUMBER   1
#define SENSOR_ANALOG_CONFIGURED_NUMBER   0


extern const Sensor_Digital_Container_Type Sensor_Digital_Config[SENSOR_DIGITAL_CONFIGURED_NUMBER];

extern const Sensor_Analog_Container_Type Sensor_Analog_Config[SENSOR_ANALOG_CONFIGURED_NUMBER];

#endif /* HAL_LED_DYNAMIC_INC_SENSOR_CFG_H_ */
