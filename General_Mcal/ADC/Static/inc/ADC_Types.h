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


#define ADC_VDDA_AS_REFRENCE        0x00
#define ADC_VREF_AS_REFRENCE        0x01

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



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
}ADC_Digital_Comparator_UnitTypr;


typedef enum{
    ADC_EventType_Software, ADC_EventType_AnalogComparator_0, ADC_EventType_AnalogComparator_1, ADC_EventType_GPIO=4, ADC_EventType_Timer,
    ADC_EventType_PWM_0_0, ADC_EventType_PWM_1_0, ADC_EventType_PWM_2_0, ADC_EventType_PWM_3_0,
    ADC_EventType_PWM_0_1, ADC_EventType_PWM_1_1, ADC_EventType_PWM_2_1, ADC_EventType_PWM_3_1,
    ADC_EventType_continuously = 0xf
}ADC_EventType;



typedef struct{
    ADC_Module_Num_Type ADC_Num;
    ADC_SS_NumType      sampleSequencer_Num;
    ADC_Channel_Num_Type UsedChannel_Num[8];
    ADC_EventType       EventTrigger;
    uint8               SampleSequencer_Priority;

    /* that register will contain what we should put to ADCSSCTLn */
    uint8               SampleSequencer_Differential_in_CTL_R;
    uint8               SampleSequencer_Temp_Sensor_in_CTL_R;
    uint8               SampleSequencer_is_End_of_Sequence_in_CTL_R;
    uint8               SampleSequencer_Interrupt_Enable_in_CTL_R;

    uint8               SampleSequencer_Operation_FIFO_or_DigitalComparator_R;
    ADC_Digital_Comparator_UnitTypr SampleSequencer_DigitalComparator_Select[8];

}ADC_SampleSequencer_ConfigType;


enum ADC_Sample_Averaging_Control{
    ADC_Sample_Averaging_None, ADC_Sample_Averaging_x2, ADC_Sample_Averaging_x4, ADC_Sample_Averaging_x8, ADC_Sample_Averaging_x16,
    ADC_Sample_Averaging_x32, ADC_Sample_Averaging_x64
};

#endif    /* ADC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: ADC_Types.h
 *********************************************************************************************************************/

