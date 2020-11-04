/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief LPUART ����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
#include "am_zsn700_lpuart.h"
#include "am_clk.h"
#include "hw/amhw_zsn700_rcc.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_uart.h"
#include "zsn700_clk.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/**
 * \brief ����ģʽ����ѯ���жϣ�����
 */
int __lpuart_mode_set (am_zsn700_lpuart_dev_t *p_dev, uint32_t new_mode);

/**
 * \brief ����Ӳ������
 */
int __lpuart_opt_set (am_zsn700_lpuart_dev_t *p_dev, uint32_t opts);

/**
 * \brief ���ؽ���������״̬����
 */
static int __lpuart_flow_rxstat_set (am_zsn700_lpuart_dev_t *p_dev, uint32_t ctrl);

/**
 * \brief ����ģʽ����
 */
static int __lpuart_flow_mode_set (am_zsn700_lpuart_dev_t *p_dev, uint32_t mode);

/**
 * \brief ���ط���������״̬��ȡ
 */
static int __lpuart_flow_txstat_get (am_zsn700_lpuart_dev_t *p_dev);

/* ZSN700 ���������������� */
static int __lpuart_ioctl (void *p_drv, int, void *);

static int __lpuart_tx_startup (void *p_drv);

static int __lpuart_callback_set (void *p_drv,
                                int   callback_type,
                                void *pfn_callback,
                                void *p_arg);

static int __lpuart_poll_getchar (void *p_drv, char *p_char);

static int __lpuart_poll_putchar (void *p_drv, char outchar);

#if 0
static int __lpuart_connect (void *p_drv);
#endif

static void __lpuart_irq_handler (void *p_arg);

/** \brief ��׼��ӿں���ʵ�� */
static const struct am_uart_drv_funcs __g_lpuart_drv_funcs = {
    __lpuart_ioctl,
    __lpuart_tx_startup,
    __lpuart_callback_set,
    __lpuart_poll_getchar,
    __lpuart_poll_putchar,
};

/******************************************************************************/

/**
 * \brief �豸���ƺ���
 *
 * ���а������û�ȡ�����ʣ�ģʽ���ã��ж�/��ѯ������ȡ֧�ֵ�ģʽ��Ӳ��ѡ�����õȹ��ܡ�
 */
