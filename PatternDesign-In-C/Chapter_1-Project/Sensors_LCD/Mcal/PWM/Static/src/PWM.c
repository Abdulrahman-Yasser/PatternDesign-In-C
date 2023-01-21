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

uint16 Low_thresholds[8];
uint16 High_thresholds[8];

static uint16 PWM_ModulesUsed = 0;

void pwm_clock_init(){
    SYSCTL_RCC_REG |= SYSCTL_RCC1_USEPWM_MASK;
    SYSCTL_RCC_REG &= ~(0x7 << SYSCTL_RCC1_PWMDIV_BIT_POS);
    SYSCTL_RCC_REG |= (SYSCTL_PWMDIV_VALUE << SYSCTL_RCC1_PWMDIV_BIT_POS);
}

void pwm_init(void){
    uint8 i, j;
    uint32 base;
    volatile uint32 delay;
    PWM_ChannelType my_channel;
    for(i = 0;i < PWM_CONFIGURED_NUMBER; i++){
        /*
         * 1
         * Giving the right values for the base and the channel
         * Making sure that the PWM pin exist
         */
        if(PWM_Container[i].pwm_block >= 0 && PWM_Container[i].pwm_block <= 3){
            base = PWM0_BASE_ADDERSS;
            my_channel = PWM_Container[i].pwm_block;
        }else if(PWM_Container[i].pwm_block > 3 && PWM_Container[i].pwm_block <= 7){
            base = PWM0_BASE_ADDERSS;
            my_channel = PWM_Container[i].pwm_block % 4;
        }else{
            continue;
        }
        /*
         * 2
         * Make sure that we do not exceed our High Threshold (if it has a value )
         */
        if(PWM_Container[i].high_threshold > 0 && PWM_Container[i].high_threshold > PWM_Container[i].load_value){
            continue;
        }
        /*
         * 3
         * Making sure that the channel was not initialized before
         * then save it's threshold to make sure the user does not exceed it after the initialization,
         * we will check whether the user going to exceed it in the run time or not
         */
        if( (PWM_ModulesUsed & (1 << my_channel) ) ){
            // the channel already initialized
        }else{
            REG_WRITE_32_BIT_PTR(SYSCTL_RCGCPWM_R, 0x01);
            REG_READ_PTR(delay, SYSCTL_RCC_REG_PWM);
            if(PWM_ModulesUsed == 0){
                pwm_clock_init();
            }
            PWM_ModulesUsed |= (1 << my_channel);
            Low_thresholds[my_channel] = PWM_Container[i].low_threshold;
            High_thresholds[my_channel] = PWM_Container[i].high_threshold;
        }
        /*
         * 4
         * Disable the PWM Channel till the configuration is done
         */
        REG_CLEAR_BIT_PTR((base + PWM_N_CTL_OFFSET +  (0x40 * my_channel)), 0);

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
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel)) , PWM_Container[i].low_threshold);
            }else if(PWM_Container[i].compare_a_value > PWM_Container[i].high_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel)) , PWM_Container[i].high_threshold);
            }else{
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPA_OFFSET +  (0x40 * my_channel)) , PWM_Container[i].compare_a_value);
            }
            /* Compare B */
            if(PWM_Container[i].compare_b_value < PWM_Container[i].low_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel)) , PWM_Container[i].low_threshold);
            }else if(PWM_Container[i].compare_b_value > PWM_Container[i].high_threshold){
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel)) , PWM_Container[i].high_threshold);
            }else{
                REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_CMPB_OFFSET +  (0x40 * my_channel)) , PWM_Container[i].compare_b_value);
            }
        }else{
            /*
             * if we are not using any threshold or there is a problem in the threshold values
             * ,just write the values
             */
            REG_WRITE_ALL_32_BIT_PTR( (base + PWM_0_CMPA_R +  (0x40 * my_channel) ) , PWM_Container[i].compare_a_value);
            REG_WRITE_ALL_32_BIT_PTR( (base + PWM_0_CMPB_R +  (0x40 * my_channel) ) , PWM_Container[i].compare_b_value);
        }

        /*
         * 6
         * Writing the PWM Load value
         */
        REG_WRITE_ALL_32_BIT_PTR( (base + PWM_N_LOAD_OFFSET + (0x40 * (my_channel)) ) , PWM_Container[i].load_value);


        /*
         * 7
         * Writing the PWM Generator functions
         */
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_A.PWM_GEN_ZERO << 0));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_A.PWM_GEN_LOAD << 2));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPAU << 4));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPAD << 6));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPBU << 8));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENA_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_A.PWM_GEN_CMPBD << 10));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_B.PWM_GEN_ZERO << 0));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_B.PWM_GEN_LOAD << 2));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPAU << 4));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPAD << 6));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPBU << 8));
        REG_WRITE_32_BIT_PTR( (base + PWM_N_GENB_OFFSET + ((0x40 * my_channel)) ) , (PWM_Container[i].Generates_B.PWM_GEN_CMPBD << 10));

        /*
         * 8
         * Writing the Counting mode either it was up or up/down
         */
        REG_WRITE_32_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * my_channel)) ) , (PWM_Container[i].count_mode) << 1);

         /*
         * 9
         * Enable the PWM
         */
        REG_WRITE_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * my_channel)) ) , 0);
    }
}

