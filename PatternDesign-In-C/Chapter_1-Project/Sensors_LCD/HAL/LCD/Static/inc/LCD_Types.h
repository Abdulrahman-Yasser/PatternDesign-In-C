/*
 * LCD_Types.h
 *
 *  Created on: Nov 26, 2022
 *      Author: abduy
 */

#ifndef HAL_LCD_STATIC_INC_LCD_TYPES_H_
#define HAL_LCD_STATIC_INC_LCD_TYPES_H_
#include "../../../../Mcal/DIO/Static/inc/DIO_Types.h"
#include "../../../../Common/Platform_Types.h"

typedef uint8 LCD_CHAR_Type;
typedef uint8 LCD_Position_Type;

typedef struct{
    DIO_ChannelType LCD_Pins[8];
}LCD_DataPins_Type;


typedef struct{
    DIO_ChannelType LCD_Pins[3];
}LCD_CTR_Pins_Type;

typedef struct LCD_Container LCD_Container_Type;

typedef struct LCD_Container{
    LCD_DataPins_Type Lcd_DataPins;
    LCD_CTR_Pins_Type Lcd_CtrlPins;
    LCD_CHAR_Type Lcd_Write_String[16];
    LCD_CHAR_Type Lcd_Read_String[16];
    Std_BoolReturnType (*Lcd_isFull)(LCD_Container_Type* const me);
    Std_BoolReturnType (*Lcd_isEmpty)(LCD_Container_Type* const me);
    Std_BoolReturnType (*Lcd_getSize)(LCD_Container_Type* const me);
    void (*Lcd_insert)(LCD_Container_Type* const me, LCD_CHAR_Type k);
    LCD_CHAR_Type (*Lcd_remove)(LCD_Container_Type* const me, LCD_Position_Type i);
};



#endif /* HAL_LCD_STATIC_INC_LCD_TYPES_H_ */
