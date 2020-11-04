/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief CLK implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */

#include "am_zsn700_clk.h"
#include "ametal.h"
#include "am_zsn700_flash.h"
#include "zsn700_periph_map.h"
#include "hw/amhw_zsn700_rcc.h"
#include "hw/amhw_zsn700_rcc_reset.h"
#include "zsn700_clk.h"
#include "hw/amhw_zsn700_lpmode.h"
#include "am_zsn700_lpmode.h"


am_zsn700_clk_dev_t    *__gp_clk_dev;
am_zsn700_lpmode_dev_t  __g_lpmode_dev;

static void __rcc_unlock (void)
{
    amhw_zsn700_rcc_set_start(0x5A5A);
    amhw_zsn700_rcc_set_start(0xA5A5);
}

/**
 * \brief ��ȡʱ��Ƶ��
 */
int am_clk_rate_get (am_clk_id_t clk_id)
{
    int clk = 0;
    int peri, num;

    num  = clk_id >> CLK_PCLK;
    peri = clk_id & 0xff;

    switch (num) {

        /* ϵͳ��ʼ��� ʱ�� */
        case 0:

            switch(peri) {

                /* XTH�ⲿ����ʱ�� */
                case 0:
                    clk = __gp_clk_dev->p_devinfo->xth_osc;
                    break;

                /* XTL�ⲿ����ʱ�� */
                case 1:
                    clk = __gp_clk_dev->p_devinfo->xtl_osc;
                    break;

                /* RCH�ڲ�����ʱ��*/
                case 2:
                    /* �ж��ڲ�����ʱ���Ƿ�ʹ�ܣ���ʹ��*/
                    if(amhw_zsn700_rcc_rch_enable_get()) {

                        if(amhw_zsn700_rcc_rch_trim_get() ==
                           (*((uint16_t*)0x00100C00))) {
                            clk = 24000000;
                        } else if(amhw_zsn700_rcc_rch_trim_get() ==
                                  (*((uint16_t*)0x00100C02))) {
                            clk = 22120000;
                        } else if(amhw_zsn700_rcc_rch_trim_get() ==
                                  (*((uint16_t*)0x00100C04))) {
                            clk = 16000000;
                        } else if(amhw_zsn700_rcc_rch_trim_get() ==
                                  (*((uint16_t*)0x00100C06))) {
                            clk = 8000000;
                        } else if(amhw_zsn700_rcc_rch_trim_get() ==
                                  (*((uint16_t*)0x00100C08))) {
                            clk = 4000000;
                        }
                    } else {
                        clk = 0;
                    }
                    break;

                /* RCL�ڲ�����ʱ��*/
                case 3:

                    /* �ж��ڲ�����ʱ���Ƿ�ʹ�ܣ���ʹ��*/
                    if(amhw_zsn700_rcc_rcl_enable_get()) {

                        if(amhw_zsn700_rcc_rcl_trim_get() ==
                           (*((uint16_t*)0x00100C20))) {
                            clk = 38400;
                        } else {
                            clk = 32768;
                        }
                    } else {
                        clk = 0;
                    }
                    break;

                /* PLL����ʱ�� */
                case 4:
                    clk = __gp_clk_dev->pllin_clk;
                    break;

                /* PLL���ʱ�� */
                case 5:
                    clk = __gp_clk_dev->pllout_clk;
                    break;

                /* SYSʱ��*/
                case 6:
                    clk = __gp_clk_dev->sys_clk;
                    break;

                /* HCLK��ʱ��*/
                case 7:
                    clk = __gp_clk_dev->hclk;
                    break;

                /* PCLK����ʱ��*/
                case 8:
                    clk = __gp_clk_dev->pclk;
                    break;
                default:
                    clk = 0;
            }
            break;

        /* zsn700��������ʱ�Ӿ�������PCLKʱ���� */
        case 1:
            clk = __gp_clk_dev->pclk;
            break;

        default :
            break;
    }
    return clk;
}

/**
 * \brief ʹ��ָ����ϵͳ������ʱ��
 */