static int __lpuart_ioctl (void *p_drv, int request, void *p_arg)
{
    am_zsn700_lpuart_dev_t *p_dev     = (am_zsn700_lpuart_dev_t *)p_drv;
    amhw_zsn700_lpuart_t   *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                      p_dev->p_devinfo->lpuart_reg_base;

    int status = AM_OK;

    switch (request) {

    /* ���������� */
    case AM_UART_BAUD_SET:

        /* ֻ���ڷ��ͿյĻ����ϲ������޸Ĳ����� */
        while (amhw_zsn700_lpuart_flag_check(
                   p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) == AM_FALSE);

        status = amhw_zsn700_lpuart_baudrate_set(p_hw_lpuart,
                                                 p_dev->clk_rate,
                                                 (uint32_t)p_arg);

        if (status > 0) {
            p_dev->baud_rate = status;
            status = AM_OK;
        } else {
            status = -AM_EIO;
        }
        break;

    /* �����ʻ�ȡ */
    case AM_UART_BAUD_GET:
        *(int *)p_arg = p_dev->baud_rate;
        break;

    /* ģʽ���� */
    case AM_UART_MODE_SET:
        status = (__lpuart_mode_set(p_dev, (int)p_arg) == AM_OK)
                 ? AM_OK : -AM_EIO;
        break;

    /* ģʽ��ȡ */
    case AM_UART_MODE_GET:
        *(int *)p_arg = p_dev->channel_mode;
        break;

    /* ��ȡ���ڿ����õ�ģʽ */
    case AM_UART_AVAIL_MODES_GET:
        *(int *)p_arg = AM_UART_MODE_INT | AM_UART_MODE_POLL;
        break;

    /* ����ѡ������ */
    case AM_UART_OPTS_SET:
        status = (__lpuart_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    /* ����ѡ���ȡ */
    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_dev->options;
        break;

    /* 485ģʽ���� */
    case AM_UART_RS485_SET:
        if (p_dev->rs485_en != (am_bool_t)(int)p_arg) {
            p_dev->rs485_en = (am_bool_t)(int)p_arg;
        }
        break;

    /* 485ģʽ״̬��ȡ */
    case AM_UART_RS485_GET:
        *(int *)p_arg = p_dev->rs485_en;
        break;

    /* ��������ģʽ */
    case AM_UART_FLOWMODE_SET:
        __lpuart_flow_mode_set(p_dev, (int)p_arg);
    break;

    /* ���ý���������״̬ */
    case AM_UART_FLOWSTAT_RX_SET:
        __lpuart_flow_rxstat_set(p_dev, (int)p_arg);
    break;

    /* ��ȡ����������״̬ */
    case AM_UART_FLOWSTAT_TX_GET:
        *(int *)p_arg = __lpuart_flow_txstat_get(p_dev);
    break;

    default:
        status = -AM_EIO;
        break;
    }

    return (status);
}

/**
 * \brief �������ڷ���(�����ж�ģʽ)
 */
int __lpuart_tx_startup (void *p_drv)
{
    char data  = 0;

    am_zsn700_lpuart_dev_t *p_dev       = (am_zsn700_lpuart_dev_t *)p_drv;
    amhw_zsn700_lpuart_t   *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                          p_dev->p_devinfo->lpuart_reg_base;

    /* ʹ�� 485 ���Ϳ������� */
    if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {
        p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
    }

    /* �ȴ���һ�δ������ */
    while (amhw_zsn700_lpuart_flag_check(p_hw_lpuart,
                                       AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) ==
                                       AM_FALSE);

    /* ��ȡ�������ݲ����� */
    if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
        amhw_zsn700_lpuart_data_write(p_hw_lpuart, data);
    }

    /* ʹ�ܷ�������ж� */
    amhw_zsn700_lpuart_int_enable(p_hw_lpuart,
                                  AMHW_ZSN700_LPUART_INT_TX_COMPLETE);

    return AM_OK;
}

/**
 * \brief �����жϷ���ص�����
 */
static int __lpuart_callback_set (void  *p_drv,
                                  int    callback_type,
                                  void  *pfn_callback,
                                  void  *p_arg)
{
    am_zsn700_lpuart_dev_t *p_dev = (am_zsn700_lpuart_dev_t *)p_drv;

    switch (callback_type) {

    /* ���÷��ͻص������еĻ�ȡ�����ַ��ص����� */
    case AM_UART_CALLBACK_TXCHAR_GET:
        p_dev->pfn_txchar_get = (am_uart_txchar_get_t)pfn_callback;
        p_dev->txget_arg      = p_arg;
        return (AM_OK);

    /* ���ý��ջص������еĴ�Ž����ַ��ص����� */
    case AM_UART_CALLBACK_RXCHAR_PUT:
        p_dev->pfn_rxchar_put = (am_uart_rxchar_put_t)pfn_callback;
        p_dev->rxput_arg      = p_arg;
        return (AM_OK);

    /* ���ô����쳣�ص����� */
    case AM_UART_CALLBACK_ERROR:
        p_dev->pfn_err = (am_uart_err_t)pfn_callback;
        p_dev->err_arg = p_arg;
        return (AM_OK);

    default:
        return (-AM_ENOTSUP);
    }
}

/**
 * \brief ��ѯģʽ�·���һ���ַ�
 */
