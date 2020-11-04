/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG72128 ��׼ͨ���û������ļ�
 * \sa am_hwconf_zlg72128_std.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-04-09 xgg, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_lpc82x.h"
#include "am_zlg72128_std.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_zlg72128
 * \copydoc am_hwconf_moniport_zlg72128.c
 * @{
 */

/** \brief ZLG72128 ����������Ϣ */
am_local am_const int __g_miniport_zlg72128_codes[] = {
    KEY_0,    /* ���� KEY0 �ļ�ֵ */
    KEY_1,    /* ���� KEY1 �ļ�ֵ */
    KEY_2,    /* ���� KEY2 �ļ�ֵ */
    KEY_3     /* ���� KEY3 �ļ�ֵ */
};

/** \brief MiniPort-ZLG72128 �豸��Ϣ */
am_local const am_zlg72128_std_devinfo_t __g_miniport_zlg72128_devinfo = {
    {
        {
            0x30,
            PIO0_6,            /*  ��λ���� */
            AM_TRUE,           /*  ʹ���ж�����*/
            PIO0_1,            /*  �ж�����*/
            5,                 /*  ��ѯʱ������ʹ���ж�����ʱ����ֵ������*/
            am_lpc82x_i2c2_inst_init,   /* I2C�����ȡ����*/
            am_lpc82x_i2c2_inst_deinit  /* I2C���ʼ������*/
        }
    },
    {
        0                          /* �������ʾ���ı�� */
    },
    500,                           /* һ����˸�����ڣ�������ʱ��Ϊ 500ms */
    500,                           /* һ����˸�����ڣ�Ϩ���ʱ��Ϊ 500ms */
    AM_ZLG72128_STD_KEY_ROW_0 | AM_ZLG72128_STD_KEY_ROW_3, /* ʵ��ʹ�õ��б�־ */
    AM_ZLG72128_STD_KEY_COL_0 | AM_ZLG72128_STD_KEY_COL_1, /* ʵ��ʹ�õ��б�־ */
    __g_miniport_zlg72128_codes,    /* ����������Ϣ */
    2                               /* ����ܸ���Ϊ 2 */
};

/** \brief ZLG72128 �豸ʵ�� */
am_local am_zlg72128_std_dev_t __g_miniport_zlg72128_dev;

/**
 * \brief ZLG72128 ��׼ͨ�ù����ʼ��
 */
int am_miniport_zlg72128_inst_init (void)
{
    return am_zlg72128_std_init(&__g_miniport_zlg72128_dev,
                                &__g_miniport_zlg72128_devinfo);
}

/**
 * @}
 */

/* end of file */
