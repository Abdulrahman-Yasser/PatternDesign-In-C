/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file    GPT.c
  *        \brief   Global Timer Module Driver (GPT)
  *
  *      \details   The File Contains all the GPT driver's functions implementation
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../../../Common/Std_Types.h"
#include "../../../../Common/CPU_resources.h"
#include "../../../../Common/Mcu_Hw.h"


#include "../inc/GPT.h"
#include "../../Dynamic/inc/GPT_Cfg.h"


 /**********************************************************************************************************************
  *  LOCAL DATA 
  *********************************************************************************************************************/
static uint16 RCG_clock = 0;

///* For calculating the software Prescaler */
static uint32 G_SW_PreScaler_RealCounter[ TIMERS_NUMBERS + GPT_PREDEF_TIMER_NUMBERS ] = {0};

static uint32 G_SW_PreScaling[ TIMERS_NUMBERS + GPT_PREDEF_TIMER_NUMBERS] = {1};

static uint32 G_BitShifting[TIMERS_NUMBERS] = {0};

static uint32 G_BitShiftingGuarding[TIMERS_NUMBERS] = {0};

static uint32 G_BitUsedGuarding[TIMERS_NUMBERS] = {0};
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


void Gpt_Notification_channel_Normal_0(void);
void Gpt_Notification_channel_Normal_1(void);
void Gpt_Notification_channel_Normal_2(void);
void Gpt_Notification_channel_Normal_3(void);
void Gpt_Notification_channel_Normal_4(void);
void Gpt_Notification_channel_Normal_5(void);

void Gpt_Notification_channel_Wide_0(void);
void Gpt_Notification_channel_Wide_1(void);
void Gpt_Notification_channel_Wide_2(void);
void Gpt_Notification_channel_Wide_3(void);
void Gpt_Notification_channel_Wide_4(void);
void Gpt_Notification_channel_Wide_5(void);

volatile uint32* GetTimerAddress(Gpt_ChannelType TimerAddress);
uint8 calculate_MaxBits(uint32 val);
void WriteUsingBB(uint32* TimerPtr, uint32 Value);
uint32 calculate_BitGuarding(uint32 val);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

uint8 calculate_MaxBits(uint32 val){
    uint8 i = 0;
    while(val > 0){
        i++;
        val = val >> 1;
    }
    return i;
}

uint32 calculate_BitGuarding(uint32 val){
    uint32 i = 0;
    while(val > 0){
        if( (val & 0x1) > 0){
            i = i << 1;
            i |= 1;
        }else{
            i = i << 1;
        }
        val = val >> 1;
    }
    return i;
}


