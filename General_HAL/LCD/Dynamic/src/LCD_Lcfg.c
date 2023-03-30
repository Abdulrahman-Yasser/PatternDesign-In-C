/*
 * LCD_Lcfg.c
 *
 *  Created on: Feb 6, 2023
 *      Author: abduy
 */

#include "../inc/LCD_Cfg.h"

const LCD_I2C_Container_Type Lcd_I2C_Config[LCD_I2C_CONFIGURED_NUMBER]={
                                                                        (I2C_ChannelType)I2C_NUM_3, LCD_FunctionSet_4B_2L_510_F, LCD_EntryMode_INC_C_SHIFT_D
};
const LCD_DIO_Container_Type Lcd_DIO_Config[LCD_DIO_CONFIGURED_NUMBER]={

};


