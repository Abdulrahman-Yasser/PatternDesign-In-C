/*
 * LED_Lcfg.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Abdu
 */

#include "../inc/Sensor_Cfg.h"

const Sensor_Digital_Container_Type Sensor_Digital_Config[SENSOR_DIGITAL_CONFIGURED_NUMBER] = {
                                                                                               {.Sensor_Data_Pins = DIO_Channel5_A}
};

const Sensor_Analog_Container_Type Sensor_Analog_Config[SENSOR_ANALOG_CONFIGURED_NUMBER] = {
                                                              {.ADC_Num = ADC_TEMPERATURE_ADC_NUM, .sampleSequencer_Num = ADC_TEMPERATURE_SS_NUM},
                                                              {.ADC_Num = ADC_FLAME_ADC_NUM, .sampleSequencer_Num = ADC_FLAME_SS_NUM},
                                                              {.ADC_Num = ADC_SMOKE_ADC_NUM, .sampleSequencer_Num = ADC_SMOKE_SS_NUM},
                                                              {.ADC_Num = ADC_WATER_ADC_NUM, .sampleSequencer_Num = ADC_WATER_SS_NUM}
};

