/*
 * FCTimer.c
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#include "FCTimer.h"

#include "../General_Mcal/GPT/Static/inc/GPT.h"
#include "../General_Mcal/GPT/Dynamic/inc/GPT_Cfg.h"

#include "../FCPeriodicPoller/FCPeriodicPoller.h"
#include <stdlib.h>

#define FC_TIMER_CHANNEL (Gpt_ChannelType)Gpt_Channel_Normal_0

static void (*oldVector)(void);
static void (*NewVector)(void);

static void handle_Timer_Interrupt(void);
void App_Function(void);

FCTimer_t* FCTimer_Create(void){
    FCTimer_t* me;
    me = (FCTimer_t*)malloc(sizeof(FCTimer_t));
    if(me != Null_Ptr){
        me->FCTimer_Channel = FC_TIMER_CHANNEL;
        FCTimer_installTimerInterruptHandler(me, handle_Timer_Interrupt);
    }
    return me;
}

static void handle_Timer_Interrupt(void){
    FCPeriodicPoller_poll();
}

void App_Function(void){
    NewVector();
}


void FCTimer_installTimerInterruptHandler(FCTimer_t* me, void (*func_ptr)(void)){
    oldVector = me->my_app;
    me->my_app = func_ptr;
    NewVector = func_ptr;
}

void FCTimer_removeTimerInterruptHandler(FCTimer_t* me){
    me->my_app = oldVector;
    oldVector = NewVector;
    NewVector = me->my_app;
}

void FCTimer_StartTimer(FCTimer_t* me, uint32 pollTime){
    Gpt_StartTimer(me->FCTimer_Channel, pollTime);
}

void FCTimer_setItsTimerChannel(FCTimer_t* me, Gpt_ChannelType gpt_ch){
    me->FCTimer_Channel = gpt_ch;
}

void FCTimer_StopTimer(FCTimer_t* me){
    Gpt_StopTimer(me->FCTimer_Channel);
}


void FCTimer_setItsFCPeriodicPoller(FCTimer_t* me, FCPeriodicPoller_t* p_FCPeriodicPoller){
    me->itsPeriodicPoller = p_FCPeriodicPoller;
}

