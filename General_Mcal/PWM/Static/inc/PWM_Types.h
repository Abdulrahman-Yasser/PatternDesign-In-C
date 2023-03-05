/*
 * PWM_Types.h
 *
 *  Created on: Jan 20, 2023
 *      Author: abduy
 */

#ifndef General_Mcal_PWM_DYNAMIC_INC_PWM_TYPES_H_
#define General_Mcal_PWM_DYNAMIC_INC_PWM_TYPES_H_

#include "../../General_Common/Std_Types.h"

typedef enum{
    PWM_CONTMODE_DOWN, PWM_COUNTMODE_UP_DOWN
}PWM_CountModeType;


typedef enum{
    PWM_action_Do_Nothing, PWM_TOGGLE, PWM_ACTION_LOW, PWM_ACTION_HIGH
}PWM_actionsType;


typedef enum{
    PWM_NUM_0_0_A, PWM_NUM_0_0_B, PWM_NUM_0_1_A, PWM_NUM_0_1_B,
    PWM_NUM_0_2_A, PWM_NUM_0_2_B, PWM_NUM_0_3_A, PWM_NUM_0_3_B,
    PWM_NUM_1_0_A, PWM_NUM_1_0_B, PWM_NUM_1_1_A, PWM_NUM_1_1_B,
    PWM_NUM_1_2_A, PWM_NUM_1_2_B, PWM_NUM_1_3_A, PWM_NUM_1_3_B,
    PWM_Num_NotUsed
}PWM_ChannelType;

typedef enum{
    PWM_GEN_ZERO, PWM_GEN_LOAD, PWM_GEN_CMPAU,
    PWM_GEN_CMPAD, PWM_GEN_CMPBU, PWM_GEN_CMPBD
}PWM_GeneratorEventsType;

typedef struct{
    PWM_actionsType PWM_GEN_ZERO;
    PWM_actionsType PWM_GEN_LOAD;
    PWM_actionsType PWM_GEN_CMPAU;
    PWM_actionsType PWM_GEN_CMPAD;
    PWM_actionsType PWM_GEN_CMPBU;
    PWM_actionsType PWM_GEN_CMPBD;
}PWM_generationsType;



/*
 * each PWM Pin will have it's own
 * Comparator register and action values
 */
typedef struct{
    PWM_ChannelType pwm_block;
    uint8 pwmdiv;
    uint32 load_value;
    PWM_generationsType Generates;
    uint32 compare_a_value;
    uint32 compare_b_value;
    PWM_CountModeType count_mode;
}PWM_ConfigType;



#endif /* General_Mcal_PWM_DYNAMIC_INC_PWM_TYPES_H_ */
