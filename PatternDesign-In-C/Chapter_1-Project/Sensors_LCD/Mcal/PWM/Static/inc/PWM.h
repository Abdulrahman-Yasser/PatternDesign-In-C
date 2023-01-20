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


void pwm_clock_init(void);

void pwm_init(void);

void PWM_UpdateThresholds(uint32 ThreshLow, uint32 ThreshHigh, PWM_ChannelType PWM_BlockNum);

void pwm_update_comparators(uint32 Comp_A, uint32 Comp_B, PWM_ChannelType PWM_BlockNum);

void pwm_update_comparators_percentage(uint32 Comp_A_percentage, uint32 Comp_B_percentage, PWM_ChannelType PWM_BlockNum);

void pwm_update_DutyCycle(uint32 DesiredDutyCycle, PWM_ChannelType PWM_BlockNum);

void pwm_update_DutyCycle_Percentage(uint32 DesiredDutyCycle_Percentage, PWM_ChannelType PWM_BlockNum);

void pwm_update_generation_b(PWM_ChannelType *block, PWM_actionsType generate_values);

void pwm_update_generation_a(PWM_ChannelType *block, PWM_actionsType generate_values);

void pwm_update_load(PWM_ChannelType *block, uint32 value);

void pwm_change_mode(PWM_ChannelType *block, PWM_CountMode_t value);

void pwm_disable(PWM_ChannelType *block, uint8 bins);

void pwm_stop(PWM_ChannelType *block, uint8 bins);

void pwm_enable(PWM_ChannelType *block, uint8 bins);



#endif /* MCAL_PWM_STATIC_INC_PWM_H_ */
