/*
 * MotorDataDisplay.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_MOTORDATADISPLAY_MOTORDATADISPLAY_H_
#define APP_HAL_PATTERN_MOTORDATADISPLAY_MOTORDATADISPLAY_H_

#include "LCD/Static/inc/LCD.h"
#include "../kinematicData/kinematicData.h"

struct FlightDataDisplay {
    struct kinematicData* itsKinematicData;
    struct LCD_Handler* itsLcd;
};


struct FlightDataDisplay * FlightDataDisplay_Create(void);

void FlightDataDisplay_showFlightData(struct FlightDataDisplay* const me);
struct kinematicData* FlightDataDisplay_getItsKinematicData(struct FlightDataDisplay* const me);
void FlightDataDisplay_setItsKinematicData(struct FlightDataDisplay* const me, struct kinematicData* p_KinematicData);
void FlightDataDisplay_run(void* mine);

#endif /* APP_HAL_PATTERN_MOTORDATADISPLAY_MOTORDATADISPLAY_H_ */
