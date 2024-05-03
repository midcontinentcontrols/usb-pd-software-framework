/***************************************************************************
  Power Delivery Source Pro Configurable globals Header File

  Company:
    Microchip Technology Inc.

  File Name:
    PSF_BootCfg.h

  Description:
    This header file contains user configurable globals and function prototypes.
************************************************************************** */
/*******************************************************************************
Copyright ©  [2022] Microchip Technology Inc. and its subsidiaries.

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

#ifndef _PSF_BOOTCFG_H    /* Guard against multiple inclusion */
#define _PSF_BOOTCFG_H


/*****************Defines to form PDOs ****************************************/
/* Macro used to form Fixed PDO 1 */
/*Source PDO 
  B31-B30   - Supply Type
  B29       - Dual Power role
  B28       - USB Suspend supported
  B27       - UnConstrained Power
  B26       - USB Communication capable
  B25       - Dual-Role Data
  B24       - Unchunked extended message
  B23-B22   - Reserved
  B21-B20   - Peak Current
  B19-B10   - Voltage in 50mV units
  B9-B0     - Maximum current in 10mA units */
#define CFG_FORM_SOURCE_FIXED_PDO1(voltage,current,DualRoleData,usbCommn,usbSusp,unconstrainedPwr,isDrp) \
    (((isDrp) << 29) | \
    ((usbSusp) << 28) | \
    ((unconstrainedPwr) << 27) | \
    ((usbCommn) << 26) | \
    ((DualRoleData) << 25) |\
    (((voltage)/50) << 10) | \
    ((current)/10))            

/*Sink PDO 
  B31-B30   - Supply Type
  B29       - Dual Power role
  B28       - Higher Capability
  B27       - UnConstrained Power
  B26       - USB Communication capable
  B25       - Dual-Role Data
  B24-B23   - Fast Role Swap required USB Type-C current
  B22-B20   - Reserved
  B19-B10   - Voltage in 50mV units
  B9-B0     - Maximum current in 10mA units */
/* Macro used to form Sink Fixed PDO 1 */
#define CFG_FORM_SINK_FIXED_PDO1(voltage,current,DualRoleData,usbCommn,unconstrainedPwr,HigherCapability,isDrp)  \
    (((isDrp) << 29) | \
    (((HigherCapability) << 28)) | \
    ((unconstrainedPwr) << 27) | \
    ((usbCommn) << 26) | \
    ((DualRoleData) << 25) |\
    (((voltage)/50) << 10) | \
    ((current)/10))  

/* Macro used to form Fixed PDOs 2 to 7 */
#define CFG_FORM_FIXED_PDOx(voltage,current)   ((((voltage)/50) << 10) | ((current)/10))

/*APDO Source
  B31-30    -11b Augumented Power Data Object
  B29-28    - 00b Programmable Power Supply
  B27       - PPS Power Limited
  B26-25    - Reserved
  B24-17    - Maximum voltage in 100mV increment 
  B16       - Reserved
  B15-8     - Minimum voltage in 100mV increment 
  B7        - Reserved
  B6-0      - Maximum current in 50mA increment */
/* Macro used to form PPS APDO */
#define CFG_FORM_PPS_APDO(minVolt,maxVolt,maxCurrent,pwrLtd)\
    (((3U) << 30U) |\
    ((pwrLtd) << 27U) | \
    (((maxVolt) / 100U) << 17U) | \
    (((minVolt) / 100U) << 8U) | \
    ((maxCurrent) / 50U)) 

/***********************Defines to form role swap policy************************/

#define CFG_FORM_ROLE_SWAP_POLICY(AsDfp_Request_DRSwap, AsUfp_Request_DRSwap, \
 AsDfp_Accept_DRSwap, AsUfp_Accept_DRSwap, AsSrc_Request_PRSwap, AsSnk_Request_PRSwap,\
 AsSrc_Accept_PRSwap, AsSnk_Accept_PRSwap, AsVCONNSrc_Req_VCONNSwap, AsNotVCONNSrc_Req_VCONNSwap,\
 AsVCONNSrc_Accept_VCONNSwap, AsNotVCONNSrc_Accept_VCONNSwap) ( (AsDfp_Request_DRSwap << 0) | \
 (AsUfp_Request_DRSwap << 1) | (AsDfp_Accept_DRSwap << 2) | (AsUfp_Accept_DRSwap << 3) \
 | (AsSrc_Request_PRSwap << 4) | (AsSnk_Request_PRSwap << 5) | (AsSrc_Accept_PRSwap << 6) \
 | (AsSnk_Accept_PRSwap << 7) | (AsVCONNSrc_Req_VCONNSwap << 8) | (AsNotVCONNSrc_Req_VCONNSwap << 9)\
 | (AsVCONNSrc_Accept_VCONNSwap << 10) | (AsNotVCONNSrc_Accept_VCONNSwap << 11))

