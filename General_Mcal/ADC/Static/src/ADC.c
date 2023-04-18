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
#include "../../General_Common/DataStructure/Normal_Queue/static/inc/Normal_Queue.h"

/**********************************************************************************************************************
 *  STATIC GLOBAL VARIABLES
 *********************************************************************************************************************/

static uint8 ADC_ModulesUsed_RcggSaver = 0;

static ADC_ValueGroup_Type *my_ADC_Buffers[8];

/**********************************************************************************************************************
 *  STATIC FUNCTIONS
 *********************************************************************************************************************/
static inline uint32 ADC_Get_Base(ADC_Module_Num_Type ADC_Num){
    if(ADC_Num == ADC_Module_0){
        return (uint32)ADC0_BASE_ADDERSS;
    }else if(ADC_Num == ADC_Module_1){
        return (uint32)ADC1_BASE_ADDERSS;
    }
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void ADC_Init(void){
    uint8 i ;
    volatile uint32 base, register_check;

    /* First, we initialize the configured Sequence Samples */
    for(i = 0; i < ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER; i++){

        /* 1 Check if the RCGC Register is initialized, initialized it if not  */

        if( ! (ADC_ModulesUsed_RcggSaver & (1 << ADC_SS_Container[i].ADC_Num)) ){
            ADC_ModulesUsed_RcggSaver |= 1 << ADC_SS_Container[i].ADC_Num;
            REG_ORING_ONE_BIT_CASTING_POINTED(SYSCTL_RCGCADC_BASE, ADC_SS_Container[i].ADC_Num);
            REG_READ_CASTING_POINTED(register_check, SYSCTL_RCGCADC_BASE);
        }
        /* Get the ADC base address using an inline function */
        base = ADC_Get_Base(ADC_SS_Container[i].ADC_Num);

        /* 2 Disable the sample sequencer before changing the SS configurations  (ADCACTSS)*/
        REG_CLEAR_ONE_BIT_CASTING_POINTED(base + ADC_ACTSS_OFFSET, ADC_SS_Container[i].sampleSequencer_Num);

        /* 3 trigger event for the Sample Sequencer (ADCEMUX) */

        /* 4 if it was PWM as trigger, specify it to which PWM via (ADCTSSEL) */
        if(ADC_SS_Container[i].EventTrigger >= ADC_EventType_PWM_0_0 || ADC_SS_Container[i].EventTrigger <= ADC_EventType_PWM_3_0 ){
            /* Using PWM Module 0 */
            REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, ADC_SS_Container[i].EventTrigger << (ADC_SS_Container[i].sampleSequencer_Num * 4));
            REG_CLEAR_THOSE_BITS_CASTING_POINTED(base + ADC_TSSEL_OFFSET, 0x30 << (ADC_SS_Container[i].EventTrigger - ADC_EventType_PWM_0_0)*8 );

        }else if(ADC_SS_Container[i].EventTrigger >= ADC_EventType_PWM_0_1 || ADC_SS_Container[i].EventTrigger <= ADC_EventType_PWM_3_1){
            /* Using PWM Module 1 */
            REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, (ADC_SS_Container[i].EventTrigger - 4) << (ADC_SS_Container[i].sampleSequencer_Num * 4));
            REG_ORING_CASTING_POINTED(base + ADC_TSSEL_OFFSET, 0x10 << (ADC_SS_Container[i].EventTrigger - ADC_EventType_PWM_0_1)*8  );

        }else{
            /* Not using PWM as event trigger */
            REG_ORING_CASTING_POINTED(base + ADC_EMUX_OFFSET, ADC_SS_Container[i].EventTrigger << (ADC_SS_Container[i].sampleSequencer_Num * 4));
        }

        /* Setting interrupt of the Sample sequencer */
        if( ADC_SS_Container[i].SampleSequencer_DifferentialInterrupt == Enable_EnumType ){
            /* Differential Analog Input */
            REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_IM_OFFSET , ADC_SS_Container[i].sampleSequencer_Num + 16);
        }else if(ADC_SS_Container[i].SampleSequencer_NormalInterrupt == Enable_EnumType ){
            /* Normal Analog Input */
            REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_IM_OFFSET , ADC_SS_Container[i].sampleSequencer_Num);
        }

        /* 5 for each sample in sample sequence, configure the input source (ADCSSMUXn) */
        /* Select ADC Input Channel or Temperature Input */

        REG_CLEAR_CASTING_POINTED(base + ADC_SSMUXn_OFFSET + (ADC_SS_Container[i].sampleSequencer_Num * 0x20) );
        REG_CLEAR_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_SS_Container[i].sampleSequencer_Num * 0x20) );

        /* Sample sequencer priority */
        REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSPRI_OFFSET, ADC_SS_Container[i].SampleSequencer_Priority << (ADC_SS_Container[i].sampleSequencer_Num * 4) );

    }

    /* Second, we initialize the configured ADC Channels */
    for(i = 0; i < ADC_CONFIGURED_CHANNELS_NUMBER; i++){
        /* Error Checking in the configuration */

        if( (ADC_CH_Container[i].Channel_Temp_Sensor_in_CTL_R & ADC_CH_Container[i].Channel_Differential_in_CTL_R) > 0){
            return;
        }

        /* 1 Check if the RCGC Register is initialized, initialized it if not. it's done in the sample sequencer */

        /* Get the ADC base address using an inline function */
        base = ADC_Get_Base(ADC_CH_Container[i].ADC_Num);

        /* 2 Disable the sample sequencer before changing the SS configurations  (ADCACTSS).
         * But it's already disabled in the Sample Sequence initialization */

        /* 3 trigger event for the Sample Sequencer (ADCEMUX).
         * done this in the Sample Sequence initialization */

        /* 5 for each channel, set it's value in the appropriate sample sequencer (ADCSSMUXn) */
        /* Select ADC Input Channel or Temperature Input */
        if(ADC_CH_Container[i].UsedChannel_Num != ADC_Channel_AIN_NotUsed){
            /* in case it's an Analog channel */
            if(ADC_CH_Container[i].Channel_Temp_Sensor_in_CTL_R == Enable_EnumType ){
                return;
            }
            /* Set the analog channel number in the Sample Sequence register */
            REG_ORING_CASTING_POINTED(base + ADC_SSMUXn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) , ADC_CH_Container[i].UsedChannel_Num << (ADC_CH_Container[i].Channel_Mux * 4) );
        }else{
            /* in case it's a Temperature input, set TS bit */
            if( ADC_CH_Container[i].Channel_Temp_Sensor_in_CTL_R == Enable_EnumType ){
                REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) , (ADC_CH_Container[i].UsedChannel_Num * 4) + 3);
            }
        }
        /* in case it has Differential Input */
        if( ADC_CH_Container[i].Channel_Differential_in_CTL_R == Enable_EnumType ){
            REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) ,  (ADC_CH_Container[i].UsedChannel_Num*4));
        }
        /* in case it has End of Sequence */
        if( ADC_CH_Container[i].Channel_is_End_of_Sequence_in_CTL_R == Enable_EnumType ){
            REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) , (ADC_CH_Container[i].UsedChannel_Num*4) + 1 );
        }
        /* in case it has an Interrupt */
        if( ADC_CH_Container[i].Channel_Interrupt_Enable_in_CTL_R  == Enable_EnumType ){
            REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSCTLn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) , (ADC_CH_Container[i].UsedChannel_Num*4) + 2 );
        }

        /* in case you going to use a  Digital Comparator (ADCSSOPn)*/
        if(ADC_CH_Container[i].Channel_Operation_DigitalComparator_R == Enable_EnumType){
            REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_SSOPn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) , (ADC_CH_Container[i].UsedChannel_Num*4));
            REG_ORING_CASTING_POINTED(base + ADC_SSDCn_OFFSET + (ADC_CH_Container[i].sampleSequencer_Num * 0x20) , ADC_CH_Container[i].Channel_DigitalComparator_Select << (ADC_CH_Container[i].Channel_Mux * 4) );
            REG_WRITE_CASTING_POINTED(base + ADC_DCCMP0_OFFSET + (ADC_CH_Container[i].Channel_Mux * 4) , (ADC_CH_Container[i].Channel_ComparisonTrigger << 12) | (ADC_CH_Container[i].Channel_OperationalConditionTrigger << 10) | (ADC_CH_Container[i].Channel_ModeTrigger << 8) |
                                                                                                         (ADC_CH_Container[i].Channel_ComparisonInterrupt << 4) | (ADC_CH_Container[i].Channel_OperationalConditionInterrupt << 2) | (ADC_CH_Container[i].Channel_ModeInterrupt));
            REG_WRITE_CASTING_POINTED(base + ADC_DCCMP0_OFFSET + (ADC_CH_Container[i].Channel_Mux * 4) , (ADC_CH_Container[i].Channel_DigitalComparator_HighBand << 16) | ADC_CH_Container[i].Channel_DigitalComparator_LowBand);
        }
    }

    /* Enabling all the Sample Sequencers */
    for(i = 0; i < ADC_CONFIGURED_SAMPLE_SEQUENCES_NUMBER; i++){

        /* Get the ADC base address using an inline function */
        base = ADC_Get_Base(ADC_SS_Container[i].ADC_Num);

        REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_ACTSS_OFFSET, ADC_SS_Container[i].sampleSequencer_Num);
    }

    /* Configurations for ADC0 only like VREF option and average sample */
    if(ADC_ModulesUsed_RcggSaver & 1 << 0){
        base = ADC0_BASE_ADDERSS;
    }
    /* using VREF pin or VDDA as the voltage reference */
    REG_WRITE_CASTING_POINTED(base +  ADC_CTL_OFFSET, ADC0_VREF_OR_VDDA);

    /* If interrupt is used, change (ADCIM) */
    REG_WRITE_CASTING_POINTED(base +  ADC_SAC_OFFSET, my_ADC0_Averging_Sample);

    /* Configurations for ADC1 only like VREF option and average sample */
    if(ADC_ModulesUsed_RcggSaver & 1 << 1){
        base = ADC1_BASE_ADDERSS;
    }
    /* using VREF pin or VDDA as the voltage reference */
    REG_WRITE_CASTING_POINTED(base +  ADC_CTL_OFFSET, ADC1_VREF_OR_VDDA);

    /* If interrupt is used, change (ADCIM) */
    REG_WRITE_CASTING_POINTED(base +  ADC_SAC_OFFSET, my_ADC1_Averging_Sample);




}

