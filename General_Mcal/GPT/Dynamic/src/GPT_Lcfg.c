/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file    GPT_Lcfg.c
  *        \brief   Global Timer Module Driver (GPT)
  *
  *      \details   The File Contains all the linking time user configurations in GPT driver's
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/GPT_Cfg.h"

 /**********************************************************************************************************************
  *  GLOBAL DATA
  *********************************************************************************************************************/

void __attribute__((weak)) App_Function(void);
void __attribute__((weak)) Default_Function(void);


const Gpt_ConfigType GPT_ConfigPtr_Container[TIMERS_NUMBERS] =
{
 {MY_TIMER0_CHANNEL, MY_TIMER0_PRESCALING_TYPE, MY_TIMER0_FREQUENCY, MY_TIMER0_WAIT_PERIOD, MY_TIMER0_MODE, MY_TIMER0_INTERRUPT, MY_TIMER0_ISR_CALLBACK, MY_TIMER0_ISR_CALLBACK },
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
};

