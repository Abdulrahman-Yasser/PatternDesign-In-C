/*
 * FCTimer.h
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_FCTIMER_FCTIMER_H_
#define APP_HAL_PATTERN_FCTIMER_FCTIMER_H_


#include "../General_Common/Std_Types.h"
#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "../FCPeriodicPoller/FCPeriodicPoller.h"


typedef struct FCTimer FCTimer_t;


struct FCTimer{
    FCPeriodicPoller_t* itsPeriodicPoller;
    Gpt_ChannelType FCTimer_Channel;
    void (*my_app)(void);
    uint16 pool_Time;
};


FCTimer_t* FCTimer_Create(void);

void FCTimer_installTimerInterruptHandler(FCTimer_t* me, void (*func_ptr)(void));
void FCTimer_removeTimerInterruptHandler(FCTimer_t* me);
void FCTimer_StartTimer(FCTimer_t* me, uint32 pollTime);

void FCTimer_StopTimer(FCTimer_t* me);
void FCTimer_setItsTimerChannel(FCTimer_t* me, Gpt_ChannelType gpt_ch);
void FCTimer_setItsPoolTime(FCTimer_t* me, uint16 its_PoolTime);
void FCTimer_setItsFCPeriodicPoller(FCTimer_t* me, FCPeriodicPoller_t* p_FCPeriodicPoller);
#endif /* APP_HAL_PATTERN_FCTIMER_FCTIMER_H_ */
