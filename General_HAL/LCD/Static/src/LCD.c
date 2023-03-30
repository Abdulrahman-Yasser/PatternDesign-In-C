/*
 * LCD.c
 *
 *  Created on: Feb 6, 2023
 *      Author: abduy
 */

#include "../inc/LCD.h"
#include "../../Dynamic/inc/LCD_Cfg.h"

#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include <stdlib.h>

#define LCD_SLAVE_ADDRESS 0x27

/**********************************************************************************************************************
 *  Private Function Definition
 *********************************************************************************************************************/
void LCD_Init(LCD_Handler_Type* const me, uint8 LCD_ID,
              Std_BoolReturnType (*LCD_Write_CMD_arg)(LCD_Handler_Type* const me, uint8 cmd),
              Std_BoolReturnType (*LCD_Read_CMD_arg)(LCD_Handler_Type* const me, uint8 cmd),
              Std_BoolReturnType (*LCD_Write_DATA_arg)(LCD_Handler_Type* const me, LCD_CHAR_Type *Data),
              Std_BoolReturnType (*LCD_Read_DATA_arg)(LCD_Handler_Type* const me, LCD_CHAR_Type *Data),
              Std_BoolReturnType (*LCD_Destroy_arg)(LCD_Handler_Type* const me));

void LCD_CleanUp(LCD_Handler_Type* me);



/**********************************************************************************************************************
 *  Public Function Definition
 *********************************************************************************************************************/

Std_BoolReturnType LCD_I2C_Write_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd);
Std_BoolReturnType LCD_I2C_Read_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd);
Std_BoolReturnType LCD_I2C_Write_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data);
Std_BoolReturnType LCD_I2C_Read_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data);
Std_BoolReturnType LCD_I2C_Destroy_Function(LCD_Handler_Type* const me);


Std_BoolReturnType LCD_DIO_Write_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd);
Std_BoolReturnType LCD_DIO_Read_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd);
Std_BoolReturnType LCD_DIO_Write_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data);
Std_BoolReturnType LCD_DIO_Read_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data);
Std_BoolReturnType LCD_DIO_Destroy_Function(LCD_Handler_Type* const me);

/**********************************************************************************************************************
 *  Public Function Implementation
 *********************************************************************************************************************/

LCD_Handler_Type *LCD_Create(LCD_Interface_Type LCD_Interface_arg, uint8 LCD_ID){
    LCD_Handler_Type* me;
    me = (LCD_Handler_Type*)malloc(sizeof(LCD_Handler_Type));
    Delay_ms(15);
    if(me != Null_Ptr){
        if(LCD_Interface_arg == LCD_Interface_I2C){
            LCD_Init(me, LCD_ID, LCD_I2C_Write_Cmd_Function, LCD_I2C_Read_Cmd_Function, LCD_I2C_Write_Data_Function, LCD_I2C_Read_Data_Function, LCD_I2C_Destroy_Function);
            /* It must be 4-bit mode,to fit the RS, En, RW and 4-bits data */
            Delay_ms(50);
            me->LCD_Write_Cmd(me, 0x3);
            Delay_ms(5);
            me->LCD_Write_Cmd(me, 0x3);
            Delay_ms(5);
            me->LCD_Write_Cmd(me, 0x3);
            Delay_ms(10);
            me->LCD_Write_Cmd(me, 0x2);
            Delay_ms(10);
            me->LCD_Write_Cmd(me, Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Initial_FunctionSet << 2 );
            me->LCD_Write_Cmd(me, LCD_I2C_INST_DISPLAY_OFF_CURSOR_OFF_BLK_OFF);
            me->LCD_Write_Cmd(me, LCD_I2C_INST_CLEAR);
            me->LCD_Write_Cmd(me, Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Initial_EntryModeSet);
            me->LCD_Write_Cmd(me, LCD_I2C_INST_DISPLAY_ON_CURSOR_ON_BLK_OFF);
        }else if(LCD_Interface_arg == LCD_Interface_DIO){
            LCD_Init(me, LCD_ID, LCD_DIO_Write_Cmd_Function, LCD_DIO_Read_Cmd_Function, LCD_DIO_Write_Data_Function, LCD_DIO_Read_Data_Function, LCD_DIO_Destroy_Function);
            Delay_ms(50);
            me->LCD_Write_Cmd(me, 0x3);
            Delay_ms(5);
            me->LCD_Write_Cmd(me, 0x3);
            Delay_ms(5);
            me->LCD_Write_Cmd(me, 0x3);
            Delay_ms(10);
            me->LCD_Write_Cmd(me, 0x2);
            Delay_ms(10);
            me->LCD_Write_Cmd(me, Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Initial_FunctionSet << 2 );
            me->LCD_Write_Cmd(me, LCD_I2C_INST_DISPLAY_OFF_CURSOR_OFF_BLK_OFF);
            me->LCD_Write_Cmd(me, LCD_I2C_INST_CLEAR);
            me->LCD_Write_Cmd(me, Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Initial_EntryModeSet);
            me->LCD_Write_Cmd(me, LCD_I2C_INST_DISPLAY_ON_CURSOR_ON_BLK_OFF);
        }
    }
    return me;
}