volatile uint32* GetTimerAddress(Gpt_ChannelType TimerAddress){
    volatile uint32* i;
    if(TimerAddress < WIDE_TIMER_RANGE_PRIVATE){
        switch(TimerAddress){
        case 0:
            i = (volatile uint32 *)GPTM_0_16_32_ADDRESS;
            break;
        case 1:
            i = (volatile uint32 *)GPTM_1_16_32_ADDRESS;
            break;
        case 2:
            i = (volatile uint32 *)GPTM_2_16_32_ADDRESS;
            break;
        case 3:
            i = (volatile uint32 *)GPTM_3_16_32_ADDRESS;
            break;
        case 4:
            i = (volatile uint32 *)GPTM_4_16_32_ADDRESS;
            break;
        case 5:
            i = (volatile uint32 *)GPTM_5_16_32_ADDRESS;
            break;
        default :
            break;
        }
    }else{
        switch(TimerAddress){
        case 6:
            i = (volatile uint32 *)GPTM_0_32_64_ADDRESS;
            break;
        case 7:
            i = (volatile uint32 *)GPTM_1_32_64_ADDRESS;
            break;
        case 8:
            i = (volatile uint32 *)GPTM_2_32_64_ADDRESS;
            break;
        case 9:
            i = (volatile uint32 *)GPTM_3_32_64_ADDRESS;
            break;
        case 10:
            i = (volatile uint32 *)GPTM_4_32_64_ADDRESS;
            break;
        case 11:
            i = (volatile uint32 *)GPTM_5_32_64_ADDRESS;
            break;
        default :
            break;
        }
    }
    return i;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
* \Description     : The function initialize all the configured timers
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr   The parameter is a container of all the configured timer by the user                 
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void Gpt_Init(const Gpt_ConfigType* ConfigPtr){
    volatile uint32* TimerPtr;
    uint8 i;
    uint32 frequency = 0;
    *(volatile uint32*)(SYSCTL_RCGCTIMER_REG) |= (1 << 0);

    for(i = 0; i < TIMERS_NUMBERS; i++){
        if(ConfigPtr[i].ChannelMode == Gpt_Mode_NotUsed){
            continue;
        }
        TimerPtr = GetTimerAddress(ConfigPtr[i].GptChannelId);

        if( (RCG_clock & (1 << ConfigPtr[i].GptChannelId) )== 0){
            REG_WRITE_32_BIT(SYSCTL_RCGCTIMER_REG, 1 << (ConfigPtr[i].GptChannelId % 6));
            RCG_clock |= 1 <<  1 << (ConfigPtr[i].GptChannelId % 6);
        }

        G_BitUsedGuarding[ConfigPtr[i].GptChannelId] = calculate_BitGuarding( Gpt_ConfigPtr[i].GptChannelTickValueMax );

        if(ConfigPtr[i].PreScalingType != Gpt_Prescale_NotUsed){
            /* in case we are using any type of preScaling we will save those values. */
            frequency = (uint16)((CPU_CLOCK * ConfigPtr[i].GptChannelTickFrequency ));
            G_BitShiftingGuarding[ConfigPtr[i].GptChannelId] = calculate_BitGuarding(frequency);
            G_BitShifting[ConfigPtr[i].GptChannelId] = calculate_MaxBits(frequency);

            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Software){
                G_SW_PreScaling[ConfigPtr[i].GptChannelId] = (uint16)frequency ;
            }else{
                G_SW_PreScaling[ConfigPtr[i].GptChannelId] = 1;
            }
        }else{
            /* in case we are NOT using any type of preScaling. */
            G_SW_PreScaling[ConfigPtr[i].GptChannelId] = 1;
            G_BitShiftingGuarding[ConfigPtr[i].GptChannelId] = 0;
            G_BitShifting[ConfigPtr[i].GptChannelId] = 0;
        }


        switch(ConfigPtr[i].ChannelMode){
        case Gpt_Mode_OneShot_A:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),2);
            /* Work as OneShot Mode */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),0);
            /* Counting Up */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),4);
            /* Write the PreScale value */
            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Hardware){
                WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAPR_REG_OFFSET),(uint8)frequency);
            }
            /* Write the Loading value */
            WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAILR_REG_OFFSET), ConfigPtr[i].GptChannelTickValueMax - 1);
            break;

        case Gpt_Mode_Periodic_A:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),2);
            /* Work as a Periodic Mode */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),1);
            /* Counting Up */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),4);
            /* Write the PreScale value */
            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Hardware){
                WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAPR_REG_OFFSET),(uint8)frequency);
            }
            /* Enable Match Interrupt */
            WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAILR_REG_OFFSET), ConfigPtr[i].GptChannelTickValueMax - 1);
            break;

        case Gpt_Mode_OneShot_B:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),2);
            /* Work as OneShot Mode */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TBMR_REG_OFFSET),0);
            /* Counting Up */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TBMR_REG_OFFSET),4);
            /* Write the PreScale value */
            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Hardware){
                WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TBPR_REG_OFFSET),(uint8)frequency);
            }
            /* Write the Loading value */
            WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TBILR_REG_OFFSET),  ConfigPtr[i].GptChannelTickValueMax - 1);
            break;

        case Gpt_Mode_Periodic_B:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),2);
            /* Work as OneShot Mode */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TBMR_REG_OFFSET),1);
            /* Counting Up */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TBMR_REG_OFFSET),4);
            /* Enable Match Interrupt */
            REG_WRITE_BIT_PTR((uint32)TimerPtr + (uint32)GPTM_TBMR_REG_OFFSET, 5);
            /* Write the PreScale value */
            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Hardware){
                WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TBPR_REG_OFFSET),(uint8)frequency);
            }
            /* Write the Loading value */
            WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TBILR_REG_OFFSET), ConfigPtr[i].GptChannelTickValueMax - 1);
            break;

        case Gpt_Mode_OneShot_Concatenate:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),2);
            /* Work as OneShot Mode */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),0);
            /* Counting Up */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),4);
            /* Write the PreScale value */
            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Hardware){
                WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAPR_REG_OFFSET),(uint8)frequency);
            }
            /* Write the Loading value */
            WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAILR_REG_OFFSET), ConfigPtr[i].GptChannelTickValueMax - 1);
            break;

        case Gpt_Mode_Periodic_Concatenate:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),2);
            /* Work as OneShot Mode */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),1);
            /* Counting Up */
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAMR_REG_OFFSET),4);
            if(ConfigPtr[i].PreScalingType == Gpt_Prescale_Hardware){
                WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAPR_REG_OFFSET),(uint8)frequency);
            }
            /* Write the Loading value */
            WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAILR_REG_OFFSET), ConfigPtr[i].GptChannelTickValueMax - 1);
            break;

        case Gpt_Mode_RTC:
            REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CFG_REG_OFFSET),0);
            break;

        case Gpt_Mode_EdgeCount:
            break;

        case Gpt_Mode_EdgeTime:
            break;

        case Gpt_Mode_PWM:
            break;

        default :
            break;
        }
    }

    TimerPtr == (uint32*)0;
    frequency = 0;

