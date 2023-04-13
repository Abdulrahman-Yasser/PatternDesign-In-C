/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  ADC.c
  *        \brief  Analog Digital Converter
  *
  *      \details  This file contains the static implementation of the driver
  *                  it contains all the function implementation logic
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/ADC.h"
#include "../../Dynamic/inc/ADC_Cfg.h"

#include "../../General_Common/Std_Types.h"
#include "../../General_Common/Mcu_Hw.h"

/**********************************************************************************************************************
 *  STATIC GLOBAL VARIABLES
 *********************************************************************************************************************/

static uint8 ADC_ModulesUsed_RcggSaver = 0;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void ADC_Init(void){
    uint8 i, j ;
    uint32 base, register_check;

    /* using VREF pin or VDDA as the voltage reference */
    REG_WRITE_CASTING_POINTED(base +  ADC_CTL_OFFSET, ADC_VREF_OR_VDDA);

    /* If interrupt is used, change (ADCIM) */
    REG_WRITE_CASTING_POINTED(base +  ADC_SAC_OFFSET, my_ADC_Averging_Sample);

    for(i = 0; i < ADC_CONFIGURED_NUMBER; i++){
        /* Error Checking in the configuration */

        if( (ADC_Container[i].SampleSequencer_Temp_Sensor_in_CTL_R & ADC_Container[i].SampleSequencer_Temp_Sensor_in_CTL_R) > 0){
            return;
        }

        /* 1 Check if the RCGC Register is initialized, initialized it if not  */

        if( ! (ADC_ModulesUsed_RcggSaver & (1 << ADC_Container[i].ADC_Num)) ){
            ADC_ModulesUsed_RcggSaver |= 1 << ADC_Container[i].ADC_Num;
            REG_ORING_ONE_BIT_CASTING_POINTED(SYSCTL_RCGCADC_BASE, ADC_Container[i].ADC_Num);
            REG_READ_CASTING_POINTED(register_check, SYSCTL_RCGCADC_BASE);
        }

        if(ADC_Container[i].ADC_Num == ADC_Module_0){
            base = ADC0_BASE_ADDERSS;
        }else if(ADC_Container[i].ADC_Num == ADC_Module_1){
            base = ADC1_BASE_ADDERSS;
        }

        /* 2 Disable the sample sequencer before changing the SS configurations  (ADCACTSS)*/
        REG_CLEAR_ONE_BIT_CASTING_POINTED(base + ADC_ACTSS_OFFSET, ADC_Container[i].sampleSequencer_Num);

        /* 3 trigger event for the Sample Sequencer (ADCEMUX) */

        /* 4 if it was PWM as trigger, specify it to which PWM via (ADCTSSEL) */
        if(ADC_Container[i].EventTrigger >= ADC_EventType_PWM_0_0 || ADC_Container[i].EventTrigger <= ADC_EventType_PWM_3_0 ){
            /* Using PWM Module 0 */
            REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, ADC_Container[i].EventTrigger << (ADC_Container[i].sampleSequencer_Num * 4));
            REG_CLEAR_THOSE_BITS_CASTING_POINTED(base + ADC_TSSEL_OFFSET, 0x30 << (ADC_Container[i].EventTrigger - ADC_EventType_PWM_0_0) );
        }else if(ADC_Container[i].EventTrigger >= ADC_EventType_PWM_0_1 || ADC_Container[i].EventTrigger <= ADC_EventType_PWM_3_1){
            /* Using PWM Module 1 */
            REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, (ADC_Container[i].EventTrigger - 4) << (ADC_Container[i].sampleSequencer_Num * 4));
            REG_ORING_CASTING_POINTED(base + ADC_TSSEL_OFFSET, 0x10 << (ADC_Container[i].EventTrigger - ADC_EventType_PWM_0_1)  );
        }else{
            /* Not using PWM as event trigger */
            REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, ADC_Container[i].EventTrigger << (ADC_Container[i].sampleSequencer_Num * 4));
        }

        /* 5 for each sample in sample sequence, configure the input source (ADCSSMUXn) */
        /* Select ADC Input Channel or Temperature Input */

        REG_CLEAR_CASTING_POINTED(base + ADC_SSMUXn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) );
        REG_CLEAR_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) );

        for(j = 0; j < 8; j++){

            if(ADC_Container[i].UsedChannel_Num[j] != ADC_Channel_AIN_NotUsed){
                /* in case it's an Analog channel */
                if(ADC_Container[i].SampleSequencer_Temp_Sensor_in_CTL_R & (1 << j)){
                    return;
                }
                /* Set the analog channel number in the Sample Sequence register */
                REG_ORING_CASTING_POINTED(base + ADC_SSMUXn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) , ADC_Container[i].UsedChannel_Num[j] << (ADC_Container[i].sampleSequencer_Num * 4) );
            }else{
                /* in case it's a Temperature input, set TS bit */
                if( ADC_Container[i].SampleSequencer_Temp_Sensor_in_CTL_R & (1 << j) ){
                    REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) ,  j + 3 );
                }
            }
            /* in case it has End of Sequence */
            if( ADC_Container[i].SampleSequencer_is_End_of_Sequence_in_CTL_R & (1 << j) ){
                REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) , j + 1 );
            }
            /* in case it has Differential Input */
            if( ADC_Container[i].SampleSequencer_Differential_in_CTL_R & (1 << j) ){
                REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) , j );
            }
            /* in case it has an Interrupt */
            if( ADC_Container[i].SampleSequencer_Interrupt_Enable_in_CTL_R & (1 << j) ){
                REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) , j + 2 );
                /* Differential Normal Analog Input */
                if( ADC_Container[i].SampleSequencer_Differential_in_CTL_R & (1 << j) ){
                    REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_IM_OFFSET , ADC_Container[i].sampleSequencer_Num + 16);
                }else{
                    /* Normal Analog Inout */
                    REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_IM_OFFSET , ADC_Container[i].sampleSequencer_Num);
                }
            }
        }

        /* Sample sequencer priority */
        REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSPRI_OFFSET, ADC_Container[i].SampleSequencer_Priority << (ADC_Container[i].sampleSequencer_Num * 4) );

        /* Enable the sample sequencer before changing the SS configurations  (ADCACTSS)*/
        REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_ACTSS_OFFSET, ADC_Container[i].sampleSequencer_Num);

        /* Choose the ADC trigger   */

        REG_CLEAR_THOSE_BITS_CASTING_POINTED(base + ADC_EMUX_OFFSET, 0xF << (ADC_Container[i].sampleSequencer_Num * 4));
        REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, ADC_Container[i].EventTrigger << (ADC_Container[i].sampleSequencer_Num * 4));



    }
}

void ADC_SoftwareTrigger_SC(ADC_SS_NumType mySampleSequencerNm);

uint16 ADC_ReadResult(ADC_SS_NumType mySampleSequencer);


/**********************************************************************************************************************
 *  END OF FILE: ADC.c
 *********************************************************************************************************************/



