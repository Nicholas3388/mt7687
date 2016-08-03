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

#include "type_def.h"
#include "top.h"
#include "mt7637_cm4_hw_memmap.h"
#include "spi_flash.h"
#include "memory_attribute.h"

#if defined(__EVB_E1__)

static UINT32 gXtalFreq;
static UINT32 gCpuFrequency;
//#define CFG_FPGA 1

void top_xtal_init(void)
{

    UINT32  u4RegVal = 0;
    unsigned long reg = HAL_REG_32(TOP_AON_CM4_STRAP_STA);
    reg = (reg >> 13) & 0x00000007;

#if (CFG_FPGA == 0)
    u4RegVal = HAL_REG_32(TOP_AON_CM4_PWRCTLCR);
    u4RegVal &= (~(CM4_PWRCTLCR_CM4_XTAL_FREQ_MASK));

    switch (reg) {
        case 0:
            gXtalFreq = 20000000;  /* 20Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_20M_OFFSET);
            break;
        case 1:
            gXtalFreq = 40000000;  /* 40Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_40M_OFFSET);
            break;
        case 2:
            gXtalFreq = 26000000;  /* 26Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_26M_OFFSET);
            break;
        case 3:
            gXtalFreq = 52000000;  /* 52Mhz */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_52M_OFFSET);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            gXtalFreq = 40000000;  /* fall through */
            u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_40M_OFFSET);
            break;
    }

#else
    gXtalFreq = 30000000;
    u4RegVal |= BIT(CM4_PWRCTLCR_CM4_XTAL_FREQ_40M_OFFSET);
#endif
    HAL_REG_32(TOP_AON_CM4_PWRCTLCR) = u4RegVal;

}


uint32_t top_xtal_freq_get(void)
{
    return gXtalFreq;
}

uint32_t top_mcu_freq_get(void)
{
    return gCpuFrequency;
}

void cmnPLL1ON(void)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgCM4PWRCtl = (volatile UINT32 *)TOP_CFG_CM4_PWR_CTL_CR;


    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    reg = reg | (CM4_MPLL_EN_PLL1_ON_PLL2_OFF << CM4_MPLL_EN_SHIFT);    // Or only, so PLL2 setting won't be cleared
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

    do {
        reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
        reg = reg & (CM4_BT_PLL_RDY_MASK << CM4_BT_PLL_RDY_SHIFT);
    } while (!reg);

}

void cmnPLL1ON_PLL2ON(uint8_t fg960M)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgCM4PWRCtl = (volatile UINT32 *)TOP_CFG_CM4_PWR_CTL_CR;

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg & ~(CM4_MCU_960_EN_MASK << CM4_MCU_960_EN_SHIFT);
    reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    reg = reg | (CM4_MCU_960_EN_DISABLE << CM4_MCU_960_EN_SHIFT);
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg & ~(CM4_MPLL_EN_MASK << CM4_MPLL_EN_SHIFT);
    reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    reg = reg | (CM4_MPLL_EN_PLL1_ON_PLL2_ON << CM4_MPLL_EN_SHIFT);
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);

    do {
        reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
        reg = reg & (CM4_WF_PLL_RDY_MASK << CM4_WF_PLL_RDY_SHIFT);
    } while (!reg);

    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg & ~(CM4_MCU_960_EN_MASK << CM4_MCU_960_EN_SHIFT);
    reg = reg & ~(CM4_NEED_RESTORE_MASK <<  CM4_NEED_RESTORE_SHIFT);    // avoid W1C
    if (fg960M) {
        reg = reg | (CM4_MCU_960_EN_ENABLE << CM4_MCU_960_EN_SHIFT);
    } else {
        reg = reg | (CM4_MCU_960_EN_DISABLE << CM4_MCU_960_EN_SHIFT);
    }
    cmnWriteRegister32(pTopCfgCM4PWRCtl, reg);
}

void cmnCpuClkConfigureToXtal(void)
{
    TOP_CFG_AON_BondingAndStrap bs;
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgCM4CKG = (volatile UINT32 *)TOP_CFG_CM4_CKG_EN0;

    // Step1. CM4_HCLK_SW set to XTAL
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_OSC << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    // Step2. CM4_RF_CLK_SW set to XTAL
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_XTAL << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    gCpuFrequency = top_xtal_freq_get();
    SystemCoreClockUpdate();
    SysTick_Set(SystemCoreClock / 1000); /* 1ms trigger */
    return;
}



