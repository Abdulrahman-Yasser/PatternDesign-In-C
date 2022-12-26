/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file    IntCtrl_Lcfg.c
  *        \brief   Nested Vector Interrupt Controller Driver
  *
  *
  *      \details   This file contains all the needed Linkning time configuration for the NVIC driver
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/IntCtrl_Cfg.h"
#include "../../Static/inc/IntCtrl_Types.h"
#include "../../../../Common/Platform_Types.h"
#include "../../../../Common/Std_Types.h"



/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

const IntCtrl_Container_t Initialized_Interrupt_Container =
{
 .FaultMask_Reg=0x0,
 .PriMask_Reg=0x0,
 .BasePriMask_Reg=0x0,
 .Prio_Group_System=IntCtrl_Prio_Group_8_SubGroup_0,
 .container_ptr={
         {Memory_Management, 0x5, IntCtrl_Disable},      {Bus_Fault, 0x5, IntCtrl_Disable},
         {Usage_Fault, 0x5, IntCtrl_Disable},            {SVCall     , 0x5, IntCtrl_Disable},
         {Debug_Monitor     , 0x5, IntCtrl_Disable},     {PendSV      , 0x5, IntCtrl_Disable},
         {SysTick      , 0x5, IntCtrl_Disable},
         {GPIO_Port_A, 0x03, IntCtrl_Disable},            {GPIO_Port_B, 0x5, IntCtrl_Disable},
         {GPIO_Port_C, 0x5, IntCtrl_Disable},            {GPIO_Port_D, 0x5, IntCtrl_Disable},
         {GPIO_Port_E, 0x5, IntCtrl_Disable},            {UART_0     , 0x5, IntCtrl_Disable},
         {UART_1     , 0x5, IntCtrl_Disable},            {SSI_0      , 0x5, IntCtrl_Disable},
         {I2C_0      , 0x5, IntCtrl_Disable},            {PWM0_Fault , 0x5, IntCtrl_Disable},
         {PWM0_Generator_1, 0x5, IntCtrl_Disable},       {PWM0_Generator_2, 0x5, IntCtrl_Disable},
         {QEI0, 0x5 , IntCtrl_Disable},                  {ADC0_Sequence_0, 0x5, IntCtrl_Disable},
         {ADC0_Sequence_1, 0x5, IntCtrl_Disable},        {ADC0_Sequence_2, 0x5, IntCtrl_Disable},
         {ADC0_Sequence_3, 0x5, IntCtrl_Disable},        {Watchdog_Timers_0_and_1, 0x5, IntCtrl_Disable},
         {Timer_0A_32, 0x5, IntCtrl_Disable},            {Timer_0B_32, 0x5, IntCtrl_Disable},
         {Timer_1A_32, 0x5, IntCtrl_Disable},            {Timer_1B_32, 0x5, IntCtrl_Disable},
         {Timer_2A_32, 0x5, IntCtrl_Disable},            {Timer_2B_32, 0x5, IntCtrl_Disable},
         {Analog_Comparator_0, 0x5, IntCtrl_Disable},    {Analog_Comparator_1, 0x5, IntCtrl_Disable},
         {System_Control, 0x5, IntCtrl_Disable},         {Flash_Memory_Control_and_EEPROM_Control, 0x5, IntCtrl_Disable},
         {GPIO_Port_F      , 0x01, IntCtrl_Disable},      {UART2      , 0x5, IntCtrl_Disable},
         {SSI1 , 0x5, IntCtrl_Disable},                  {Timer_3A_32, 0x5, IntCtrl_Disable},
         {Timer_3B_32, 0x5, IntCtrl_Disable},            {I2C1, 0x5, IntCtrl_Disable},
         {QEI1, 0x5, IntCtrl_Disable},                   {CAN0, 0x5, IntCtrl_Disable},
         {CAN1, 0x5, IntCtrl_Disable},                   {Hibernation_Module, 0x5, IntCtrl_Disable},
         {USB, 0x5, IntCtrl_Disable},                    {PWM_Generator_3, 0x5, IntCtrl_Disable},
         {DMA_Software, 0x5, IntCtrl_Disable},           {DMA_Error, 0x5, IntCtrl_Disable},
         {ADC1_Sequence_0, 0x5, IntCtrl_Disable},        {ADC1_Sequence_1, 0x5, IntCtrl_Disable},
         {ADC1_Sequence_2, 0x5, IntCtrl_Disable},        {ADC1_Sequence_3     , 0x5, IntCtrl_Disable},
         {SSI2      , 0x5, IntCtrl_Disable},             {SSI3      , 0x5, IntCtrl_Disable},
         {UART3 , 0x5, IntCtrl_Disable},                 {UART4, 0x5, IntCtrl_Disable},
         {UART5, 0x5, IntCtrl_Enable},                  {UART6, 0x5, IntCtrl_Disable},
         {UART7, 0x5, IntCtrl_Enable},                  {I2C2, 0x5, IntCtrl_Disable},
         {I2C3, 0x5, IntCtrl_Disable},                   {Timer_4A_32, 0x5, IntCtrl_Disable},
         {Timer_4B_32, 0x5, IntCtrl_Disable},            {Timer_5A_32, 0x5, IntCtrl_Disable},
         {Timer_5B_32, 0x5, IntCtrl_Disable},            {Timer_0A_64, 0x5, IntCtrl_Disable},
         {Timer_0B_64, 0x5, IntCtrl_Disable},            {Timer_1A_64, 0x5, IntCtrl_Disable},
         {Timer_1B_64, 0x5, IntCtrl_Disable},            {Timer_2A_64, 0x5, IntCtrl_Disable},
         {Timer_2B_64, 0x5, IntCtrl_Disable},            {Timer_3A_64, 0x5, IntCtrl_Disable},
         {Timer_3B_64, 0x5, IntCtrl_Disable},            {Timer_4A_64, 0x5, IntCtrl_Disable},
         {Timer_4B_64, 0x5, IntCtrl_Disable},            {Timer_5A_64, 0x5, IntCtrl_Disable},
         {Timer_5B_64, 0x5, IntCtrl_Disable},            {System_Exception, 0x5, IntCtrl_Disable},
         {PWM1_Generator_0, 0x5, IntCtrl_Disable},       {PWM1_Generator_1, 0x5, IntCtrl_Disable},
         {PWM1_Generator_2, 0x5, IntCtrl_Disable},       {PWM1_Generator_3, 0x5, IntCtrl_Disable},
         {PWM1_Fault, 0x5, IntCtrl_Disable}
     }
};

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/