uint8 pwm_update_comparator_a(PWM_ChannelType channel, uint32 value){
    uint32 base;
    uint8 return_value = RETURN_FINE;
    if(value > High_thresholds[channel]){
        value = High_thresholds[channel];
        return_value = RETURN ERROR;
    }else if(value < Low_thresholds[channel]){
        value = Low_thresholds[channel];
        return_value = RETURN ERROR;
    }else{
    }

    if(channel < 4){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = channel % 4;
    }

    REG_CLEAR_BIT_PTR((base + PWM_N_CTL_OFFSET +  (0x40 * channel)), 0);
    REG_WRITE_ALL_32_BIT_PTR( (base + PWM_0_CMPA_R +  (0x40 * channel) ) , value);
    REG_WRITE_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * channel)) ) , 0);

    return return_value;
}

uint8 pwm_update_comparator_b(PWM_ChannelType channel, uint32 value){
    uint32 base;
    uint8 return_value = RETURN_FINE;
    if(value > High_thresholds[channel]){
        value = High_thresholds[channel];
        return_value = RETURN ERROR;
    }else if(value < Low_thresholds[channel]){
        value = Low_thresholds[channel];
        return_value = RETURN ERROR;
    }else{
    }

    if(channel < 4){
        base = PWM0_BASE_ADDERSS;
    }else{
        base = PWM1_BASE_ADDERSS;
        channel = channel % 4;
    }

    REG_CLEAR_BIT_PTR((base + PWM_N_CTL_OFFSET +  (0x40 * channel)), 0);
    REG_WRITE_ALL_32_BIT_PTR( (base + PWM_0_CMPB_R +  (0x40 * channel) ) , value);
    REG_WRITE_BIT_PTR( (base + PWM_N_CTL_OFFSET +  ((0x40 * channel)) ) , 0);

    return return_value;
}

