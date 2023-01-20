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



static int PWM_ModulesUsed = 0;

void pwm_clock_init(){
    SYSCTL_RCC_REG |= SYSCTL_RCC1_USEPWM_MASK;
    SYSCTL_RCC_REG &= ~(0x7 << SYSCTL_RCC1_PWMDIV_BIT_POS);
    SYSCTL_RCC_REG |= (SYSCTL_PWMDIV_VALUE << SYSCTL_RCC1_PWMDIV_BIT_POS);
}

void pwm_init(void){
    uint8 i;
    volatile uint32 delay;
    for(i = 0;i < PWM_CONFIGURED_NUMBER; i++){
        /*
         * Making sure that the PWM pin exist
         */
        if(PWM_Container[i].pwm_block_num > 3){
            return;
        }
        /*
         * Make sure that we do not exceed our load value
         */
        if(PWM_Container[i].high_threshold > PWM_Container[i].load_value){
            return;
        }
        /*
         * if the channel is already used do not reconfigure it and return
         */
        if( !(PWM_ModulesUsed & (1 << PWM_Container[i].pwm_block_num) ) ){
            REG_WRITE_32_BIT_PTR(SYSCTL_RCGCPWM_R, 0x01);
            REG_READ_PTR(SYSCTL_RCC_REG_PWM, delay);
            if(g_pwm_0_init > 0){
                pwm_clock_init();
            }
        }else{
            return;
        }
        /*
         * Disable the PWM Channel till the configuration is done
         */
        REG_CLEAR_BIT_PTR((PWM0_base_R + PWM_0_CTL_R +  (0x40 * PWM_Container[i].pwm_block_num)), 0);
    }
        if(PWM_Container[i].compare_a_value < PWM_Container[i].low_threshold){
            HWREG(PWM0_base_R + PWM_0_CMPA_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].low_threshold;
        }else if(PWM_Container[i].compare_a_value > PWM_Container[i].high_threshold){
            HWREG(PWM0_base_R + PWM_0_CMPA_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].high_threshold;
        }else{
            HWREG(PWM0_base_R + PWM_0_CMPA_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].compare_a_value;
        }
        if(PWM_Container[i].compare_b_value < PWM_Container[i].low_threshold){
            HWREG(PWM0_base_R + PWM_0_CMPB_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].low_threshold;
        }else if(PWM_Container[i].compare_b_value > PWM_Container[i].high_threshold){
            HWREG(PWM0_base_R + PWM_0_CMPB_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].high_threshold;
        }else{
            HWREG(PWM0_base_R + PWM_0_CMPB_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].compare_b_value;
        }
        HWREG(PWM0_base_R + PWM_0_LOAD_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].load_value;
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_a.PWM_GEN_ZERO << 0);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_b.PWM_GEN_ZERO << 0);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_a.PWM_GEN_LOAD << 2);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_b.PWM_GEN_LOAD << 2);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPAU << 4);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPAU << 4);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPAD << 6);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPAD << 6);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPBU << 8);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPBU << 8);
        HWREG(PWM0_base_R + PWM_0_GENA_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPBD << 10);
        HWREG(PWM0_base_R + PWM_0_GENB_R + (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPBD << 10);
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * PWM_Container[i].pwm_block_num)) |= (PWM_Container[i].count_mode) << 1;
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * PWM_Container[i].pwm_block_num)) |= (1 << 0);
    }else{
        if(g_pwm_1_init == 0){
            HWREG(SYSCTL_RCGCPWM_R) |= 0x02;
            delay = HWREG(SYSCTL_RCC_REG_PWM);
            if(g_pwm_0_init == 0){
                pwm_clock_init();
            }
            g_pwm_1_init = 1;
        }
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (PWM_Container[i].pwm_block_num%4))) &= ~(1 << 0);
        if(PWM_Container[i].compare_a_value < PWM_Container[i].low_threshold){
            HWREG(PWM1_base_R + PWM_0_CMPA_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].low_threshold;
        }else if(PWM_Container[i].compare_a_value > PWM_Container[i].high_threshold){
            HWREG(PWM1_base_R + PWM_0_CMPA_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].high_threshold;
        }else{
            HWREG(PWM1_base_R + PWM_0_CMPA_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].compare_a_value;
        }
        if(PWM_Container[i].compare_b_value < PWM_Container[i].low_threshold){
            HWREG(PWM1_base_R + PWM_0_CMPB_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].low_threshold;
        }else if(PWM_Container[i].compare_b_value > PWM_Container[i].high_threshold){
            HWREG(PWM1_base_R + PWM_0_CMPB_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].high_threshold;
        }else{
            HWREG(PWM1_base_R + PWM_0_CMPB_R +  (0x40 * PWM_Container[i].pwm_block_num)) = PWM_Container[i].compare_b_value;
        }
        HWREG(PWM1_base_R + PWM_0_LOAD_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) = PWM_Container[i].load_value;
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_a.PWM_GEN_ZERO << 0);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_b.PWM_GEN_ZERO << 0);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_a.PWM_GEN_LOAD << 2);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_b.PWM_GEN_LOAD << 2);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPAU << 4);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPAU << 4);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPAD << 6);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPAD << 6);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPBU << 8);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPBU << 8);
        HWREG(PWM1_base_R + PWM_0_GENA_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_a.PWM_GEN_CMPBD << 10);
        HWREG(PWM1_base_R + PWM_0_GENB_R + (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].generate_values_b.PWM_GEN_CMPBD << 10);
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (PWM_Container[i].count_mode) << 1;
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (1 << 0);
//        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (PWM_Container[i].pwm_block_num%4))) |= (1 << 2);
    }
}

void pwm_update_comparator_a(PWM_generator_config_t *block, uint32 value){
    if(value > block->high_threshold){
        value = block->high_threshold;
    }else if(value < block->low_threshold){
        value = block->low_threshold;
    }else{

    }
    block->compare_a_value = value;
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_CMPA_R + (0x40 * block->pwm_block_num)) = block->compare_a_value;
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_CMPA_R + (0x40 * (block->pwm_block_num%4))) = block->compare_a_value;
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
    }
}

void pwm_update_comparator_b(PWM_generator_config_t *block, uint32 value){
    if(value > block->high_threshold){
        value = block->high_threshold;
    }else if(value < block->low_threshold){
        value = block->low_threshold;
    }else{

    }
    block->compare_b_value = value;
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

void pwm_update_comparator_a_percentage(PWM_generator_config_t *block, uint32 value){
    int temp = 0;
    if(value > 100){
        return;
    }
    temp = (block->high_threshold - block->low_threshold) * value / 100;
    temp = temp + block->low_threshold;
    block->compare_a_value = temp;
    if (block->pwm_block_num <= 3){
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) &= ~(1 << 0);
        HWREG(PWM0_base_R + PWM_0_CMPA_R + (0x40 * block->pwm_block_num)) = block->compare_a_value;
        HWREG(PWM0_base_R + PWM_0_CTL_R +  (0x40 * block->pwm_block_num)) |= (1 << 0);
    }else{
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) &= ~(1 << 0);
        HWREG(PWM1_base_R + PWM_0_CMPA_R + (0x40 * (block->pwm_block_num%4))) = block->compare_a_value;
        HWREG(PWM1_base_R + PWM_0_CTL_R +  (0x40 * (block->pwm_block_num%4))) |= (1 << 0);
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
