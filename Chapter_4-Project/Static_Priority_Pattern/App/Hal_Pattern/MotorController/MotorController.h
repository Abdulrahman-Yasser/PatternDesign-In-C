/*
 * MotorController.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_MOTORCONTROLLER_MOTORCONTROLLER_H_
#define APP_HAL_PATTERN_MOTORCONTROLLER_MOTORCONTROLLER_H_


void MotorController_Init(void);

void MotorController_Cleanup(void);

void MotorController_run(void);

void move(void);

void zero(void);

void MotorController_initRelations(void);


#endif /* APP_HAL_PATTERN_MOTORCONTROLLER_MOTORCONTROLLER_H_ */
