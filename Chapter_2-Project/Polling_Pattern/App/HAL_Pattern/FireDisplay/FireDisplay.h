/*
 * MedicalDisplay.h
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_FIREDISPLAY_FIREDISPLAY_H_
#define APP_HAL_PATTERN_FIREDISPLAY_FIREDISPLAY_H_

#include "../General_Common/Std_Types.h"
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"

typedef struct FireDisplay FireDisplay_t;
struct FireDisplay{
    DigitalInterface_Type* Flame_LED, *Temp_LED, *FIRE_LED;
};

FireDisplay_t* FireDisplay_Create(void);


void FireDisplay_showStatus(FireDisplay_t* me, uint8 Flamestatus, uint8 Tempstatus);


#endif /* APP_HAL_PATTERN_FIREDISPLAY_FIREDISPLAY_H_ */
