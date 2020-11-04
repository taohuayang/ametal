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
 * \brief ������ BMG160 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-11  wk, first implementation.
 * \endinternal
 */
 
#include "am_sensor_bmg160.h"
#include "am_common.h"
#include "zlg116_pin.h"
#include "am_zlg116_inst_init.h"

/** \brief ������ BMG160 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_bmg160_devinfo __g_bmg160_info = {
        PIOB_0,            /*< \brief �������Ŷ��� */
        0x68               /*< \breif BMG160 I2C��ַ */
};

/** \breif ������ BMG160 �豸�ṹ�嶨�� */
am_local struct am_sensor_bmg160_dev __g_bmg160_dev;

/** \brief ������ BMG160 �豸ʵ���� */
am_sensor_handle_t am_sensor_bmg160_inst_init (void)
{
    return am_sensor_bmg160_init(&__g_bmg160_dev,
                                 &__g_bmg160_info,
                                 am_zlg116_i2c1_inst_init());
}

/** \brief ������ BMG160 ʵ�����ʼ�� */
am_err_t am_sensor_bmg160_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_bmg160_deinit(handle);
}

/* end of file */