Std_ReturnType ADC_SetupResultBuffer(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm, ADC_ValueGroup_Type* DataBufferPtr){
    Std_ReturnType my_return = E_OK;

    if(DataBufferPtr == Null_Ptr){
        my_return = E_NOK;
        return my_return;
    }
    else if(my_ADC_Buffers[mySampleSequencerNm + (4*ADC_Num)] != Null_Ptr){
        my_return = E_NOK;
    }
    my_ADC_Buffers[mySampleSequencerNm + (4*ADC_Num)] = DataBufferPtr;

    return my_return;
}

void ADC_StartConversion(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm){
    uint32 base;

    base = ADC_Get_Base(ADC_Num);

    REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_PSSI_OFFSET, mySampleSequencerNm);
}

void ADC_StopConversion(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm){

}

Std_ReturnType ADC_ReadGroup(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm, ADC_ValueGroup_Type* DataBufferPtr){
    if(my_ADC_Buffers[mySampleSequencerNm + (ADC_Num*4)] != Null_Ptr){
        DataBufferPtr = my_ADC_Buffers[mySampleSequencerNm + (ADC_Num*4)];
        while(! NormalQueue_Static_isEmpty(my_ADC_Buffers[mySampleSequencerNm + (ADC_Num*4)]) ){
            NormalQueue_Static_remove( my_ADC_Buffers[mySampleSequencerNm + (ADC_Num*4)] );
        }
    }else{
        return E_NOK;
    }
    return E_OK;
}

