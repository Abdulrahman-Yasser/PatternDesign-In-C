/*
 * CRRobotArmManager.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>

#include "CRRobotArmManager.h"
#include "../RobotArm/RobotArm.h"
#include "../CRDisplay/CRDisplay.h"
#include "../UserInput/UserInput.h"

/* Constructors and destructors:*/
void CRRobotArmManager_Init(CRRobotArmManager* const me){
    me->itsCRDisplay = Null_Ptr;
    me->itsRobotArm = Null_Ptr;
    me->itsUserInput = Null_Ptr;
}

void CRRobotArmManager_Cleanup(CRRobotArmManager* const me);

/* Operations */
void CRRobotArmManager_motorZero(void* p_pvparameter){
    uint8 success;
    CRRobotArmManager* const me = p_pvparameter;
    TickType_t CRMotorZero = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&CRMotorZero, 1000);
        vTaskSuspendAll();
        success = RobotArm_moveTo(me->itsRobotArm, 0, 0, 0);
        xTaskResumeAll();
        if(success){
            CRDisplay_printMsg(me->itsCRDisplay,"It Is zero!");
        }else{
            CRDisplay_printMsg(me->itsCRDisplay,"Cannot zero!");
        }
    }
}

void CRRobotArmManager_moveRobotArm(void* p_pvparameter){
    /* local stack variable declarations */
    uint8 x, y, z, success = 1;
    CRRobotArmManager* const me = p_pvparameter;
    TickType_t CRMoveRobot = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&CRMoveRobot, 1000);
        /* noncritical region code */

        /* note that the function below has its
        own critical region and so cannot be
        called inside of the critical region
        of this function
        */

        x = UserInput_getX(me->itsUserInput);
        y = UserInput_getY(me->itsUserInput);
        z = UserInput_getZ(me->itsUserInput);

        /* critical region begins */

        vTaskSuspendAll();

        /* critical region code */

        success = RobotArm_moveTo(me->itsRobotArm,x,y,z);

        /* critical region ends */

        xTaskResumeAll();

        /* more noncritical region code */

        CRDisplay_printMsg(me->itsCRDisplay, "Result is ");
        CRDisplay_printMsg(me->itsCRDisplay, int_to_string(success) );
    }
}

struct CRDisplay* CRRobotArmManager_getItsCRDisplay(const CRRobotArmManager* const me){
    return me->itsCRDisplay;
}

void CRRobotArmManager_setItsCRDisplay(CRRobotArmManager* const me, struct CRDisplay* p_CRDisplay){
    me->itsCRDisplay = p_CRDisplay;
}

struct RobotArm* CRRobotArmManager_getItsRobotArm(const CRRobotArmManager* const me){
    return me->itsRobotArm;
}

void CRRobotArmManager_setItsRobotArm(CRRobotArmManager* const me, struct RobotArm* p_RobotArm){
    me->itsRobotArm = p_RobotArm;
}

struct UserInput* CRRobotArmManager_getItsUserInput(const CRRobotArmManager* const me){
    return me->itsUserInput;
}

void CRRobotArmManager_setItsUserInput(CRRobotArmManager* const me, struct UserInput* p_UserInput){
    me->itsUserInput = p_UserInput;
}

CRRobotArmManager * CRRobotArmManager_Create(void){
    CRRobotArmManager* me;
    me = (CRRobotArmManager*)malloc(sizeof(CRRobotArmManager));
    if(me != NULL){
        CRRobotArmManager_Init(me);
    }
    return me;
}

void CRRobotTaskHandlerInit(CRRobotArmManager* const me){

    TaskHandle_t MoveTheRobotTaskHandler;
    xTaskCreate(CRRobotArmManager_moveRobotArm, "Moving", 128, me, 2, &MoveTheRobotTaskHandler);

    TaskHandle_t ZeroTheRobotTaskHandler;
    xTaskCreate(CRRobotArmManager_motorZero, "Zero", 128, me, 3, &ZeroTheRobotTaskHandler);

    TaskHandle_t ChangingTheValuesTaskHandler;
    xTaskCreate(UserInput_Set_xyz, "UserInput", 128, me->itsUserInput, 3, &ChangingTheValuesTaskHandler);
}

void CRRobotArmManager_Destroy(CRRobotArmManager* const me){
    free(me);
}

