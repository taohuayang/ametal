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
 * \brief ZSN603�����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-04-22  htf, first implementation.
 * \endinternal
 */
#include <am_hwconf_zsn603_i2c.h>
#include "ametal.h"
#include "am_i2c.h"
#include "zsn603.h"
#include "zlg116_pin.h"
#include "am_zsn603.h"
#include "am_uart_rngbuf.h"
#include "zsn603_platform.h"
#include "am_zlg116_inst_init.h"

/**< \brief ZSN603(UARTģʽ) �豸ʵ�� */
static   zsn603_uart_dev_t          __g_zsn603_uart_dev;

/**< \brief ZSN603(UARTģʽ) �豸��Ϣ */
static const zsn603_uart_devinfo_t  __g_uart_info = {
     0xb2,
    {
        -1,
        PIOA_12,
        am_zlg116_uart2_inst_init,
        am_zlg116_uart2_inst_deinit,
        9600,
    }
};
/** \brief ZSN603 ʵ����ʼ�������ZSN603��׼������(UARTģʽ) */
zsn603_handle_t  am_zsn603_uart_inst_init (void)
{
    return zsn603_uart_init(&__g_zsn603_uart_dev, &__g_uart_info);
}
