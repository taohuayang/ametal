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
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32f03x_inst_init.h"
#include "am_zlg72128_std.h"
#include "hc32x3x_pin.h"
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

static am_zlg72128_std_dev_t           __g_miniport_zlg72128;
static const am_zlg72128_std_devinfo_t __g_miniport_zlg72128_info = {
    {
            {
                ZLG72128_PIN_HIGH_SLV_ADDR,
                PIOB_3,                     /* ��λ���� */
                AM_TRUE,                   /* ��ʹ���ж����� */
                PIOC_12,                    /* �ж����� */
                5,                          /* ��ѯʱ������ʹ���ж�����ʱ����ֵ������ */
                am_hc32_i2c1_inst_init,
                am_hc32_i2c1_inst_deinit
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
