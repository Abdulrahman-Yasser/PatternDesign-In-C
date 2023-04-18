/*
 * FireDetectionDisplay.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_FIREDETECTIONDISPLAY_FIREDETECTIONDISPLAY_H_
#define APP_FIREDETECTIONDISPLAY_FIREDETECTIONDISPLAY_H_

#include "../ECGPkg.h"
#include "../TMDQueue/TMDQueue.h"

struct TMDQueue;

typedef struct FireDetectionDisplay FireDetectionDisplay;

struct FireDetectionDisplay {
    int index;
    struct TMDQueue* itsTMDQueue;
};



#endif /* APP_FIREDETECTIONDISPLAY_FIREDETECTIONDISPLAY_H_ */