#if GPT_PREDEF_TIMER_100US_32BIT == Enable
    if(TimerPtr == (uint32*)0){
        TimerPtr = GetTimerAddress(Gpt_Channel_Wide_5);
    }
    if(frequency == 0){
        frequency = CPU_CLOCK*1;
    }

    REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr + GPTM_CFG_REG_OFFSET), 1);
    /* Work as a OneShot Mode */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 0);
    /* Counting Up */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 4);
    /* Write the HardWare PreScale value */
    /* 10 Us per Time */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAPR_REG_OFFSET), frequency);
    /* Write the loading value */
    G_SW_PreScaling[0] = 100;
    /* Start the Timer */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_CTL_REG_OFFSET), 0);
#endif
#if GPT_PREDEF_TIMER_60US_16BIT == Enable
    if(TimerPtr == (uint32*)0){
        TimerPtr = GetTimerAddress(Gpt_Channel_Wide_5);
    }
    if(frequency == 0){
        frequency = CPU_CLOCK*1;
    }

    REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr + GPTM_CFG_REG_OFFSET), 1);
    /* Work as a OneShot Mode */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 0);
    /* Counting Up */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 4);
    /* Write the PreScale value */
    /* 10 Us per Time */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAPR_REG_OFFSET), frequency);
    /* Write the loading value */
    G_SW_PreScaling[1] = 60;
    /* Start the Timer */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_CTL_REG_OFFSET), 0);
#endif
#if GPT_PREDEF_TIMER_40US_24BIT == Enable
    if(TimerPtr == (uint32*)0){
        TimerPtr = GetTimerAddress(Gpt_Channel_Wide_5);
    }
    if(frequency == 0){
        frequency = CPU_CLOCK*1;
    }

    REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr + GPTM_CFG_REG_OFFSET), 1);
    /* Work as a OneShot Mode */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 0);
    /* Counting Up */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 4);
    /* Write the PreScale value */
    /* 10 Us per Time */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAPR_REG_OFFSET), frequency);
    /* Write the loading value */
    G_SW_PreScaling[2] = 40;
    /* Start the Timer */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_CTL_REG_OFFSET), 0);
#endif
#if GPT_PREDEF_TIMER_20US_32BIT == Enable
    if(TimerPtr == (uint32*)0){
        TimerPtr = GetTimerAddress(Gpt_Channel_Wide_5);
    }
    if(frequency == 0){
        frequency = CPU_CLOCK*1;
    }

    REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr + GPTM_CFG_REG_OFFSET), 1);
    /* Work as a OneShot Mode */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 0);
    /* Counting Up */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_TAMR_REG_OFFSET), 4);
    /* Write the PreScale value */
    /* 10 Us per Time */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_TAPR_REG_OFFSET), frequency);
    /* Write the loading value */
    G_SW_PreScaling[3] = 20;
    /* Start the Timer */
    REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr + GPTM_CTL_REG_OFFSET), 0);
