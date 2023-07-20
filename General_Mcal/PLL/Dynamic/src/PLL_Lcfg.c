/*
 * PLL_Lcfg.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Abdu
 */
#include "../inc/PLL_Cfg.h"

extern PLL_Container_Type PLL_Container = {
                                    .Div400 = PLL_DIV200,
                                    .myClockSource = SystemClockSource_MOSC,
                                    .my_initial_speed = SystemClockXTAL_16MHZ
};



