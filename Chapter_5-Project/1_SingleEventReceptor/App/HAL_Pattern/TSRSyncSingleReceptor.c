/*
 * TSRSyncSingleReceptor.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdu
 */

#include "TSRSyncSingleReceptor.h"

void TokenizerSyncSingleReceptor_enter_GotNumber(TokenizerSyncSingleReceptor* const me){
    me->tensPlace = 10.0;
}

void TokenizerSyncSingleReceptor_enter_NoNumber(TokenizerSyncSingleReceptor* const me){
    me->result = 0.0;
}

void TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const me){

}

void TokenizerSyncSingleReceptor_enter_ProcessingWholePart(TokenizerSyncSingleReceptor* const me){
    me->result = (me->result * 10) + digit(me->ch);
}

void TokenizerSyncSingleReceptor_exit_GotNumber(TokenizerSyncSingleReceptor* const me){
    me->subStateID = NULL_SSTATE;
}

void TokenizerSyncSingleReceptor_exit_NoNumber(TokenizerSyncSingleReceptor* const me){

}

void TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const me){

}

void TokenizerSyncSingleReceptor_exit_ProcessingWholePart(TokenizerSyncSingleReceptor* const me){

}

void TokenizerSyncSingleReceptor_Init(TokenizerSyncSingleReceptor* const me){
    me->ch = 'x';
    me->result = 0.0;
    me->tensPlace = 10.0;

    me->stateID = NONUMBER_STATE;
    me->subStateID = NULL_SSTATE;
}

void TokenizerSyncSingleReceptor_Cleanup(TokenizerSyncSingleReceptor* const me){

}

void TokenizerSyncSingleReceptor_eventDispatch(TokenizerSyncSingleReceptor* const me, Event e){
    xSemaphoreTake(me->itsMutex, 0);
    switch (e.eType) {
    case EVDIGIT:
        switch (me->stateID) {
        case NONUMBER_STATE:
            /* transition to GotNumber state, default substate */
            TokenizerSyncSingleReceptor_exit_NoNumber(me);
            me->ch = e.ed.c;
            TokenizerSyncSingleReceptor_enter_GotNumber(me);
            me->stateID = GOTNUMBER_STATE;
            TokenizerSyncSingleReceptor_enter_ProcessingWholePart(me);
            me->subStateID = PROCESSINGWHOLEPART_SSTATE;
            printf("Current value of result: %g\n", me->result);
            break;
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
            case PROCESSINGWHOLEPART_SSTATE:
                TokenizerSyncSingleReceptor_exit_ProcessingWholePart(me);
                me->ch = e.ed.c;
                TokenizerSyncSingleReceptor_enter_ProcessingWholePart(me);
                printf("Current value of result: %g\n", me->result);
                break;
            case PROCESSINGFRACTIONALPART_SSTATE:
                TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(me);
                me->ch = e.ed.c;
                me->result += digit(me->ch) / me->tensPlace;
                me->tensPlace *= 10.0;
                TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(me);
                printf("Current value of result: %g\n", me->result);
                break;
            };
        };
        break;
    case EVDOT:
        me->ch = '.';
        switch (me->stateID) {
        case NONUMBER_STATE:
        /* transition to GotNumber state, default substate */
            TokenizerSyncSingleReceptor_exit_NoNumber(me);
            TokenizerSyncSingleReceptor_enter_GotNumber(me);
            me->stateID = GOTNUMBER_STATE;
            TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(me);
            me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
            break;
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
            case PROCESSINGWHOLEPART_SSTATE:
                TokenizerSyncSingleReceptor_exit_ProcessingWholePart(me);
                TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(me);
                me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                break;
            };
        };
    break;
    case EVWHITESPACE:
    case EVENDOFSTRING:
        switch (me->stateID) {
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
            case PROCESSINGWHOLEPART_SSTATE:
                TokenizerSyncSingleReceptor_exit_ProcessingWholePart(me);
                break;
            case PROCESSINGFRACTIONALPART_SSTATE:
                TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(me);
                break;
            };
            TokenizerSyncSingleReceptor_exit_GotNumber(me);
            printf("Number: %g\n", me->result);
            TokenizerSyncSingleReceptor_enter_NoNumber(me);
            me->stateID = NONUMBER_STATE;
            break;
        };
        break;
    }; // end switch e.eType
    xSemaphoreGive(me->itsMutex);
}

SemaphoreHandle_t TokenizerSyncSingleReceptor_getItsMutex(const TokenizerSyncSingleReceptor* const me){
    return me->itsMutex;
}

void TokenizerSyncSingleReceptor_setItsMutex(TokenizerSyncSingleReceptor* const me,SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