#endif
}



/******************************************************************************
* \Syntax          : void Gpt_DisableNotification(Gpt_ChannelType Channel)
* \Description     : The function Disable all ISRs in a timer Channel
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Gpt_ChannelType   The parameter contains the Timer's number
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void Gpt_DisableNotification(Gpt_ChannelType Channel){
    /* To prevent the function to be interrupted by the same Channel */
    uint8 i = 0;
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << Channel) > 0){
        return;
    }else{
        Re_entrantSaver |= 1 << Channel;
    }

    volatile uint32* TimerPtr = GetTimerAddress(Channel);
    if( (Gpt_ConfigPtr[Channel].Interrupt_Type & (1 << Gpt_Interrupt_NotUsed ))> 0){

    }else{
        if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_Concatenate ){
            for(i = 0; i < WIDE_TIMER_RANGE_PRIVATE; i++){
                REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr +GPTM_IMR_REG_OFFSET), Gpt_ConfigPtr[Channel].Interrupt_Type & 0x1F);
            }
        }else if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_B){
            for(i = 8; i < 12; i++){
                REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr +GPTM_IMR_REG_OFFSET), Gpt_ConfigPtr[Channel].Interrupt_Type & 0xF00);
            }
        }
    }
    Re_entrantSaver &= ~(1 << Channel);
}

/******************************************************************************
* \Syntax          : void Gpt_EnableNotification(Gpt_ChannelType Channel)
* \Description     : The function Enables all the ISRs in a timer Channel
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Gpt_ChannelType   The parameter contains the Timer's number
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void Gpt_EnableNotification(Gpt_ChannelType Channel){
    /* To prevent the function to be interrupted by the same Channel */
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << Channel) > 0){
        return;
    }else{
        Re_entrantSaver |= 1 << Channel;
    }

    volatile uint32* TimerPtr = GetTimerAddress(Channel);
    WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_ICR_REG_OFFSET), 0xFFF);
    if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_Concatenate){
        WriteUsingBB((uint32*)((uint8*)TimerPtr +GPTM_IMR_REG_OFFSET), Gpt_ConfigPtr[Channel].Interrupt_Type & 0x1F);
    }else if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_B){
        WriteUsingBB((uint32*)((uint8*)TimerPtr +GPTM_IMR_REG_OFFSET), Gpt_ConfigPtr[Channel].Interrupt_Type & 0xF00);
    }
    Re_entrantSaver &= ~(1 << Channel);
}

/******************************************************************************
* \Syntax          : void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
* \Description     : The function Start the timer and load it with a specific value
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Gpt_ChannelType    The parameter contains the Timer's number
* \Parameters (in) : Gpt_ValueType      The value that will be loaded in the timer
* \Parameters (out): None
* \Return value:   : None
*
*******************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value){
    /* To prevent the function to be interrupted by the same Channel */
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << Channel) > 0){
        return;
    }else{
        Re_entrantSaver |= 1 << Channel;
    }

    volatile uint32* TimerPtr = GetTimerAddress(Channel);
    if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_Concatenate ){
        /* Write the Loading value */
        REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr +GPTM_CTL_REG_OFFSET),0);
        WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAILR_REG_OFFSET), Value - 1);
        REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CTL_REG_OFFSET),0);
    }else if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_B ){
        /* Write the Loading value */
        REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr +GPTM_CTL_REG_OFFSET),8);
        WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TBILR_REG_OFFSET), Value - 1);
        REG_SET_PEIPTH_BB_PTR(((uint8*)TimerPtr +GPTM_CTL_REG_OFFSET),8);
    }
    Re_entrantSaver &= ~(1 << Channel);
}