void ADC_ReadingOperation(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencer){
    uint32 base, RegisterCheck;
    uint16 data;


    base = ADC_Get_Base(ADC_Num);

    if(my_ADC_Buffers[mySampleSequencer + (ADC_Num*4)] == Null_Ptr){
        return;
    }

    ADC_StartConversion(ADC_Num, mySampleSequencer);
    /* the sample finished it's conversion ? */
    do{
        REG_READ_CASTING_POINTED(RegisterCheck, base + ADC_RIS_OFFSET );
    }while(RegisterCheck & (1 << mySampleSequencer));

    /* read the FIFO till the EMPTY FIFO flag set high */
    do{
        REG_READ_CASTING_POINTED(data, base + ADC_SSFIFOn_OFFSET + (mySampleSequencer*0x20) );
        if(!NormalQueue_Static_isFull( my_ADC_Buffers[mySampleSequencer + (ADC_Num*4)] ) ){
            NormalQueue_Static_insert( my_ADC_Buffers[mySampleSequencer + (ADC_Num*4)] , data);
        }
        REG_READ_CASTING_POINTED(RegisterCheck, base + ADC_SSFSTATn_OFFSET + (mySampleSequencer*0x20) );
    }while(! (RegisterCheck & (1 << 8) ) );

    REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_ISC_OFFSET , mySampleSequencer);
}

uint32 ADC_ReadOneValue(ADC_Module_Num_Type ADC_Num, ADC_SS_NumType mySampleSequencerNm){
    uint32 base, RegisterCheck;
    uint16 data;

    base = ADC_Get_Base(ADC_Num);


    /* in case there is no data in the built-in queue, then apply a read operation */
    if(NormalQueue_Static_isEmpty( my_ADC_Buffers[mySampleSequencerNm + (ADC_Num*4)] ) ){

        ADC_StartConversion(ADC_Num, mySampleSequencerNm);
        /* the sample finished it's conversion ? */
        do{
            REG_READ_CASTING_POINTED(RegisterCheck, base + ADC_RIS_OFFSET );
        }while(RegisterCheck & (1 << mySampleSequencerNm));

        REG_READ_CASTING_POINTED(data, base + ADC_SSFIFOn_OFFSET + (mySampleSequencerNm*0x20) );

        REG_ORING_ONE_BIT_CASTING_POINTED(base + ADC_ISC_OFFSET , mySampleSequencerNm);
    }else{
        /* in case there is data in the built-in queue, just return it */
        data = NormalQueue_Static_remove(my_ADC_Buffers[mySampleSequencerNm + (ADC_Num*4)]);
    }

    return data;

}


/**********************************************************************************************************************
 *  END OF FILE: ADC.c
 *********************************************************************************************************************/



