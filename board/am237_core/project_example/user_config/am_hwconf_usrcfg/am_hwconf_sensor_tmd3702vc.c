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
 * \brief ������ TMD3702VC �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tmd3702vc.h"
#include "am_common.h"
#include "zlg237_pin.h"
#include "am_zlg237_inst_init.h"

am_const am_local tmd3702vc_param_config_t __g_tmd3702vc_param_default = {
        AM_TMD3702VC_ATIME_50MS,                    /* ALS ADC�Ļ���ʱ�� */
        AM_TMD3702VC_WTIME_2_78MS_OR_33_4MS,        /* (��wlong_en�������)���wlong_enΪ�棬�ȴ�ʱ��Ϊ���ߣ�����Ϊǰ�� */
        0,                                          /* �������ϴ�������Prox�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page25 */
        0,                                          /* �������ϴ�������ALS�жϣ��ò���ֱ�����üĴ���ֵ����ϸ���ݲ��������ֲ�Page25 */
        AM_FALSE,                                   /* WLONGʹ�����ã�ʹ�ܺ�WTIMEֵ������12�� */
        AM_FALSE,                                   /* Prox���峤������16������ */
        AM_TMD3702VC_PULSE_LEN_16US_OR_256US,       /* (��ppulse_len_16x_en�������)Prox���峤�ȣ��� ppulse_len_16x_enΪ�棬��Ϊ���ߣ�����Ϊǰ��*/
        16,                                         /* (��apc_disable�������)һ��Prox���ڵ���������� */
        AM_TMD3702VC_PGAIN_4,                       /* Prox IR���������� */
        AM_TMD3702VC_PLDRIVE_19MA,                  /* Prox IR VCSEL���� */
        AM_TMD3702VC_IR_MUX_DISABLE,                /* IR_MUX */
        AM_TMD3702VC_AGAIN_256,                     /* ALS/Color���������� */
        AM_FALSE,                                   /* sleep_after_interrupt */
        AM_TMD3702VC_APC_DISABLE,                   /* Prox�Զ������������ */
        AM_TMD3702VC_ELECTRICAL_OPTICAL_CROSSTALK,  /* ProxУ׼����ѡ�� */
        AM_TMD3702VC_BINSRCH_TARGET_15,             /* Proxƫ��У׼Ŀ�� */
        AM_FALSE,                                   /* Prox�Զ�ƫ�Ƶ������� */
        AM_TMD3702VC_SAMPLE_SIZE_DISABLE,           /* Proxƽ������ */
        2816,                                       /* Prox��������ʱ��(us) */
};

/** \brief ������ TMD3702VC �豸��Ϣʵ�� */
am_const am_local struct am_sensor_tmd3702vc_devinfo __g_tmd3702vc_info = {
        &__g_tmd3702vc_param_default,               /**< \brief ������ʼ�� */
        PIOC_2,                                     /**< \brief ����������� */
        0x49,                                       /**< \brief I2C 7λ �豸��ַ */
};

/** \breif ������ TMD3702VC �豸�ṹ�嶨�� */
am_local struct am_sensor_tmd3702vc_dev __g_tmd3702vc_dev;

/** \brief ������ TMD3702VC �豸ʵ���� */
am_sensor_handle_t am_sensor_tmd3702vc_inst_init (void)
{
    return am_sensor_tmd3702vc_init(&__g_tmd3702vc_dev,
                                    &__g_tmd3702vc_info,
                                    am_zlg237_i2c1_inst_init());
}

/** \brief ������ TMD3702VC ʵ�����ʼ�� */
am_err_t am_sensor_tmd3702vc_inst_deinit (am_sensor_handle_t handle)
{
    return am_sensor_tmd3702vc_deinit(handle);
}

/* end of file */