int am_clk_enable (am_clk_id_t clk_id)
{
    int peri;

    peri = clk_id & 0xff;

    /* �ж�����ʱ���Ƿ��Ѿ�ʹ�ܣ���ʹ��ʱ���Ҹ�λʱ�� */
    if(amhw_zsn700_rcc_peripheral_enable_check((amhw_zsn700_peripheral)peri) == 0) {
        amhw_zsn700_rcc_peripheral_enable((amhw_zsn700_peripheral)peri);
        am_zsn700_clk_reset(clk_id);
    }

    return AM_OK;
}

/**
 * \brief ����ָ����ϵͳ������ʱ��
 */
int am_clk_disable (am_clk_id_t clk_id)
{
    int peri;

    peri = clk_id & 0xff;

    amhw_zsn700_rcc_peripheral_disable((amhw_zsn700_peripheral)peri);

    return AM_OK;
}

int am_zsn700_clk_reset (am_clk_id_t clk_id)
{
    int peri;

    peri = clk_id & 0xff;

    amhw_zsn700_rcc_reset((amhw_zsn700_rcc_reset_peripheral)peri);

    amhw_zsn700_rcc_reset_stop((amhw_zsn700_rcc_reset_peripheral)peri);

    return AM_OK;
}

int am_zsn700_clk_update (am_clk_id_t clk_id, int clk)
{
    switch (clk_id) {

    case CLK_PLLIN:
        __gp_clk_dev->pllin_clk = clk;
        break;

    case CLK_PLLOUT:
        __gp_clk_dev->pllout_clk = clk;
        break;

    case CLK_SYSCLK:
        __gp_clk_dev->sys_clk = clk;
        break;

    case CLK_HCLK:
        __gp_clk_dev->hclk = clk;
        break;

    case CLK_PCLK:
        __gp_clk_dev->pclk = clk;
        break;

    default:
        break;
    }

    return AM_OK;
}

const am_zsn700_clk_dev_t *am_zsn700_clk_devinfo_get (void)
{
    if (__gp_clk_dev == NULL)  {
        return NULL;
    }

    return __gp_clk_dev;
}

int am_zsn700_div_get (am_clk_id_t clk_id)
{
    int div = 0;

    if (__gp_clk_dev == NULL)  {
        return -AM_EINVAL;
    }

    switch (clk_id) {

    case CLK_HCLK:
        div =  __gp_clk_dev->p_devinfo->hclk_div;
        break;

    case CLK_PCLK:
        div =  __gp_clk_dev->p_devinfo->pclk_div;
        break;

    default:
        break;
    }

    return div;
}

static void __rcl_enable (amhw_zsn700_rcl_fre_t rcl_clk, uint32_t *sysclk)
{
    if(rcl_clk == AMHW_ZSN700_RCl_FRE_32768Hz) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��32.768KHz��*/
        amhw_zsn700_rcc_rcl_trim_set(*((uint16_t*)rcl_clk));
        *sysclk = 32768;
    } else {

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zsn700_rcc_rcl_trim_set(*((uint16_t*)rcl_clk));
        *sysclk = 38400;
    }

    amhw_zsn700_rcc_rcl_waittime_set(AMHW_ZSN700_RCL_WAITTIME_256);

    __rcc_unlock();
    amhw_zsn700_rcc_rcl_enable();

    /* �ȴ��ȶ�*/
    while(amhw_zsn700_rcc_rcl_state_get() == AM_FALSE);
}

