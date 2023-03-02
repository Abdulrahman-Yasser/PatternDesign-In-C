/*
 * LCD_Cfg.h
 *
 *  Created on: Feb 6, 2023
 *      Author: abduy
 */

#ifndef HAL_LCD_DYNAMIC_INC_LCD_CFG_H_
#define HAL_LCD_DYNAMIC_INC_LCD_CFG_H_

#include "../../Static/inc/LCD_Types.h"

#define LCD_I2C_CONFIGURED_NUMBER   1
#define LCD_DIO_CONFIGURED_NUMBER   0


extern const LCD_I2C_Container_Type Lcd_I2C_Config[LCD_I2C_CONFIGURED_NUMBER];
extern const LCD_DIO_Container_Type Lcd_DIO_Config[LCD_DIO_CONFIGURED_NUMBER];



#endif /* HAL_LCD_DYNAMIC_INC_LCD_CFG_H_ */
