/*
 * PLL.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Abdu
 */

#include "../inc/PLL.h"
#include "../inc/PLL_Types.h"
#include "../../Dynamic/inc/PLL_Cfg.h"
#include "Mcu_Hw.h"
#include "Platform_Types.h"
#include "CPU_resources.h"

#define RCC2_USERCC2_MASK   31
#define RCC2_BYPASS2_MASK   11
#define RCC2_OSCSRC_MASK    4
#define RCC_XTAL_MASK       6
#define RCC2_PWRDN2_MASK    13
#define RCC2_DIV400_MASK    30
#define RCC2_SYSDIV2_MASK   23
#define RIS_PLLRIS_MASK     6
#define RCC_USESYSDIV_MASK    22


void PLL_Init(void){
    uint32 my_system_divider;
    if(! (PLL_Container.myClockSource == SystemClockSource_MOSC || PLL_Container.myClockSource == SystemClockSource_PIOSC )){
        return ;
    }
    // too low, it can't be lowe than 4MHZ
    // Use RCC2 Register
    REG_ORING_ONE_BIT_CASTING_POINTED( SYSCTL_RCC2_REG, (RCC2_USERCC2_MASK));

    // do not use PLL until it's initialized
    REG_ORING_ONE_BIT_CASTING_POINTED( SYSCTL_RCC2_REG, (RCC2_BYPASS2_MASK));

    // Clear XTAL field Clock while PLL is initializing
    REG_CLEAR_THOSE_BITS_CASTING_POINTED(SYSCTL_RCC_REG, 0x3F << RCC_XTAL_MASK);
    REG_ORING_CASTING_POINTED( SYSCTL_RCC_REG, ( (PLL_Container.my_initial_speed - 1) << RCC_XTAL_MASK) );
    if(CPU_CLOCK < 4){
        return;
    }

    // Set initial XTAL Clock while PLL is initializing
    REG_CLEAR_THOSE_BITS_CASTING_POINTED(SYSCTL_RCC2_REG, 0b111 << RCC2_OSCSRC_MASK);
    REG_ORING_CASTING_POINTED(SYSCTL_RCC2_REG, PLL_Container.myClockSource << RCC2_OSCSRC_MASK);

    // active PLL
    REG_CLEAR_ONE_BIT_CASTING_POINTED(SYSCTL_RCC2_REG, RCC2_PWRDN2_MASK);

    // Clear SysDiv to set it to your value
    REG_CLEAR_THOSE_BITS_CASTING_POINTED(SYSCTL_RCC2_REG, 0x7f << (RCC2_SYSDIV2_MASK-1) );
    if(PLL_Container.Div400 == PLL_DIV400){
        my_system_divider = 400 / CPU_CLOCK ;
        REG_ORING_ONE_BIT_CASTING_POINTED(SYSCTL_RCC2_REG, RCC2_DIV400_MASK);
        REG_ORING_CASTING_POINTED( SYSCTL_RCC2_REG, (my_system_divider - 1) <<  (RCC2_SYSDIV2_MASK - 1));
    }else{
        my_system_divider = 200 / CPU_CLOCK ;
        REG_CLEAR_ONE_BIT_CASTING_POINTED(SYSCTL_RCC2_REG, RCC2_DIV400_MASK);
        REG_ORING_CASTING_POINTED( SYSCTL_RCC2_REG, (my_system_divider - 1) <<  RCC2_SYSDIV2_MASK );
    }
    do{
        REG_READ_CASTING_POINTED(my_system_divider, SYSCTL_RIS_REG);
    }while(! (my_system_divider & (1 << RIS_PLLRIS_MASK) ) );
    REG_ORING_ONE_BIT_CASTING_POINTED(SYSCTL_RCC_REG, RCC_USESYSDIV_MASK);
    REG_CLEAR_ONE_BIT_CASTING_POINTED( SYSCTL_RCC2_REG, RCC2_BYPASS2_MASK );
}

