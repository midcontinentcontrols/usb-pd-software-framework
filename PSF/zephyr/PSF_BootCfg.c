/***************************************************************************
  User Configuration File

  Company:
    Microchip Technology Inc.

  File Name:
    PSF_BootCfg.c

  Summary:
    User Configuration Source file

  Description:
    This source file contains user configurable globals and functions.

************************************************************************** */
/*******************************************************************************
Copyright � [2022] Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software and
any derivatives exclusively with Microchip products. It is your responsibility
to comply with third party license terms applicable to your use of third party
software (including open source software) that may accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES
OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN
ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST
EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU
HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "PSF_Config.h"
#include "upd350_pio_drivers.h"
#include "pd_timer.h"
#include <string.h>

/*******************************************************************/
/******************* Global variables********************************/
/*******************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
void PSF_LoadConfig(GLOBAL_CFG_STATUS_DATA *pasCfgStatusData)
{
	uint8_t u8Length = SET_TO_ZERO;

    pasCfgStatusData->u16ProductID = CONFIG_CFG_PRODUCT_ID;
    pasCfgStatusData->u16VendorID = CONFIG_CFG_VENDOR_ID;
    pasCfgStatusData->u8HWVersion = CONFIG_CFG_HW_VERSION;
    pasCfgStatusData->u8SiVersion = CONFIG_CFG_SILICON_VERSION;
    pasCfgStatusData->u8ManfStringLength = CONFIG_CFG_MANUFACTURER_STR_LEN;

    while(u8Length < pasCfgStatusData->u8ManfStringLength)
    {
        pasCfgStatusData->u8aManfString[u8Length] = CONFIG_CFG_MANUFACTURER_STR[u8Length];
        u8Length++;
    }

/***********************************Port Specific configuration***********************/

/*************************************************************************************/
/**************************************Port 0 Configurations**************************/
/*************************************************************************************/
    pasCfgStatusData->sPerPortData[PORT0].u32CfgData = CONFIG_CFG_PORT_0_CFG_DATA;

    pasCfgStatusData->sPerPortData[PORT0].u8Pio_FAULT_IN = (uint8_t)eUPD_PIO5;
    pasCfgStatusData->sPerPortData[PORT0].u8Mode_FAULT_IN = (uint8_t)eINPUT_ACTIVE_LOW;
    pasCfgStatusData->sPerPortData[PORT0].u8Pio_EN_VBUS = (uint8_t)eUPD_PIO3;
    pasCfgStatusData->sPerPortData[PORT0].u8Mode_EN_VBUS = (uint8_t)ePUSH_PULL_ACTIVE_HIGH;

    pasCfgStatusData->sPerPortData[PORT0].u8OCSThresholdPercentage = SET_TO_ZERO;
    pasCfgStatusData->sPerPortData[PORT0].u8OVThresholdPercentage = CONFIG_CFG_PORT_0_OVER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT0].u8UVThresholdPercentage = CONFIG_CFG_PORT_0_UNDER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT0].u8FaultInDebounceInms = CONFIG_CFG_PORT_0_FAULT_IN_OCS_DEBOUNCE_MS;
    pasCfgStatusData->sPerPortData[PORT0].u8VCONNOCSDebounceInms = CONFIG_CFG_PORT_0_VCONN_OCS_DEBOUNCE_IN_MS;
    pasCfgStatusData->sPerPortData[PORT0].u8VBUSMaxFaultCnt = CONFIG_CFG_PORT_0_MAX_VBUS_POWER_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT0].u8VCONNMaxFaultCnt = CONFIG_CFG_PORT_0_MAX_VCONN_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT0].u16PowerGoodTimerInms = MILLISECONDS_TO_TICKS(CONFIG_CFG_PORT_0_POWER_GOOD_TIMER_MS);
    pasCfgStatusData->sPerPortData[PORT0].u16MaxSrcPrtCurrentIn10mA = CONFIG_CFG_PORT_0_MAX_PORT_CURRENT_IN_10mA;

