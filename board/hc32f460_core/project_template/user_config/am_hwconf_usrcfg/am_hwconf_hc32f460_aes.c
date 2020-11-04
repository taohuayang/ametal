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
 * \brief HC32F460 aes �û������ļ�
 * \sa am_hwconf_hc32f460_aes.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-26
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_aes.h"
#include "hw/amhw_hc32f460_aes.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_aes
 * \copydoc am_hwconf_hc32f460_aes.c
 * @{
 */

/**
 * \brief AES ƽ̨��ʼ��
 */
void __hc32f460_plfm_aes_init (void)
{
    /* ����AES�� */
    am_clk_enable(CLK_AES);
}

/**
 * \brief AES ƽ̨ȥ��ʼ��
 */
void __hc32f460_plfm_aes_deinit (void)
{
    /* �ر�AESʱ�� */
    am_clk_disable(CLK_AES);
}

/** \brief AES �豸��Ϣ */
static const am_hc32f460_aes_devinfo_t __g_aes_devinfo =
{
    /**< \brief ָ��aes�Ĵ������ָ�� */
    HC32F460_AES_BASE,

    /**< \brief aesƽ̨��ʼ������ */
    __hc32f460_plfm_aes_init,

    /**< \brief aesƽ̨���ʼ������  */
    __hc32f460_plfm_aes_deinit,
};

/** \brief AES�豸ʵ�� */
static am_hc32f460_aes_dev_t __g_aes_dev;

/** \brief AES ʵ����ʼ�������AES��׼������ */
am_aes_handle_t am_hc32f460_aes_inst_init (void)
{
    return am_hc32f460_aes_init(&__g_aes_dev, &__g_aes_devinfo);
}

/** \brief AES ʵ�����ʼ�� */
void am_hc32f460_aes_inst_deinit (am_aes_handle_t handle)
{
    am_hc32f460_aes_deinit(handle);
}

/**
 * @}
 */

/* end of file */
