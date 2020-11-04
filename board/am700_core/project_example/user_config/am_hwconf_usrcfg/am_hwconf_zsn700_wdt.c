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
 * \brief ZSN700 WDT �û������ļ�
 * \sa am_hwconf_zsn700_wdt.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10
 * \endinternal
 */

#include "am_zsn700_wdt.h"
#include "am_zsn700.h"
#include "am_zsn700_clk.h"
#include "hw/amhw_zsn700_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_zsn700_wdt
 * \copydoc am_hwconf_zsn700_wdt.c
 * @{
 */

/** \brief WDT ƽ̨��ʼ�� */
static void __zsn700_wdt_plfm_init (void)
{
    am_clk_enable(CLK_WDT);
}

/** \brief ���WDT ƽ̨��ʼ�� */
static void __zsn700_wdt_plfm_deinit (void)
{
    am_clk_disable(CLK_WDT);
}

/** \brief WDT �豸��Ϣ */
static const am_zsn700_wdt_devinfo_t  __g_wdt_devinfo = {
    ZSN700_WDT_BASE,          /**< \brief WDT�Ĵ�����ַ */
    CLK_WDT,                  /**< \brief ʱ��ID */
    __zsn700_wdt_plfm_init,   /**< \brief WDT ƽ̨��ʼ�� */
    __zsn700_wdt_plfm_deinit, /**< \brief ���WDT ƽ̨��ʼ�� */
};

/** \brief WDT�豸ʵ�� */
static am_zsn700_wdt_dev_t __g_wdt_dev;

/**
 * \brief WDT ʵ����ʼ�������WDT��׼������
 */
am_wdt_handle_t am_zsn700_wdt_inst_init (void)
{
    return am_zsn700_wdt_init(&__g_wdt_dev, &__g_wdt_devinfo);
}

/**
 * \brief WDT ʵ�����ʼ��
 */
void am_zsn700_wdt_inst_deinit (am_wdt_handle_t handle)
{
    am_zsn700_wdt_deinit(handle);
}

/**
 * @}
 */

/* end of file */
