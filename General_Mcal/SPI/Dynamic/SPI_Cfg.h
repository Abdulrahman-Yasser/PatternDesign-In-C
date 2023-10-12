/*
 * SPI_Cfg.h
 *
 *  Created on: Sep 30, 2023
 *      Author: Abdu
 */

#ifndef SPI_DYNAMIC_SPI_CFG_H_
#define SPI_DYNAMIC_SPI_CFG_H_

#include "../Static/SPI_Types.h"

#define SSI_CONFIGURED_NUMBER 1

extern const SsiConfig_t Ssi_Container[SSI_CONFIGURED_NUMBER] ;

const SsiConfig_t* SPI_getConfig(void);

#endif /* SPI_DYNAMIC_SPI_CFG_H_ */
