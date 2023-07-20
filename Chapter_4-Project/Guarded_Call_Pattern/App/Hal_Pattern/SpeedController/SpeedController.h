/*
 * SpeedController.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_SPEEDCONTROLLER_SPEEDCONTROLLER_H_
#define APP_HAL_PATTERN_SPEEDCONTROLLER_SPEEDCONTROLLER_H_


struct SpeedController;

struct SpeedController* SpeedController_Create(void);

void SpeedController_manageSpeed(struct SpeedController* const me);
struct kinematicData* SpeedController_getItsKinematicData(struct  SpeedController* const me);
void SpeedController_setItsKinematicData(struct SpeedController* const me, struct kinematicData* p_KinematicData);

void SpeedController_run(void* mine);


#endif /* APP_HAL_PATTERN_SPEEDCONTROLLER_SPEEDCONTROLLER_H_ */
