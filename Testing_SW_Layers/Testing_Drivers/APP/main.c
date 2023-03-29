

/**
 * main.c
 */

#include "Testing_DS1037/Testing_DS1307.h"


int main(void)
{
    /*
     * the loop program is here to test the Device.
     * do not forget to edit PORT_Cfg, I2c_Cfg and DIO_Cfg to your own configuration
     */
//    Testing_DS1307();
    Testing_I2C_Initialization();
    Testing_I2C_Loop();
}
