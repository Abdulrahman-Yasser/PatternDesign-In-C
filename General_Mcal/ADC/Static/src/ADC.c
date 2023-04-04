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

static uint8 ADC_ModulesUsed = 0;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void ADC_Init(void){
    uint8 i ;
    uint32 base, register_check;

    for(i = 0; i < ADC_CONFIGURED_NUMBER; i++){

        /* Check if the RCGC Register is initialized, initialized it if not  */

        if( ! (ADC_ModulesUsed & (1 << ADC_Container[i].ADC_Num)) ){
            ADC_ModulesUsed |= 1 << ADC_Container[i].ADC_Num;
            REG_ORING_ONE_BIT_CASTING_POINTED(SYSCTL_RCGCADC_BASE, ADC_Container[i].ADC_Num);
            REG_READ_CASTING_POINTED(register_check, SYSCTL_RCGCADC_BASE);
        }

        if(ADC_Container[i].ADC_Num == ADC_Module_0){
            base = ADC0_BASE_ADDERSS;
        }else if(ADC_Container[i].ADC_Num == ADC_Module_1){
            base = ADC1_BASE_ADDERSS;
        }

        /* Disable the sample sequencer before changing the SS configurations  */

        REG_CLEAR_ONE_BIT_CASTING_POINTED(base + ADC_ACTSS_OFFSET, ADC_Container[i].sampleSequencer_Num);

        /* Choose the ADC trigger   */

        REG_CLEAR_THOSE_BITS_CASTING_POINTED(base + ADC_EMUX_OFFSET, 0xF << (ADC_Container[i].sampleSequencer_Num * 4));
        REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, ADC_Container[i].EventTrigger << (ADC_Container[i].sampleSequencer_Num * 4));

        /* Select ADC Input Channel */

        REG_CLEAR_THOSE_BITS_CASTING_POINTED(base + ADC_SSMUXn_OFFSET + (ADC_Container[i].sampleSequencer_Num * 0x20) , 0xF << (ADC_Container[i].sampleSequencer_Num * 4));
        REG_ORING_CASTING_POINTED(base + ADC_SSMUXn_OFFSET , ADC_Container[i].EventTrigger << (ADC_Container[i].sampleSequencer_Num * 4));

    }
}

void ADC_SoftwareTrigger_SC(ADC_SS_NumType mySampleSequencerNm);

uint16 ADC_ReadResult(ADC_SS_NumType mySampleSequencer);


/**********************************************************************************************************************
 *  END OF FILE: ADC.c
 *********************************************************************************************************************/



