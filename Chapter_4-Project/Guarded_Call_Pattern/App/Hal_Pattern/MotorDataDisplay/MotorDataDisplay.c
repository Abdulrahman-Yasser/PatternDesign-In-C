/*
 * MotorDataDisplay.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "MotorDataDisplay.h"
#include "../Speed/Speed.h"
#include "../Direction/Direction.h"

#include <stdlib.h>



struct FlightDataDisplay *FlightDataDisplay_Create(void){
    struct FlightDataDisplay *me;
    me = (struct FlightDataDisplay *)malloc(sizeof(struct FlightDataDisplay ));
    me->itsLcd = LCD_Create(LCD_Interface_I2C, 0);
    return me;
}

void FlightDataDisplay_showFlightData(struct FlightDataDisplay* const me){
    struct speed s;
    struct Direction d;
    LCD_CHAR_Type *my_char;
    s = kinematicData_getSpeed(me->itsKinematicData);
    my_char = "Speed : ";
    me->itsLcd->LCD_Write_Cmd(me->itsLcd, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
    me->itsLcd->LCD_Write_Data(me->itsLcd, my_char);
    my_char = int_to_string(getSpeed(&s));
    me->itsLcd->LCD_Write_Data(me->itsLcd, my_char);


    d = kinematicData_getDirection(me->itsKinematicData);
    my_char = "Direction : ";
    me->itsLcd->LCD_Read_Cmd(me->itsLcd, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
    me->itsLcd->LCD_Write_Data(me->itsLcd, my_char);
    my_char = int_to_string(getDirection(&d));
    me->itsLcd->LCD_Write_Data(me->itsLcd, my_char);
}

struct kinematicData* FlightDataDisplay_getItsKinematicData(struct FlightDataDisplay* const me){
    return me->itsKinematicData;
}

void FlightDataDisplay_setItsKinematicData(struct FlightDataDisplay* const me, struct kinematicData* p_KinematicData){
    me->itsKinematicData = p_KinematicData;
}

