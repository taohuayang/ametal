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
 * \brief zlg72128 AMetalƽ̨����ZLG72128ͨ��������
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21 adw, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "zlg72128.h"
#include "lpc82x_pin.h"
#include "am_lpc82x_inst_init.h"

/** \brief  ����һ��  ZLG72128  ʵ��*/
static zlg72128_dev_t      __g_zlg72128_dev;

static const zlg72128_devinfo_t __g_zlg72128_devinfo = {
    {
        0x30,        /* �豸�ӻ���ַ */
        PIO0_6,      /* ��λ���� */
        AM_TRUE,     /* ͨ������£�����ʹ���ж����� */
        PIO0_1,      /* ZLG72128 �� KEY_INT ������ LPC824 �� PIO0_1 ���� */
        10,          /* ʹ���ж�����ʱ����ֵ�����塣����ʹ���ж����ţ����ѯ���Ϊ 5ms */
        am_lpc82x_i2c2_inst_init,  /* I2C�����ȡ���� */
        am_lpc82x_i2c2_inst_deinit /* I2C���ʼ������ */
    }
};

zlg72128_handle_t  am_zlg72128_inst_init (void)
{
     return zlg72128_init(&__g_zlg72128_dev,
                          &__g_zlg72128_devinfo);
}
