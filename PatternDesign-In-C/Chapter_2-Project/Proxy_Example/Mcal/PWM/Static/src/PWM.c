/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  pwm.c
  *        \brief  pwm Driver
  *
  *      \details  This file contains the static implementation of the driver
  *                  it contains all the function implementation logic
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include <Mcal/PWM/Static/inc/PWM.h>
#include <Mcal/PWM/Dynamic/inc/PWM_Cfg.h>
#include "../../../../Common/Std_Types.h"


#include "../../../../Common/Mcu_Hw.h"
#include "../../../../Common/CPU_resources.h"

/**********************************************************************************************************************
 *  Variables Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/

static uint16 Low_thresholds[16];
static uint16 High_thresholds[16];
static uint16 Load_Values[16];
static uint16 PWM_ModulesUsed = 0;

/**********************************************************************************************************************
 *  LOCAL Functions Definition
 *********************************************************************************************************************/

static void pwm_clock_init(void);

/**********************************************************************************************************************
 *  LOCAL Functions Implementation
 *********************************************************************************************************************/

void pwm_clock_init(void){
    volatile uint32 delay;

    REG_WRITE_32_BIT_PTR( SYSCTL_RCC_REG_PWM , SYSCTL_RCC1_USEPWM_MASK);
    REG_CLEAR_SPECIFIC_BIT_PTR( SYSCTL_RCC_REG_PWM , (0x7 << SYSCTL_RCC1_PWMDIV_BIT_POS));
    REG_WRITE_32_BIT_PTR( SYSCTL_RCC_REG_PWM , (SYSCTL_PWMDIV_VALUE << SYSCTL_RCC1_PWMDIV_BIT_POS));
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void pwm_init(void){
    uint8 i;
    uint32 base;
    volatile uint32 delay;
    PWM_ChannelType my_channel;
    for(i = 0;i < PWM_CONFIGURED_NUMBER; i++){

    /*
     * Saving the values in a program life time variable, to make sure
     *  that there is no wrong value would enter by the user
     */
        Low_thresholds[ PWM_Container[i].pwm_block ] = PWM_Container[i].low_threshold;
        High_thresholds[ PWM_Container[i].pwm_block ] = PWM_Container[i].high_threshold;
        Load_Values[ PWM_Container[i].pwm_block ] = PWM_Container[i].load_value;


        /*
         * 1
         * Making sure that the channel was not initialized before
         * then save it's threshold to make sure the user does not exceed it after the initialization,
         * we will check whether the user going to exceed it in the run time or not
         */
        if( (PWM_ModulesUsed & (1 << PWM_Container[i].pwm_block) ) ){
            // the channel already initialized
        }else{
            if(PWM_ModulesUsed == 0){
                pwm_clock_init();
            }
            if(PWM_Container[i].pwm_block < 8){
                /* PWM 0 */
                REG_WRITE_32_BIT_PTR(SYSCTL_RCGCPWM_R, 0x01);
            }else{
                /* PWM 1 */
                REG_WRITE_32_BIT_PTR(SYSCTL_RCGCPWM_R, 0x02);
            }
            REG_READ_PTR(delay, SYSCTL_RCC_REG_PWM);
            PWM_ModulesUsed |= (1 << PWM_Container[i].pwm_block);
        }

        /*
         * 2
         * Giving the right values for the base and the channel
         * Making sure that the PWM pin exist
         */
        if(PWM_Container[i].pwm_block <= 7){
            base = PWM0_BASE_ADDERSS;
            my_channel = PWM_Container[i].pwm_block;
        }else if(PWM_Container[i].pwm_block > 7 && PWM_Container[i].pwm_block <= 13){
            base = PWM1_BASE_ADDERSS;
            my_channel = (PWM_ChannelType)((uint8)PWM_Container[i].pwm_block % 8);
        }else{
            continue;
        }

        /*
         * 3
         * Make sure that we do not exceed our High Threshold (if it has a value )
         */
        if(PWM_Container[i].high_threshold > 0 && PWM_Container[i].high_threshold > PWM_Container[i].load_value){
            continue;
        }
        /*
         * 4
         * Disable the PWM Channel till the configuration is done
         */
        REG_CLEAR_BIT_PTR((base + PWM_N_CTL_OFFSET +  (0x40 * my_channel/2)), 0);

        /*
         * 5
         * Write Compare A, Compare B values
         * if we are using a high threshold that we should not exceed and a low threshold that we don't exceed
         */
        if(PWM_Container[i].high_threshold > 0 && PWM_Container[i].low_threshold < PWM_Container[i].high_threshold){
            /*
             * make sure that the compare match is in the allowed range between LowThreshold : HighThreshold
             * if its not in the range put the Threshold as the compare value
             */
            /* Compare A */
            if(PWM_Container[i].compare_a_value < PWM_Container[i].low_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel/2)) , PWM_Container[i].low_threshold);
            }else if(PWM_Container[i].compare_a_value > PWM_Container[i].high_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel/2)) , PWM_Container[i].high_threshold);
            }else{
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel/2)) , PWM_Container[i].compare_a_value);
            }
            /* Compare B */
            if(PWM_Container[i].compare_b_value < PWM_Container[i].low_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel/2)) , PWM_Container[i].low_threshold);
            }else if(PWM_Container[i].compare_b_value > PWM_Container[i].high_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel/2)) , PWM_Container[i].high_threshold);
            }else{
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel/2)) , PWM_Container[i].compare_b_value);
            }
        }else{
            /*
             * if we are not using any threshold or there is a problem in the threshold values
             * ,just write the values
             */
            REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel/2) ) , PWM_Container[i].compare_a_value);
            REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel/2) ) , PWM_Container[i].compare_b_value);
        }

        /*
         * 6
         * Writing the PWM Load value
         */
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_LOAD_OFFSET + (0x40 * (my_channel/2)) ) , PWM_Container[i].load_value);


        /*
         * 7
         * Writing the PWM Generator functions
         */
        if(PWM_Container[i].pwm_block % 2 == 0){
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_A.PWM_GEN_ZERO << 0));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_A.PWM_GEN_LOAD << 2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPAU << 4));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPAD << 6));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPBU << 8));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPBD << 10));
        }else if(PWM_Container[i].pwm_block % 2 == 1){
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_B.PWM_GEN_ZERO << 0));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_B.PWM_GEN_LOAD << 2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPAU << 4));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPAD << 6));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPBU << 8));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel/2)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPBD << 10));
        }

        /*
         * 8
         * Writing the Counting mode either it was up or up/down
         */
        REG_WRITE_32_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * my_channel/2)) ) , (PWM_Container[i].count_mode) << 1);

         /*
         * 9
         * Enable the PWM
         */
        REG_WRITE_32_BIT_PTR((base + PWM_ENABLE_OFFSET) , PWM_Container[i].SubChannel << (my_channel/2 * 2));
        REG_WRITE_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * my_channel/2)) ) , 0);
    }
}

