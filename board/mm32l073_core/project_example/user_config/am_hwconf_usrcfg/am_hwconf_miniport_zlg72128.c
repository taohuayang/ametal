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
 * \brief MiniPort-ZLG72128 �����ļ�
 * \sa am_hwconf_miniport_zlg72128.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_mm32l073_inst_init.h"
#include "am_zlg72128_std.h"
#include "mm32l073_pin.h"
#include "am_input.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_zlg72128
 * \copydoc am_hwconf_miniport_zlg72128.c
 * @{
 */

/*******************************************************************************
    Local global variables
*******************************************************************************/

static const int __g_key_codes[]    = {
    KEY_0, KEY_1,
    KEY_2, KEY_3
};


static const am_zlg72128_std_devinfo_t __g_miniport_zlg72128_info = {
    {
        {
            0x30,
            PIOB_5,                     /* ��λ���� todo */
            AM_FALSE,                   /* ʹ���ж����� */
            PIOB_3,                     /* �ж����� todo */
            5,                          /* ��ѯʱ������ʹ���ж�����ʱ����ֵ������ */
            am_mm32l073_i2c1_inst_init,   /* I2C�����ȡ����*/
            am_mm32l073_i2c1_inst_deinit  /* I2C���ʼ������*/
        }
    },
    {
        0                           /* �������ʾ���ı�� */
    },
    500,                            /* һ����˸�����ڣ�������ʱ��Ϊ500ms */
    500,                            /* һ����˸�����ڣ�Ϩ���ʱ��Ϊ500ms */
    AM_ZLG72128_STD_KEY_ROW_0 | AM_ZLG72128_STD_KEY_ROW_3,
    AM_ZLG72128_STD_KEY_COL_0 | AM_ZLG72128_STD_KEY_COL_1,
    __g_key_codes,                  /* �������룬 KEY_0 ~ KEY3 */
    2                               /* ����ܸ���Ϊ2 */
};

/*******************************************************************************
    Public functions
*******************************************************************************/

/** \brief ZLG72128 �豸ʵ�� */
static am_zlg72128_std_dev_t      __g_miniport_zlg72128;


/* MiniPort-ZLG72128 ʵ����ʼ�� */
int am_miniport_zlg72128_inst_init (void)
{
    return  am_zlg72128_std_init(&__g_miniport_zlg72128,
                                 &__g_miniport_zlg72128_info);
}

/**
 * @}
 */

/* end of file */
