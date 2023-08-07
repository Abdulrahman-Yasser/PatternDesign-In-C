/**********************************************************************************************************************
 *  FILE DESCRIPTION
 �*��-----------------------------------------------------------------------------------------------------------------*/
/**��������\file��ADC_Lcfg.c
 �*��������\brief��Digital Input Output Driver
 �*
 �*������\details��This file contains all the needed Linkning time configuration
 �*
 �*
 �*********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/ADC_Cfg.h"

const ADC_SampleSequencer_ConfigType ADC_SS_Container[ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER] = {
                                                                                                 {
                                                                                 .ADC_Num = ADC_Module_0,
                                                                                 .sampleSequencer_Num = ADC_SS_2,
                                                                                 .EventTrigger = ADC_EventType_Software,
                                                                                 .SampleSequencer_Priority = 0x0,
                                                                                 .SampleSequencer_DifferentialInterrupt = Disable_EnumType,
                                                                                 .SampleSequencer_NormalInterrupt = Disable_EnumType
                                                                                                 }
};

/*
 * i've changed end of sequence from enable to disable, so the FIFO would be full.
 * It've successfully worked.
 * if all EOF are zeros, then it will only read one value in the FIFO
 *
 * You also should change the ADC_SampleSequence_Input_MUX0 which represent one
 * analog pin of the SampleSequencer
 *
 * make sure to set EOF for the last Mux
 *
 * It is legal to have multiple samples within a sequence generate interrupts.
 *
 * Only one Interrupt and one EOF in the sequencer
 */

const ADC_Channel_ConfigType ADC_CH_Container[ADC_CONFIGURED_CHANNELS_NUMBER] = {
                                                                                 {ADC_TEMPERATURE_ADC_NUM, ADC_TEMPERATURE_SS_NUM, ADC_Channel_AIN0, ADC_SampleSequence_Input_MUX0,
                                                                                  Disable_EnumType, Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                  Disable_EnumType, ADC_Digital_Comparator_NotUsed, 0, 0,
                                                                                  Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                  Disable_EnumType, Disable_EnumType, Disable_EnumType},

                                                                                  {ADC_FLAME_ADC_NUM, ADC_FLAME_SS_NUM, ADC_Channel_AIN1, ADC_SampleSequence_Input_MUX1,
                                                                                   Disable_EnumType, Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                   Disable_EnumType, ADC_Digital_Comparator_NotUsed, 0, 0,
                                                                                   Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                   Disable_EnumType, Disable_EnumType, Disable_EnumType},

                                                                                   {ADC_SMOKE_ADC_NUM, ADC_SMOKE_SS_NUM, ADC_Channel_AIN2, ADC_SampleSequence_Input_MUX2,
                                                                                    Disable_EnumType, Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                    Disable_EnumType, ADC_Digital_Comparator_NotUsed, 0, 0,
                                                                                    Disable_EnumType, Disable_EnumType, Disable_EnumType,
                                                                                    Disable_EnumType, Disable_EnumType, Disable_EnumType},

                                                                                 {ADC_WATER_ADC_NUM, ADC_WATER_SS_NUM, ADC_Channel_AIN3, ADC_SampleSequence_Input_MUX3,
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
