/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __CAMERA_SCCB_H__
#define __CAMERA_SCCB_H__

//#include "kal_release.h"
#include "cam_sw_types.h"

#define MAX_SW_SCCB_FAIL_TRY_NO    3

typedef enum
{
	VA12,
	VRTC,
	VMIC,
	VAUDN,
	VAUDP,
	VRF28,
	VRF=VRF28,
	VTCXO,
	VA25,
	VCAMA,
	VCAMD,
	VCAM_IO,
	VCAM_AF,
	VIO28,
	VUSB,
	VBT,
	VSIM,
	VSIM1 = VSIM,
	VSIM2,
	VIBR,
	VMC,
	VMC1,
	VCAMA2,
	VCAMD2,
	VFM,
	VM12,
	VM12_1,
	VM12_2,
    VM12_INT,
	VCORE,
	VCORE2,
	VIO18,
	VPA_SW,
	VPROC,
	VRF18,
	VA,
	VA28 = VA,
	VM,
	VSF,
	VWIFI2V8,
	VWIFI3V3,
	V3GTX,
	V3GRX,
	VGP,
	VGP2,
	VSDIO,
	VDIG,	
	VBUS,
	VA1,
	VA2,
	VBACKUP,
	PMU_LDO_BUCK_MAX
}PMU_LDO_BUCK_LIST_ENUM;

