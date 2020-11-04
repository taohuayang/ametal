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
 * \sa am_hwconf_zlg118_aes.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_zlg118.h"
#include "am_zlg118_aes.h"
#include "hw/amhw_zlg118_aes.h"
#include "zlg118_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg118_aes
 * \copydoc am_hwconf_zlg118_aes.c
 * @{
 */

/**
 * \brief AES ƽ̨��ʼ��
 */
void __zlg118_plfm_aes_init (void)
{
    /* ����AES�� */
    am_clk_enable(CLK_AES);
}

/**
 * \brief AES ƽ̨ȥ��ʼ��
 */
void __zlg118_plfm_aes_deinit (void)
{
    /* �ر�AESʱ�� */
    am_clk_disable(CLK_AES);
}

/** \brief AES �豸��Ϣ */
static const am_zlg118_aes_devinfo_t __g_aes_devinfo =
{
    /**< \brief ָ��aes�Ĵ������ָ�� */
    ZLG118_AES_BASE,

    /**< \brief aesƽ̨��ʼ������ */
    __zlg118_plfm_aes_init,

    /**< \brief aesƽ̨���ʼ������  */
    __zlg118_plfm_aes_deinit,
};

/** \brief AES�豸ʵ�� */
static am_zlg118_aes_dev_t __g_aes_dev;

/** \brief AES ʵ����ʼ�������AES��׼������ */
am_aes_handle_t am_zlg118_aes_inst_init (void)
{
    return am_zlg118_aes_init(&__g_aes_dev, &__g_aes_devinfo);
}

/** \brief AES ʵ�����ʼ�� */
void am_zlg118_aes_inst_deinit (am_aes_handle_t handle)
{
    am_zlg118_aes_deinit(handle);
}

/**
 * @}
 */

/* end of file */