void LCD_Destroy(LCD_Handler_Type* const me){
    LCD_CleanUp(me);
}
/*
 * ====================================== LCD DIO ======================================
 */

Std_BoolReturnType LCD_DIO_Write_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd){
    int i;
    Std_BoolReturnType my_return = E_TRUE;
    Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_RS_Pin, DIO_Level_LOW);
    Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_RW_Pin, DIO_Level_LOW);
    Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_E_Pin, DIO_Level_LOW);
    for(i = 0; i < 8; i++){
        Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Data_Pins.LCD_Pin[i], (DIO_LevelType)(1 & (cmd >> i)) );
    }
    Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_E_Pin, DIO_Level_HIGH);
    Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_E_Pin, DIO_Level_LOW);
    /* For those commands i should wait 1.6ms, but any command else i will just wait 40us */
    if(cmd == LCD_I2C_INST_CLEAR || cmd == LCD_I2C_INST_CURSOR_TO_HOME){
        Delay_ms(2);
    }else{
        Delay_ms(1);
    }
    return my_return;
}

Std_BoolReturnType LCD_DIO_Read_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd){
    Std_BoolReturnType my_return = E_TRUE;

    return my_return;
}

Std_BoolReturnType LCD_DIO_Write_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data){
    int i;
    Std_BoolReturnType my_return = E_TRUE;
    while(*Data == '\0'){
        Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_RS_Pin, DIO_Level_HIGH);
        Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_RW_Pin, DIO_Level_LOW);
        Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_E_Pin, DIO_Level_LOW);
        for(i = 0; i < 8; i++){
            Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Data_Pins.LCD_Pin[i], (DIO_LevelType)(1 & ((uint8)(*Data) >> i)) );
        }
        Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_E_Pin, DIO_Level_HIGH);
        Dio_WriteChannel(Lcd_DIO_Config[me->LCD_ID].LCD_Ctrl_Pins.LCD_E_Pin, DIO_Level_LOW);
        Delay_ms(1);
    }
    return my_return;
}

Std_BoolReturnType LCD_DIO_Read_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data){
    Std_BoolReturnType my_return = E_TRUE;

    return my_return;
}

Std_BoolReturnType LCD_DIO_Destroy_Function(LCD_Handler_Type* const me){
    /*
     * whatever you want here
     */
    Std_BoolReturnType r = E_TRUE;
    if(me != Null_Ptr){
        LCD_CleanUp(me);
    }
    free(me);
    return r;
}

/*
 * ====================================== LCD I2C ======================================
 */


