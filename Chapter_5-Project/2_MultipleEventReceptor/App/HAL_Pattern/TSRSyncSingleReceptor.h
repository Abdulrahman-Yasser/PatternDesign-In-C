/*
 * TSRSyncSingleReceptor.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_TSRSYNCSINGLERECEPTOR_H_
#define APP_HAL_PATTERN_TSRSYNCSINGLERECEPTOR_H_

#include "FreeRTOS.h"
#include "semphr.h"

#include <stdio.h>
#include "TokenizeAsyncSinglePkg.h"



typedef struct{
    char ch;
    double result;
    TSTATETYPE stateID;
    TSUBSTATETYPE subStateID;
    double tensPlace;
    SemaphoreHandle_t itsMutex;
}TokenizerSyncSingleReceptor;

void TokenizerSyncSingleReceptor_enter_GotNumber(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_enter_NoNumber(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_enter_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_enter_ProcessingWholePart(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_exit_GotNumber(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_exit_NoNumber(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_exit_ProcessingFractionalPart(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_exit_ProcessingWholePart(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_Init(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_Cleanup(TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_eventDispatch(TokenizerSyncSingleReceptor* const me, Event e);
SemaphoreHandle_t TokenizerSyncSingleReceptor_getItsMutex(const TokenizerSyncSingleReceptor* const me);
void TokenizerSyncSingleReceptor_setItsMutex(TokenizerSyncSingleReceptor* const me,SemaphoreHandle_t  p_Mutex);



#endif /* APP_HAL_PATTERN_TSRSYNCSINGLERECEPTOR_H_ */