/******************************************************************************
* \Syntax          : void Gpt_StopTimer(Gpt_ChannelType Channel)
* \Description     : The function Stops the timer and Reload it with zero
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Gpt_ChannelType    The parameter contains the Timer's number
* \Parameters (out): None
* \Return value:   : None
*
*******************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel){
    /* To prevent the function to be interrupted by the same Channel */
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << Channel) > 0){
        return;
    }else{
        Re_entrantSaver |= 1 << Channel;
    }

    volatile uint32* TimerPtr = GetTimerAddress(Channel);
    if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_A || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_Concatenate ){
        REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr +GPTM_CTL_REG_OFFSET),0);
        WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TAV_REG_OFFSET), 0);
        Re_entrantSaver &= ~(1 << Channel);
    }else if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_B ){
        REG_CLR_PERIPH_BB_PTR(((uint8*)TimerPtr +GPTM_CTL_REG_OFFSET),8);
        WriteUsingBB((uint32*)((uint8*)TimerPtr + GPTM_TBV_REG_OFFSET), 0);
        Re_entrantSaver &= ~(1 << Channel);
    }
}

/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
* \Description     : The function Returns the Elapsed time of the timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Gpt_ChannelType    The parameter contains the Timer's number
* \Parameters (out): None
* \Return value:   : Gpt_ValueType      The Elapsed time that the timer needs
*
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel){
    /* To prevent the function to be interrupted by the same Channel */
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << Channel) > 0){
        return 0;
    }else{
        Re_entrantSaver |= 1 << Channel;
    }
    Re_entrantSaver &= ~(1 << Channel);

    volatile uint32* timePtr = GetTimerAddress(Channel);
    uint32 temp_RealCounter, temp_PreScale;
    Gpt_ValueType returnValue;
    /* Reading the real counter */
    if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_B){
        temp_RealCounter = *(volatile uint32*)((uint8*)timePtr + GPTM_TBV_REG_OFFSET);
        temp_PreScale = *(volatile uint32*)((uint8*)timePtr + GPTM_TAPV_REG_OFFSET);
    }else{
        temp_RealCounter = *(volatile uint32*)((uint8*)timePtr + GPTM_TAV_REG_OFFSET);
        temp_PreScale = (temp_RealCounter >> 16 ) & 0xFF;
    }

    if(Gpt_ConfigPtr[Channel].PreScalingType == Gpt_Prescale_NotUsed){
        returnValue = temp_RealCounter & G_BitUsedGuarding[Channel];
    }else if(Gpt_ConfigPtr[Channel].PreScalingType == Gpt_Prescale_Hardware){
        if( Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_Concatenate){
            temp_RealCounter = temp_RealCounter >> G_BitShifting[Channel];
            temp_PreScale = temp_PreScale & G_BitShiftingGuarding[Channel];
            temp_PreScale = temp_PreScale << ( 32 - G_BitShifting[Channel] );
            returnValue = temp_RealCounter | temp_PreScale;
        }else{
            temp_RealCounter = temp_RealCounter >> G_BitShifting[Channel] ;
            temp_PreScale = temp_PreScale & G_BitShiftingGuarding[Channel] ;
            temp_PreScale = temp_PreScale << ( 16 - G_BitShifting[Channel] );
            returnValue = temp_RealCounter | temp_PreScale;
        }
    }else{
        temp_PreScale = G_SW_PreScaler_RealCounter[Channel] << (32 - G_BitShifting[Channel] );
        returnValue = temp_PreScale | ( temp_RealCounter >> G_BitShifting[Channel] );
    }
    return returnValue;
}

