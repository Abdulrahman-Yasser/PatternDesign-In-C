/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Types.h
 *       Module:  Nested Vector Interrupt Controller Driver (NVIC)
 *
 *  Description:  This File contains the standard types defined in the NVIC Driver
 *
 *********************************************************************************************************************/

#ifndef INTCTRL_TYPES_H
#define INTCTRL_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../General_Common/Std_Types.h"



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define IntCtrl_Prio_Group_8_SubGroup_0 0x04    /* bxxx */
#define IntCtrl_Prio_Group_4_SubGroup_2 0x05    /* bxxy */
#define IntCtrl_Prio_Group_2_SubGroup_4 0x06    /* bxyy */
#define IntCtrl_Prio_Group_0_SubGroup_8 0x07    /* byyy */



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
    Reset=1, Non_Maskable_Interrupt, Hard_Fault, Memory_Management, Bus_Fault, Usage_Fault, SVCall=11, Debug_Monitor
    ,PendSV=14, SysTick,GPIO_Port_A = 16, GPIO_Port_B, GPIO_Port_C, GPIO_Port_D, GPIO_Port_E, UART_0, UART_1, SSI_0, I2C_0,PWM0_Fault,
    PWM0_Generator_0,PWM0_Generator_1,PWM0_Generator_2,QEI0,ADC0_Sequence_0,ADC0_Sequence_1,ADC0_Sequence_2,ADC0_Sequence_3,
    Watchdog_Timers_0_and_1,Timer_0A_32, Timer_0B_32,Timer_1A_32,Timer_1B_32,Timer_2A_32,Timer_2B_32,Analog_Comparator_0,Analog_Comparator_1,
    System_Control = 44,Flash_Memory_Control_and_EEPROM_Control,GPIO_Port_F, UART2 = 49,SSI1,Timer_3A_32,Timer_3B_32,I2C1,QEI1,CAN0,CAN1,Hibernation_Module = 59,
    USB,PWM_Generator_3,DMA_Software,  DMA_Error,ADC1_Sequence_0,ADC1_Sequence_1,ADC1_Sequence_2,ADC1_Sequence_3,SSI2 = 73,SSI3,UART3,UART4,UART5,UART6,UART7,
    I2C2 = 84,I2C3,  Timer_4A_32,Timer_4B_32,Timer_5A_32 = 108,Timer_5B_32,Timer_0A_64,Timer_0B_64,Timer_1A_64,  Timer_1B_64,Timer_2A_64,Timer_2B_64,Timer_3A_64,
    Timer_3B_64,Timer_4A_64,Timer_4B_64,  Timer_5A_64,Timer_5B_64,System_Exception,PWM1_Generator_0 = 150,PWM1_Generator_1,PWM1_Generator_2,PWM1_Generator_3,
    PWM1_Fault
}IntCtrl_InterruptType_t;

typedef uint8 IntCtrl_Prio_t;

typedef enum{IntCtrl_Disable, IntCtrl_Enable}IntCtrl_state_t;

typedef struct
{
    IntCtrl_InterruptType_t int_num;
    IntCtrl_Prio_t int_priority;
    IntCtrl_state_t int_state;
}IntCtrl_Config_t;


  
#endif    /* INTCTRL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Types.h
 *********************************************************************************************************************/