/***********************Defines to form VDM Header************************/
/* VDM Header (From Table 6-25 Structured VDM Header of PD 3.0 Spec)
   B31-16  - Standard or Vendor ID (SVID) 
   B15     - VDM Type 
   B14-13  - Structured VDM Version
   B12-11  - Reserved 
   B10-8   - Object Position 
   B7-6    - Command Type 
   B5      - Reserved 
   B4-0    - Command */

#define CFG_FORM_VDM_HEADER(svid,vdmType,svdmVersion,objPos,cmdType,cmd) \
    (((svid) << 16) | \
    ((vdmType) << 15) | \
    ((svdmVersion) << 13) | \
    ((objPos) << 8) | \
    ((cmdType) << 6) | \
    (cmd))

/****************** Defines to configure Discover Identity ****************/
/***************************** ID HEADER VDO*************************/
/* ID Header VDO (From Table 6-29 ID Header VDO of PD 3.0 Spec)
   B31     - USB Commn Capable as USB Host
   B30     - USB Commn Capable as USB Device 
   B29-27  - Product Type (UFP/Cable Plug)
   B26     - Modal Operation Supported
   B25-23  - Product Type (DFP)
   B22-21  - Connector Type 
   B20-16  - Reserved 
   B15-0   - USB Vendor ID */

#define CFG_FORM_ID_HEADER_VDO(host,device,prodTypeUFP,modalOpr,prodTypeDFP,connectorType,vendorID) \
    (((host) << 31) | \
    ((device) << 30) | \
    ((prodTypeUFP) << 27) | \
    ((modalOpr) << 26) | \
    ((prodTypeDFP) << 23) | \
    ((connectorType) << 21) | \
    (vendorID))

/***************************** PRODUCT VDO*************************/
/* Product VDO (From Table 6-34 ID Product VDO of PD 3.0 Spec)
   B31-16     - USB Product ID
   B15-0      - bcd Device */

#define CFG_FORM_PRODUCT_VDO(productID,bcdDevice) \
    (((productID) << 16) | \
    (bcdDevice))

/******************* PRODUCT TYPE VDO - UFP VDO 1 *********************/
/* UFP VDO 1 (From Table 6-35 UFP VDO 1 of PD 3.0 Spec)
   B31-29  - UFP VDO Version 
   B28     - Reserved 
   B27-24  - Device Capability 
   B23-22  - Connector Type 
   B21-6   - Reserved  
   B5-3    - Alternate Modes
   B2-0    - USB Highest Speed */

#define CFG_FORM_UFP_VDO_1(vdoVer,devCapability,connectorType,altModes,usbSpeed) \
    (((vdoVer) << 29) | \
    ((devCapability) << 24) | \
    ((connectorType) << 22) | \
    ((altModes) << 3) | \
    (usbSpeed))

/******************* PRODUCT TYPE VDO - UFP VDO 2 *********************/
/* UFP VDO 2 (From Table 6-36 UFP VDO 2 of PD 3.0 Spec)
   B31-30  - Reserved
   B29-23  - USB4 Min Power
   B22-16  - USB4 Max Power 
   B15-14  - Reserved
   B13-7   - USB3 Min Power
   B6-0    - USB3 Max Power */

#define CFG_FORM_UFP_VDO_2(usb4MinPwr,usb4MaxPwr,usb3MinPwr,usb3MaxPwr) \
    (((usb4MinPwr) << 23) | \
    ((usb4MaxPwr) << 16) | \
    ((usb3MinPwr) << 7) | \
    (usb3MaxPwr))


/******************* PRODUCT TYPE VDO - DFP VDO *********************/
/* DFP VDO (From Table 6-37 DFP VDO of PD 3.0 Spec)
   B31-29  - DFP VDO Version
   B28-27  - Reserved
   B26-24  - Host Capability
   B23-22  - Connector Type
   B21-5   - Reserved
   B4-0    - Port Number */

#define CFG_FORM_DFP_VDO(vdoVersion,hostCapability,connectorType,portNum) \
    (((vdoVersion) << 29) | \
    ((hostCapability) << 24) | \
    ((connectorType) << 22) | \
    (portNum))


void PSF_LoadConfig(GLOBAL_CFG_STATUS_DATA *pasCfgStatusData);

#endif /* _PSF_BOOTCFG_H */

/* *****************************************************************************
 End of File
 */