uint8 pwm_update_comparator_a_percentage(PWM_ChannelType channel, uint32 value){
    int temp = 0;
    if(value > 100){
        return;
    }
    if(High_thresholds[channel] > 0){
        temp = (High_threshold[channel] - Low_threshold[channel]) * value / 100;
        temp = temp + Low_threshold[channel];
    }
    if (block->pwm_block_num <= 3){
        REG_CLEAR_BIT_PTR((PWM0_BASE_ADDERSS + PWM_N_CTL_OFFSET +  (0x40 * channel)), 0);
        REG_WRITE_ALL_32_BIT_PTR( (PWM0_BASE_ADDERSS + PWM_0_CMPA_R +  (0x40 * channel) ) , value);
        REG_WRITE_BIT_PTR( (PWM0_BASE_ADDERSS + PWM_N_CTL_OFFSET +  ((0x40 * channel)) ) , 0);
    }else{
        REG_CLEAR_BIT_PTR((PWM1_BASE_ADDERSS + PWM_N_CTL_OFFSET +  (0x40 * channel)), 0);
        REG_WRITE_ALL_32_BIT_PTR( (PWM1_BASE_ADDERSS + PWM_0_CMPA_R +  (0x40 * channel) ) , value);
        REG_WRITE_BIT_PTR( (PWM1_BASE_ADDERSS + PWM_N_CTL_OFFSET +  ((0x40 * channel)) ) , 0);
    }
}

void pwm_update_comparator_b_percentage(PWM_generator_config_t *block, uint32 value){
    int temp = 0;
    if(value > 100){
        return;
    }
    temp = (block->high_threshold - block->low_threshold) * value / 100;
    temp = temp + block->low_threshold;
    block->compare_b_value = temp;
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_CMPB_R + (0x40 * block->pwm_block_num)) = block->compare_b_value;
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_CMPB_R + (0x40 * (block->pwm_block_num%4))) = block->compare_b_value;
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
    }
}

void pwm_update_generation_a(PWM_generator_config_t *block, PWM_generations_t generate_values){
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_ZERO << 0);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_LOAD << 2);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPAU << 4);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPAD << 6);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPBU << 8);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPBD << 10);
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_ZERO << 0);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_LOAD << 2);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPAU << 4);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPAD << 6);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPBU << 8);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPBD << 10);
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
    }
}


void pwm_update_generation_b(PWM_generator_config_t *block, PWM_generations_t generate_values){
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_ZERO << 0);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_LOAD << 2);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPAU << 4);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPAD << 6);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPBU << 8);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * block->pwm_block_num)) |= (generate_values.PWM_GEN_CMPBD << 10);
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_ZERO << 0);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_LOAD << 2);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPAU << 4);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPAD << 6);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPBU << 8);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (block->pwm_block_num%4))) |= (generate_values.PWM_GEN_CMPBD << 10);
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
    }
}

void pwm_update_load(PWM_generator_config_t *block, uint32 value){
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_LOAD_R + (0x40 * block->pwm_block_num)) = value;
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_LOAD_R + (0x40 * (block->pwm_block_num%4))) = value;
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
    }
}

void pwm_change_mode(PWM_generator_config_t *block, PWM_CountMode_t value){
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (value << 1);
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (value << 1);
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
    }
}

void pwm_disable(PWM_generator_config_t *block, uint8 bins){
    bins = bins & 0x3;
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_ENABLE_R +  (0x40 * block->pwm_block_num)) &= ~(bins << (block->pwm_block_num * 2));
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R ) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_ENABLE_R ) &= ~(bins << ((block->pwm_block_num%4) * 2));
    }
}

void pwm_stop(PWM_generator_config_t *block, uint8 bins){
    bins = bins & 0x3;
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_ENABLE_R +  (0x40 * block->pwm_block_num)) &= ~(bins << (block->pwm_block_num * 2));
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R ) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_ENABLE_R ) &= ~(bins << ((block->pwm_block_num%4) * 2));
        HWREG(PWM1_base_R + PWM_0_CTL_R ) |= (1 << 0);
    }
}

void pwm_enable(PWM_generator_config_t *block, uint8 bins){
    bins = bins & 0x3;
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R) |= (1 << 0);
        HWREG(PWM0_base_R + PWM_ENABLE_R) |= (bins << (block->pwm_block_num * 2));
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R) |= (1 << 0);
        HWREG(PWM1_base_R + PWM_ENABLE_R) |= (bins << ((block->pwm_block_num%4) * 2));
    }
}