static void __rch_enable (amhw_zsn700_rch_fre_t rch_clk, uint32_t *sysclk)
{
    uint16_t temp      = amhw_zsn700_rcc_rch_trim_get();
    uint32_t trim_addr = 0x00100C08;
    uint32_t trim_set  = 0;
    uint8_t  setnum    = 0;
    uint8_t  i         = 0;

    /* ��ȡ��ǰ��ŵ�Ƶ��У׼ֵ */
    if(temp == (*((uint16_t*)AMHW_ZSN700_RCH_FRE_24MHz))) {
        trim_addr = 0x00100C00;
    } else if(temp == (*((uint16_t*)AMHW_ZSN700_RCH_FRE_22MHz))) {
        trim_addr = 0x00100C02;
    } else if(temp == (*((uint16_t*)AMHW_ZSN700_RCH_FRE_16MHz))) {
        trim_addr = 0x00100C04;
    } else if(temp == (*((uint16_t*)AMHW_ZSN700_RCH_FRE_8MHz))) {
        trim_addr = 0x00100C06;
    } else if(temp == (*((uint16_t*)AMHW_ZSN700_RCH_FRE_4MHz))) {
        trim_addr = 0x00100C08;
    }

    /* ����У׼Ƶ�� */
    trim_set = (uint32_t)rch_clk;
    if(trim_addr == trim_set) {
        amhw_zsn700_rcc_rch_trim_set(*((volatile uint16_t*)trim_set));
    } else if(trim_addr > trim_set){

        setnum   = (trim_addr - trim_set) >> 1;
        trim_set = trim_addr;

        for(i = 0; i < setnum; i++) {
            trim_set = trim_set - 2;
            amhw_zsn700_rcc_rch_trim_set(*((volatile uint16_t*)trim_set));
        }
    } else {

        setnum   = (trim_set - trim_addr) >> 1;
        trim_set = trim_addr;

        for(i = 0; i < setnum; i++) {
            trim_set = trim_set + 2;
            amhw_zsn700_rcc_rch_trim_set(*((uint16_t*)trim_set));
        }
    }

    switch(rch_clk) {
    case AMHW_ZSN700_RCH_FRE_24MHz:
        *sysclk = 24000000;
        break;
    case AMHW_ZSN700_RCH_FRE_22MHz:
        *sysclk = 22120000;
        break;
    case AMHW_ZSN700_RCH_FRE_16MHz:
        *sysclk = 16000000;
        break;
    case AMHW_ZSN700_RCH_FRE_8MHz:
        *sysclk = 8000000;
        break;
    case AMHW_ZSN700_RCH_FRE_4MHz:
        *sysclk = 4000000;
        break;
    }

    __rcc_unlock();
    amhw_zsn700_rcc_rch_enable();

    /* �ȴ��ȶ�*/
    while(amhw_zsn700_rcc_rch_state_get() == AM_FALSE);
}

static void __xth_enable (uint32_t xth_clk, uint32_t *sysclk)
{
    /* �ⲿ������������ѡ�� */
    amhw_zsn700_rcc_xth_xtal_driver_set(AMHW_ZSN700_XTH_XTAL_DRIVER_DEFAULT);

    /* �ⲿ������Ƶ��ѡ�� */
    if((xth_clk >= 4000000) && (xth_clk < 6000000)) {
        amhw_zsn700_rcc_xth_xtal_fre_set(AMHW_ZSN700_XTH_XTAL_FRE_4_6);
    } else if((xth_clk >= 6000000) && (xth_clk < 12000000)) {
        amhw_zsn700_rcc_xth_xtal_fre_set(AMHW_ZSN700_XTH_XTAL_FRE_6_12);
    } else if((xth_clk >= 12000000) && (xth_clk < 20000000)) {
        amhw_zsn700_rcc_xth_xtal_fre_set(AMHW_ZSN700_XTH_XTAL_FRE_12_20);
    } else {
        amhw_zsn700_rcc_xth_xtal_fre_set(AMHW_ZSN700_XTH_XTAL_FRE_20_32);
    }

    /* �ⲿ����ʱ��XTH�ȶ�ʱ��ѡ�� */
    amhw_zsn700_rcc_xth_waittime_set(AMHW_ZSN700_XTH_WAITTIME_16384);

    __rcc_unlock();

    amhw_zsn700_rcc_xth_enable();

    /* �ȴ��ȶ�*/
    while(amhw_zsn700_rcc_xth_state_get() == AM_FALSE);

    *sysclk = xth_clk;
}

