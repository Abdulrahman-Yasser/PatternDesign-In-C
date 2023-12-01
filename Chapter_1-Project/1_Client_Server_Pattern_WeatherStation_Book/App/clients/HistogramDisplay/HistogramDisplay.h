/*
 * HistogramDisplay.h
 *  Server Client, receives the data when it decides to receive
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_HISTOGRAMDISPLAY_HISTOGRAMDISPLAY_H_
#define APP_HISTOGRAMDISPLAY_HISTOGRAMDISPLAY_H_

#include "../../ECGPkg.h"
#include "HAL_Layer/LCD/Static/inc/LCD_Types.h"
struct TMDQueue;

/* class HistogramDisplay */

typedef struct HistogramDisplay HistogramDisplay;

#define HISTOGRAM_LCD_ID HistogramDisplay_LCD_ID

struct HistogramDisplay {
    int index;
    struct TMDQueue* itsTMDQueue;
    LCD_Handler_Type* my_lcd;
};

/* Constructors and destructors:*/

void HistogramDisplay_Init(HistogramDisplay* const me);

void HistogramDisplay_Cleanup(HistogramDisplay* const me);

/* Operations */

void HistogramDisplay_getValue(HistogramDisplay* const me);

void HistogramDisplay_updateHistogram(HistogramDisplay* const me);

struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const me);

void HistogramDisplay_setItsLCD(HistogramDisplay* const me, LCD_Handler_Type *p_LCD_Handler);

void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me, struct TMDQueue*p_TMDQueue);

HistogramDisplay * HistogramDisplay_Create(void);

void HistogramDisplay_Destroy(HistogramDisplay* const me);



#endif /* APP_HISTOGRAMDISPLAY_HISTOGRAMDISPLAY_H_ */
