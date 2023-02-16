/*
 * LCD.h
 *
 *  Created on: Feb 6, 2023
 *      Author: abduy
 */

#ifndef HAL_LCD_STATIC_INC_LCD_H_
#define HAL_LCD_STATIC_INC_LCD_H_

#include "LCD_Types.h"

#define LCD_I2C_RS_INSTRUCTION              (uint8)0
#define LCD_I2C_RS_DATA                     (uint8)1

#define LCD_I2C_RW_WRITE                    (uint8)0
#define LCD_I2C_RW_READ                     (uint8)1

#define LCD_I2C_INST_CLEAR                          (uint8)0x01
#define LCD_I2C_INST_CURSOR_TO_HOME                 (uint8)0x02

/*  that instruction will make the cursor/Address Counter decrements to left
 *  when we enter a new character. */
#define LCD_I2C_INST_CURSOR_DEC_LEFT                (uint8)0x04

/*  that instruction will make the cursor/Address Counter increments to right
 *  when we enter a new character. */
#define LCD_I2C_INST_CURSOR_INC_RIGHT               (uint8)0x06

/*  that instruction will make the Address Counter decrements to left
 *  when we enter a new character and the display will be shifted left. */
#define LCD_I2C_INST_DISPLAY_SHIFT_RIGHT            (uint8)0x05

/*  that instruction will make the Address Counter increments to right
 *  when we enter a new character and the display will be shifted right. */
#define LCD_I2C_INST_DISPLAY_SHIFT_LEFT             (uint8)0x07

#define LCD_I2C_INST_DISPLAY_OFF_CURSOR_OFF_BLK_OFF     (uint8)0x08
#define LCD_I2C_INST_DISPLAY_OFF_CURSOR_OFF_BLK_ON      (uint8)0x09
#define LCD_I2C_INST_DISPLAY_OFF_CURSOR_ON_BLK_OFF      (uint8)0x0A
#define LCD_I2C_INST_DISPLAY_OFF_CURSOR_ON_BLK_ON       (uint8)0x0B
#define LCD_I2C_INST_DISPLAY_ON_CURSOR_OFF_BLK_OFF      (uint8)0x0C
#define LCD_I2C_INST_DISPLAY_ON_CURSOR_OFF_BLK_ON       (uint8)0x0D
#define LCD_I2C_INST_DISPLAY_ON_CURSOR_ON_BLK_OFF       (uint8)0x0E
#define LCD_I2C_INST_DISPLAY_ON_CURSOR_BLK_ON           (uint8)0x0F

#define LCD_I2C_CFG_2_LINES_4_DATA                  (uint8)0x28
#define LCD_I2C_CFG_2_LINES_8_DATA                  (uint8)0x38

#define LCD_I2C_SET_DDRAM_ADDRESS(Line, Pos)        (uint8)(0x80+(Line*0x40)+Pos)

#define LCD_I2C_INST_CURSOR_SHIFT_LEFT              (uint8)0x10
#define LCD_I2C_INST_CURSOR_SHIFT_RIGHT             (uint8)0x14

//#define LCD_I2C_INST_DISPLAY_SHIFT_LEFT             (uint8)0x18
//#define LCD_I2C_INST_DISPLAY_SHIFT_RIGHT            (uint8)0x1C

#define LCD_I2C_INST_CURSOR_GO_1ST_LINE             (uint8)0x80
#define LCD_I2C_INST_CURSOR_GO_2ND_LINE             (uint8)0xC0

#define LCD_I2C_CFG_2_LINES_4_DATA                  (uint8)0x28
#define LCD_I2C_CFG_2_LINES_8_DATA                  (uint8)0x38



#define LCD_I2C_INSTRUCTION_ON_OFF_CTRL             (uint8)0x08
#define LCD_I2C_INSTRUCTION_CURSOR_OR_CHAR_SHIFT    (uint8)0x10
#define LCD_I2C_INSTRUCTION_BUY_FUNCTION            (uint8)0x10

/*
 * ====================================== Public Function Definition ======================================
 */

/* LCD_ID must be the array address that contains the lcd configuration */

LCD_Handler_Type *LCD_Create(LCD_Interface_Type LCD_Interface_arg, uint8 LCD_ID);
void LCD_DIO_Destroy(LCD_Handler_Type* const me);


#endif /* HAL_LCD_STATIC_INC_LCD_H_ */