/**************************************Source Configurations**************************/
    pasCfgStatusData->sPerPortData[PORT0].u8SourcePDOCnt = CONFIG_CFG_PORT_0_SOURCE_NUM_OF_PDOS;

    /*PDOs update*/
    pasCfgStatusData->sPerPortData[PORT0].u32aSourcePDO[INDEX_0] = CONFIG_CFG_PORT_0_SOURCE_PDO_1;
    pasCfgStatusData->sPerPortData[PORT0].u32aSourcePDO[INDEX_1] = CONFIG_CFG_PORT_0_SOURCE_PDO_2;
    pasCfgStatusData->sPerPortData[PORT0].u32aSourcePDO[INDEX_2] = CONFIG_CFG_PORT_0_SOURCE_PDO_3;
    pasCfgStatusData->sPerPortData[PORT0].u32aSourcePDO[INDEX_3] = CONFIG_CFG_PORT_0_SOURCE_PDO_4;

 /*Configure role swap policy for note type port*/
    pasCfgStatusData->sPerPortData[PORT0].u16SwapPolicy = CONFIG_CFG_PORT_0_ROLE_SWAP_POLICY;

    pasCfgStatusData->sPerPortData[PORT0].u16FeatureSelect = CONFIG_CFG_PORT_0_FEATURE_SELECT;

    //pasCfgStatusData->sPBPerPortData[PORT0].u16MaxPrtPwrBankAIn250mW = (60*4);
    //pasCfgStatusData->sPBPerPortData[PORT0].u16MaxPrtPwrBankBIn250mW = (45*4);
    //pasCfgStatusData->sPBPerPortData[PORT0].u16MaxPrtPwrBankCIn250mW = (15*4);

/*************************************************************************************/
/**************************************Port 1 Configurations**************************/
/*************************************************************************************/
#if (CONFIG_PD_PORT_COUNT > 1)
    pasCfgStatusData->sPerPortData[PORT1].u32CfgData = CONFIG_CFG_PORT_1_CFG_DATA;

    pasCfgStatusData->sPerPortData[PORT1].u8Pio_FAULT_IN = (uint8_t)eUPD_PIO5;
    pasCfgStatusData->sPerPortData[PORT1].u8Mode_FAULT_IN = (uint8_t)eINPUT_ACTIVE_LOW;
    pasCfgStatusData->sPerPortData[PORT1].u8Pio_EN_VBUS = (uint8_t)eUPD_PIO3;
    pasCfgStatusData->sPerPortData[PORT1].u8Mode_EN_VBUS = (uint8_t)ePUSH_PULL_ACTIVE_HIGH;

    pasCfgStatusData->sPerPortData[PORT1].u8OCSThresholdPercentage = SET_TO_ZERO;
    pasCfgStatusData->sPerPortData[PORT1].u8OVThresholdPercentage = CONFIG_CFG_PORT_1_OVER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT1].u8UVThresholdPercentage = CONFIG_CFG_PORT_1_UNDER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT1].u8FaultInDebounceInms = CONFIG_CFG_PORT_1_FAULT_IN_OCS_DEBOUNCE_MS;
    pasCfgStatusData->sPerPortData[PORT1].u8VCONNOCSDebounceInms = CONFIG_CFG_PORT_1_VCONN_OCS_DEBOUNCE_IN_MS;
    pasCfgStatusData->sPerPortData[PORT1].u8VBUSMaxFaultCnt = CONFIG_CFG_PORT_1_MAX_VBUS_POWER_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT1].u8VCONNMaxFaultCnt = CONFIG_CFG_PORT_1_MAX_VCONN_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT1].u16PowerGoodTimerInms = MILLISECONDS_TO_TICKS(CONFIG_CFG_PORT_1_POWER_GOOD_TIMER_MS);
    pasCfgStatusData->sPerPortData[PORT1].u16MaxSrcPrtCurrentIn10mA = CONFIG_CFG_PORT_1_MAX_PORT_CURRENT_IN_10mA;

/**************************************Source Configurations**************************/
    pasCfgStatusData->sPerPortData[PORT1].u8SourcePDOCnt = CONFIG_CFG_PORT_1_SOURCE_NUM_OF_PDOS;

    /*PDOs update*/
    pasCfgStatusData->sPerPortData[PORT1].u32aSourcePDO[INDEX_0] = CONFIG_CFG_PORT_0_SOURCE_PDO_1;
    pasCfgStatusData->sPerPortData[PORT1].u32aSourcePDO[INDEX_1] = CONFIG_CFG_PORT_0_SOURCE_PDO_2;
    pasCfgStatusData->sPerPortData[PORT1].u32aSourcePDO[INDEX_2] = CONFIG_CFG_PORT_0_SOURCE_PDO_3;
    pasCfgStatusData->sPerPortData[PORT1].u32aSourcePDO[INDEX_3] = CONFIG_CFG_PORT_0_SOURCE_PDO_4;

 /*Configure role swap policy for note type port*/
    pasCfgStatusData->sPerPortData[PORT1].u16SwapPolicy = CONFIG_CFG_PORT_1_ROLE_SWAP_POLICY;
    pasCfgStatusData->sPerPortData[PORT1].u16FeatureSelect = CONFIG_CFG_PORT_1_FEATURE_SELECT;

    //pasCfgStatusData->sPBPerPortData[PORT1].u16MaxPrtPwrBankAIn250mW = (60*4);
    //pasCfgStatusData->sPBPerPortData[PORT1].u16MaxPrtPwrBankBIn250mW = (45*4);
    //pasCfgStatusData->sPBPerPortData[PORT1].u16MaxPrtPwrBankCIn250mW = (15*4);

