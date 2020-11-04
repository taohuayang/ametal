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
 * \brief ������ TMD2750 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tmd2750.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local tmd2750_param_config_t __g_tmd2750_param_default = {
        AM_TMD2750_ATIME_50MS,                      /* ALS ADC�Ļ���ʱ�� */
        AM_TMD2750_WTIME_2_78MS_OR_33_4MS,          /* (��wlong_en�������)���wlong_enΪ�棬�ȴ�ʱ��Ϊ���ߣ�����Ϊǰ�� */
        0,                                          /* �������ϴ�������Prox�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page25 */
        0,                                          /* �������ϴ�������ALS�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page25 */
        AM_FALSE,                                   /* WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
        AM_FALSE,                                   /* Prox���峤������16������ */
        AM_TMD2750_PULSE_LEN_16US_OR_256US,         /* (��ppulse_len_16x_en�������)Prox���峤�ȣ��� ppulse_len_16x_enΪ�棬��Ϊ���ߣ�����Ϊǰ��*/
        16,                                         /* (��apc_disable�������)һ��Prox���ڵ���������� */
        AM_TMD2750_PGAIN_4,                         /* Prox IR���������� */
        AM_TMD2750_PLDRIVE_19MA,                    /* Prox IR VCSEL���� */
        AM_TMD2750_AGAIN_256,                       /* ALS���������� */
        AM_FALSE,                                   /* sleep_after_interrupt */
        AM_TMD2750_APC_DISABLE,                     /* Prox�Զ������������ */
        AM_TMD2750_ELECTRICAL_OPTICAL_CROSSTALK,    /* ProxУ׼����ѡ�� */
        AM_TMD2750_BINSRCH_TARGET_15,               /* Proxƫ��У׼Ŀ�� */
        AM_FALSE,                                   /* Prox�Զ�ƫ�Ƶ������� */
        AM_TMD2750_SAMPLE_SIZE_DISABLE,             /* Proxƽ������ */
        2816,                                       /* Prox��������ʱ��(us) */
};

/** \brief ������ TMD2750 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tmd2750_devinfo __g_tmd2750_info = {
        &__g_tmd2750_param_default,             /**< \brief ������ʼ�� */
        PIOC_1,                                 /**< \brief ����������� */
        0x49,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TMD2750 �豸�ṹ�嶨�� */
am_local struct am_sensor_tmd2750_dev __g_tmd2750_dev;

/** \brief ������ TMD2750 �豸ʵ���� */
am_sensor_handle_t am_sensor_tmd2750_inst_init (void)
{
    return am_sensor_tmd2750_init(&__g_tmd2750_dev,
                                  &__g_tmd2750_info,
                                  am_zlg237_i2c1_inst_init());
}

/** \brief ������ TMD2750 ʵ�����ʼ�� */
am_err_t am_sensor_tmd2750_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tmd2750_deinit(handle);
}

/* end of file */