/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
* \Description     : The function Returns the Remaining time of the timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Gpt_ChannelType    The parameter contains the Timer's number
* \Parameters (out): None
* \Return value:   : Gpt_ValueType      The Remaining time that the timer needs
*
*******************************************************************************/
/* it returns the concatenation between (Prescale | Timer) */
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel){
    /* To prevent the function to be interrupted by the same Channel */
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << Channel) > 0){
        return 0;
    }else{
        Re_entrantSaver |= 1 << Channel;
    }

    Re_entrantSaver &= ~(1 << Channel);
    volatile uint32* timePtr = GetTimerAddress(Channel);
    uint32 temp_RealCounter, temp_PreScale, temp_bits;
    Gpt_ValueType returnValue;
    /* Reading the real counter */
    if(Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_B){
        temp_RealCounter = *(volatile uint32*)((uint8*)timePtr + GPTM_TBV_REG_OFFSET);
        temp_PreScale = *(volatile uint32*)((uint8*)timePtr + GPTM_TAPV_REG_OFFSET);
    }else{
        temp_RealCounter = *(volatile uint32*)((uint8*)timePtr + GPTM_TAV_REG_OFFSET);
        temp_PreScale = (temp_RealCounter >> 16 ) & 0xFF;
    }

    if(Gpt_ConfigPtr[Channel].PreScalingType == Gpt_Prescale_NotUsed){
        returnValue = temp_RealCounter & G_BitUsedGuarding[Channel];
        returnValue =( 0xFFFFFFFF - returnValue ) & G_BitUsedGuarding[Channel];
    }else if(Gpt_ConfigPtr[Channel].PreScalingType == Gpt_Prescale_Hardware){
        if( Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Channel].ChannelMode == Gpt_Mode_Periodic_Concatenate){
            temp_RealCounter = temp_RealCounter >> G_BitShifting[Channel];
            temp_PreScale = temp_PreScale & G_BitShiftingGuarding[Channel];
            temp_PreScale = temp_PreScale << ( 32 - G_BitShifting[Channel] );
            returnValue = temp_RealCounter | temp_PreScale;
            returnValue = ~returnValue;
        }else{
            temp_RealCounter = temp_RealCounter >> G_BitShifting[Channel] ;
            temp_PreScale = temp_PreScale & G_BitShiftingGuarding[Channel] ;
            temp_PreScale = temp_PreScale << ( 16 - G_BitShifting[Channel] );
            returnValue = temp_RealCounter | temp_PreScale;
            returnValue = ~returnValue;
        }
    }else{
        temp_PreScale = G_SW_PreScaler_RealCounter[Channel] << (32 - G_BitShifting[Channel] );
        returnValue = temp_PreScale | ( temp_RealCounter >> G_BitShifting[Channel] );
        returnValue = ~returnValue;
    }
    return returnValue;
}

/******************************************************************************
* \Syntax          : Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr)
* \Description     : The function Returns the Elapsed time of the timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : PredefTimer        The PreDefined timer Number
* \Parameters (out): TimeValuePtr       The Remaining time that the timer needs
* \Return value:   : Std_ReturnType     E_NOK
*                                       E_OK
*******************************************************************************/
/* it returns the concatenation between (Prescale | Timer) */
Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr){
    /* To prevent the function to be interrupted by the same Channel */
    static uint16 Re_entrantSaver = 0;
    if(Re_entrantSaver & (1 << (PredefTimer)) > 0){
        return E_NOK;
    }else{
        Re_entrantSaver |= 1 << (PredefTimer);
    }

    *TimeValuePtr = (G_SW_PreScaling[PredefTimer+TIMERS_NUMBERS] - G_SW_PreScaler_RealCounter[PredefTimer+TIMERS_NUMBERS]);
    Re_entrantSaver &= ~(1 << PredefTimer);
    return E_OK;
}


/******************************************************************************
* \Syntax          : void Gpt_Notification_channel_Normal_0(void)
* \Description     : The function that will be called when ISR arrives
*
* \Sync\Async      : Synchronous
* \Reentrancy      : non-Reentrant
* \Parameters (in) : PredefTimer        None
* \Parameters (out): TimeValuePtr       None
* \Return value:   : Std_ReturnType     None
*******************************************************************************/
void Gpt_Notification_channel_Normal_0(void){
    volatile uint32* timePtr = (uint32*)GPTM_0_16_32_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if( temp & Gpt_ConfigPtr[Gpt_Channel_Normal_0].Interrupt_Type & ( (1 << Gpt_InterruptOverFlow) | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Normal_0] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_0] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_0] == G_SW_PreScaling[0]){
            Gpt_ConfigPtr[Gpt_Channel_Normal_0].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_0] = 0;
        }
    }else if( temp & Gpt_ConfigPtr[Gpt_Channel_Normal_0].Interrupt_Type &( (1 << Gpt_InterruptMatch) | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_0].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Normal_0].GptNotificationCallBack_Match();
    }
}


