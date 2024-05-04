/*
===============================================================================
 Author      : Adam Hemphill
 Copyright   : 2021-2022 Mid Continent Controls, Inc.
===============================================================================
*/

#ifndef __MC2_ZEPHYR_DRIVERS_UPD350B_PLATFORM_INTEGRATION_H
#define __MC2_ZEPHYR_DRIVERS_UPD350B_PLATFORM_INTEGRATION_H

#include <stdint.h>

void PSF_APP_SPI_Drv_Initialize();
uint8_t PSF_APP_SPIInitialisation();
uint8_t PSF_APP_HWTimerInit();
uint8_t PSF_APP_SPIRead(uint8_t port, uint8_t* txBuf, uint8_t txLen, uint8_t* rxBuf, uint8_t rxLen);
uint8_t PSF_APP_SPIWrite(uint8_t port, uint8_t *txBuf, uint8_t txLen);
void PSF_APP_EnterCriticalSection();
void PSF_APP_ExitCriticalSection();
void* PSF_APP_MemCpy(void* dest, const void* src, int len);
int PSF_APP_MemCmp(const void* ptr1, const void* ptr2, int len);


#endif //__MC2_ZEPHYR_DRIVERS_UPD350B_PLATFORM_INTEGRATION_H