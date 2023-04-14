/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC.h
 *       Module:  ADC
 *
 *  Description:  The file got all the global function we will use in the driver
 *
 *********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/ADC_Types.h"
#include "../../General_Common/Std_Types.h"



/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void ADC_Init(void);

Std_ReturnType ADC_SetupResultBuffer(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm, ADC_ValueGroup_Type* DataBufferPtr);

void ADC_StartConversion(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm);

void ADC_StopConversion(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm);

Std_ReturnType ADC_ReadGroup(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm, ADC_ValueGroup_Type* DataBufferPtr);

void ADC_ReadingOperation(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencer);




#endif    /* ADC_H */

/**********************************************************************************************************************
 *  END OF FILE: ADC.h
 *********************************************************************************************************************/