static void __xtl_enable (uint32_t xtl_clk, uint32_t *sysclk)
{

    /* �ⲿ������������ѡ�� */
    amhw_zsn700_rcc_xtl_xtal_driver_set(AMHW_ZSN700_XTL_XTAL_DRIVER_DEFAULT);

    /* XTL�����񵴷��ȵĵ��� */
    amhw_zsn700_rcc_xtl_xtal_amplitude_set(AMHW_ZSN700_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

    /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
    amhw_zsn700_rcc_xtl_waittime_set(AMHW_ZSN700_XTL_WAITTIME_16384);

    __rcc_unlock();

    amhw_zsn700_rcc_xtl_enable();

    /* �ȴ��ȶ�*/
    while(amhw_zsn700_rcc_xtl_state_get() == AM_FALSE);

    *sysclk = xtl_clk;
}

static void __pll_enable (am_zsn700_clk_dev_t           *p_dev,
                          const am_zsn700_clk_devinfo_t *p_devinfo)
{
    uint32_t temp;

    /* PLL����ʱ��ѡ�� */
    if(p_devinfo->pllin_src == AMHW_ZSN700_PLL_INPUT_FRE_SRC_XTH_PF00) {
        amhw_zsn700_rcc_pll_input_fre_src_set(AMHW_ZSN700_PLL_INPUT_FRE_SRC_XTH_PF00);
        __xth_enable(p_devinfo->xth_osc, &temp);

    } else if(p_devinfo->pllin_src == AMHW_ZSN700_PLL_INPUT_FRE_SRC_XTH_XTAL) {
        amhw_zsn700_rcc_pll_input_fre_src_set(AMHW_ZSN700_PLL_INPUT_FRE_SRC_XTH_XTAL);
        __xth_enable(p_devinfo->xth_osc, &temp);
    } else {
        amhw_zsn700_rcc_pll_input_fre_src_set(AMHW_ZSN700_PLL_INPUT_FRE_SRC_RCH);
        __rch_enable(p_devinfo->rch_osc, &temp);
    }

    p_dev->pllin_clk  = temp;

    p_dev->pllout_clk = temp * p_devinfo->pll_mul;

    p_dev->sys_clk    = p_dev->pllout_clk;

    /* PLL����Ƶ�ʷ�Χѡ�� */
    if((p_dev->pllin_clk >= 4000000) && (p_dev->pllin_clk < 6000000)) {
        amhw_zsn700_rcc_pll_input_fre_set(AMHW_ZSN700_PLL_INPUT_FRE_4_6);
    } else if((p_dev->pllin_clk >= 6000000) &&
              (p_dev->pllin_clk < 12000000)) {
        amhw_zsn700_rcc_pll_input_fre_set(AMHW_ZSN700_PLL_INPUT_FRE_6_12);
    } else if((p_dev->pllin_clk >= 12000000) &&
              (p_dev->pllin_clk < 20000000)) {
        amhw_zsn700_rcc_pll_input_fre_set(AMHW_ZSN700_PLL_INPUT_FRE_12_20);
    } else {
        amhw_zsn700_rcc_pll_input_fre_set(AMHW_ZSN700_PLL_INPUT_FRE_20_24);
    }

    /* PLL���Ƶ�ʷ�Χѡ�� */
    if((p_dev->pllout_clk >= 8000000) && (p_dev->pllout_clk < 12000000)) {
        amhw_zsn700_rcc_pll_output_fre_set(AMHW_ZSN700_PLL_OUTPUT_FRE_8_12);
    } else if((p_dev->pllout_clk >= 12000000) &&
              (p_dev->pllout_clk < 18000000)) {
        amhw_zsn700_rcc_pll_output_fre_set(AMHW_ZSN700_PLL_OUTPUT_FRE_12_18);
    } else if((p_dev->pllout_clk >= 18000000) &&
              (p_dev->pllout_clk < 24000000)) {
        amhw_zsn700_rcc_pll_output_fre_set(AMHW_ZSN700_PLL_OUTPUT_FRE_18_24);
    } else if((p_dev->pllout_clk >= 24000000) &&
              (p_dev->pllout_clk < 36000000)) {
        amhw_zsn700_rcc_pll_output_fre_set(AMHW_ZSN700_PLL_OUTPUT_FRE_24_36);
    } else {
        amhw_zsn700_rcc_pll_output_fre_set(AMHW_ZSN700_PLL_OUTPUT_FRE_36_48);
    }

    /* PLL��Ƶϵ��ѡ�� */
    amhw_zsn700_rcc_pll_divn_set(p_devinfo->pll_mul);

    /* PLL�ȶ�ʱ��ѡ�� */
    amhw_zsn700_rcc_pll_waittime_set(AMHW_ZSN700_PLL_WAITTIME_16384);

    __rcc_unlock();
    amhw_zsn700_rcc_pll_enable();

    /* �ȴ��ȶ�*/
    while(amhw_zsn700_rcc_pll_state_get() == AM_FALSE);
}

/**
 * \brief CLK ��ʼ��
 */
int am_zsn700_clk_init (am_zsn700_clk_dev_t           *p_dev,
                        const am_zsn700_clk_devinfo_t *p_devinfo)

{
    uint8_t hclk_unit = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }

    p_dev->p_devinfo  = p_devinfo;
    __gp_clk_dev      = p_dev;


    if (p_devinfo->pllin_src == AMHW_ZSN700_PLL_INPUT_FRE_SRC_XTH_PF00) {

        /* CLKƽ̨��ʼ��������ʱ������ */
        if (p_devinfo->pfn_plfm_init) {
            p_devinfo->pfn_plfm_init();
        }
    }

    switch(p_devinfo->sysclk_src) {

    case AMHW_ZSN700_SYSCLK_RCH:

        __rch_enable(p_devinfo->rch_osc,  &p_dev->sys_clk);
        break;

    case AMHW_ZSN700_SYSCLK_XTH:

        __xth_enable(p_devinfo->xth_osc, &p_dev->sys_clk);
        break;

    case AMHW_ZSN700_SYSCLK_RCL:

        __rcl_enable(p_devinfo->rcl_osc,  &p_dev->sys_clk);
        break;

    case AMHW_ZSN700_SYSCLK_XTL:

        __xtl_enable(p_devinfo->xtl_osc,  &p_dev->sys_clk);
        break;

    case AMHW_ZSN700_SYSCLK_PLL:

        __pll_enable(p_dev, p_devinfo);
        break;

    default :
        return AM_ERROR;
    }

    /* ����ϵͳʱ��Դ���� */
    p_dev->sys_type = p_devinfo->sysclk_src;

    if((p_dev->sys_clk) > 24000000) {
        am_zsn700_flash_waitcycle(ZSN700_FLASH,
                                  AMHW_ZSN700_FLASH_READ_WAITTIME_2);
    }

    __rcc_unlock();
    amhw_zsn700_rcc_sys_clk_set(p_devinfo->sysclk_src);

    if((p_dev->sys_clk) <= 24000000) {
            am_zsn700_flash_waitcycle(ZSN700_FLASH,
                                      AMHW_ZSN700_FLASH_READ_WAITTIME_1);
    }

    __rcc_unlock();
    amhw_zsn700_rcc_hclk_set((amhw_zsn700_hclk_src)p_devinfo->hclk_div);

    __rcc_unlock();
    amhw_zsn700_rcc_pclk_set((amhw_zsn700_pclk_src)p_devinfo->pclk_div);

    p_dev->hclk = p_dev->sys_clk / (0x1ul << p_devinfo->hclk_div);
    p_dev->pclk = p_dev->hclk / (0x1ul << p_devinfo->pclk_div);

    hclk_unit = p_dev->hclk / 4000000;

    am_clk_enable(CLK_FLASH);

    am_zsn700_flash_init(ZSN700_FLASH, hclk_unit, AM_TRUE);

    return AM_OK;
}

