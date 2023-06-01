/*
 * MotorSpeedSensor.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_MOTORSpeedSENSOR_MOTORSpeedSENSOR_H_
#define APP_HAL_PATTERN_MOTORSpeedSENSOR_MOTORSpeedSENSOR_H_

void MotorSpeedSensor_Init(void);

void MotorSpeedSensor_Cleanup(void);

void MotorSpeedSensor_run(void);

void getSpeed(void);

void MotorSpeedSensor_initRelations(void);




#endif /* APP_HAL_PATTERN_MOTORSpeedSENSOR_MOTORSpeedSENSOR_H_ */
