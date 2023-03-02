/*
 * LCD_Types.h
 *
 *  Created on: Feb 6, 2023
 *      Author: abduy
 */

#ifndef HAL_LCD_STATIC_INC_LCD_TYPES_H_
#define HAL_LCD_STATIC_INC_LCD_TYPES_H_



#include "../../General_Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../../General_Mcal/I2C/Dynamic/inc/I2C_Cfg.h"

typedef uint8 LCD_CHAR_Type;

typedef I2C_ChannelType LCD_I2C_Channel_Type;

typedef enum{
    LCD_Interface_DIO, LCD_Interface_I2C
}LCD_Interface_Type;

/*
 * nBit_nLine_n*nDot
 */
typedef enum{
    LCD_FunctionSet_4B_1L_57_F = 8, LCD_FunctionSet_4B_1L_510_F,
    LCD_FunctionSet_4B_2L_57_F, LCD_FunctionSet_4B_2L_510_F,
    LCD_FunctionSet_8B_1L_57_F, LCD_FunctionSet_8B_1L_510_F,
    LCD_FunctionSet_8B_2L_57_F, LCD_FunctionSet_8B_2L_510_F,
}LCD_Function_Set_Type;

typedef enum{
    LCD_EntryMode_INC_C_SHIFT_D = 4, LCD_EntryMode_INC_C_NOSHIFT_D,
    LCD_EntryMode_DEC_C_SHIFT_D, LCD_EntryMode_DEC_C_NOSHIFT_D
}LCD_Entry_Mode_Type;



typedef struct LCD_Handler LCD_Handler_Type;

struct LCD_Handler{
    uint8 LCD_ID;

    Std_BoolReturnType (*LCD_Write_Cmd)(LCD_Handler_Type* const me, uint8 cmd);
    Std_BoolReturnType (*LCD_Read_Cmd)(LCD_Handler_Type* const me, uint8 cmd);
    Std_BoolReturnType (*LCD_Write_Data)(LCD_Handler_Type* const me, LCD_CHAR_Type *Data);
    Std_BoolReturnType (*LCD_Read_Data)(LCD_Handler_Type* const me, LCD_CHAR_Type *Data);
};


/*
 * ==================================================== I2C LCD ====================================================
 */

typedef struct LCD_I2C_Container LCD_I2C_Container_Type;


struct LCD_I2C_Container{
    LCD_I2C_Channel_Type LCD_I2C_Channel;

    LCD_Function_Set_Type LCD_I2C_Initial_FunctionSet;
    LCD_Entry_Mode_Type LCD_I2C_Initial_EntryModeSet;
};

/*
 * ==================================================== DIO LCD ====================================================
 */

typedef struct{
    DIO_ChannelType LCD_Pin[8];
}LCD_Data_Pins_Type;


typedef struct{
    DIO_ChannelType LCD_E_Pin;
    DIO_ChannelType LCD_RS_Pin;
    DIO_ChannelType LCD_RW_Pin;
}LCD_CTR_Pins_Type;

typedef struct LCD_DIO_Container LCD_DIO_Container_Type;

struct LCD_DIO_Container{
    LCD_Data_Pins_Type LCD_Data_Pins;
    LCD_CTR_Pins_Type LCD_Ctrl_Pins;

    LCD_Function_Set_Type LCD_Initial_FunctionSet;
    LCD_Entry_Mode_Type LCD_Initial_EntryModeSet;
};


#endif /* HAL_LCD_STATIC_INC_LCD_TYPES_H_ */
