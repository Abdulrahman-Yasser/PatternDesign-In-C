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
    ADC_Channel_AIN6, ADC_Channel_AIN7, ADC_Channel_AIN8, ADC_Channel_AIN9, ADC_Channel_AIN10, ADC_Channel_AIN11
}ADC_Channel_Num_Type;

typedef enum{
    ADC_EventType_Software, ADC_EventType_Comparator_0, ADC_EventType_Comparator_1, ADC_EventType_GPIO=4, ADC_EventType_Timer,
    ADC_EventType_PWM_0, ADC_EventType_PWM_1, ADC_EventType_PWM_2, ADC_EventType_PWM_3, ADC_EventType_continuously = 0xf
}ADC_EventType;

typedef struct{
    ADC_Module_Num_Type ADC_Num;
    ADC_SS_NumType      sampleSequencer_Num;
    ADC_Channel_Num_Type UsedChannel_Num[8];
    ADC_EventType       EventTrigger;
}ADC_ConfigType;

#endif    /* ADC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: ADC_Types.h
 *********************************************************************************************************************/

