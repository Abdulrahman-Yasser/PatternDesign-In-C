/*
 * SPI.h
 *
 *  Created on: Sep 30, 2023
 *      Author: Abdu
 */

#ifndef SPI_STATIC_SPI_H_
#define SPI_STATIC_SPI_H_

#include "../Dynamic/SPI_Cfg.h"
#include "SPI_Types.h"

void Spi_Init(SsiConfig_t const* const Config);

void Spi_Transmit_one_package(SSI_Channel_t const ssi_channel, uint16 const data);

uint16 Spi_RegisterReceive(SSI_Channel_t ssi_channel);

void Spi_Set_Callback(SSI_Channel_t ssi_channel, SSI_Interrupt_Type SSI_Interrupt_event, void (*DioCallBackFun)(void));

#endif /* SPI_STATIC_SPI_H_ */
