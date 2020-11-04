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
 * \brief IWDG������ӿ�
 * \internal
 * \par Modification history
 * - 1.00 15-07-10  sss, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_stm32f103rbt6_iwdg.h"
#include "hw/amhw_stm32f103rbt6_iwdg.h"

/****************************************************************************
 * Functions Declaration
 ***************************************************************************/

static int __iwdg_feed (void *p_drv);
static int __iwdg_enable (void *p_drv, uint32_t timeout);
static int __iwdg_info_get (void *p_drv, am_wdt_info_t *p_info);

/** \brief ���Ź���׼�������ṹ�� */
static const struct am_wdt_drv_funcs __g_iwdg_drv_funcs = {
    __iwdg_info_get,
    __iwdg_enable,
    __iwdg_feed
};

/** \brief ��ȡ���Ź���Ϣ */
static int __iwdg_info_get (void *p_drv, am_wdt_info_t *p_info)
{
    uint32_t wdt_freq      = 40000;
    uint32_t wdt_freq_max  = wdt_freq / 4;
    uint32_t wdt_freq_min  = wdt_freq / 256;

    p_info->min_timeout_ms = 1 * 1000 / wdt_freq_max + 1;
    p_info->max_timeout_ms = (uint64_t)(0xFFF + 1) * 1000 /
                             (uint64_t)wdt_freq_min  ;

    return AM_OK;
}

/** \brief ι������ */
static int __iwdg_feed (void *p_drv)
{
    am_stm32f103rbt6_iwdg_dev_t *p_dev     = (am_stm32f103rbt6_iwdg_dev_t *)p_drv;
    amhw_stm32f103rbt6_iwdg_t   *p_hw_iwdg =
                           (amhw_stm32f103rbt6_iwdg_t *)p_dev->p_devinfo->iwdg_regbase;

    amhw_stm32f103rbt6_iwdg_keyvalue_set(p_hw_iwdg, 0xAAAA);

    return AM_OK;
}

/** \brief ���ó�ʱʱ�䲢�������Ź� */
static int __iwdg_enable (void *p_drv, uint32_t timeout_ms)
{
    am_stm32f103rbt6_iwdg_dev_t *p_dev     = (am_stm32f103rbt6_iwdg_dev_t *)p_drv;
    amhw_stm32f103rbt6_iwdg_t   *p_hw_iwdg =
                           (amhw_stm32f103rbt6_iwdg_t *)p_dev->p_devinfo->iwdg_regbase;

    uint32_t wdt_freq = 40000;
    uint32_t ticks;
    uint32_t div = 1;

    ticks = (uint64_t) (timeout_ms) * wdt_freq / 1000;

    div = ticks / 0xFFF + 1;

    amhw_stm32f103rbt6_iwdg_keyvalue_set(p_hw_iwdg, 0x5555);
    while(amhw_stm32f103rbt6_iwdg_status_get(p_hw_iwdg) & 0x1ul);

    if (div <= 4) {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 0);
        p_dev->div = 4;
    } else if (div <= 8) {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 1);
        p_dev->div = 8;
    } else if (div <= 16) {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 2);
        p_dev->div = 16;
    } else if (div <= 32) {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 3);
        p_dev->div = 32;
    } else if (div <= 64) {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 4);
        p_dev->div = 64;
    } else if (div <= 128) {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 5);
        p_dev->div = 128;
    } else {
        amhw_stm32f103rbt6_iwdg_div_set (p_hw_iwdg, 6);
        p_dev->div = 256;
    }

    wdt_freq /= p_dev->div;
    ticks = (uint64_t) (timeout_ms) * wdt_freq / 1000;

    amhw_stm32f103rbt6_iwdg_keyvalue_set(p_hw_iwdg, 0x5555);
    while(amhw_stm32f103rbt6_iwdg_status_get(p_hw_iwdg) & 0x2ul);
    amhw_stm32f103rbt6_iwdg_reload_set (p_hw_iwdg, ticks);

    /* �������Ź� */
    amhw_stm32f103rbt6_iwdg_keyvalue_set(p_hw_iwdg, 0xAAAA);
    amhw_stm32f103rbt6_iwdg_keyvalue_set(p_hw_iwdg, 0xCCCC);

    return AM_OK;
}

/** \brief ��ʼ��IWDG����ȡ��׼������ */
am_wdt_handle_t am_stm32f103rbt6_iwdg_init (am_stm32f103rbt6_iwdg_dev_t           *p_dev,
                                  const am_stm32f103rbt6_iwdg_devinfo_t *p_devinfo)
{
    if (p_devinfo == NULL) {
        return NULL;
    }

    p_dev->p_devinfo        = p_devinfo;
    p_dev->wdt_serv.p_funcs = (struct am_wdt_drv_funcs *)&__g_iwdg_drv_funcs;
    p_dev->wdt_serv.p_drv   = p_dev;
    p_dev->div              = 4;

    /* ���Ź�ƽ̨��ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    return &(p_dev->wdt_serv);
}

/** \brief IWDG���ʼ�� */
void am_stm32f103rbt6_iwdg_deinit (am_wdt_handle_t handle)
{
    am_stm32f103rbt6_iwdg_dev_t *p_dev = (am_stm32f103rbt6_iwdg_dev_t *)handle;

    if (NULL == p_dev) {
        return ;
    }

    p_dev->p_devinfo = NULL;

    p_dev->wdt_serv.p_funcs = NULL;
    p_dev->wdt_serv.p_drv   = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
