/**********************************************************************************************************************
  *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
 /**        \file  PORT_Lcfg.c
  *        \brief   Port driver
  *
  *      \details   the file contains all the linking variables conofigurations
  *
  *
  *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  INCLUDES
  *********************************************************************************************************************/
#include "../inc/PORT_Cfg.h"
#include "../../Static/inc/PORT_Types.h"
/*
PA0 17 - U0Rx - - - - - - CAN1Rx - - -
PA1 18 - U0Tx - - - - - - CAN1Tx - - -
PA2 19 - - SSI0Clk - - - - - - - - -
PA3 20 - - SSI0Fss - - - - - - - - -
PA4 21 - - SSI0Rx - - - - - - - - -
PA5 22 - - SSI0Tx - - - - - - - - -
PA6 23 - - - I2C1SCL - M1PWM2 - - - - - -
PA7 24 - - - I2C1SDA - M1PWM3 - - - - - -
PB0 45 USB0ID U1Rx - - - - - T2CCP0 - - - -
PB1 46 USB0VBUS U1Tx - - - - - T2CCP1 - - - -
PB2 47 - - - I2C0SCL - - - T3CCP0 - - - -
PB3 48 - - - I2C0SDA - - - T3CCP1 - - - -
PB4 58 AIN10 - SSI2Clk - M0PWM2 - - T1CCP0 CAN0Rx - - -
PB5 57 AIN11 - SSI2Fss - M0PWM3 - - T1CCP1 CAN0Tx - - -
PB6 1 - - SSI2Rx - M0PWM0 - - T0CCP0 - - - -
PB7 4 - - SSI2Tx - M0PWM1 - - T0CCP1 - - - -
PC0 52 - TCK SWCLK - - - - - T4CCP0 - - - -
PC1 51 - TMS SWDIO - - - - - T4CCP1 - - - -
PC2 50 - TDI - - - - - T5CCP0 - - - -
PC3 49 - TDO SWO - - - - - T5CCP1 - - - -
PC4 16 C1- U4Rx U1Rx - M0PWM6 - IDX1 WT0CCP0 U1RTS - - -
PC5 15 C1+ U4Tx U1Tx - M0PWM7 - PhA1 WT0CCP1 U1CTS - - -
PC6 14 C0+ U3Rx - - - - PhB1 WT1CCP0 USB0EPEN - - -
PC7 13 C0- U3Tx - - - - - WT1CCP1 USB0PFLT - - -
PD0 61 AIN7 SSI3Clk SSI1Clk I2C3SCL M0PWM6 M1PWM0 - WT2CCP0 - - - -
PD1 62 AIN6 SSI3Fss SSI1Fss I2C3SDA M0PWM7 M1PWM1 - WT2CCP1 - - - -
PD2 63 AIN5 SSI3Rx SSI1Rx - M0FAULT0 - - WT3CCP0 USB0EPEN - - -
PD3 64 AIN4 SSI3Tx SSI1Tx - - - IDX0 WT3CCP1 USB0PFLT - - -
PD4 43 USB0DM U6Rx - - - - - WT4CCP0 - - - -
PD5 44 USB0DP U6Tx - - - - - WT4CCP1 - - - -
PD6 53 - U2Rx - - M0FAULT0 - PhA0 WT5CCP0 - - - -
PD7 10 - U2Tx - - - - PhB0 WT5CCP1 NMI - - -
PE0 9 AIN3 U7Rx - - - - - - - - - -
PE1 8 AIN2 U7Tx - - - - - - - - - -
PE2 7 AIN1 - - - - - - - - - - -
PE3 6 AIN0 - - - - - - - - - - -
PE4 59 AIN9 U5Rx - I2C2SCL M0PWM4 M1PWM2 - - CAN0Rx - - -
PE5 60 AIN8 U5Tx - I2C2SDA M0PWM5 M1PWM3 - - CAN0Tx - - -
PF0 28 - U1RTS SSI1Rx CAN0Rx - M1PWM4 PhA0 T0CCP0 NMI C0o - -
PF1 29 - U1CTS SSI1Tx - - M1PWM5 PhB0 T0CCP1 - C1o TRD1 -
PF2 30 - - SSI1Clk - M0FAULT0 M1PWM6 - T1CCP0 - - TRD0 -
PF3 31 - - SSI1Fss CAN0Tx - M1PWM7 - T1CCP1 - - TRCLK -
PF4 5 - - - - - M1FAULT0 IDX0 T2CCP0 USB0EPEN - -
*/
 /**********************************************************************************************************************
  *  GLOBAL DATA
  *********************************************************************************************************************/
/* Testing ADC */


const Port_ConfigType ConfigPtr[configured_pins] =
{
  {Port_Pin_E3, Port_PinLevel_LOW, Port_PinDir_IN, Port_PinMode_ADC, Port_PinInternal_HW, Port_PinOutputCurrent_2ma}
};


/**********************************************************************************************************************
 * Testing I2C
 *********************************************************************************************************************/

/* I2CSDA Should be Open-Drain*/
//const Port_ConfigType ConfigPtr[configured_pins] =
//{
//  {Port_Pin_D0, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_I2Cn, Port_PinInternal_HW, Port_PinOutputCurrent_2ma},  // SCL
//  {Port_Pin_D1, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_I2Cn, Port_PinInternal_OpenDrain, Port_PinOutputCurrent_2ma}  // SDA
//};

/* For initializing the whole pins */
/*
const Port_ConfigType ConfigPtr[configured_pins] =
{
  {Port_Pin_A0, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A1, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A2, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A3, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A4, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A5, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A6, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_A7, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B0, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B1, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B2, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B3, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B4, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B5, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B6, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_B7, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C0, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C1, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C2, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C3, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C4, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C5, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C6, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_C7, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D0, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D1, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D2, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D3, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D4, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D5, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D6, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_D7, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_E0, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_E1, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_E2, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_E3, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_E4, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_E5, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_F0, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_F1, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_DIO, Port_PinInternal_PullDown, Port_PinOutputCurrent_2ma},
  {Port_Pin_F2, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_DIO, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_F3, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma},
  {Port_Pin_F4, Port_PinLevel_LOW, Port_PinDir_OUT, Port_PinMode_NONE, Port_PinInternal_PullUp, Port_PinOutputCurrent_2ma}
};
*/