static int __lpuart_poll_putchar (void *p_drv, char outchar)
{
    am_zsn700_lpuart_dev_t *p_dev     = (am_zsn700_lpuart_dev_t *)p_drv;
    amhw_zsn700_lpuart_t   *p_hw_lpuart = (amhw_zsn700_lpuart_t *)p_dev->p_devinfo->lpuart_reg_base;

    /* ����ģ���Ƿ����, AM_FALSE:æ; TURE: ���� */
    if(amhw_zsn700_lpuart_flag_check(
           p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        if ((p_dev->rs485_en) && (p_dev->p_devinfo->pfn_rs485_dir != NULL)) {

            /* ���� 485 Ϊ����ģʽ */
            p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
        }

        /* ����һ���ַ� */
        amhw_zsn700_lpuart_data_write(p_hw_lpuart, outchar);

        /* �ȴ�������� */
        while (amhw_zsn700_lpuart_flag_check(
                   p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) == AM_FALSE);

        if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {
            p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
        }
    }

    return (AM_OK);
}

/**
 * \brief ��ѯģʽ�½����ַ�
 */
static int __lpuart_poll_getchar (void *p_drv, char *p_char)
{
    am_zsn700_lpuart_dev_t *p_dev       = (am_zsn700_lpuart_dev_t *)p_drv;
    amhw_zsn700_lpuart_t   *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                           p_dev->p_devinfo->lpuart_reg_base;
    uint8_t           *p_inchar  = (uint8_t *)p_char;

    /* ����ģ���Ƿ���У�AM_FALSE:æ,���ڽ���; TURE: �Ѿ����յ�һ���ַ� */
    if(amhw_zsn700_lpuart_flag_check(
           p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        /* ����һ���ַ� */
        *p_inchar = amhw_zsn700_lpuart_data_read(p_hw_lpuart);

        amhw_zsn700_lpuart_flag_clr(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE);
    }

    return (AM_OK);
}

/**
 * \brief ���ô���ģʽ
 */
int __lpuart_mode_set (am_zsn700_lpuart_dev_t *p_dev, uint32_t new_mode)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                        p_dev->p_devinfo->lpuart_reg_base;

    /* ��֧������ģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }

    if (new_mode == AM_UART_MODE_INT) {

        am_int_connect(p_dev->p_devinfo->inum,
                       __lpuart_irq_handler,
                       (void *)p_dev);

        am_int_enable(p_dev->p_devinfo->inum);

        /* ʹ�ܽ�������ж� */
        amhw_zsn700_lpuart_int_enable(p_hw_lpuart,
                                      AMHW_ZSN700_LPUART_INT_RX_COMPLETE);
    } else {

        /* �ر����д����ж� */
        amhw_zsn700_lpuart_int_disable(p_hw_lpuart, AMHW_ZSN700_LPUART_INT_ALL);
    }

    p_dev->channel_mode = new_mode;

    return (AM_OK);
}

/**
 * \brief ����ѡ������
 */
int __lpuart_opt_set (am_zsn700_lpuart_dev_t *p_dev, uint32_t options)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                        p_dev->p_devinfo->lpuart_reg_base;
    uint32_t            cfg_flags = 0;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* ����ֹͣλ */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x3ul << 14);
        cfg_flags |= AMHW_ZSN700_LPUART_STOP_2_0_BIT;
    } else {
        cfg_flags &= ~(0x3ul << 14);
        cfg_flags |= AMHW_ZSN700_LPUART_STOP_1_0_BIT;
    }

    /* ���ü��鷽ʽ */
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x3ul << 2);

        if (options & AM_UART_PARODD) {
            cfg_flags |= AMHW_ZSN700_LPUART_HW_PARITY_ODD;
        } else {
            cfg_flags |= AMHW_ZSN700_LPUART_HW_PARITY_EVEN;
        }
    } else {
        cfg_flags &= ~(0x3ul << 2);
        cfg_flags |= AMHW_ZSN700_LPUART_PARITY_NO;
    }

    /* �������Ч���� */
    amhw_zsn700_lpuart_stop_bit_sel(p_hw_lpuart  , (cfg_flags & (0x3ul << 14)));
    amhw_zsn700_lpuart_parity_bit_sel(p_hw_lpuart, (cfg_flags & (0x3ul << 2)));

    p_dev->options = options;

    return (AM_OK);
}
/******************************************************************************/
/**
 * \brief ����������״̬���ã�����أ�
 */
