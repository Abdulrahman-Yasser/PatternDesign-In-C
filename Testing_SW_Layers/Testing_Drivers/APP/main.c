

/**
 * main.c
 */

#include "main.h"
int main(void)

{
    /*
     * the loop program is here to test the Device.
     * do not forget to edit PORT_Cfg, I2c_Cfg and DIO_Cfg to your own configuration
     */
    Testing_LCD_and_SpecificDriverTempInit();
    Testing_LCD_and_SpecificDriverTemp_loop();
}
