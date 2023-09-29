/*
 * PLL_Types.h
 *
 *  Created on: Jul 17, 2023
 *      Author: Abdu
 */

#ifndef PLL_STATIC_INC_PLL_TYPES_H_
#define PLL_STATIC_INC_PLL_TYPES_H_

#include "Std_Types.h"

typedef enum{
    SystemClockSource_MOSC, SystemClockSource_PIOSC,
    SystemClockSource_PIOSC_Div_4,
    SystemClockSource_LFIOSC, SystemClockSource_Hibernation=7,
    SystemClockSource_PLL
}SystemClockSource_Type;

typedef enum{
    SystemClockXTAL_4MHZ = 6, SystemClockXTAL_4_096MHZ, SystemClockXTAL_4_9152MHZ,
    SystemClockXTAL_5MHZ, SystemClockXTAL_5_12MHZ, SystemClockXTAL_6MHZ,
    SystemClockXTAL_6_144MHZ, SystemClockXTAL_7_372MHZ, SystemClockXTAL_8MHZ,
    SystemClockXTAL_8_192MHZ, SystemClockXTAL_10MHZ, SystemClockXTAL_12MHZ,
    SystemClockXTAL_12_288MHZ, SystemClockXTAL_13_56MHZ, SystemClockXTAL_14_31MHZ,
    SystemClockXTAL_16MHZ, SystemClockXTAL_16_384MHZ, SystemClockXTAL_18MHZ,
    SystemClockXTAL_20MHZ, SystemClockXTAL_24MHZ, SystemClockXTAL_25MHZ
}SystemClockXTAL_Type;

typedef enum{
    PLL_DIV400, PLL_DIV200
}PLL_DIV400_Type;

typedef struct {
    SystemClockSource_Type  myClockSource;
    SystemClockXTAL_Type my_initial_speed;
    PLL_DIV400_Type         Div400;
}PLL_Container_Type;


typedef struct {
    SystemClockXTAL_Type  myClockSource_XTAL;
}MIOSC_Container_Type;


#endif /* PLL_STATIC_INC_PLL_TYPES_H_ */
