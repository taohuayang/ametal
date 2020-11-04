/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2020 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ISO7816�û������ļ�
 * \sa am_hwconf_iso7816.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-27  licl, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_pwm.h"
#include "am_iso7816.h"

#include "am_zsn700.h"
#include "am_zsn700_tim_pwm.h"
#include "am_zsn700_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_iso7816
 * \copydoc am_hwconf_iso7816.c
 * @{
 */

am_local am_iso7816_devinfo_t   __g_iso_7816_devinfo = {
        PIOD_2,                             /* vcc pin*/
        PIOB_9,                             /* rst pin */
        PIOC_13,                            /* clk pin */
        PIOC_13_TIM3_CH1B | PIOC_13_OUT_PP, /* clkout mode */
        AM_ZSN700_TIM_PWM_CH1B,             /* clkout chan */
        PIOB_8,                             /* io pin */
        PIOB_8_UART0_TXD  | PIOB_8_OUT_PP,  /* io rx mode */
        AM_FALSE,                           /* ��Դ����Ч */
        2000000                             /* 2M clk */
};

am_local am_iso7816_dev_t       __g_iso7816_dev;

/** \brief ISO7816 �Ӵ�ʽ��ʵ����ʼ�� */
am_iso7816_handle_t am_iso7816_inst_init (void)
{

    /* ����������Ϊ�첽��˫��ģʽ(AMHW_ZSN700_UART_WORK_MODE_4), żУ�� */
    am_uart_handle_t uart_handle = am_zsn700_uart0_inst_init();
    am_pwm_handle_t  pwm_handle  = am_zsn700_tim3_pwm_inst_init();

    if (NULL != uart_handle && NULL != pwm_handle) {
        return am_iso7816_init(&__g_iso7816_dev,
                               uart_handle,
                               pwm_handle,
                               &__g_iso_7816_devinfo);
    }

    return NULL;
}

/**
 * @}
 */

/* end of file */