static int __lpuart_flow_rxstat_set (am_zsn700_lpuart_dev_t *p_dev,
                                     uint32_t                ctrl)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = NULL;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    p_hw_lpuart = (amhw_zsn700_lpuart_t *)p_dev->p_devinfo->lpuart_reg_base;

    if (AM_UART_FLOWCTL_NO == p_dev->flowctl_mode) {
        return -AM_ENOTSUP;

    /* �����Ӳ�����أ�����RTS������ŵ�λ */
    } else if (AM_UART_FLOWCTL_HW == p_dev->flowctl_mode) {
        if (AM_UART_FLOWSTAT_ON == ctrl) {
            /* ����RTS�ܽ�,����     */
            am_gpio_set(p_dev->p_devinfo->hwflowctl_cfg.rts_pin, 0);

        } else {
            /* ����RTS�ܽ�,����     */
            am_gpio_set(p_dev->p_devinfo->hwflowctl_cfg.rts_pin, 1);
        }
    } else {
        /* �����������أ�����XON/XOFF�����ַ� */
        if (AM_UART_FLOWSTAT_ON == ctrl) {
            amhw_zsn700_lpuart_data_write(p_hw_lpuart, AM_ZSN700_LPUART_XON);
        } else {
            amhw_zsn700_lpuart_data_write(p_hw_lpuart, AM_ZSN700_LPUART_XOFF);
        }
    }

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief ����ģʽ���ã������أ�������أ�Ӳ�����أ�
 */
static int __lpuart_flow_mode_set(am_zsn700_lpuart_dev_t *p_dev, uint32_t mode)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = NULL;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    p_hw_lpuart = (amhw_zsn700_lpuart_t *)p_dev->p_devinfo->lpuart_reg_base;
    p_dev->flowctl_mode = mode;

    /* ������ */
    if(AM_UART_FLOWCTL_NO == p_dev->flowctl_mode) {
        p_dev->flowctl_tx_stat = AM_UART_FLOWSTAT_ON;

        /* Ӳ�����ؽ���     */
        amhw_zsn700_lpuart_disable(p_hw_lpuart, AMHW_ZSN700_LPUART_CTS);
        amhw_zsn700_lpuart_disable(p_hw_lpuart, AMHW_ZSN700_LPUART_RTS);

        /* Ӳ���������Ž��ʼ�� */
        if(p_dev->p_devinfo->hwflowctl_cfg.pfn_hwflowctl_ioconfig != NULL) {
            p_dev->p_devinfo->hwflowctl_cfg.pfn_hwflowctl_ioconfig(AM_FALSE);
        }

    /* Ӳ������ */
    } else if (AM_UART_FLOWCTL_HW == p_dev->flowctl_mode) {

        /* Ӳ���������ų�ʼ�� */
        if(p_dev->p_devinfo->hwflowctl_cfg.pfn_hwflowctl_ioconfig != NULL) {
            p_dev->p_devinfo->hwflowctl_cfg.pfn_hwflowctl_ioconfig(AM_TRUE);
        }

        amhw_zsn700_lpuart_enable(p_hw_lpuart, AMHW_ZSN700_LPUART_CTS);
        amhw_zsn700_lpuart_enable(p_hw_lpuart, AMHW_ZSN700_LPUART_RTS);
    } else {

        amhw_zsn700_lpuart_disable(p_hw_lpuart, AMHW_ZSN700_LPUART_CTS);
        amhw_zsn700_lpuart_disable(p_hw_lpuart, AMHW_ZSN700_LPUART_RTS);

        /* Ӳ���������Ž��ʼ�� */
        if(p_dev->p_devinfo->hwflowctl_cfg.pfn_hwflowctl_ioconfig != NULL) {
            p_dev->p_devinfo->hwflowctl_cfg.pfn_hwflowctl_ioconfig(AM_FALSE);
        }
    }

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief ����������״̬��ȡ
 */
static int __lpuart_flow_txstat_get (am_zsn700_lpuart_dev_t *p_dev)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = NULL;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    p_hw_lpuart = (amhw_zsn700_lpuart_t *)p_dev->p_devinfo->lpuart_reg_base;

    if(AM_UART_FLOWCTL_HW == p_dev->flowctl_mode) {

        /* cts��״̬�����仯ʱ��״̬λ��Ч */
        if(amhw_zsn700_lpuart_flag_check(
               p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_CTS_TRIGGER) == AM_TRUE) {

            /* ���cts״̬λ */
            amhw_zsn700_lpuart_flag_clr(p_hw_lpuart,
                                        AMHW_ZSN700_LPUART_FLAG_CTS_TRIGGER);

            /* �ж�cts��ǰ�ߵ͵�ƽ */
            if (am_gpio_get(p_dev->p_devinfo->hwflowctl_cfg.cts_pin) == 0) {
                return (int)AM_UART_FLOWSTAT_ON;
            } else {
                return (int)AM_UART_FLOWSTAT_OFF;
            }
        } else {
            return (int)p_dev->flowctl_tx_stat;
        }
    } else {
        return (int)p_dev->flowctl_tx_stat;
    }
}

