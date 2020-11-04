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
 * \brief HC32F460 WDT �û������ļ�
 * \sa am_hwconf_hc32f460_wdt.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

#include "am_hc32f460_wdt.h"
#include "am_hc32f460.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_wdt
 * \copydoc am_hwconf_hc32f460_wdt.c
 * @{
 */

/** \brief WDT ƽ̨��ʼ�� */
static void __hc32f460_wdt_plfm_init (void)
{

}

/** \brief ���WDT ƽ̨��ʼ�� */
static void __hc32f460_wdt_plfm_deinit (void)
{

}

/** \brief WDT �豸��Ϣ */
static const am_hc32f460_wdt_devinfo_t  __g_wdt_devinfo = {
    HC32F460_WDT_BASE,          /**< \brief WDT�Ĵ�����ַ */
    CLK_PCLK3,                  /**< \brief ʱ��ID */
    INUM_WDT,                   /**< \brief �ж�ID */

    /** \brief ˢ�´���/�����������¼����ͣ��ж�/��λ�� */
    AM_HC32F460_WDT_TRIGGER_EVENT_REQUEST_RESET,

    /** \brief WDT��sleepģʽ�¼�����ֹ/��� */
    AM_HC32F460_WDT_SLEEPOFF,

    /** \brief ˢ���������� */
    AM_HC32F460_WDT_REFRESH_RANGE_100,
    __hc32f460_wdt_plfm_init,   /**< \brief WDT ƽ̨��ʼ�� */
    __hc32f460_wdt_plfm_deinit, /**< \brief ���WDT ƽ̨��ʼ�� */
};

/** \brief WDT�豸ʵ�� */
am_hc32f460_wdt_dev_t __g_wdt_dev;

/**
 * \brief WDT ʵ����ʼ�������WDT��׼������
 */
am_wdt_handle_t am_hc32f460_wdt_inst_init (void)
{
    return am_hc32f460_wdt_init(&__g_wdt_dev, &__g_wdt_devinfo);
}

/**
 * \brief WDT ʵ�����ʼ��
 */
void am_hc32f460_wdt_inst_deinit (am_wdt_handle_t handle)
{
    am_hc32f460_wdt_deinit(handle);
}

/**
 * @}
 */

/* end of file */
