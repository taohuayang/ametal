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
 * \brief HC32F460 HASH �û������ļ�
 * \sa am_hwconf_hc32f460_hash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_hash.h"
#include "hw/amhw_hc32f460_hash.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_hash
 * \copydoc am_hwconf_hc32f460_hash.c
 * @{
 */

/**
 * \brief HASH ƽ̨��ʼ��
 */
static void __hc32f460_plfm_hash_init (void)
{
    /* ����HASH�� */
    am_clk_enable(CLK_HASH);
}

/**
 * \brief HASH ƽ̨ȥ��ʼ��
 */
static void __hc32f460_plfm_hash_deinit (void)
{
    /* �ر�HASHʱ�� */
    am_clk_disable(CLK_HASH);
}

/** \brief HASH �豸��Ϣ */
static const am_hc32f460_hash_devinfo_t __g_hash_devinfo =
{
    /** \brief ָ��hash�Ĵ������ָ�� */
    HC32F460_HASH_BASE,

    /** \brief hashƽ̨��ʼ������ */
    __hc32f460_plfm_hash_init,

    /** \brief hashƽ̨���ʼ������  */
    __hc32f460_plfm_hash_deinit,
};

/** \brief HASH�豸ʵ�� */
static am_hc32f460_hash_dev_t __g_hash_dev;

/** \brief HASH ʵ����ʼ�������HASH��׼������ */
am_hash_handle_t am_hc32f460_hash_inst_init (void)
{
    return am_hc32f460_hash_init(&__g_hash_dev, &__g_hash_devinfo);
}

/** \brief HASH ʵ�����ʼ�� */
void am_hc32f460_hash_inst_deinit (am_hash_handle_t handle)
{
    am_hc32f460_hash_deinit(handle);
}

/**
 * @}
 */

/* end of file */
