/*
 * ButtonDriver.h
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_BUTTONDRIVER_BUTTONDRIVER_H_
#define APP_HAL_PATTERN_BUTTONDRIVER_BUTTONDRIVER_H_

#include "../General_Common/Std_Types.h"
#include "../General_HAL/Button_Interface/Static/inc/Button.h"

#define LOOPS_PER_MS (1000)
#define DEBOUNCE_TIME (40)

struct Button;
struct LedEmitter;
struct Timer;

typedef struct ButtonDriver ButtonDriver;


struct ButtonDriver {
    uint8 oldState;
    uint8 toggleOn;
    Button_Type* itsButton;
    struct LedEmitter* itsLedEmitter;
    struct Timer* itsTimer;
};

void ButtonDriver_Init(ButtonDriver* const me);
void ButtonDriver_Cleanup(ButtonDriver* const me);
/* Operations */
void ButtonDriver_eventReceive(ButtonDriver* const me);
Button_Type* ButtonDriver_getItsButton(const ButtonDriver* const me);
void ButtonDriver_setItsButton(ButtonDriver* const me, Button_Type* p_Button);
struct LedEmitter* ButtonDriver_getItsLedEmitter(const ButtonDriver* const me);
void ButtonDriver_setItsLedEmitter(ButtonDriver* const me, struct LedEmitter* p_LedEmitter);

ButtonDriver * ButtonDriver_Create(void);
void ButtonDriver_Destroy(ButtonDriver* const me);

#endif /* APP_HAL_PATTERN_BUTTONDRIVER_BUTTONDRIVER_H_ */