/*************************************************************************************/
/**************************************Port 2 Configurations**************************/
/*************************************************************************************/
#if (CONFIG_PD_PORT_COUNT > 2)
    pasCfgStatusData->sPerPortData[PORT2].u32CfgData = CONFIG_CFG_PORT_2_CFG_DATA;

    pasCfgStatusData->sPerPortData[PORT2].u8Pio_FAULT_IN = (uint8_t)eUPD_PIO5;
    pasCfgStatusData->sPerPortData[PORT2].u8Mode_FAULT_IN = (uint8_t)eINPUT_ACTIVE_LOW;
    pasCfgStatusData->sPerPortData[PORT2].u8Pio_EN_VBUS = (uint8_t)eUPD_PIO3;
    pasCfgStatusData->sPerPortData[PORT2].u8Mode_EN_VBUS = (uint8_t)ePUSH_PULL_ACTIVE_HIGH;

    pasCfgStatusData->sPerPortData[PORT2].u8OCSThresholdPercentage = SET_TO_ZERO;
    pasCfgStatusData->sPerPortData[PORT2].u8OVThresholdPercentage = CONFIG_CFG_PORT_2_OVER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT2].u8UVThresholdPercentage = CONFIG_CFG_PORT_2_UNDER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT2].u8FaultInDebounceInms = CONFIG_CFG_PORT_2_FAULT_IN_OCS_DEBOUNCE_MS;
    pasCfgStatusData->sPerPortData[PORT2].u8VCONNOCSDebounceInms = CONFIG_CFG_PORT_2_VCONN_OCS_DEBOUNCE_IN_MS;
    pasCfgStatusData->sPerPortData[PORT2].u8VBUSMaxFaultCnt = CONFIG_CFG_PORT_2_MAX_VBUS_POWER_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT2].u8VCONNMaxFaultCnt = CONFIG_CFG_PORT_2_MAX_VCONN_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT2].u16PowerGoodTimerInms = MILLISECONDS_TO_TICKS(CONFIG_CFG_PORT_2_POWER_GOOD_TIMER_MS);
    pasCfgStatusData->sPerPortData[PORT2].u16MaxSrcPrtCurrentIn10mA = CONFIG_CFG_PORT_2_MAX_PORT_CURRENT_IN_10mA;

/**************************************Source Configurations**************************/
    pasCfgStatusData->sPerPortData[PORT2].u8SourcePDOCnt = CONFIG_CFG_PORT_2_SOURCE_NUM_OF_PDOS;

    /*PDOs update*/
    pasCfgStatusData->sPerPortData[PORT2].u32aSourcePDO[INDEX_0] = CONFIG_CFG_PORT_0_SOURCE_PDO_1;
    pasCfgStatusData->sPerPortData[PORT2].u32aSourcePDO[INDEX_1] = CONFIG_CFG_PORT_0_SOURCE_PDO_2;
    pasCfgStatusData->sPerPortData[PORT2].u32aSourcePDO[INDEX_2] = CONFIG_CFG_PORT_0_SOURCE_PDO_3;
    pasCfgStatusData->sPerPortData[PORT2].u32aSourcePDO[INDEX_3] = CONFIG_CFG_PORT_0_SOURCE_PDO_4;

 /*Configure role swap policy for note type port*/
    pasCfgStatusData->sPerPortData[PORT2].u16SwapPolicy = CONFIG_CFG_PORT_1_ROLE_SWAP_POLICY;
    pasCfgStatusData->sPerPortData[PORT2].u16FeatureSelect = CONFIG_CFG_PORT_1_FEATURE_SELECT;

    //pasCfgStatusData->u8PwrThrottleCfg = 0x07;
    //pasCfgStatusData->sPBPerPortData[PORT2].u16MaxPrtPwrBankAIn250mW = (60*4);
    //pasCfgStatusData->sPBPerPortData[PORT2].u16MaxPrtPwrBankBIn250mW = (45*4);
    //pasCfgStatusData->sPBPerPortData[PORT2].u16MaxPrtPwrBankCIn250mW = (15*4);