Std_BoolReturnType LCD_I2C_Write_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd){
    Std_BoolReturnType my_return = E_TRUE;

    uint8 dataU, dataL;
    uint8 data_t[4];
    dataU = cmd & 0xf0;
    dataL = (cmd << 4)&0xf0;
    data_t[0] = dataU | 0x0C;  // en =1, rs =0
    data_t[1] = dataU | 0x08;  // en =0, rs =0
    data_t[2] = dataL | 0x0C;  // en =1, rs =0
    data_t[3] = dataL | 0x08;  // en =0, rs =0

    I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[0], 0);
    I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[1], 0);
    I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[2], 0);
    I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[3], 0);

    my_return = I2C_MasterPoke_to_transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, LCD_SLAVE_ADDRESS, 0, 4);
    Delay_ms(1);
    return my_return;
}

Std_BoolReturnType LCD_I2C_Read_Cmd_Function(LCD_Handler_Type* const me, uint8 cmd){
    Std_BoolReturnType my_return = E_TRUE;

    return my_return;
}

Std_BoolReturnType LCD_I2C_Write_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data){
    Std_BoolReturnType my_return = E_TRUE;
    int i = 0;
    while(Data[i] && Data[i] != '\0'){
        uint8 dataU, dataL;
        uint8 data_t[4];
        dataU = Data[i] & 0xf0;
        dataL = (Data[i] << 4)&0xf0;
        data_t[0] = dataU | 0x0D;  // en =1, rs =1
        data_t[1] = dataU | 0x09;  // en =0, rs =1
        data_t[2] = dataL | 0x0D;  // en =1, rs =1
        data_t[3] = dataL | 0x09;  // en =0, rs =1

        I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[0], 1);
        I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[1], 1);
        I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[2], 1);
        I2C_Push_to_Transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, data_t[3], 1);

        I2C_MasterPoke_to_transmit(Lcd_I2C_Config[me->LCD_ID].LCD_I2C_Channel, LCD_SLAVE_ADDRESS, 0, 4);
        Delay_ms(1);
        i++;
    }
    return my_return;
}

Std_BoolReturnType LCD_I2C_Read_Data_Function(LCD_Handler_Type* const me, LCD_CHAR_Type *Data){
    Std_BoolReturnType my_return = E_TRUE;

    return my_return;
}


Std_BoolReturnType LCD_I2C_Destroy_Function(LCD_Handler_Type* const me){
    /*
     * whatever you want here
     */
    Std_BoolReturnType r = E_TRUE;
    if(me != Null_Ptr){
        LCD_CleanUp(me);
    }
    free(me);
    return r;
}


/*
 * ====================================== Private Function Definition ======================================
 */

void LCD_Init(LCD_Handler_Type* const me, uint8 LCD_ID,
              Std_BoolReturnType (*LCD_Write_CMD_arg)(LCD_Handler_Type* const me, uint8 cmd),
              Std_BoolReturnType (*LCD_Read_CMD_arg)(LCD_Handler_Type* const me, uint8 cmd),
              Std_BoolReturnType (*LCD_Write_DATA_arg)(LCD_Handler_Type* const me, LCD_CHAR_Type *Data),
              Std_BoolReturnType (*LCD_Read_DATA_arg)(LCD_Handler_Type* const me, LCD_CHAR_Type *Data),
              Std_BoolReturnType (*LCD_Destroy_arg)(LCD_Handler_Type* const me)){
    me->LCD_ID = LCD_ID;

    me->LCD_Read_Cmd = LCD_Read_CMD_arg;
    me->LCD_Read_Data = LCD_Read_DATA_arg;
    me->LCD_Write_Cmd = LCD_Write_CMD_arg;
    me->LCD_Write_Data = LCD_Write_DATA_arg;
    me->LCD_Destroy = LCD_Destroy_arg;
}

void LCD_CleanUp(LCD_Handler_Type* me){
    me->LCD_ID = 0;
    me->LCD_Read_Cmd = Null_Ptr;
    me->LCD_Read_Data = Null_Ptr;
    me->LCD_Write_Cmd = Null_Ptr;
    me->LCD_Write_Data = Null_Ptr;

    free(me);
}
