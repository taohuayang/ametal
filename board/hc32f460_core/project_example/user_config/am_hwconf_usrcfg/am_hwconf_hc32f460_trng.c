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
 * \brief HC32F460 TRNG �û������ļ�
 * \sa am_hwconf_hc32f460_trng.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-26
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_trng.h"
#include "hw/amhw_hc32f460_trng.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_trng
 * \copydoc am_hwconf_hc32f460_trng.c
 * @{
 */

/**
 * \brief TRNG ƽ̨��ʼ��
 */
void __hc32f460_plfm_trng_init (void)
{
    /** \brief ����TRNGʱ�� */
    am_clk_enable (CLK_TRNG);
}

/**
 * \brief TRNG ƽ̨ȥ��ʼ��
 */
void __hc32f460_plfm_trng_deinit (void)
{
    /** \brief �ر�TRNGʱ�� */
    am_clk_disable (CLK_TRNG);
}

/** \brief TRNG �豸��Ϣ */
static const am_hc32f460_trng_devinfo_t __g_trng_devinfo =
{
    /** \brief trng�Ĵ��������ַ  */
    HC32F460_TRNG_BASE,

    /**
     * \brief TRNG ������λ����
     */
    AMHW_HC32F460_TRNG_CNT_256,

    /** \brief trngƽ̨��ʼ������ */
    __hc32f460_plfm_trng_init,

    /** \brief trngƽ̨���ʼ������  */
    __hc32f460_plfm_trng_deinit,
};

/** \brief TRNG�豸ʵ�� */
static am_hc32f460_trng_dev_t __g_trng_dev;

/** \brief TRNG ʵ����ʼ�������TRNG��׼������ */
am_trng_handle_t am_hc32f460_trng_inst_init (void)
{
    return am_hc32f460_trng_init(&__g_trng_dev, &__g_trng_devinfo);
}

/** \brief TRNG ʵ�����ʼ�� */
void am_hc32f460_trng_inst_deinit (am_trng_handle_t handle)
{
    am_hc32f460_trng_deinit(handle);
}

/**
 * @}
 */

/* end of file */
