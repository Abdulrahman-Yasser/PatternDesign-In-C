/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC_Cfg.h
 *       Module:  ADC
 *
 *  Description:  The file got all the USER configurations and all the constant values
 *
 *********************************************************************************************************************/
#ifndef ADC_CFG_H
#define ADC_CFG_H

#include "../../Static/inc/ADC_Types.h"

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/

#endif  /* ADC_CFG_H */

#define ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER  1
#define ADC_CONFIGURED_CHANNELS_NUMBER          4

#define ADC_BUFFER_SIZE                         5

#define ADC0_VREF_OR_VDDA                ADC_VDDA_AS_REFRENCE
#define ADC1_VREF_OR_VDDA                ADC_VDDA_AS_REFRENCE

#define ADC_TEMPERATURE_ID          0
#define ADC_TEMPERATURE_ADC_NUM     ADC_Module_0
#define ADC_TEMPERATURE_SS_NUM      ADC_SS_2
#define ADC_TEMPERATURE_Pin         (ADC_Channel_Num_Type)ADC_Channel_AIN0

#define ADC_FLAME_ID                1
#define ADC_FLAME_ADC_NUM           ADC_Module_0
#define ADC_FLAME_SS_NUM            ADC_SS_2
#define ADC_FLAME_Pin               (ADC_Channel_Num_Type)ADC_Channel_AIN1

#define ADC_SMOKE_ID                2
#define ADC_SMOKE_ADC_NUM           ADC_Module_0
#define ADC_SMOKE_SS_NUM            ADC_SS_2
#define ADC_SMOKE_Pin               (ADC_Channel_Num_Type)ADC_Channel_AIN2

#define ADC_WATER_ID                3
#define ADC_WATER_ADC_NUM           ADC_Module_0
#define ADC_WATER_SS_NUM            ADC_SS_2
#define ADC_WATER_Pin               (ADC_Channel_Num_Type)ADC_Channel_AIN3

extern const ADC_SampleSequencer_ConfigType ADC_SS_Container[ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER];
extern const ADC_Channel_ConfigType ADC_CH_Container[ADC_CONFIGURED_CHANNELS_NUMBER];
extern enum ADC_Sample_Averaging_Control my_ADC0_Averging_Sample;
extern enum ADC_Sample_Averaging_Control my_ADC1_Averging_Sample;


/**********************************************************************************************************************
 *  END OF FILE: ADC_Cfg.h
 *********************************************************************************************************************/

