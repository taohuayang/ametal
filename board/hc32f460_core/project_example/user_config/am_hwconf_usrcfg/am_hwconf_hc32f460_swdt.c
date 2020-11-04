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
 * \brief HC32F460 SWDT �û������ļ�
 * \sa am_hwconf_hc32f460_swdt.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

#include "am_hc32f460.h"
#include "hc32f460_icg.h"
#include "am_hc32f460_swdt.h"
/**
 * \addtogroup am_if_src_hwconf_hc32f460_swdt
 * \copydoc am_hwconf_hc32f460_swdt.c
 * @{
 */


/** \brief SWDT ƽ̨��ʼ�� */
static void __hc32f460_swdt_plfm_init (void)
{

}

/** \brief ���SWDT ƽ̨��ʼ�� */
static void __hc32f460_swdt_plfm_deinit (void)
{

}

/** \brief SWDT �豸��Ϣ */
static const am_hc32f460_swdt_devinfo_t  __g_swdt_devinfo = {
    HC32F460_SWDT_BASE,          /**< \brief SWDT�Ĵ�����ַ */
    CLK_SWDTCLK,                 /**< \brief ʱ��ID */
    INUM_SWDT,                   /**< \brief �ж�ID */
    HC32F460_ICG0_SWDT_ITS,      /**< \brief �����¼����ͣ��ж�/��λ�� */
    __hc32f460_swdt_plfm_init,   /**< \brief SWDT ƽ̨��ʼ�� */
    __hc32f460_swdt_plfm_deinit, /**< \brief ���SWDT ƽ̨��ʼ�� */
};

/** \brief SWDT�豸ʵ�� */
am_hc32f460_swdt_dev_t __g_swdt_dev;

/**
 * \brief SWDT ʵ����ʼ�������WDT��׼������
 */
am_wdt_handle_t am_hc32f460_swdt_inst_init (void)
{
    return am_hc32f460_swdt_init(&__g_swdt_dev, &__g_swdt_devinfo);
}

/**
 * \brief SWDT ʵ�����ʼ��
 */
void am_hc32f460_swdt_inst_deinit (am_wdt_handle_t handle)
{
    am_hc32f460_swdt_deinit(handle);
}

/**
 * @}
 */

/* end of file */
