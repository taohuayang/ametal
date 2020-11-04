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
 * \brief HC32 PCNT �û������ļ�
 * \sa am_hwconf_hc32f03x_pcnt.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "hc32_clk.h"
#include "hc32_inum.h"
#include "hc32_regbase.h"
#include "am_hc32_clk.h"
#include "am_hc32_pcnt.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f03x_pcnt
 * \copydoc am_hwconf_hc32f03x_pcnt.c
 * @{
 */

/**
 * \brief PCNT ƽ̨��ʼ������
 */
am_local void __hc32f03x_pcnt_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_5, PIOB_5_INPUT_FLOAT | PIOB_5_PCNT_S0);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_INPUT_FLOAT | PIOB_7_PCNT_S1);

    am_clk_enable(CLK_PCNT);
}

/**
 * \brief PCNT ƽ̨���ʼ������
 */
am_local void __hc32f03x_pcnt_plfm_deinit (void)
{
    am_clk_disable(CLK_PCNT);
}

/** \brief PCNT �豸��Ϣ */
am_local am_const am_hc32_pcnt_devinfo_t __g_hc32f03x_pcnt_devinfo = {
        HC32_PCNT_BASE,
        CLK_PCNT,
        INUM_PCNT,
        __hc32f03x_pcnt_plfm_init,
        __hc32f03x_pcnt_plfm_deinit
};

/** \brief PCNT �豸ʵ�� */
am_local am_hc32_pcnt_dev_t __g_hc32f03x_pcnt_dev;

/**
 * \brief PCNT ʵ����ʼ��
 */
am_hc32_pcnt_handle_t am_hc32f03x_pcnt_inst_init (void)
{
    return am_hc32_pcnt_init(&__g_hc32f03x_pcnt_dev, &__g_hc32f03x_pcnt_devinfo);
}

/**
 * \brief PCNT ʵ�����ʼ��
 */
void am_hc32f03x_pcnt_inst_deinit (am_hc32_pcnt_handle_t handle)
{
    am_hc32_pcnt_deinit(handle);
}

/**
 * @}
 */

/* end of file */