am_zsn700_lpmode_handle_t am_zsn700_lpmode_init (void)
{
    __g_lpmode_dev.lpmode_mode = AM_ZSN700_LPMODE_MODE_RUN;

    return &__g_lpmode_dev;
}

/**
 * \brief LPMODEģʽ��ϵͳʱ������
 *
 * \param[in] mode LPMODE ģʽ����
 *
 * \retval  AM_OK      ģʽ�л���Ч
 * \retval  AM_ERROR   ģʽ�л�����
 * \retval -AM_EINVAL  ʽ��������
 */
int am_zsn700_lpmode_clk_change (am_zsn700_lpmode_mode_t mode)
{
    switch(mode) {

    /* ֱ�����³�ʼ��CLK���� */
    case AM_ZSN700_LPMODE_MODE_RUN:
        __g_lpmode_dev.lpmode_mode = AM_ZSN700_LPMODE_MODE_RUN;
        amhw_zsn700_lpmode_sevonpend(AM_FALSE);
        amhw_zsn700_lpmode_sleepdeep(AM_FALSE);
        amhw_zsn700_lpmode_sleeponexit(AM_FALSE);
        if(__gp_clk_dev->sys_type == AMHW_ZSN700_SYSCLK_RCL) {
            am_zsn700_clk_init(__gp_clk_dev, __gp_clk_dev->p_devinfo);
            __rcc_unlock();
            amhw_zsn700_rcc_rcl_disable();
        }
        break;

    /* ֱ�����³�ʼ��CLK����,������˯��ģʽ */
    case AM_ZSN700_LPMODE_MODE_SLEEP:
        __g_lpmode_dev.lpmode_mode = AM_ZSN700_LPMODE_MODE_SLEEP;
        amhw_zsn700_lpmode_sevonpend(AM_FALSE);
        amhw_zsn700_lpmode_sleepdeep(AM_FALSE);
        amhw_zsn700_lpmode_sleeponexit(AM_FALSE);
        if(__gp_clk_dev->sys_type == AMHW_ZSN700_SYSCLK_RCL) {
            am_zsn700_clk_init(__gp_clk_dev, __gp_clk_dev->p_devinfo);
            __rcc_unlock();
            amhw_zsn700_rcc_rcl_disable();
        }
        break;
    case AM_ZSN700_LPMODE_MODE_DEEPSLEEP:
        __g_lpmode_dev.lpmode_mode = AM_ZSN700_LPMODE_MODE_DEEPSLEEP;
        amhw_zsn700_lpmode_sevonpend(AM_FALSE);
        amhw_zsn700_lpmode_sleepdeep(AM_FALSE);
        amhw_zsn700_lpmode_sleeponexit(AM_FALSE);

        if((__gp_clk_dev->sys_type != AMHW_ZSN700_SYSCLK_RCL) ||
           (__gp_clk_dev->sys_type != AMHW_ZSN700_SYSCLK_XTL)) {


            __rcl_enable(AMHW_ZSN700_RCl_FRE_32768Hz,  &__gp_clk_dev->sys_clk);

            /* ����ϵͳʱ��Դ���� */
            __gp_clk_dev->sys_type = AMHW_ZSN700_SYSCLK_RCL;

            /* �л�ʱ��Դ */
            __rcc_unlock();
            amhw_zsn700_rcc_sys_clk_set(AMHW_ZSN700_SYSCLK_RCL);

            __gp_clk_dev->hclk = __gp_clk_dev->sys_clk /
                                 (0x1ul << __gp_clk_dev->p_devinfo->hclk_div);
            __gp_clk_dev->pclk = __gp_clk_dev->hclk /
                                 (0x1ul << __gp_clk_dev->p_devinfo->pclk_div);
        }
        break;
    default:
        return -AM_EINVAL;
    }

    return AM_OK;
}

