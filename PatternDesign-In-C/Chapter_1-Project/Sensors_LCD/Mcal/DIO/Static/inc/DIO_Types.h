/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Types.h
 *       Module:  DIO
 *
 *  Description:  The file got all the special types that we used for the DIO module
 *
 *********************************************************************************************************************/

#ifndef DIO_TYPES_H
#define DIO_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../../../Common/Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum{
    DIO_Channel0_A, DIO_Channel1_A, DIO_Channel2_A, DIO_Channel3_A, DIO_Channel4_A, DIO_Channel5_A, DIO_Channel6_A, DIO_Channel7_A,
    DIO_Channel0_B, DIO_Channel1_B, DIO_Channel2_B, DIO_Channel3_B, DIO_Channel4_B, DIO_Channel5_B, DIO_Channel6_B, DIO_Channel7_B,
    DIO_Channel0_C, DIO_Channel1_C, DIO_Channel2_C, DIO_Channel3_C, DIO_Channel4_C, DIO_Channel5_C, DIO_Channel6_C, DIO_Channel7_C,
    DIO_Channel0_D, DIO_Channel1_D, DIO_Channel2_D, DIO_Channel3_D, DIO_Channel4_D, DIO_Channel5_D, DIO_Channel6_D, DIO_Channel7_D,
    DIO_Channel0_E, DIO_Channel1_E, DIO_Channel2_E, DIO_Channel3_E, DIO_Channel4_E, DIO_Channel5_E,
    DIO_Channel0_F=40, DIO_Channel1_F, DIO_Channel2_F, DIO_Channel3_F, DIO_Channel4_F
}DIO_ChannelType;

typedef enum{
    DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD, DIO_PORTE, DIO_PORTF
}DIO_PortType;

typedef enum{
    DIO_HIGH, DIO_LOW
}DIO_LevelType;

typedef uint8 DIO_PortLevelType;

#endif    /* DIO_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: DIO_Types.h
 *********************************************************************************************************************/

