/**********************************************************************************************************************
 *  FILE DESCRIPTION
 �*��-----------------------------------------------------------------------------------------------------------------*/
/**��������\file��PWM_Lcfg.c
 �*��������\brief��Digital Input Output Driver
 �*
 �*������\details��This file contains all the needed Linkning time configuration
 �*
 �*
 �*********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/PWM_Cfg.h"

/* PB4, PB5 */
const PWM_ConfigType PWM_Container[PWM_CONFIGURED_NUMBER] = {
     {PWM_NUM_0_0_A,  0, 65534,
      {PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing},
      0, 0, PWM_CONTMODE_DOWN}
};

