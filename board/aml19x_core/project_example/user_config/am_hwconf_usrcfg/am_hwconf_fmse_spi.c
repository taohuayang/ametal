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
 * \brief ��ȫоƬFMSE A03 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-03  yrz, first implementation.
 * \endinternal
 */

#include "hc32_pin.h"
#include "am_fmse_a03.h"
#include "am_fmse_spi.h"
#include "am_common.h"
#include "am_hc32l19x_inst_init.h"

/** \brief ��ȫоƬFMSE A03 �豸��Ϣʵ�� */
am_const am_local am_fmse_spi_devinfo_t __g_fmse_spi_devinfo = {
    PIOB_12,
    2000000
};

/** \breif ��ȫоƬFMSE A03 �豸�ṹ�嶨�� */
am_local struct am_fmse_spi_dev __g_fmse_spi_dev;

/** \brief ��ȫоƬFMSE A03 �豸ʵ���� */
am_fmse_handle_t am_fmse_spi_inst_init (void)
{
    return am_fmse_spi_init(&__g_fmse_spi_dev,
                            &__g_fmse_spi_devinfo,
                             am_hc32_spi1_poll_inst_init());
}

/** \brief ��ȫоƬFMSE A03 ʵ�����ʼ�� */
am_err_t am_fmse_spi_inst_deinit (am_fmse_handle_t handle)
{
    return am_fmse_spi_deinit(handle);
}

/* end of file */
