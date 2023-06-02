

/**
 * main.c
 */

#include "main.h"


int main(void)
{
    main_Init();
    main_Loop();
}


void main_Init(void){
    Port_Init();
    pwm_init();
    Dio_Init();
}

void main_Loop(void){
    struct UserInput* itsUserInput;
    itsUserInput = UserInput_Create();
    struct RobotArm* itsRobotArm;
    itsRobotArm = RobotArm_Create();
    struct CRDisplay *itsCRDisplay;
    itsCRDisplay = CRDisplay_Create();
    struct CRRobotArmManager* myCRRobotArmManager;
    myCRRobotArmManager = CRRobotArmManager_Create();

    CRRobotArmManager_setItsCRDisplay(myCRRobotArmManager, itsCRDisplay);
    CRRobotArmManager_setItsRobotArm(myCRRobotArmManager, itsRobotArm);
    CRRobotArmManager_setItsUserInput(myCRRobotArmManager, itsUserInput);

    CRRobotTaskHandlerInit(myCRRobotArmManager);
    vTaskStartScheduler();
    while(1){
    }
}
