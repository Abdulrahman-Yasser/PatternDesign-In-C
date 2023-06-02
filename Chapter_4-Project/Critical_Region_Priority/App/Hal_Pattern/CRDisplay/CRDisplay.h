/*
 * CRDisplay.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_CRDISPLAY_CRDISPLAY_H_
#define APP_HAL_PATTERN_CRDISPLAY_CRDISPLAY_H_

struct CRDisplay;

struct CRDisplay* CRDisplay_Create(void);

void CRDisplay_printMsg(struct CRDisplay* me, char* str);


#endif /* APP_HAL_PATTERN_CRDISPLAY_CRDISPLAY_H_ */