uint8 pwm_update_comparator(PWM_ChannelType channel, PWM_SubChannelType A_or_B, uint32 value){
    uint32 base;
    uint8 return_value = RETURN_FINE;
    if(value > High_thresholds[channel]){
        value = High_thresholds[channel];
        return_value = RETURN_ERROR;
    }else if(value < Low_thresholds[channel]){
        value = Low_thresholds[channel];
        return_value = RETURN_ERROR;
    }else if(value > Load_Values[channel]){
        value = Load_Values[channel];
        return_value = RETURN_ERROR;
    }else{

    }

    if(channel < 7){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR((base + PWM_N_CTL_OFFSET +  (0x40 * channel/2)), 0);
    if(A_or_B == PWM_SUB_CHANNEL_A || A_or_B == PWM_SUB_CHANNEL_BOTH){
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * channel/2) ) , value);
    }else{
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * channel/2) ) , value);
    }
    REG_WRITE_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * channel/2)) ) , 0);

    return return_value;
}


uint8 pwm_update_comparator_percentage(PWM_ChannelType channel, PWM_SubChannelType A_or_B, uint32 value){
    uint32 temp = 0, base;
    uint8 return_value = RETURN_FINE;

    /*
     * making sure that the value is less than 100
     */
    if(value > 100){
        return_value = RETURN_ERROR;
        value = 100;
    }

    /*
     * Writing the value in the range between LowThreshold : HighThreshold
     */
    if(High_thresholds[channel] > 0){
        temp = (High_thresholds[channel] - Low_thresholds[channel]) * value / 100;
        temp = temp + Low_thresholds[channel];
    }else{
        temp = Load_Values[channel] * value / 100;
    }

    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR((base + PWM_N_CTL_OFFSET +  (0x40 * channel/2)), 0);
    if(A_or_B == PWM_SUB_CHANNEL_A || A_or_B == PWM_SUB_CHANNEL_BOTH){
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * channel/2) ) , temp);
    }else{
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * channel/2) ) , temp);
    }
    REG_WRITE_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * channel/2)) ) , 0);
    return return_value;
}

