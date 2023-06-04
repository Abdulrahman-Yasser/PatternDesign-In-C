/*
 * SpeedController.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */


#include "../Speed/Speed.h"
#include "../KinematicData/KinematicData.h"
#include "SpeedController.h"
#include <stdlib.h>



struct SpeedController* SpeedController_Create(void){
    struct SpeedController* me;
    me = (struct SpeedController*)malloc(sizeof(struct SpeedController));
    return me;
}

void SpeedController_manageSpeed(struct SpeedController* const me){
    uint8 s = ((rand()%100) / 10) * 10;
    kinematicData_setSpeed(me->itsKinematicData, me->ownShipSpeed);
}
struct KinematicData* SpeedController_getItsKinematicData(struct  SpeedController* const me){
    return me->itsKinematicData;
}
void SpeedController_setItsKinematicData(struct SpeedController* const me, struct KinematicData* p_KinematicData){
    me->itsKinematicData = p_KinematicData;
}



