/*
 * Direction.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_DIRECTION_DIRECTION_H_
#define APP_HAL_PATTERN_DIRECTION_DIRECTION_H_


#include "../General_Common/Std_Types.h"

struct Direction{
    uint8 my_direction;
};

struct Direction* Direction_Create(void);

uint8 getDirection(struct Direction* me);

void setDirection(struct Direction* me, uint8 d);


#endif /* APP_HAL_PATTERN_DIRECTION_DIRECTION_H_ */
