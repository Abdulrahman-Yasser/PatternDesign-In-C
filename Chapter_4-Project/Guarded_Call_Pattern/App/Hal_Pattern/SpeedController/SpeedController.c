/*
 * SpeedController.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */


#include "../Speed/Speed.h"
#include "../kinematicData/kinematicData.h"
#include "SpeedController.h"
#include <stdlib.h>


struct SpeedController{
    struct speed ownShipSpeed;
    struct kinematicData* itsKinematicData;
};

struct SpeedController* SpeedController_Create(void){
    struct SpeedController* me;
    me = (struct SpeedController*)malloc(sizeof(struct SpeedController));
    return me;
}

void SpeedController_manageSpeed(struct SpeedController* const me){
    uint8 s = ((rand()%100) / 10) * 10;
    setSpeed(&(me->ownShipSpeed), s);
    kinematicData_setSpeed(me->itsKinematicData, me->ownShipSpeed);
}
struct kinematicData* SpeedController_getItsKinematicData(struct  SpeedController* const me){
    return me->itsKinematicData;
}
void SpeedController_setItsKinematicData(struct SpeedController* const me, struct kinematicData* p_KinematicData){
    me->itsKinematicData = p_KinematicData;
}


void SpeedController_run(void* mine){
    struct SpeedController* me = mine;
    TickType_t SC_Delay = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&SC_Delay, 1000);
        SpeedController_manageSpeed(me);
    }
}