/*******************************************************************************
  LPUART interrupt request handler
*******************************************************************************/

/**
 * \brief ���ڽ����жϷ���
 */
void __lpuart_irq_rx_handler (am_zsn700_lpuart_dev_t *p_dev)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                        p_dev->p_devinfo->lpuart_reg_base;
    char data;

    /* �Ƿ�Ϊ����Rx�ж� */
    if (amhw_zsn700_lpuart_flag_check(
            p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE) == AM_TRUE) {

        amhw_zsn700_lpuart_flag_clr(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE);

        /* ��ȡ�½������� */
        data = amhw_zsn700_lpuart_data_read(p_hw_lpuart);

        /* ����½������� */
        p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
    }
}

/**
 * \brief ���ڷ����жϷ���
 */
void __lpuart_irq_tx_handler (am_zsn700_lpuart_dev_t *p_dev)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                        p_dev->p_devinfo->lpuart_reg_base;

    char data;

    if (amhw_zsn700_lpuart_flag_check(
            p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE) == AM_TRUE) {

        amhw_zsn700_lpuart_flag_clr(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE);

        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_zsn700_lpuart_data_write(p_hw_lpuart, data);
        } else {

            /* û�����ݴ��;͹رշ����ж� */
            amhw_zsn700_lpuart_int_disable(p_hw_lpuart,
                                           AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE);

            /* ����485���Ϳ������� */
            if ((p_dev->rs485_en) && (p_dev->p_devinfo->pfn_rs485_dir)) {

                /* ���� 485 Ϊ����ģʽ */
                p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
            }
        }
    }
}

/**
 * \brief �����жϷ�����
 */
void __lpuart_irq_handler (void *p_arg)
{
    am_zsn700_lpuart_dev_t  *p_dev     = (am_zsn700_lpuart_dev_t *)p_arg;
    amhw_zsn700_lpuart_t    *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                       p_dev->p_devinfo->lpuart_reg_base;

    uint32_t lpuart_int_stat = amhw_zsn700_lpuart_flag_get(p_hw_lpuart);

    if (amhw_zsn700_lpuart_flag_check(
            p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE) == AM_TRUE) {

         __lpuart_irq_rx_handler(p_dev);

    } else if (amhw_zsn700_lpuart_flag_check(
                   p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE) == AM_TRUE) {

        __lpuart_irq_tx_handler(p_dev);

    } else {

    }

    /* �����ж� */
    if ((p_dev->other_int_enable & lpuart_int_stat) != 0) {

        lpuart_int_stat &= p_dev->other_int_enable;

        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AM_ZSN700_LPUART_ERRCODE_LPUART_OTHER_INT,
                           (void *)p_hw_lpuart,
                           1);
        }
    }

}

#if 0
/**
 * \brief LPUART�жϺ������ӣ���ʹ���ж�ģʽʱ��Ҫ���ô˺���
 */
