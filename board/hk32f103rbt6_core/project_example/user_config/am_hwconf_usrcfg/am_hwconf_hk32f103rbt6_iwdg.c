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
 * \brief HK32F103RBT6 IWDG �û������ļ�
 * \sa am_hwconf_hk32f103rbt6_iwdg.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

#include "am_hk32f103rbt6.h"
#include "am_hk32f103rbt6_iwdg.h"
#include "amhw_hk32f103rbt6_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_iwdg
 * \copydoc am_hwconf_hk32f103rbt6_iwdg.c
 * @{
 */

/** \brief IDWG ƽ̨��ʼ�� */
static void __hk32f103rbt6_iwdg_plfm_init (void)
{

    /* ��鸴λ�Ƿ��ɿ��Ź���ɵ� */
    if (amhw_hk32f103rbt6_rcc_reset_flag() & AMHW_HK32F103RBT6_RCC_CSR_IWDGRSTF) {
        amhw_hk32f103rbt6_rcc_reset_flag_clear();
    }

    amhw_hk32f103rbt6_rcc_lsi_enable();

    while (amhw_hk32f103rbt6_rcc_lsirdy_read() == AM_FALSE);
}

/** \brief ��� IWDG ƽ̨��ʼ�� */
static void __hk32f103rbt6_iwdg_plfm_deinit (void)
{
}

/** \brief IWDG �豸��Ϣ */
static const am_hk32f103rbt6_iwdg_devinfo_t __g_iwdg_devinfo = {
    HK32F103RBT6_IWDG_BASE,          /**< \brief IWDG �Ĵ�����ַ */
    __hk32f103rbt6_iwdg_plfm_init,    /**< \brief IWDG ƽ̨��ʼ�� */
    __hk32f103rbt6_iwdg_plfm_deinit,  /**< \brief ���IWDG ƽ̨��ʼ�� */
};

/** \brief IWDG�豸ʵ�� */
static am_hk32f103rbt6_iwdg_dev_t __g_iwdg_dev;

/**
 * \brief IWDG ʵ����ʼ�������IWDG��׼������
 */
am_wdt_handle_t am_hk32f103rbt6_iwdg_inst_init (void)
{
    return am_hk32f103rbt6_iwdg_init(&__g_iwdg_dev, &__g_iwdg_devinfo);
}

/**
 * \brief IWDG ʵ�����ʼ��
 */
void am_hk32f103rbt6_iwdg_inst_deinit (am_wdt_handle_t handle)
{
    am_hk32f103rbt6_iwdg_deinit(handle);
}

/**
 * @}
 */

/* end of file */
