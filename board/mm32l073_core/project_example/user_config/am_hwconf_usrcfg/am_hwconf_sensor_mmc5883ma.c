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
 * \brief ������ MMC5883MA �����ļ�
 * 
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-30  wk, first implementation
 * \endinternal
 */
 
#include "am_sensor_mmc5883ma.h"
#include "am_common.h"
#include "zlg116_pin.h"
#include "am_zlg116_inst_init.h"

/** \brief ������ MMC5883MA �豸��Ϣʵ�� */
am_const am_local struct am_sensor_mmc5883ma_devinfo __g_mmc5883ma_info = {
        PIOB_0,            /*< \brief �������Ŷ���   */
        0x30               /*< \breif MMC5883MA I2C��ַ */
};

/** \breif ������ MMC5883MA �豸�ṹ�嶨�� */
am_local struct am_sensor_mmc5883ma_dev __g_mmc5883ma_dev;

/** \brief ������ MMC5883MA �豸ʵ���� */
am_sensor_handle_t am_sensor_mmc5883ma_inst_init (void)
{
    return am_sensor_mmc5883ma_init(&__g_mmc5883ma_dev,
                                    &__g_mmc5883ma_info,
                                    am_zlg116_i2c1_inst_init());
}

/** \brief ������ MMC5883MA ʵ�����ʼ�� */
am_err_t am_sensor_mmc5883ma_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_mmc5883ma_deinit(handle);
}

/* end of file */