typedef enum
{
	PMU_VOLT_00_000000_V =        0,
	PMU_VOLT_00_100000_V =   100000,
	PMU_VOLT_00_200000_V =   200000,
	PMU_VOLT_00_300000_V =   300000,
	PMU_VOLT_00_400000_V =   400000,
	PMU_VOLT_00_500000_V =   500000,
	PMU_VOLT_00_600000_V =   600000,
	PMU_VOLT_00_700000_V =   700000,
	PMU_VOLT_00_725000_V =   725000,
	PMU_VOLT_00_750000_V =   750000,
	PMU_VOLT_00_775000_V =   775000,
	PMU_VOLT_00_800000_V =   800000,
	PMU_VOLT_00_825000_V =   825000,
	PMU_VOLT_00_850000_V =   850000,
	PMU_VOLT_00_875000_V =   875000,
	PMU_VOLT_00_900000_V =   900000,
	PMU_VOLT_00_925000_V =   925000,
	PMU_VOLT_00_950000_V =   950000,
	PMU_VOLT_00_975000_V =   975000,
	PMU_VOLT_01_000000_V =  1000000,
	PMU_VOLT_01_025000_V =  1025000,
	PMU_VOLT_01_050000_V =  1050000,
	PMU_VOLT_01_075000_V =  1075000,
	PMU_VOLT_01_100000_V =  1100000,
	PMU_VOLT_01_125000_V =  1125000,
	PMU_VOLT_01_150000_V =  1150000,
	PMU_VOLT_01_175000_V =  1175000,
	PMU_VOLT_01_200000_V =  1200000,
	PMU_VOLT_01_225000_V =  1225000,
	PMU_VOLT_01_250000_V =  1250000,
	PMU_VOLT_01_275000_V =  1275000,
	PMU_VOLT_01_300000_V =  1300000,
	PMU_VOLT_01_325000_V =  1325000,
	PMU_VOLT_01_350000_V =  1350000,
	PMU_VOLT_01_375000_V =  1375000,
	PMU_VOLT_01_400000_V =  1400000,
	PMU_VOLT_01_425000_V =  1425000,
	PMU_VOLT_01_450000_V =  1450000,
	PMU_VOLT_01_475000_V =  1475000,
	PMU_VOLT_01_500000_V =  1500000,
	PMU_VOLT_01_520000_V =  1520000,
	PMU_VOLT_01_525000_V =  1525000,
	PMU_VOLT_01_540000_V =  1540000,
	PMU_VOLT_01_550000_V =  1550000,
	PMU_VOLT_01_560000_V =  1560000,
	PMU_VOLT_01_575000_V =  1575000,
	PMU_VOLT_01_580000_V =  1580000,
	PMU_VOLT_01_600000_V =  1600000,
	PMU_VOLT_01_620000_V =  1620000,
	PMU_VOLT_01_625000_V =  1625000,
	PMU_VOLT_01_640000_V =  1640000,
	PMU_VOLT_01_650000_V =  1650000,
	PMU_VOLT_01_660000_V =  1660000,
	PMU_VOLT_01_675000_V =  1675000,
	PMU_VOLT_01_680000_V =  1680000,
	PMU_VOLT_01_700000_V =  1700000,
	PMU_VOLT_01_720000_V =  1720000,
	PMU_VOLT_01_725000_V =  1725000,
	PMU_VOLT_01_740000_V =  1740000,
	PMU_VOLT_01_750000_V =  1750000,
	PMU_VOLT_01_760000_V =  1760000,
	PMU_VOLT_01_775000_V =  1775000,
	PMU_VOLT_01_780000_V =  1780000,
	PMU_VOLT_01_800000_V =  1800000,
	PMU_VOLT_01_820000_V =  1820000,
	PMU_VOLT_01_825000_V =  1825000,
	PMU_VOLT_01_840000_V =  1840000,
	PMU_VOLT_01_850000_V =  1850000,
	PMU_VOLT_01_860000_V =  1860000,
	PMU_VOLT_01_875000_V =  1875000,
	PMU_VOLT_01_880000_V =  1880000,
	PMU_VOLT_01_900000_V =  1900000,
	PMU_VOLT_01_920000_V =  1920000,
	PMU_VOLT_01_925000_V =  1925000,
	PMU_VOLT_01_940000_V =  1940000,
	PMU_VOLT_01_950000_V =  1950000,
	PMU_VOLT_01_960000_V =  1960000,
	PMU_VOLT_01_975000_V =  1975000,
	PMU_VOLT_01_980000_V =  1980000,
	PMU_VOLT_02_000000_V =  2000000,
	PMU_VOLT_02_020000_V =  2020000,
	PMU_VOLT_02_040000_V =  2040000,
	PMU_VOLT_02_050000_V =  2050000,
	PMU_VOLT_02_060000_V =  2060000,
	PMU_VOLT_02_080000_V =  2080000,
	PMU_VOLT_02_100000_V =  2100000,
	PMU_VOLT_02_120000_V =  2120000,
	PMU_VOLT_02_125000_V =  2125000,
	PMU_VOLT_02_140000_V =  2140000,	
	PMU_VOLT_02_200000_V =  2200000,
	PMU_VOLT_02_275000_V =  2275000,
	PMU_VOLT_02_300000_V =  2300000,
	PMU_VOLT_02_350000_V =  2350000,
	PMU_VOLT_02_425000_V =  2425000,
	PMU_VOLT_02_400000_V =  2400000,	
	PMU_VOLT_02_500000_V =  2500000,
	PMU_VOLT_02_575000_V =  2575000,
	PMU_VOLT_02_600000_V =  2600000,
	PMU_VOLT_02_650000_V =  2650000,
	PMU_VOLT_02_700000_V =  2700000,
	PMU_VOLT_02_725000_V =  2725000,
	PMU_VOLT_02_750000_V =  2750000,
	PMU_VOLT_02_800000_V =  2800000,
	PMU_VOLT_02_850000_V =  2850000,
	PMU_VOLT_02_875000_V =  2875000,
	PMU_VOLT_02_900000_V =  2900000,
	PMU_VOLT_02_950000_V =  2950000,
	PMU_VOLT_03_000000_V =  3000000,
	PMU_VOLT_03_025000_V =  3025000,
	PMU_VOLT_03_100000_V =  3100000,
	PMU_VOLT_03_175000_V =  3175000,
	PMU_VOLT_03_200000_V =  3200000,	
	PMU_VOLT_03_250000_V =  3250000,
	PMU_VOLT_03_275000_V =  3275000,
	PMU_VOLT_03_300000_V =  3300000,
	PMU_VOLT_03_325000_V =  3325000,
	PMU_VOLT_03_350000_V =  3350000,
	PMU_VOLT_03_400000_V =  3400000,
	PMU_VOLT_03_500000_V =  3500000,
	PMU_VOLT_03_650000_V =  3650000,
	PMU_VOLT_03_775000_V =  3775000,
	PMU_VOLT_03_800000_V =  3800000,
	PMU_VOLT_03_825000_V =  3825000,
	PMU_VOLT_03_850000_V =  3850000,
	PMU_VOLT_03_900000_V =  3900000,
	PMU_VOLT_03_950000_V =  3950000,
	PMU_VOLT_03_975000_V =  3975000,
	PMU_VOLT_04_000000_V =  4000000,
	PMU_VOLT_04_012500_V =  4012500,
	PMU_VOLT_04_025000_V =  4025000,
	PMU_VOLT_04_037500_V =  4037500,
	PMU_VOLT_04_050000_V =  4050000,
	PMU_VOLT_04_062500_V =  4062500,
	PMU_VOLT_04_067500_V =  4067500,
	PMU_VOLT_04_075000_V =  4075000,
	PMU_VOLT_04_087500_V =  4087500,
	PMU_VOLT_04_100000_V =  4100000,
	PMU_VOLT_04_112500_V =  4112500,
	PMU_VOLT_04_115000_V =  4115000,
	PMU_VOLT_04_116000_V =  4116000,
	PMU_VOLT_04_125000_V =  4125000,
	PMU_VOLT_04_137500_V =  4137500,
	PMU_VOLT_04_150000_V =  4150000,
	PMU_VOLT_04_162500_V =  4162500,
	PMU_VOLT_04_175000_V =  4175000,
	PMU_VOLT_04_187500_V =  4187500,
	PMU_VOLT_04_200000_V =  4200000,
	PMU_VOLT_04_212500_V =  4212500,
	PMU_VOLT_04_225000_V =  4225000,
	PMU_VOLT_04_237500_V =  4237500,
	PMU_VOLT_04_250000_V =  4250000,
	PMU_VOLT_04_262500_V =  4262500,
	PMU_VOLT_04_275000_V =  4275000,
	PMU_VOLT_04_287500_V =  4287500,
	PMU_VOLT_04_300000_V =  4300000,
	PMU_VOLT_04_325000_V =  4325000,
	PMU_VOLT_04_350000_V =  4350000,
	PMU_VOLT_04_362500_V =  4362500,
	PMU_VOLT_04_375000_V =  4375000,
	PMU_VOLT_04_400000_V =  4400000,
	PMU_VOLT_04_411500_V =  4411500,
	PMU_VOLT_04_425000_V =  4425000,
	PMU_VOLT_04_450000_V =  4450000,
	PMU_VOLT_04_500000_V =  4500000,
	PMU_VOLT_04_550000_V =  4550000,
	PMU_VOLT_04_600000_V =  4600000,
	PMU_VOLT_04_700000_V =  4700000,
	PMU_VOLT_04_800000_V =  4800000,
	PMU_VOLT_04_850000_V =  4850000,	
	PMU_VOLT_04_950000_V =  4950000,
	PMU_VOLT_05_000000_V =  5000000,	
	PMU_VOLT_05_150000_V =  5150000,
	PMU_VOLT_05_250000_V =  5250000,
	PMU_VOLT_05_300000_V =  5300000,
	PMU_VOLT_05_450000_V =  5450000,
	PMU_VOLT_06_000000_V =  6000000,
	PMU_VOLT_06_500000_V =  6500000,
	PMU_VOLT_06_750000_V =  6750000,
	PMU_VOLT_07_000000_V =  7000000,
	PMU_VOLT_07_250000_V =  7250000,
	PMU_VOLT_07_500000_V =  7500000,
	PMU_VOLT_08_000000_V =  8000000,
	PMU_VOLT_08_500000_V =  8500000,
	PMU_VOLT_09_500000_V =  9500000,
	PMU_VOLT_10_000000_V = 10000000,
	PMU_VOLT_10_500000_V = 10500000,	
	PMU_VOLT_MAX,
	PMU_VOLT_INVALID
}PMU_VOLTAGE_ENUM;


