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
 * \brief ������ MPL3115A2 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-11  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_mpl3115a2.h"
#include "am_common.h"
#include "zlg116_pin.h"
#include "am_zlg116_inst_init.h"

/** \brief ������ MPL3115A2 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_mpl3115a2_devinfo __g_mpl3115a2_info = {
    PIOB_0,                     /*< \brief �������Ŷ���    */
    0x60,                       /*< \breif MPL3115A2 I2C��ַ */
    am_zlg116_i2c1_inst_init,   /*< \brief I2C����ʵ����ʼ������ */
    am_zlg116_i2c1_inst_deinit, /*< \brief I2C���ʼ������ */
};

/** \breif ������ MPL3115A2 �豸�ṹ�嶨�� */
am_local struct am_sensor_mpl3115a2_dev __g_mpl3115a2_dev;

/** \brief ������ MPL3115A2 �豸ʵ���� */
am_sensor_handle_t am_sensor_mpl3115a2_inst_init (void)
{
    return am_sensor_mpl3115a2_init(&__g_mpl3115a2_dev,
                                    &__g_mpl3115a2_info,
                                    am_zlg116_i2c1_inst_init());
}

/** \brief ������ MPL3115A2 ʵ�����ʼ�� */
am_err_t am_sensor_mpl3115a2_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_mpl3115a2_deinit(handle);
}

/* end of file */
