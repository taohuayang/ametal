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
 * \brief ZLG TRNG �û������ļ�
 * \sa am_hwconf_zlg118_trng.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_zlg118.h"
#include "am_zlg118_trng.h"
#include "hw/amhw_zlg118_trng.h"
#include "zlg118_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg118_trng
 * \copydoc am_hwconf_zlg118_trng.c
 * @{
 */

/**
 * \brief TRNG ƽ̨��ʼ��
 */
void __zlg118_plfm_trng_init (void)
{
    /* ����TRNGʱ�� */
    am_clk_enable (CLK_RNG);
}

/**
 * \brief TRNG ƽ̨ȥ��ʼ��
 */
void __zlg118_plfm_trng_deinit (void)
{
    /* �ر�TRNGʱ�� */
    am_clk_disable (CLK_RNG);
}

/** \brief TRNG �豸��Ϣ */
static const am_zlg118_trng_devinfo_t __g_trng_devinfo =
{
    /**< \brief ָ��TRNG�Ĵ������ָ�� */
    ZLG118_TRNG_BASE,

    /**
     * \brief TRNG ������λ����
     *
     * \note : �ο�amhw_zlg118_trng.h��ö�ٶ��壺RNG ��������λ����
     */
    AMHW_ZLG118_TRNG_CNT_256,

    /**< \brief trngƽ̨��ʼ������ */
    __zlg118_plfm_trng_init,

    /**< \brief trngƽ̨���ʼ������  */
    __zlg118_plfm_trng_deinit,
};

/** \brief TRNG�豸ʵ�� */
static am_zlg118_trng_dev_t __g_trng_dev;

/** \brief TRNG ʵ����ʼ�������TRNG��׼������ */
am_trng_handle_t am_zlg118_trng_inst_init (void)
{
    return am_zlg118_trng_init(&__g_trng_dev, &__g_trng_devinfo);
}

/** \brief TRNG ʵ�����ʼ�� */
void am_zlg118_trng_inst_deinit (am_trng_handle_t handle)
{
    am_zlg118_trng_deinit(handle);
}

/**
 * @}
 */

/* end of file */
