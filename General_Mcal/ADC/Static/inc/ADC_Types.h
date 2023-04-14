/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Types.h
 *       Module:  DIO
 *
 *  Description:  The file got all the special types that we used for the DIO module
 *
 *********************************************************************************************************************/

#ifndef ADC_TYPES_H
#define ADC_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../General_Common/Std_Types.h"
#include "../../General_Common/DataStructure/Normal_Queue/static/inc/Normal_Queue.h"


#define ADC_VDDA_AS_REFRENCE        0x00
#define ADC_VREF_AS_REFRENCE        0x01

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef  Normal_Queue_StaticUint ADC_ValueGroup_Type;

typedef enum{
    ADC_Module_0, ADC_Module_1
}ADC_Module_Num_Type;

typedef enum{
    ADC_SS_0, ADC_SS_1, ADC_SS_2, ADC_SS_3
}ADC_SS_NumType;



//typedef enum{
//    ADC_ModuleControl_Interrupt_generation, ADC_ModuleControl_DMA,
//}ADC_ModuleControl_Type;

typedef enum{
    ADC_Channel_AIN0, ADC_Channel_AIN1, ADC_Channel_AIN2, ADC_Channel_AIN3, ADC_Channel_AIN4, ADC_Channel_AIN5,
    ADC_Channel_AIN6, ADC_Channel_AIN7, ADC_Channel_AIN8, ADC_Channel_AIN9, ADC_Channel_AIN10, ADC_Channel_AIN11,
     ADC_Channel_AIN_NotUsed
}ADC_Channel_Num_Type;

typedef enum{
    ADC_Digital_Comparator_0, ADC_Digital_Comparator_1, ADC_Digital_Comparator_2, ADC_Digital_Comparator_3,
    ADC_Digital_Comparator_4, ADC_Digital_Comparator_5, ADC_Digital_Comparator_6, ADC_Digital_Comparator_7,
    ADC_Digital_Comparator_NotUsed
}ADC_Digital_Comparator_UnitType;

typedef enum{
    ADC_SampleSequence_Input_MUX0, ADC_SampleSequence_Input_MUX1, ADC_SampleSequence_Input_MUX2, ADC_SampleSequence_Input_MUX3,
    ADC_SampleSequence_Input_MUX4, ADC_SampleSequence_Input_MUX5, ADC_SampleSequence_Input_MUX6, ADC_SampleSequence_Input_MUX7
}ADC_SS_Input_Multiplexer_Type;
typedef enum{
    ADC_EventType_Software, ADC_EventType_AnalogComparator_0, ADC_EventType_AnalogComparator_1, ADC_EventType_GPIO=4, ADC_EventType_Timer,
    ADC_EventType_PWM_0_0, ADC_EventType_PWM_1_0, ADC_EventType_PWM_2_0, ADC_EventType_PWM_3_0,
    ADC_EventType_PWM_0_1, ADC_EventType_PWM_1_1, ADC_EventType_PWM_2_1, ADC_EventType_PWM_3_1,
    ADC_EventType_continuously = 0xf
}ADC_EventType;


typedef enum{
    ADC_Comparison_Condition_LOWBand, ADC_Comparison_Condition_MidBand, ADC_Comparison_Condition_HighBand = 3
}ADC_Comparison_ConditionType;

typedef enum{
    ADC_Comparison_Mode_Always, ADC_Comparison_Mode_Once, ADC_Comparison_Mode_HysteresisAlways, ADC_Comparison_Mode_HysteresisOnce
}ADC_Comparison_ModeType;

typedef struct{
    ADC_Module_Num_Type ADC_Num;
    ADC_SS_NumType      sampleSequencer_Num;
    ADC_EventType       EventTrigger;
    uint8               SampleSequencer_Priority;
    Enable_vs_DisableType   SampleSequencer_NormalInterrupt;
    Enable_vs_DisableType   SampleSequencer_DifferentialInterrupt;
}ADC_SampleSequencer_ConfigType;


typedef struct{
    ADC_Module_Num_Type     ADC_Num;
    ADC_SS_NumType          sampleSequencer_Num;
    ADC_Channel_Num_Type    UsedChannel_Num;
    ADC_SS_Input_Multiplexer_Type   Channel_Mux;

    /* General Configuration */

    /* that register will contain what we should put to ADCSSCTLn */
    Enable_vs_DisableType   Channel_Differential_in_CTL_R;
    Enable_vs_DisableType   Channel_Temp_Sensor_in_CTL_R;
    Enable_vs_DisableType   Channel_is_End_of_Sequence_in_CTL_R;
    Enable_vs_DisableType   Channel_Interrupt_Enable_in_CTL_R;

    /* Digital comparator configuration */
    Enable_vs_DisableType   Channel_Operation_DigitalComparator_R;
    ADC_Digital_Comparator_UnitType Channel_DigitalComparator_Select;
    uint16                  Channel_DigitalComparator_HighBand;
    uint16                  Channel_DigitalComparator_LowBand;

    Enable_vs_DisableType   Channel_ComparisonTrigger;
    ADC_Comparison_ModeType Channel_ModeTrigger;
    ADC_Comparison_ConditionType Channel_OperationalConditionTrigger;

    Enable_vs_DisableType   Channel_ComparisonInterrupt;
    ADC_Comparison_ModeType Channel_ModeInterrupt;
    ADC_Comparison_ConditionType Channel_OperationalConditionInterrupt;

}ADC_Channel_ConfigType;


enum ADC_Sample_Averaging_Control{
    ADC_Sample_Averaging_None, ADC_Sample_Averaging_x2, ADC_Sample_Averaging_x4, ADC_Sample_Averaging_x8, ADC_Sample_Averaging_x16,
    ADC_Sample_Averaging_x32, ADC_Sample_Averaging_x64
};

#endif    /* ADC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: ADC_Types.h
 *********************************************************************************************************************/