/*************************************************************************************/
/**************************************Port 3 Configurations**************************/
/*************************************************************************************/
#if (CONFIG_PD_PORT_COUNT > 3)
    pasCfgStatusData->sPerPortData[PORT3].u32CfgData = CONFIG_CFG_PORT_3_CFG_DATA;

    pasCfgStatusData->sPerPortData[PORT3].u8Pio_FAULT_IN = (uint8_t)eUPD_PIO5;
    pasCfgStatusData->sPerPortData[PORT3].u8Mode_FAULT_IN = (uint8_t)eINPUT_ACTIVE_LOW;
    pasCfgStatusData->sPerPortData[PORT3].u8Pio_EN_VBUS = (uint8_t)eUPD_PIO3;
    pasCfgStatusData->sPerPortData[PORT3].u8Mode_EN_VBUS = (uint8_t)ePUSH_PULL_ACTIVE_HIGH;

    pasCfgStatusData->sPerPortData[PORT3].u8OCSThresholdPercentage = SET_TO_ZERO;
    pasCfgStatusData->sPerPortData[PORT3].u8OVThresholdPercentage = CONFIG_CFG_PORT_3_OVER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT3].u8UVThresholdPercentage = CONFIG_CFG_PORT_3_UNDER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT3].u8FaultInDebounceInms = CONFIG_CFG_PORT_3_FAULT_IN_OCS_DEBOUNCE_MS;
    pasCfgStatusData->sPerPortData[PORT3].u8VCONNOCSDebounceInms = CONFIG_CFG_PORT_3_VCONN_OCS_DEBOUNCE_IN_MS;
    pasCfgStatusData->sPerPortData[PORT3].u8VBUSMaxFaultCnt = CONFIG_CFG_PORT_3_MAX_VBUS_POWER_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT3].u8VCONNMaxFaultCnt = CONFIG_CFG_PORT_3_MAX_VCONN_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT3].u16PowerGoodTimerInms = MILLISECONDS_TO_TICKS(CONFIG_CFG_PORT_3_POWER_GOOD_TIMER_MS);
    pasCfgStatusData->sPerPortData[PORT3].u16MaxSrcPrtCurrentIn10mA = CONFIG_CFG_PORT_3_MAX_PORT_CURRENT_IN_10mA;

/**************************************Source Configurations**************************/
    pasCfgStatusData->sPerPortData[PORT3].u8SourcePDOCnt = CONFIG_CFG_PORT_3_SOURCE_NUM_OF_PDOS;

    /*PDOs update*/
    pasCfgStatusData->sPerPortData[PORT3].u32aSourcePDO[INDEX_0] = CONFIG_CFG_PORT_0_SOURCE_PDO_1;
    pasCfgStatusData->sPerPortData[PORT3].u32aSourcePDO[INDEX_1] = CONFIG_CFG_PORT_0_SOURCE_PDO_2;
    pasCfgStatusData->sPerPortData[PORT3].u32aSourcePDO[INDEX_2] = CONFIG_CFG_PORT_0_SOURCE_PDO_3;
    pasCfgStatusData->sPerPortData[PORT3].u32aSourcePDO[INDEX_3] = CONFIG_CFG_PORT_0_SOURCE_PDO_4;

 /*Configure role swap policy for note type port*/
    pasCfgStatusData->sPerPortData[PORT3].u16SwapPolicy = CONFIG_CFG_PORT_3_ROLE_SWAP_POLICY;
    pasCfgStatusData->sPerPortData[PORT3].u16FeatureSelect = CONFIG_CFG_PORT_3_FEATURE_SELECT;

    //pasCfgStatusData->sPBPerPortData[PORT3].u16MaxPrtPwrBankAIn250mW = (60*4);
    //pasCfgStatusData->sPBPerPortData[PORT3].u16MaxPrtPwrBankBIn250mW = (45*4);
    //pasCfgStatusData->sPBPerPortData[PORT3].u16MaxPrtPwrBankCIn250mW = (15*4);
#endif
#endif
#endif
}



/* *****************************************************************************
 End of File
 */