int __lpuart_connect (void *p_drv)
{
    am_zsn700_lpuart_dev_t *p_dev = (am_zsn700_lpuart_dev_t *)p_drv;

    /* �����ж������ţ������ж� */
    am_int_connect(p_dev->p_devinfo->inum, __lpuart_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    amhw_zsn700_lpuart_int_enable(p_dev->p_devinfo->lpuart_reg_base,
                                  p_dev->other_int_enable);

    return AM_OK;
}
#endif /* 0 */

/**
 * \brief Ĭ�ϻص�����
 *
 * \returns AW_ERROR
 */
static int __lpuart_dummy_callback (void *p_arg, char *p_outchar)
{
    return (AM_ERROR);
}

/**
 * \brief ���ڳ�ʼ������
 */
am_uart_handle_t am_zsn700_lpuart_init (
                     am_zsn700_lpuart_dev_t           *p_dev,
                     const am_zsn700_lpuart_devinfo_t *p_devinfo)
{
    amhw_zsn700_lpuart_t  *p_hw_lpuart;

    if (p_devinfo == NULL) {
        return NULL;
    }

    /* ��ȡ���ò��� */
    p_hw_lpuart                = (amhw_zsn700_lpuart_t  *)
                                  p_devinfo->lpuart_reg_base;
    p_dev->p_devinfo           = p_devinfo;
    p_dev->lpuart_serv.p_funcs = (struct am_uart_drv_funcs *)
                                  &__g_lpuart_drv_funcs;
    p_dev->lpuart_serv.p_drv   = p_dev;
    p_dev->baud_rate           = p_devinfo->baud_rate;
    p_dev->options             = 0;

    /* ��ʼ��Ĭ�ϻص����� */
    p_dev->pfn_txchar_get    = (int (*) (void *, char*))__lpuart_dummy_callback;
    p_dev->txget_arg         = NULL;
    p_dev->pfn_rxchar_put    = (int (*) (void *, char ))__lpuart_dummy_callback;
    p_dev->rxput_arg         = NULL;
    p_dev->pfn_err           =
                     (int (*) (void *, int, void*, int))__lpuart_dummy_callback;

    p_dev->err_arg           = NULL;

    p_dev->flowctl_mode      = AM_UART_FLOWCTL_NO;
    p_dev->flowctl_tx_stat   = AM_UART_FLOWSTAT_ON;

    p_dev->other_int_enable  = p_devinfo->other_int_enable  &
                               ~(AMHW_ZSN700_LPUART_INT_TX_COMPLETE |
                                 AMHW_ZSN700_LPUART_INT_RX_COMPLETE);
    p_dev->rs485_en          = AM_FALSE;

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    /* ����ͨ��ʱ��Դ */
    amhw_zsn700_lpuart_clk_src_sel(p_hw_lpuart, p_devinfo->sclk_src);

    if(p_devinfo->sclk_src == AMHW_ZSN700_LPUART_SCLK_SRC_XTL) {

        /* �ⲿ������������ѡ�� */
        amhw_zsn700_rcc_xtl_xtal_driver_set(AMHW_ZSN700_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zsn700_rcc_xtl_xtal_amplitude_set(
            AMHW_ZSN700_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zsn700_rcc_xtl_waittime_set(AMHW_ZSN700_XTL_WAITTIME_16384);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_xtl_state_get() == AM_FALSE);

        /* ����ʱ�ӻ�ȡ */
        p_dev->clk_rate = 32768;

    } else if(p_devinfo->sclk_src == AMHW_ZSN700_LPUART_SCLK_SRC_RCL) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zsn700_rcc_rcl_trim_set(*((uint16_t*)0x00100C20));

        amhw_zsn700_rcc_rcl_waittime_set(AMHW_ZSN700_RCL_WAITTIME_256);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_rcl_state_get() == AM_FALSE);

        /* ����ʱ�ӻ�ȡ */
        p_dev->clk_rate = 32768;
    } else {
        p_dev->clk_rate = am_clk_rate_get(CLK_PCLK);
    }

    if(p_devinfo->work_mode == AMHW_ZSN700_LPUART_WORK_MODE_0) {

        /* ģʽ0ͨ��ʱ�ӷ�Ƶϵ��������Ч */
        amhw_zsn700_lpuart_clk_div_sel(p_hw_lpuart,
                                       AMHW_ZSN700_LPUART_SCLK_DIV_MODE0_NO);
    } else {

        /* ����ͨ��ʱ�ӷ�Ƶϵ��Ϊ��С */
        amhw_zsn700_lpuart_clk_div_sel(p_hw_lpuart,
                                       AMHW_ZSN700_LPUART_SCLK_DIV_MODE2_8);
    }

    /* ����ģʽ���� */
    if (p_devinfo->work_mode == AMHW_ZSN700_LPUART_WORK_MODE_4) {
        amhw_zsn700_lpuart_single_line_half_enable(p_hw_lpuart);
        amhw_zsn700_lpuart_mode_sel(p_hw_lpuart, AMHW_ZSN700_LPUART_WORK_MODE_1);
    } else {
        amhw_zsn700_lpuart_mode_sel(p_hw_lpuart, p_devinfo->work_mode);
    }
    p_dev->work_mode = p_devinfo->work_mode;


    /* ����ģʽ2/3���ҿ����˶����ַ�Զ�ʶ�������������� */
    if((p_devinfo->work_mode == 2) || (p_devinfo->work_mode == 3)) {

        if((p_devinfo->mut_addr.enable == AM_TRUE)) {

            /* ���ôӻ���ַ����Ա������������豸���͵����ݶ��ԣ�*/
            amhw_zsn700_lpuart_slaver_addr_set(p_hw_lpuart,
                                               p_devinfo->mut_addr.addr);

            /* ���õ�ַ���� */
            amhw_zsn700_lpuart_slaver_addr_set(p_hw_lpuart,
                                               p_devinfo->mut_addr.addr_mask);

            /* �����ַ�Զ�ʶ��ʹ�� */
            amhw_zsn700_lpuart_enable(p_hw_lpuart,
                                      AMHW_ZSN700_LPUART_MUT_ADR_AUTO);
        }
    }

    /* ��ȡ���ڼ��鷽ʽ����ѡ�� */
    if (p_devinfo->cfg_flags & (AMHW_ZSN700_LPUART_HW_PARITY_ODD)) {
        p_dev->options |= AM_UART_PARENB | AM_UART_PARODD;
    } else if(p_devinfo->cfg_flags & (AMHW_ZSN700_LPUART_HW_PARITY_EVEN)){
        p_dev->options |= AM_UART_PARENB;
    } else {

    }

    /* ��ȡ����ֹͣλ����ѡ�� */
    if (p_devinfo->cfg_flags & (AMHW_ZSN700_LPUART_STOP_2_0_BIT)) {
        p_dev->options |= AM_UART_STOPB;
    } else {

    }

    /* �ȴ����Ϳ���� */
    while (amhw_zsn700_lpuart_flag_check(
               p_hw_lpuart, AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) == AM_FALSE);

    __lpuart_opt_set (p_dev, p_dev->options);

    /* ����ģʽ���ã������أ�������أ�Ӳ�����أ�*/
    __lpuart_flow_mode_set(p_dev, AM_UART_FLOWCTL_NO);

    /* ���ò����� */
    p_dev->baud_rate = amhw_zsn700_lpuart_baudrate_set(p_hw_lpuart,
                                                       p_dev->clk_rate,
                                                       p_devinfo->baud_rate);
    /* Ĭ����ѯģʽ */
    __lpuart_mode_set(p_dev, AM_UART_MODE_POLL);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_lpuart_enable(p_hw_lpuart,AMHW_ZSN700_LPUART_RX);

    if (p_dev->p_devinfo->pfn_rs485_dir) {

        /* ��ʼ�� 485 Ϊ����ģʽ */
        p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
    }

    return &(p_dev->lpuart_serv);
}

