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

/*************************************************************
* Function : Spi_Init()
*//**
* \b Description:
*
* This function is used to initialize the Spi based on the configuration
table
* defined in spi_cfg module.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0)
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: The peripheral is set up with the configuration
*
* @param[in] Config is a pointer to the configuration table that contains
* the initialization for the peripheral.
*
* @return void
*
* \b Example:
* @code
* const SpiConfig_t *SpiConfig = Spi_ConfigGet();
*
* Spi_Init(SpiConfig);
* @endcode
*
* @see Spi_ConfigGet
* @see Spi_Init
* @see Spi_Transfer
* @see Spi_RegisterWrite
* @see Spi_RegisterRead
* @see Spi_CallbackRegister
*
************************************************************/
void Spi_Init(SpiConfig_t const* const Config);

/**********************************************************************
* Function : Spi_Transfer()
*//**
* \b Description:
*
* This function is used to initialize a data transfer on the SPI bus.
* PRE-CONDITION: Spi_Init must be called with valid configuration data
* PRE-CONDITION: SpiTransfer_t must be configured for the device
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: Data transferred based on configuration
*
* @param[in] Config is a configured structure describing the data
* transfer that occurs.
*
* @return void
*
* \b Example:
* @code
* const SpiConfig_t *SpiConfig = Spi_ConfigGet();
*
* Spi_Init(SpiConfig);
* Spi_Transfer(AccelerometerConfig);
*
* @endcode
*
* @see Spi_ConfigGet
* @see Spi_Init
* @see Spi_Transfer
* @see Spi_RegisterWrite
* @see Spi_RegisterRead
* @see Spi_CallbackRegister
*
**********************************************************************/
void Spi_Transfer(SpiTransfer_t const* const Config);

void Spi_RegisterWrite(uint32_t const Address,
                       uint32 const Value);

uint32 Spi_RegisterRead(uint32 const Adddress);

void Spi_CallbackRegister(SpiCallback_t const Function,
                          TYPE (*CallbackFunction)(type));


#endif /* SPI_STATIC_SPI_H_ */