uint8 pwm_update_generation(PWM_ChannelType channel, PWM_SubChannelType A_or_B, PWM_GeneratorEventsType Event, PWM_actionsType Action){
    uint32  base;
    uint8 return_value = RETURN_FINE;

    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0) ;
    if(A_or_B == PWM_SUB_CHANNEL_A || A_or_B == PWM_SUB_CHANNEL_BOTH){
        REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (0x3) << Event*2);
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (Action) << Event*2);
    }else{
        REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (0x3) << Event*2);
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (Action) << Event*2);
    }
    REG_WRITE_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) ,  0);
    return return_value;
}

uint8 PWM_UpdateThresholds(PWM_ChannelType channel, uint32 ThreshLow, uint32 ThreshHigh){
    uint32  base, temp1, temp2;
    uint8 return_value = RETURN_FINE;

    /*
     * Getting the base address and the Channel address
     */

    High_thresholds[channel] = ThreshHigh;
    Low_thresholds[channel] = ThreshLow;

    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_READ_PTR(temp1, base + PWM_N_CMPA_OFFSET + (0x40 * channel/2));
    REG_READ_PTR(temp2, base + PWM_N_CMPB_OFFSET + (0x40 * channel/2));
    if(temp1 > ThreshHigh){
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * channel/2) ) , temp1);
    }
    if(temp1 < ThreshLow){
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * channel/2) ) , temp1);
    }
    if(temp2 > ThreshHigh){
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * channel/2) ) , temp2);
    }
    if(temp2 < ThreshLow){
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * channel/2) ) , temp2);
    }
    return return_value;
}