/**
 * \brief ��ȡ LPMODE ģʽ
 *
 * \param[in] ��
 *
 * \return am_zsn700_lpmode_mode_t ��һö�����͵�ֵ
 */
am_zsn700_lpmode_mode_t am_zsn700_lpmode_mode_get (void)
{
    return __g_lpmode_dev.lpmode_mode;
}

/**
 * \brief ���˯��ģʽ
 *
 * \param[in] stata  AM_TRUE  �� ���˳��жϴ�����Զ��ٴν������ߣ�
 *                   AM_FALSE �� ���Ѻ����Զ���������
 *
 * \return ��
 */
void am_zsn700_lpmode_deepsleep (am_bool_t stata)
{
    amhw_zsn700_lpmode_sleepdeep(AM_TRUE);

    if(stata) {
        amhw_zsn700_lpmode_sleeponexit(AM_TRUE);
    } else {
        amhw_zsn700_lpmode_sleeponexit(AM_FALSE);
    }

    amhw_zsn700_lpmode_wfi();

    /* �жϵ��µ�˯�߻��Ѻ���һ�����Ӧ�ôӴ˴���ʼ���л�������ʱ�ӣ����ܱ�֤�������� */
    am_zsn700_lpmode_clk_change(AM_ZSN700_LPMODE_MODE_RUN);
}

/**
 * \brief ��ͨ˯��ģʽ
 *
 * \param[in] stata  AM_TRUE  �� ���˳��жϴ�����Զ��ٴν������ߣ�
 *                   AM_FALSE �� ���Ѻ����Զ���������
 *
 * \return ��
 */
void am_zsn700_lpmode_sleep (am_bool_t stata)
{
    amhw_zsn700_lpmode_sleepdeep(AM_FALSE);

    if(stata) {
        amhw_zsn700_lpmode_sleeponexit(AM_TRUE);
    } else {
        amhw_zsn700_lpmode_sleeponexit(AM_FALSE);
    }

    amhw_zsn700_lpmode_wfi();
}

/* end of file */
