/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  ADC_Lcfg.c
  *        \brief  Digital Input Output Driver
  *
  *      \details  This file contains all the needed Linkning time configuration
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/ADC_Cfg.h"

const ADC_SampleSequencer_ConfigType ADC_SS_Container[ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER] = {
                                                                                                 {
                                                                                 .ADC_Num = ADC_Module_0,
                                                                                 .sampleSequencer_Num = ADC_SS_3,
                                                                                 .EventTrigger = ADC_EventType_Software,
                                                                                 .SampleSequencer_Priority = 0x0,
                                                                                 .SampleSequencer_DifferentialInterrupt = Disable_EnumType,
                                                                                 .SampleSequencer_NormalInterrupt = Disable_EnumType
                                                                                                 }
};

const ADC_Channel_ConfigType ADC_CH_Container[ADC_CONFIGURED_CHANNELS_NUMBER] = {
                                                                                 {ADC_Module_0, ADC_SS_3, ADC_Channel_AIN0, ADC_SampleSequence_Input_MUX0,
                                                                                  Disable_EnumType, Disable_EnumType, Enable_EnumType, Enable_EnumType,
                                                                                  Disable_EnumType, ADC_Digital_Comparator_NotUsed, 0, 0,
                                                                                  Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                  Disable_EnumType, Disable_EnumType, Disable_EnumType}
};

enum ADC_Sample_Averaging_Control my_ADC0_Averging_Sample = ADC_Sample_Averaging_x4;
enum ADC_Sample_Averaging_Control my_ADC1_Averging_Sample = ADC_Sample_Averaging_x4;
/**********************************************************************************************************************
 *  END OF FILE: ADC_Lcfg.c
 *********************************************************************************************************************/
