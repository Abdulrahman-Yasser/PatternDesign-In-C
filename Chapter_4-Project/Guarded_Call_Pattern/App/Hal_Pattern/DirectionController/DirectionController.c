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
    uint8 d = (rand()%2);
    setDirection(&(me->ownShipDirection), d);
    kinematicData_setDirection(me->itsKinematicData, me->ownShipDirection);
}

struct kinematicData* DirectionController_getItsKinematicData(struct  DirectionController* const me){
    return me->itsKinematicData;
}

void DirectionController_setItsKinematicData(struct DirectionController* const me, struct kinematicData* p_KinematicData){
    me->itsKinematicData = p_KinematicData;
}

void DirectionController_run(void* mine){
    struct DirectionController* me = mine;
    TickType_t DC_Delay = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&DC_Delay, 1000);
        DirectionController_manageDirection(me);
    }
}
