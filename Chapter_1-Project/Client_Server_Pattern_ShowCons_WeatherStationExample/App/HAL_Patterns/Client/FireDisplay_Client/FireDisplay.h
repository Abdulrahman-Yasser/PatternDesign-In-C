/*
 * FireDisplay.h
 *
 *  Created on: Apr 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_CLIENT_FIREDISPLAY_H_
#define APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_CLIENT_FIREDISPLAY_H_

#include "../../../ECGPkg.h"
#include "../General_HAL/LCD/Static/inc/LCD_Types.h"
#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"
struct TMDQueue;

typedef struct FireDisplay FireDisplay;

struct FireDisplay{
    int index;
    struct TMDQueue* itsTMDQueue;
    LCD_Handler_Type* my_lcd;
    DigitalInterface_Type* my_Buzzer;
    DigitalInterface_Type* my_Led;
};

void FireDisplay_Init(FireDisplay* const me);

void FireDisplay_Cleanup(FireDisplay* const me);

/* Operations */

void FireDisplay_getValue(FireDisplay* const me);

void FireDisplay_updateFireDisplay(FireDisplay* const me);

struct TMDQueue* FireDisplay_getItsTMDQueue(const FireDisplay* const me);

void FireDisplay_setItsLCD(FireDisplay* const me, LCD_Handler_Type *p_LCD_Handler);

void FireDisplay_setItsBUZZER(FireDisplay* const me, DigitalInterface_Type* p_BUZZER_Handler);

void FireDisplay_setItsLED(FireDisplay* const me, DigitalInterface_Type* p_LED_Handler);

void FireDisplay_setItsTMDQueue(FireDisplay* const me, struct TMDQueue*p_TMDQueue);

FireDisplay * FireDisplay_Create(void);

void FireDisplay_Destroy(FireDisplay* const me);



#endif /* APP_HAL_PATTERNS_CLIENT_FIREDISPLAY_CLIENT_FIREDISPLAY_H_ */