/**
 * \brief ����ȥ��ʼ��
 */
void am_zsn700_lpuart_deinit (am_zsn700_lpuart_dev_t *p_dev)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = (amhw_zsn700_lpuart_t *)
                                        p_dev->p_devinfo->lpuart_reg_base;
    p_dev->lpuart_serv.p_funcs   = NULL;
    p_dev->lpuart_serv.p_drv     = NULL;

    if (p_dev->channel_mode == AM_UART_MODE_INT) {

        /* Ĭ��Ϊ��ѯģʽ */
        __lpuart_mode_set(p_dev, AM_UART_MODE_POLL);
    }

    amhw_zsn700_lpuart_disable(p_hw_lpuart,AMHW_ZSN700_LPUART_RX);
    amhw_zsn700_lpuart_disable(p_hw_lpuart,AMHW_ZSN700_LPUART_CTS);
    amhw_zsn700_lpuart_disable(p_hw_lpuart,AMHW_ZSN700_LPUART_RTS);
    amhw_zsn700_lpuart_disable(p_hw_lpuart,AMHW_ZSN700_LPUART_DMA_TX);
    amhw_zsn700_lpuart_disable(p_hw_lpuart,AMHW_ZSN700_LPUART_DMA_RX);
    amhw_zsn700_lpuart_disable(p_hw_lpuart,AMHW_ZSN700_LPUART_MUT_ADR_AUTO);

    am_int_disable(p_dev->p_devinfo->inum);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