void Gpt_Notification_channel_Normal_1(void){
    volatile uint32* timePtr = (uint32*)GPTM_1_16_32_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_1].Interrupt_Type & ((1 << Gpt_InterruptOverFlow) | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Normal_1] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_1] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_1] == G_SW_PreScaling[1]){
            Gpt_ConfigPtr[Gpt_Channel_Normal_1].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_1] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_1].Interrupt_Type & ((1 << Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_1].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Normal_1].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Normal_2(void){
    volatile uint32* timePtr = (uint32*)GPTM_2_16_32_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_2].Interrupt_Type & ( (1 << Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Normal_2] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_2] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_2] == G_SW_PreScaling[2]){
            Gpt_ConfigPtr[Gpt_Channel_Normal_2].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_2] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_2].Interrupt_Type &( (1 << Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_2].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Normal_2].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Normal_3(void){
    volatile uint32* timePtr = (uint32*)GPTM_3_16_32_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_3].Interrupt_Type & ((1 << Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Normal_3] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_3] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_3] == G_SW_PreScaling[3]){
            Gpt_ConfigPtr[Gpt_Channel_Normal_3].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_3] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_3].Interrupt_Type & ( (1 << Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_3].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Normal_3].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Normal_4(void){
    volatile uint32* timePtr = (uint32*)GPTM_4_16_32_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_4].Interrupt_Type & ( (1 << Gpt_InterruptOverFlow) | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Normal_4] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_4] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_4] == G_SW_PreScaling[4]){
            Gpt_ConfigPtr[Gpt_Channel_Normal_4].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_4] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_4].Interrupt_Type & ( (1 << Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_4].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Normal_4].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Normal_5(void){
    volatile uint32* timePtr = (uint32*)GPTM_5_16_32_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_5].Interrupt_Type &( (1 << Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode  == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode  == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Normal_5] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_5] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_5] == G_SW_PreScaling[5]){
            Gpt_ConfigPtr[Gpt_Channel_Normal_5].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Normal_5] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Normal_5].Interrupt_Type & ( (1 <<  Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Normal_5].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Normal_5].GptNotificationCallBack_Match();
    }
}

void Gpt_Notification_channel_Wide_0(void){
    volatile uint32* timePtr = (uint32*)GPTM_0_32_64_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_0].Interrupt_Type & ( (1 <<  Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode  == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Wide_0] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_0] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_0] == G_SW_PreScaling[Gpt_Channel_Wide_0]){
            Gpt_ConfigPtr[Gpt_Channel_Wide_0].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_0] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_0].Interrupt_Type & ( (1 <<  Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_0].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Wide_0].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Wide_1(void){
    volatile uint32* timePtr = (uint32*)GPTM_1_32_64_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_1].Interrupt_Type & ( (1 <<  Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Wide_1] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_1] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_1] == G_SW_PreScaling[Gpt_Channel_Wide_1]){
            Gpt_ConfigPtr[Gpt_Channel_Wide_1].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_1] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_1].Interrupt_Type & ( (1 <<  Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_1].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Wide_1].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Wide_2(void){
    volatile uint32* timePtr = (uint32*)GPTM_2_32_64_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_2].Interrupt_Type & ( (1 <<  Gpt_InterruptOverFlow ) | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }


        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Wide_2] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_2] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_2] == G_SW_PreScaling[Gpt_Channel_Wide_2]){
            Gpt_ConfigPtr[Gpt_Channel_Wide_2].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_2] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_2].Interrupt_Type & ( (1 <<  Gpt_InterruptMatch) | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_2].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Wide_2].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Wide_3(void){
    volatile uint32* timePtr = (uint32*)GPTM_3_32_64_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_3].Interrupt_Type & ( (1 <<  Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Wide_3] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_3] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_3] == G_SW_PreScaling[Gpt_Channel_Wide_3]){
            Gpt_ConfigPtr[Gpt_Channel_Wide_3].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_3] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_3].Interrupt_Type & ( (1 <<  Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_3].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Wide_3].GptNotificationCallBack_Match();
    }
}
void Gpt_Notification_channel_Wide_4(void){
    volatile uint32* timePtr = (uint32*)GPTM_4_32_64_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);
    if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_4].Interrupt_Type & ( (1 <<  Gpt_InterruptOverFlow)  | (1 << Gpt_InterruptOverFlow << 8)) ){
        /* Individual Mode */
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_OneShot_A || Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),8);
        }
        /* if Software preScaler disabled, G_SW_PreScaling[Gpt_Channel_Wide_4] = 1 and will be UP
         * if it's enable it will just increment and go on                                          */
        G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_4] ++;
        if(G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_4] == G_SW_PreScaling[Gpt_Channel_Wide_4]){
            Gpt_ConfigPtr[Gpt_Channel_Wide_4].GptNotificationCallBack_OverFlowEvent();
            G_SW_PreScaler_RealCounter[Gpt_Channel_Wide_4] = 0;
        }
    }else if(temp & Gpt_ConfigPtr[Gpt_Channel_Wide_4].Interrupt_Type & ( (1 <<  Gpt_InterruptMatch)  | (1 << Gpt_InterruptMatch << 8)) ){
        if(Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_OneShot_Concatenate || Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_Periodic_Concatenate ||Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_OneShot_A ||Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_Periodic_A){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
        }else if(Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_OneShot_B || Gpt_ConfigPtr[Gpt_Channel_Wide_4].ChannelMode == Gpt_Mode_Periodic_B){
            REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),11);
        }
        Gpt_ConfigPtr[Gpt_Channel_Wide_4].GptNotificationCallBack_Match();
    }
}

