/*
 * SpeedController.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SPEEDCONTROLLER_SPEEDCONTROLLER_H_
#define APP_HAL_PATTERN_SPEEDCONTROLLER_SPEEDCONTROLLER_H_


struct SpeedController{
    struct speed ownShipSpeed;
    struct KinematicData* itsKinematicData;
};

struct SpeedController* SpeedController_Create(void);

void SpeedController_manageSpeed(struct SpeedController* const me);
struct KinematicData* SpeedController_getItsKinematicData(struct  SpeedController* const me);
void SpeedController_setItsKinematicData(struct SpeedController* const me, struct KinematicData* p_KinematicData);



#endif /* APP_HAL_PATTERN_SPEEDCONTROLLER_SPEEDCONTROLLER_H_ */
