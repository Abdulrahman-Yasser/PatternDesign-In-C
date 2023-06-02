/*
 * CRRobotArmManager.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_CRROBOTARMMANAGER_CRROBOTARMMANAGER_H_
#define APP_HAL_PATTERN_CRROBOTARMMANAGER_CRROBOTARMMANAGER_H_

#include "../../General_Common/Std_Types.h"

struct CRDisplay;
struct RobotArm;
struct UserInput;

typedef struct CRRobotArmManager CRRobotArmManager;

struct CRRobotArmManager {
    struct CRDisplay* itsCRDisplay;
    struct RobotArm* itsRobotArm;
    struct UserInput* itsUserInput;
};

/* Constructors and destructors:*/
void CRRobotArmManager_Init(CRRobotArmManager* const me);

void CRRobotArmManager_Cleanup(CRRobotArmManager* const me);

/* Operations */
void CRRobotArmManager_motorZero(void* p_pvparameter);

void CRRobotArmManager_moveRobotArm(void* p_pvparameter);

struct CRDisplay* CRRobotArmManager_getItsCRDisplay(const CRRobotArmManager* const me);

void CRRobotArmManager_setItsCRDisplay(CRRobotArmManager* const me, struct CRDisplay* p_CRDisplay);

struct RobotArm* CRRobotArmManager_getItsRobotArm(const CRRobotArmManager* const me);

void CRRobotArmManager_setItsRobotArm(CRRobotArmManager* const me, struct RobotArm* p_RobotArm);

struct UserInput* CRRobotArmManager_getItsUserInput(const CRRobotArmManager* const me);

void CRRobotArmManager_setItsUserInput(CRRobotArmManager* const me, struct UserInput* p_UserInput);

CRRobotArmManager * CRRobotArmManager_Create(void);

void CRRobotTaskHandlerInit(CRRobotArmManager* const me);

void CRRobotArmManager_Destroy(CRRobotArmManager* const me);


#endif /* APP_HAL_PATTERN_CRROBOTARMMANAGER_CRROBOTARMMANAGER_H_ */