void cmnCpuClkConfigureTo192M(void)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgCM4CKG = (volatile UINT32 *)TOP_CFG_CM4_CKG_EN0;

    // Step1. Power on PLL1 & 2
    cmnPLL1ON_PLL2ON(TRUE);

    // Step2. CM4_RF_CLK_SW set to PLL2(960)
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_WIFI_PLL_960 << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    // Step3. set divider to 1+8/2=5, ->  960/5=192Mhz
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_MCU_DIV_SEL_MASK << CM4_MCU_DIV_SEL_SHIFT);
    reg = reg | (8 << CM4_MCU_DIV_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    // Step4. CM4_HCLK_SW set to PLL_CK
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_PLL << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    return;
}

//
//  Configure CM4 MCU to 160Mhz
//

void cmnCpuClkConfigureTo160M(void)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgCM4CKG = (volatile UINT32 *)TOP_CFG_CM4_CKG_EN0;

    // Step1. Power on PLL1 & 2
    cmnPLL1ON_PLL2ON(FALSE);
#if 0
    volatile UINT32 *pTopCfgCM4PWRCtl = (volatile UINT32 *)TOP_CFG_CM4_PWR_CTL_CR;
    reg = cmnReadRegister32(pTopCfgCM4PWRCtl);
    reg = reg | (CM4_MCU_960_EN_DISABLE << CM4_MCU_960_EN_SHIFT);
#endif
    // Step2. CM4_RF_CLK_SW set to PLL2(320)
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_WIFI_PLL_320 << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    // Step3. set divider to 1+2/2=2, ->  320/2=160Mhz
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_MCU_DIV_SEL_MASK << CM4_MCU_DIV_SEL_SHIFT);
    reg = reg | (2 << CM4_MCU_DIV_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    // Step4. CM4_HCLK_SW set to PLL_CK
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_PLL << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    return;
}


//
//  Configure CM4 MCU to 64Mhz
//
void cmnCpuClkConfigureTo64M(void)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgCM4CKG = (volatile UINT32 *)TOP_CFG_CM4_CKG_EN0;

    // Step1. Power on PLL1
    cmnPLL1ON();

    // Step2. CM4_RF_CLK_SW set to XTAL
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_WBTAC_MCU_CK_SEL_MASK << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    reg = reg | (CM4_WBTAC_MCU_CK_SEL_XTAL << CM4_WBTAC_MCU_CK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);

    while (reg != cmnReadRegister32(pTopCfgCM4CKG));

    // Step3. CM4_HCLK_SW set to SYS_64M
    reg = cmnReadRegister32(pTopCfgCM4CKG);
    reg = reg & ~(CM4_HCLK_SEL_MASK << CM4_HCLK_SEL_SHIFT);
    reg = reg | (CM4_HCLK_SEL_SYS_64M << CM4_HCLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgCM4CKG, reg);
    return;
}

#else /*the following is E2 clock configuration,modified by zhanguo*/

//
//  Using Xtal as SPI Flash clock
//
ATTR_TEXT_IN_TCM void cmnSerialFlashClkConfToXtal(void)
{
    volatile UINT32 reg;
    volatile UINT32 *pTopCfgHclk = (volatile UINT32 *)TOP_CFG_HCLK_2M_CKGEN;

    reg = cmnReadRegister32(pTopCfgHclk);
    reg = reg & ~(SF_TOP_CLK_SEL_MASK << SF_TOP_CLK_SEL_SHIFT);
    reg = reg | (SF_TOP_CLK_SEL_XTAL << SF_TOP_CLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgHclk, reg);
}

#ifdef HAL_FLASH_MODULE_ENABLED
//
//  Using PLL1/64M as SPI Flash clock
//
ATTR_TEXT_IN_TCM void cmnSerialFlashClkConfTo64M(void)
{
    volatile UINT32 reg = 0;
    volatile UINT32 *pTopCfgHclk = (volatile UINT32 *)TOP_CFG_HCLK_2M_CKGEN;

    //open PLL1
    cmnPLL1ON();

    // Switch flash clock from XTAL to SYS 64Mhz.
    reg = cmnReadRegister32(pTopCfgHclk);
    reg = reg & ~(SF_TOP_CLK_SEL_MASK << SF_TOP_CLK_SEL_SHIFT);
    reg = reg | (SF_TOP_CLK_SEL_SYS_64M << SF_TOP_CLK_SEL_SHIFT);
    cmnWriteRegister32(pTopCfgHclk, reg);

#if 1 /*set KGD value*/
    mSetHWEntry(SFC_MISC1_DEL_LATCH_LATENCY, 0);
    mSetHWEntry(SFC_MISC1_SMPCK_INV, 1);
    mSetHWEntry(SFC_DELAY_CONTROL3_SFCK_SAM_DLY, 0x18);
#endif
    return;
}
#endif

#endif


