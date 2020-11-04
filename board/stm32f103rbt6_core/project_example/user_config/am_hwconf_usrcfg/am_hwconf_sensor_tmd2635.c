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
 * \brief ������ TMD2635 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tmd2635.h"
#include "am_common.h"
#include "stm32f103rbt6_pin.h"
#include "am_stm32f103rbt6_inst_init.h"

am_const am_local tmd2635_param_config_t __g_tmd2635_param_default = {
        0,                                          /* �������ϴ�������Prox�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page16 */
        AM_FALSE,                                   /* WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
        AM_TMD2635_PGAIN_4,                         /* Prox IR���������� */
        16,                                         /* (��apc_disable�������)һ��Prox���ڵ���������� */
        AM_TMD2635_PULSE_LEN_16US,                  /* Prox���峤�� */
        AM_TMD2635_PLDRIVE_10MA,                    /* Prox IR VCSEL���� */
        AM_TMD2635_PWTIME_2_78MS_OR_33_4MS,         /* (��pwlong_en�������)���pwlong_enΪ�棬�ȴ�ʱ��Ϊ���ߣ�����Ϊǰ�� */
        AM_TMD2635_PDSELECT_NEAR_PHOTODIODE,        /* ��������ѡ�� */
        AM_FALSE,                                   /* sleep_after_interrupt */
        AM_TMD2635_APC_DISABLE,                     /* Prox�Զ������������ */
        AM_TMD2635_PMAVG_DISABLE,                   /* PMAVG���� */
        AM_TMD2635_NO_HARDWARE_AVERAGING,           /* CALAVG���� */
        AM_TMD2635_ELECTRICAL_OPTICAL_CROSSTALK,    /* ProxУ׼����ѡ�� */
        AM_TMD2635_PRATE_IGNORED,                   /* CALPRATE���� */
        AM_TMD2635_BINSRCH_TARGET_15,               /* Proxƫ��У׼Ŀ�� */
        AM_FALSE,                                   /* Prox�Զ�ƫ�Ƶ������� */
        AM_TMD2635_SAMPLE_SIZE_DISABLE,             /* Proxƽ������ */
        2816,                                       /* Prox��������ʱ��(us) */
};

/** \brief ������ TMD2635 �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tmd2635_devinfo __g_tmd2635_info = {
        &__g_tmd2635_param_default,             /**< \brief ������ʼ�� */
        PIOC_0,                                 /**< \brief ����������� */
        0x39,                                   /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TMD2635 �豸�ṹ�嶨�� */
am_local struct am_sensor_tmd2635_dev __g_tmd2635_dev;

/** \brief ������ TMD2635 �豸ʵ���� */
am_sensor_handle_t am_sensor_tmd2635_inst_init (void)
{
    return am_sensor_tmd2635_init(&__g_tmd2635_dev,
                                  &__g_tmd2635_info,
                                  am_stm32f103rbt6_i2c1_inst_init());
}

/** \brief ������ TMD2635 ʵ�����ʼ�� */
am_err_t am_sensor_tmd2635_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tmd2635_deinit(handle);
}

/* end of file */
