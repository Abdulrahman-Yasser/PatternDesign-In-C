/*
 * Speed.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SPEED_SPEED_H_
#define APP_HAL_PATTERN_SPEED_SPEED_H_


#include "../General_Common/Std_Types.h"

struct speed{
    uint8 my_speed;
};


struct speed* Speed_Create(void);

uint8 getSpeed(struct speed* me);
void setSpeed(struct speed* me, uint8 s);



#endif /* APP_HAL_PATTERN_SPEED_SPEED_H_ */
