/*
 * DirectionController.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "DirectionController.h"
#include <stdlib.h>


struct DirectionController* DirectionController_Create(void){
    struct DirectionController* me;
    me = (struct DirectionController*)malloc(sizeof(struct DirectionController));
    return me;
}

void DirectionController_manageDirection(struct DirectionController* const me){
    kinematicData_setDirection(me->itsKinematicData, me->ownShipDirection);
}

struct KinematicData* DirectionController_getItsKinematicData(struct  DirectionController* const me){
    return me->itsKinematicData;
}

void DirectionController_setItsKinematicData(struct DirectionController* const me, struct KinematicData* p_KinematicData){
    me->itsKinematicData = p_KinematicData;
}

