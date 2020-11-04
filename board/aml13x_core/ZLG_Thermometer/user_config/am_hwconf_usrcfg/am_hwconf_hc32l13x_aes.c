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
 * \brief ZLG aes �û������ļ�
 * \sa am_hwconf_hc32_aes.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32_aes.h"
#include "hw/amhw_hc32_aes.h"
#include "hc32x3x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_aes
 * \copydoc am_hwconf_hc32_aes.c
 * @{
 */

/**
 * \brief AES ƽ̨��ʼ��
 */
void __hc32_plfm_aes_init (void)
{
    /* ����AES�� */
    am_clk_enable(CLK_AES);
}

/**
 * \brief AES ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_aes_deinit (void)
{
    /* �ر�AESʱ�� */
    am_clk_disable(CLK_AES);
}

/** \brief AES �豸��Ϣ */
static const am_hc32_aes_devinfo_t __g_aes_devinfo =
{
    /**< \brief ָ��aes�Ĵ������ָ�� */
    HC32_AES_BASE,

    /**< \brief aesƽ̨��ʼ������ */
    __hc32_plfm_aes_init,

    /**< \brief aesƽ̨���ʼ������  */
    __hc32_plfm_aes_deinit,
};

/** \brief AES�豸ʵ�� */
static am_hc32_aes_dev_t __g_aes_dev;

/** \brief AES ʵ����ʼ�������AES��׼������ */
am_aes_handle_t am_hc32_aes_inst_init (void)
{
    return am_hc32_aes_init(&__g_aes_dev, &__g_aes_devinfo);
}

/** \brief AES ʵ�����ʼ�� */
void am_hc32_aes_inst_deinit (am_aes_handle_t handle)
{
    am_hc32_aes_deinit(handle);
}

/**
 * @}
 */

/* end of file */
