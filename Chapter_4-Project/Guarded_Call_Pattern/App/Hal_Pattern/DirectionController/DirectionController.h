/*
 * DirectionController.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_DIRECTIONCONTROLLER_DIRECTIONCONTROLLER_H_
#define APP_HAL_PATTERN_DIRECTIONCONTROLLER_DIRECTIONCONTROLLER_H_


#include "../Direction/Direction.h"
#include "../kinematicData/kinematicData.h"

struct DirectionController{
    struct Direction ownShipDirection;
    struct kinematicData* itsKinematicData;
};

struct DirectionController* DirectionController_Create(void);

void DirectionController_manageDirection(struct DirectionController* const me);
struct kinematicData* DirectionController_getItsKinematicData(struct  DirectionController* const me);
void DirectionController_setItsKinematicData(struct DirectionController* const me, struct kinematicData* p_KinematicData);

void DirectionController_run(void* me);



#endif /* APP_HAL_PATTERN_DIRECTIONCONTROLLER_DIRECTIONCONTROLLER_H_ */
