/*
 * LedEmitter.h
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_LEDEMITTER_LEDEMITTER_H_
#define APP_HAL_PATTERN_LEDEMITTER_LEDEMITTER_H_

#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

typedef struct LedEmitter LedEmitter;

struct LedEmitter{
    DigitalInterface_Type *Led;
};

LedEmitter *LedEmitter_Create(DIO_ChannelType led_Ch);
void LedEmitter_Destroy(LedEmitter* me);

void LedEmitter_startEmitting(LedEmitter* me);
void LedEmitter_stopEmitting(LedEmitter* me);

#endif /* APP_HAL_PATTERN_LEDEMITTER_LEDEMITTER_H_ */
