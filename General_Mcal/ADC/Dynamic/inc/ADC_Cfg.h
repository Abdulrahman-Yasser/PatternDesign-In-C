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
#define ADC_CONFIGURED_CHANNELS_NUMBER          1

#define ADC_BUFFER_SIZE                         16

#define ADC0_VREF_OR_VDDA                ADC_VDDA_AS_REFRENCE
#define ADC1_VREF_OR_VDDA                ADC_VDDA_AS_REFRENCE

extern const ADC_SampleSequencer_ConfigType ADC_SS_Container[ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER];
extern const ADC_Channel_ConfigType ADC_CH_Container[ADC_CONFIGURED_CHANNELS_NUMBER];
extern enum ADC_Sample_Averaging_Control my_ADC0_Averging_Sample;
extern enum ADC_Sample_Averaging_Control my_ADC1_Averging_Sample;


/**********************************************************************************************************************
 *  END OF FILE: ADC_Cfg.h
 *********************************************************************************************************************/

