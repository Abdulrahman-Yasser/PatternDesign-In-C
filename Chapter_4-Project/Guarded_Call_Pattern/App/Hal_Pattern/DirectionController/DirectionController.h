/*
 * DirectionController.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_DIRECTIONCONTROLLER_DIRECTIONCONTROLLER_H_
#define APP_HAL_PATTERN_DIRECTIONCONTROLLER_DIRECTIONCONTROLLER_H_


#include "../Direction/Direction.h"
#include "../KinematicData/KinematicData.h"

struct DirectionController{
    struct Direction ownShipDirection;
    struct KinematicData* itsKinematicData;
};

struct DirectionController* DirectionController_Create(void);

void DirectionController_manageDirection(struct DirectionController* const me);
struct KinematicData* DirectionController_getItsKinematicData(struct  DirectionController* const me);
void DirectionController_setItsKinematicData(struct DirectionController* const me, struct KinematicData* p_KinematicData);



#endif /* APP_HAL_PATTERN_DIRECTIONCONTROLLER_DIRECTIONCONTROLLER_H_ */