void Gpt_Notification_channel_Wide_5(void){
    volatile uint32* timePtr = (uint32*)GPTM_5_32_64_ADDRESS;
    uint32 temp = *(volatile uint32*)((uint8*)timePtr + GPTM_MIS_REG_OFFSET);

    if(temp & (1 << Gpt_InterruptOverFlow)  & (1 << Gpt_InterruptOverFlow << 8)){
        REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),0);
#if GPT_PREDEF_TIMER_100US_32BIT == Enable
        G_SW_PreScaler_RealCounter[0 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[0] == G_SW_PreScaler_RealCounter[0 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_100US_32BIT_FUN_OVERFLOW();
        }
#endif
#if GPT_PREDEF_TIMER_60US_16BIT == Enable
        G_SW_PreScaler_RealCounter[1 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[1] == G_SW_PreScaler_RealCounter[1 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_60US_16BIT_FUN_OVERFLOW();
        }
#endif
#if GPT_PREDEF_TIMER_40US_24BIT == Enable
        G_SW_PreScaler_RealCounter[2 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[2] == G_SW_PreScaler_RealCounter[2 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_40US_24BIT_FUN_OVERFLOW();
        }
#endif
#if GPT_PREDEF_TIMER_20US_32BIT == Enable
        G_SW_PreScaler_RealCounter[3 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[3] == G_SW_PreScaler_RealCounter[3 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_20US_32BIT_FUN_OVERFLOW();
        }
#endif
    }
    if(temp & (1 << Gpt_InterruptMatch)  & (1 << Gpt_InterruptMatch << 8)){
        REG_SET_PEIPTH_BB_PTR(((uint8*)timePtr +GPTM_ICR_REG_OFFSET),4);
#if GPT_PREDEF_TIMER_100US_32BIT == Enable
        G_SW_PreScaler_RealCounter[0 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[0] == G_SW_PreScaler_RealCounter[0 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_100US_32BIT_FUN_MATCH();
        }
#endif
#if GPT_PREDEF_TIMER_60US_16BIT == Enable
        G_SW_PreScaler_RealCounter[1 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[1] == G_SW_PreScaler_RealCounter[1 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_60US_16BIT_FUN_MATCH();
        }
#endif
#if GPT_PREDEF_TIMER_40US_24BIT == Enable
        G_SW_PreScaler_RealCounter[2 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[2] == G_SW_PreScaler_RealCounter[2 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_40US_24BIT_FUN_MATCH();
        }
#endif
#if GPT_PREDEF_TIMER_20US_32BIT == Enable
        G_SW_PreScaler_RealCounter[3 + TIMERS_NUMBERS]++;
        if( G_SW_PreScaling[3] == G_SW_PreScaler_RealCounter[3 + TIMERS_NUMBERS] ){
            GPT_PREDEF_TIMER_20US_32BIT_FUN_MATCH();
        }
#endif
    }
}


