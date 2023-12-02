/*
 * HistogramDisplay.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_HISTOGRAMDISPLAY_HISTOGRAMDISPLAY_H_
#define APP_HAL_PATTERNS_CLIENT_HISTOGRAMDISPLAY_HISTOGRAMDISPLAY_H_

#include "HAL_Layer/LCD/Static/inc/LCD_Types.h"
#include "../../Observer/Observer.h"

/*
 * here i've used singelton pattern. I have only one instance of HistogramDiplay which i can get
 * it's handler using HistogramDisplay_Create(). But i can't destroy it, because once i destroy
 * it i can't make another one.
 * I've made it like that because the update function needs to be void(*funptr)(void)
 * and if i had one static instance i would change it easily in the general void function
 * and pass the data to that global variable inside the  void function.
 * if i did not do that i will have to make the HistogramDisplay be an argument in the void(*funptr)(HistogramDisplay)
 */

/* class HistogramDisplay */

struct HistogramDisplay;

#define HISTOGRAM_LCD_ID HistogramDisplay_LCD_ID


/* Constructors and destructors:*/

void HistogramDisplay_Init(struct HistogramDisplay* me);


/* Operations */

/*
 * this is the function that will be passed to the observer's void function pointer.
 * so it have to be void argument and return void
 * and that's the reason why i have only one instance of HistogramDisplay so i can change it's easily in the
 * update function.
 * the function is static, so no one can invoke it other than the Observable
 */
//void HistogramDisplay_updateHistogram(void);

void HistogramDisplay_setItsLCD(struct HistogramDisplay* const me, LCD_Handler_Type *p_LCD_Handler);

Observer* HistogramDisplay_getObserver(void);

struct HistogramDisplay * HistogramDisplay_GetHandler(void);






#endif /* APP_HAL_PATTERNS_CLIENT_HISTOGRAMDISPLAY_HISTOGRAMDISPLAY_H_ */
