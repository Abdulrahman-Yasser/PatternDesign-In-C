/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  PWM_Lcfg.c
  *        \brief  Digital Input Output Driver
  *
  *      \details  This file contains all the needed Linkning time configuration
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <Mcal/PWM/Dynamic/inc/PWM_Cfg.h>


const PWM_ConfigType PWM_Container[PWM_CONFIGURED_NUMBER] = {
     {PWM_NUM_0_1, 0, 65534,
      {PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing},
      {PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing},
      0, 0, PWM_CONTMODE_DOWN, 55703, 29490}
};

