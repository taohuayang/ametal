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
 * \brief MicroPort RS485 �û������ļ�
 * \sa am_hwconf_microport_rs485.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-16  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg_uart.h"
#include "hw/amhw_zlg_uart.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg116_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_microport_rs485
 * \copydoc am_hwconf_microport_rs485.c
 * @{
 */

/** \brief RS485 ����������� */
#define __MICROPORT_RS485_DIR_PIN   PIOA_15

/**
 * \brief RS485 ������ƺ���
 *
 * \param[in] is_txmode AM_TRUE: ����ģʽ�� AM_FALSE: ����ģʽ
 */
void __microport_rs485_dir (am_bool_t is_txmode)
{
    am_gpio_set(__MICROPORT_RS485_DIR_PIN, (int)is_txmode);
}

/** \brief MicroPort RS485 ƽ̨��ʼ�� */
am_local void __microport_rs485_plfm_init (void)
{

    /* ���ų�ʼ�� PIOA_9 -> UART1_TX  PIOA_10 -> UART1_RX */
    am_gpio_pin_cfg(PIOA_9, PIOA_9_UART1_TX | PIOA_9_AF_PP);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX | PIOA_10_INPUT_FLOAT);

    am_gpio_pin_cfg(__MICROPORT_RS485_DIR_PIN, AM_GPIO_OUTPUT_INIT_LOW);
}

/** \brief ��� MicroPort RS485 ƽ̨��ʼ�� */
am_local void __microport_rs485_plfm_deinit (void)
{

    /* �ر� UART1 ʱ�� */
    am_clk_disable(CLK_UART1);

    am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_10, AM_GPIO_INPUT);
}

/** \brief MicroPort RS485 �豸��Ϣ */
am_local am_const am_zlg_uart_devinfo_t __g_microport_rs485_devinfo = {
    ZLG116_UART1_BASE,              /**< \brief ���� 1 */
    INUM_UART1,                     /**< \brief ���� 1 ���жϱ�� */
    CLK_UART1,                      /**< \brief ���� 1 ��ʱ�� */

    AMHW_ZLG_UART_DATA_8BIT |       /**< \brief 8 λ���� */
    AMHW_ZLG_UART_PARITY_NO |       /**< \brief �޼��� */
    AMHW_ZLG_UART_STOP_1BIT,        /**< \brief 1 ��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    __microport_rs485_dir,          /**< \brief RS485 �����л����� */
    __microport_rs485_plfm_init,    /**< \brief UART1 ��ƽ̨��ʼ�� */
    __microport_rs485_plfm_deinit,  /**< \brief UART1 ��ƽ̨ȥ��ʼ�� */
};

/** \brief ���� MicroPort RS485 �豸 */
am_local am_zlg_uart_dev_t __g_microport_rs485_dev;

/** \brief MicroPort RS485 ʵ����ʼ������� UART ��׼������ */
am_uart_handle_t am_microport_rs485_inst_init (void)
{
    am_uart_handle_t handle;
    handle = am_zlg_uart_init(&__g_microport_rs485_dev,
                              &__g_microport_rs485_devinfo);
    if (NULL != handle) {
        am_uart_ioctl(handle, AM_UART_RS485_SET, (void *)AM_TRUE);
    }

    return handle;
}

/**
 * @}
 */

/* end of file */