uint8 pwm_AutomaticDutyCycle(PWM_ChannelType channel, PWM_SubChannelType Channel_A_or_B, uint32 DesiredDutyCycle){
    uint32  base, temp1, temp2;
    uint8 return_value = RETURN_FINE;

    temp1 = Load_Values[channel];
    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    temp2 = (temp1 * DesiredDutyCycle / 100) - 2;
    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    /*
     * make it just down counter
     */
    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 1);
    /*
     * Change the generation events to fit the duty cycles easily
     * Change the Compare Register to fit the Duty Cycle Usage
     */
    if(DesiredDutyCycle != 100){
        switch(Channel_A_or_B){
        case PWM_SUB_CHANNEL_A:
            REG_CLEAR_32_BIT_PTR( base + PWM_N_GENA_OFFSET + (0x40 * channel/2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_LOAD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_CMPAD*2);

            REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * channel/2) ) , temp2);
            break;
        case  PWM_SUB_CHANNEL_B:
            REG_CLEAR_32_BIT_PTR( base + PWM_N_GENB_OFFSET + (0x40 * channel/2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_LOAD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_CMPBD*2);

            REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * channel/2) ) , temp2);
            break;
        case  PWM_SUB_CHANNEL_BOTH:
                REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (0x3) << PWM_GEN_LOAD*2);
                REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_LOAD*2);
                REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (0x3) << PWM_GEN_ZERO*2);
                REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);
                REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (0x3) << PWM_GEN_CMPAD*2);
                REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_CMPAD*2);

                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * channel/2) ) , temp2);

                REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (0x3) << PWM_GEN_LOAD*2);
                REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_LOAD*2);
                REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (0x3) << PWM_GEN_ZERO*2);
                REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);
                REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (0x3) << PWM_GEN_CMPBD*2);
                REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_CMPBD*2);

                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * channel/2) ) , temp2);
                break;
        }
    }else{
        switch(Channel_A_or_B){
        case PWM_SUB_CHANNEL_A:
            REG_CLEAR_32_BIT_PTR( base + PWM_N_GENA_OFFSET + (0x40 * channel/2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_CMPAD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_LOAD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);

            break;

        case PWM_SUB_CHANNEL_B:
            REG_CLEAR_32_BIT_PTR( base + PWM_N_GENB_OFFSET + (0x40 * channel/2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_CMPBD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_LOAD*2);

            break;
        case  PWM_SUB_CHANNEL_BOTH:
            REG_CLEAR_32_BIT_PTR( base + PWM_N_GENA_OFFSET + (0x40 * channel/2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_CMPAD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_LOAD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);

            REG_CLEAR_32_BIT_PTR( base + PWM_N_GENB_OFFSET + (0x40 * channel/2));
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_action_Do_Nothing) << PWM_GEN_CMPBD*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_LOW) << PWM_GEN_ZERO*2);
            REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * channel/2)) ) , (PWM_ACTION_HIGH) << PWM_GEN_LOAD*2);

            break;

        }
    }
    REG_WRITE_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    return return_value;
}


uint8 pwm_update_load(PWM_ChannelType channel, uint32 value){
    uint32  base;
    uint8 return_value = RETURN_FINE;

    Load_Values[channel] = value;
    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    REG_WRITE_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    return return_value;
}


uint8 pwm_changeCount_mode(PWM_ChannelType channel, PWM_CountModeType value){
    uint32  base;
    uint8 return_value = RETURN_FINE;

    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    REG_CLEAR_SPECIFIC_BIT_PTR( (base + PWM_N_CTL_OFFSET + ((0x40 * channel/2)) ) , (0x3) << 1);
    REG_WRITE_32_BIT_PTR( (base + PWM_N_CTL_OFFSET + ((0x40 * channel/2)) ) , (value) << 1);
    REG_WRITE_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    return return_value;
}

uint8 pwm_disable(PWM_ChannelType channel, PWM_SubChannelType Pins){
    uint32  base;
    uint8 return_value = RETURN_FINE;

    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    REG_CLEAR_SPECIFIC_BIT_PTR(base + PWM_ENABLE_OFFSET +  (0x40 * channel/2) , 1 << (channel));
    return return_value;
}

uint8 pwm_stop(PWM_ChannelType channel, PWM_SubChannelType Pins){
    uint32  base;
    uint8 return_value = RETURN_FINE;

    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    Pins = Pins & 0x3;
    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    REG_CLEAR_SPECIFIC_BIT_PTR(base + PWM_ENABLE_OFFSET +  (0x40 * channel/2) , 1 << (channel));
    REG_WRITE_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    return return_value;
}

uint8 pwm_enable(PWM_ChannelType channel){
    uint32  base;
    uint8 return_value = RETURN_FINE;

    /*
     * Getting the base address and the Channel address
     */
    if(channel < 8){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = (PWM_ChannelType)((uint8)channel % 8);
    }

    REG_CLEAR_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    REG_WRITE_32_BIT_PTR((base + PWM_ENABLE_OFFSET) , 1 << (channel));
    REG_WRITE_BIT_PTR(base + PWM_N_CTL_OFFSET +  (0x40 * channel/2) , 0);
    return return_value;
}