typedef enum
{
  CAMERA_HW_SCCB = 1, /* 0 indicate no init */
  CAMERA_SW_SCCB
} CAMERA_SCCB_MODE;

typedef enum
{
  CAMERA_SCCB_16BIT,
  CAMERA_SCCB_8BIT
} CAMERA_SCCB_WIDTH;

typedef enum
{
  CAMERA_SCCB_SENSOR,
  CAMERA_SCCB_LENS,
  CAMERA_SCCB_EEPROM,
  CAMERA_SCCB_MATV,
  
  CAMERA_SCCB_MAX,
} CAMERA_SCCB_OWNER;

void CamWriteCmosSensor(kal_uint8 Addr, kal_uint8 Para);
void CamWriteCmosSensor8(kal_uint16 Addr, kal_uint8 Para);
kal_uint16 CamReadCmosSensor(kal_uint16 Addr);
void LensWriteCmosSensor(kal_uint16 Addr, kal_uint16 Para);
kal_uint16 LensReadCmosSensor(kal_uint16 Addr);
void EepromWriteCmosSensor(kal_uint16 Addr, kal_uint16 Para);
kal_uint16 EepromReadCmosSensor(kal_uint16 Addr);
void MatvWriteCmosSensor(kal_uint16 Addr, kal_uint16 Para);
kal_uint16 MatvReadCmosSensor(kal_uint16 Addr);

void MatvSccbInit(CAMERA_SCCB_MODE Mode,
                        kal_uint8 HWSccbClkPinMode, kal_uint8 HWSccbDataPinMode,
                        kal_uint16 SWSccbDelay);
void CameraSccbOpen(CAMERA_SCCB_OWNER Owner,
                           kal_uint8 SccbWriteId,
                           CAMERA_SCCB_WIDTH SccbAddrWidth, CAMERA_SCCB_WIDTH SccbDataWidth,
                           kal_uint16 HWSccbSpeed);
void CameraSccbDisWR(CAMERA_SCCB_OWNER Owner);
void CameraSccbClose(CAMERA_SCCB_OWNER Owner);

#endif
