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
 * \brief ZLG116 WWDT �û������ļ�
 * \sa am_hwconf_zlg116_iwdg.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  sss, first implementation.
 * \endinternal
 */

#include "am_zlg116.h"
#include "hw/amhw_zlg116_rcc.h"
#include "am_zlg_iwdg.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_iwdg
 * \copydoc am_hwconf_zlg116_iwdg.c
 * @{
 */

/** \brief WWDT ƽ̨��ʼ�� */
static void __zlg_iwdg_plfm_init (void)
{

    /* ��鸴λ�Ƿ��ɿ��Ź���ɵ� */
    if (amhw_zlg116_rcc_reset_flag() & AMHW_ZLG116_RCC_AHB_IWDGRSTF) {
        amhw_zlg116_rcc_reset_flag_clear();
    }

    amhw_zlg116_rcc_lsi_enable();

    while (amhw_zlg116_rcc_lsirdy_read() == AM_FALSE);
}

/** \brief ���WWDT ƽ̨��ʼ�� */
static void __zlg_iwdg_plfm_deinit (void)
{

}

/** \brief WWDT �豸��Ϣ */
static const am_zlg_iwdg_devinfo_t  __g_iwdg_devinfo = {
    ZLG116_IWDG_BASE,       /**< \brief WWDT �Ĵ�����ַ */
    __zlg_iwdg_plfm_init,   /**< \brief WWDT ƽ̨��ʼ�� */
    __zlg_iwdg_plfm_deinit, /**< \brief ���WWDT ƽ̨��ʼ�� */
};

/** \brief WWDT �豸ʵ�� */
static am_zlg_iwdg_dev_t __g_iwdg_dev;

/**
 * \brief WWDT ʵ����ʼ�������WDT��׼������
 */
am_wdt_handle_t am_zlg116_iwdg_inst_init (void)
{
    return am_zlg_iwdg_init(&__g_iwdg_dev, &__g_iwdg_devinfo);
}

/**
 * \brief WWDT ʵ�����ʼ��
 */
void am_zlg116_iwdg_inst_deinit (am_wdt_handle_t handle)
{
    am_zlg_iwdg_deinit(handle);
}

/**
 * @}
 */

/* end of file */
