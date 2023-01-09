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


 /**********************************************************************************************************************
  *  GLOBAL DATA
  *********************************************************************************************************************/
const Port_ConfigType ConfigPtr[configured_pins] =
{
  {Port_Pin_B1, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_DIO, Port_PinInternal_PullDown, Port_PinOutputCurrent_2ma},
  {Port_Pin_B0, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_DIO, Port_PinInternal_PullDown, Port_PinOutputCurrent_2ma},
  {Port_Pin_B2, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_I2Cn, Port_PinInternal_PullDown, Port_PinOutputCurrent_2ma},
  {Port_Pin_B3, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_I2Cn, Port_PinInternal_OpenDrain, Port_PinOutputCurrent_2ma},
  {Port_Pin_A6, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_I2Cn, Port_PinInternal_PullDown, Port_PinOutputCurrent_2ma},
  {Port_Pin_A7, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_I2Cn, Port_PinInternal_OpenDrain, Port_PinOutputCurrent_2ma}
};

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

