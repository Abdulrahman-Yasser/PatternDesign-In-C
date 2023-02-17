/*
 * PWM.h
 *
 *  Created on: Jan 20, 2023
 *      Author: abduy
 */

#ifndef MCAL_PWM_STATIC_INC_PWM_H_
#define MCAL_PWM_STATIC_INC_PWM_H_

#include "PWM_Types.h"


#define SYSCTL_RCC1_USEPWM_MASK      0x00100000  /* USING DIVIDOR FOR PWM */
#define SYSCTL_RCC1_PWMDIV_BIT_POS      17       /* PWMDIV Bits Postion start from bit number 17 */
#define SYSCTL_PWMDIV_VALUE          0X00        /* PWM DIVISION VALUE */



void pwm_init(void);

uint8 pwm_update_comparator(PWM_ChannelType channel, uint32 value);

uint8 pwm_update_comparator_percentage(PWM_ChannelType channel, uint32 value);

uint8 pwm_update_generation(PWM_ChannelType channel, PWM_GeneratorEventsType Event, PWM_actionsType Action);

uint8 PWM_UpdateThresholds(PWM_ChannelType channel, uint32 ThreshLow, uint32 ThreshHigh);

uint8 pwm_AutomaticDutyCycle(PWM_ChannelType channel, uint32 DesiredDutyCycle);

uint8 pwm_update_load(PWM_ChannelType channel, uint32 value);

uint8 pwm_changeCount_mode(PWM_ChannelType channel, PWM_CountModeType value);

uint8 pwm_disable(PWM_ChannelType channel);

uint8 pwm_stop(PWM_ChannelType channel);

uint8 pwm_enable(PWM_ChannelType channel);



#endif /* MCAL_PWM_STATIC_INC_PWM_H_ */
