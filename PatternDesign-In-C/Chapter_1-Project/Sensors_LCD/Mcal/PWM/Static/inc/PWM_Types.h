/*
 * PWM_Types.h
 *
 *  Created on: Jan 20, 2023
 *      Author: abduy
 */

#ifndef MCAL_PWM_DYNAMIC_INC_PWM_TYPES_H_
#define MCAL_PWM_DYNAMIC_INC_PWM_TYPES_H_

#include "../../../../Common/Std_Types.h"

typedef enum{
    PWM_CONTMODE_DOWN, PWM_COUNTMODE_UP_DOWN
}PWM_CountModeType;


typedef enum{
    PWM_action_Do_Nothing, PWM_TOGGLE, PWM_ACTION_LOW, PWM_ACTION_HIGH
}PWM_actionsType;


typedef enum{
    PWM_NUM_0_0, PWM_NUM_0_1, PWM_NUM_1_0, PWM_NUM_1_1,
    PWM_NUM_2_0, PWM_NUM_2_1, PWM_NUM_3_0, PWM_NUM_4_1, PWM_NUM_NotUsed
}PWM_ChannelType;

typedef struct{
    PWM_actionsType PWM_GEN_ZERO;
    PWM_actionsType PWM_GEN_LOAD;
    PWM_actionsType PWM_GEN_CMPAU;
    PWM_actionsType PWM_GEN_CMPAD;
    PWM_actionsType PWM_GEN_CMPBU;
    PWM_actionsType PWM_GEN_CMPBD;
}PWM_generationsType;


typedef struct{
    PWM_ChannelType pwm_block_num;
    uint32 compare_value;
    PWM_generationsType generate_values;
}PWM_ChannelConfigType;


/*
 * each PWM Pin will have it's own
 * Comparator register and action values
 */
typedef struct{
    PWM_ChannelConfigType pwm_block_num[2];
    uint8 pwmdiv;
    uint32 load_value;
    PWM_CountModeType count_mode;
    uint32 high_threshold;
    uint32 low_threshold;
}PWM_ConfigType;



#endif /* MCAL_PWM_DYNAMIC_INC_PWM_TYPES_H_ */
