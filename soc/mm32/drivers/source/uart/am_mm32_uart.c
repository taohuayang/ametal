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
 * \brief UART ����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */
#include "am_mm32_uart.h"
#include "am_clk.h"
#include "am_int.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

#define  __UART_CLK_RATE   24000000

/**
 * \brief ����ģʽ����ѯ���жϣ�����
 */
int __uart_mode_set (am_mm32_uart_dev_t *p_dev, uint32_t new_mode);

/**
 * \brief ����Ӳ������
 */
int __uart_opt_set (am_mm32_uart_dev_t *p_dev, uint32_t opts);

/* ZLG ���������������� */
static int __uart_ioctl (void *p_drv, int, void *);

static int __uart_tx_startup (void *p_drv);

static int __uart_callback_set (void *p_drv,
                                int   callback_type,
                                void *pfn_callback,
                                void *p_arg);

static int __uart_poll_getchar (void *p_drv, char *p_char);

static int __uart_poll_putchar (void *p_drv, char outchar);

#if 0
static int __uart_connect (void *p_drv);
#endif

static void __uart_irq_handler (void *p_arg);

/** \brief ��׼��ӿں���ʵ�� */
static const struct am_uart_drv_funcs __g_uart_drv_funcs = {
    __uart_ioctl,
    __uart_tx_startup,
    __uart_callback_set,
    __uart_poll_getchar,
    __uart_poll_putchar,
};

/******************************************************************************/

/**
 * \brief �豸���ƺ���
 *
 * ���а������û�ȡ�����ʣ�ģʽ���ã��ж�/��ѯ������ȡ֧�ֵ�ģʽ��Ӳ��ѡ�����õȹ��ܡ�
 */
static int __uart_ioctl (void *p_drv, int request, void *p_arg)
{
    am_mm32_uart_dev_t *p_dev     = (am_mm32_uart_dev_t *)p_drv;
    amhw_mm32_uart_t   *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    int status = AM_OK;

    switch (request) {

    /* ���������� */
    case AM_UART_BAUD_SET:

        /* ֻ���ڵ�ǰ������ɵĻ����ϲ������޸Ĳ����� */
        while (amhw_mm32_uart_status_flag_check(p_hw_uart, AMHW_MM32_UART_TX_COMPLETE_FALG) == AM_FALSE);

        status = amhw_mm32_uart_baudrate_set(p_hw_uart,
                                               am_clk_rate_get(p_dev->p_devinfo->clk_num),
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
        status = (__uart_mode_set(p_dev, (int)p_arg) == AM_OK)
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
        status = (__uart_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    /* ����ѡ���ȡ */
    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_dev->options;
        break;

    case AM_UART_RS485_SET:
        if (p_dev->rs485_en != (am_bool_t)(int)p_arg) {
            p_dev->rs485_en = (am_bool_t)(int)p_arg;
        }
        break;

    case AM_UART_RS485_GET:
        *(int *)p_arg = p_dev->rs485_en;
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
int __uart_tx_startup (void *p_drv)
{
    char data  = 0;

    am_mm32_uart_dev_t *p_dev     = (am_mm32_uart_dev_t *)p_drv;
    amhw_mm32_uart_t   *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    /* ʹ�� 485 ���Ϳ������� */
    if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {
        p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
    }

    /* �ȴ���һ�δ������ */
    while (amhw_mm32_uart_status_flag_check(p_hw_uart, AMHW_MM32_UART_TX_COMPLETE_FALG) == AM_FALSE);

    /* ��ȡ�������ݲ����� */
    if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
        amhw_mm32_uart_data_write(p_hw_uart, data);
    }

    /* ʹ�ܷ����ж� */
    amhw_mm32_uart_int_enable(p_hw_uart, AMHW_MM32_UART_INT_TX_EMPTY_ENABLE);
    return AM_OK;
}

/**
 * \brief �����жϷ���ص�����
 */
static int __uart_callback_set (void  *p_drv,
                                int    callback_type,
                                void  *pfn_callback,
                                void  *p_arg)
{
    am_mm32_uart_dev_t *p_dev = (am_mm32_uart_dev_t *)p_drv;

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
static int __uart_poll_putchar (void *p_drv, char outchar)
{
    am_mm32_uart_dev_t *p_dev     = (am_mm32_uart_dev_t *)p_drv;
    amhw_mm32_uart_t   *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    /* ����ģ���Ƿ����, AM_FALSE:æ; TURE: ���� */
    if(amhw_mm32_uart_status_flag_check(p_hw_uart, AMHW_MM32_UART_TX_EMPTY_FLAG) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        if ((p_dev->rs485_en) && (p_dev->p_devinfo->pfn_rs485_dir != NULL)) {

            /* ���� 485 Ϊ����ģʽ */
            p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
        }

        /* ����һ���ַ� */
        amhw_mm32_uart_data_write(p_hw_uart, outchar);

        if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {

            /* �ȴ�������� */
            while (!(p_hw_uart->csr & 0x01));

            p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
        }
    }

    return (AM_OK);
}

/**
 * \brief ��ѯģʽ�½����ַ�
 */
static int __uart_poll_getchar (void *p_drv, char *p_char)
{
    am_mm32_uart_dev_t *p_dev     = (am_mm32_uart_dev_t *)p_drv;
    amhw_mm32_uart_t   *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    uint8_t           *p_inchar  = (uint8_t *)p_char;

    /* ����ģ���Ƿ���У�AM_FALSE:æ,���ڽ���; TURE: �Ѿ����յ�һ���ַ� */
    if(amhw_mm32_uart_status_flag_check(p_hw_uart, AMHW_MM32_UART_RX_VAL_FLAG) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        /* ����һ���ַ� */
        *p_inchar = amhw_mm32_uart_data_read(p_hw_uart);
    }

    return (AM_OK);
}

/**
 * \brief ���ô���ģʽ
 */
int __uart_mode_set (am_mm32_uart_dev_t *p_dev, uint32_t new_mode)
{
    amhw_mm32_uart_t *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    /* ��֧������ģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }

    if (new_mode == AM_UART_MODE_INT) {

        am_int_connect(p_dev->p_devinfo->inum,
                       __uart_irq_handler,
                       (void *)p_dev);
        am_int_enable(p_dev->p_devinfo->inum);

        /* ʹ��RDRF����׼�ж� */
        amhw_mm32_uart_int_enable(p_hw_uart, AMHW_MM32_UART_INT_RX_VAL_ENABLE);
    } else {

        /* �ر����д����ж� */
        amhw_mm32_uart_int_disable(p_hw_uart, AMHW_MM32_UART_INT_ALL_ENABLE_MASK);
    }

    p_dev->channel_mode = new_mode;

    return (AM_OK);
}

/**
 * \brief ����ѡ������
 */
int __uart_opt_set (am_mm32_uart_dev_t *p_dev, uint32_t options)
{
    amhw_mm32_uart_t *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    uint8_t          cfg_flags = 0;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* �ڸı�UART�Ĵ���ֵǰ ���շ��ͽ��� */
    amhw_mm32_uart_disable(p_hw_uart);

    /* �������ݳ��� */
    switch (options & AM_UART_CSIZE) {

    case AM_UART_CS5:
        cfg_flags |= AMHW_MM32_UART_DATA_5BIT;
        break;

    case AM_UART_CS6:
        cfg_flags |= AMHW_MM32_UART_DATA_6BIT;
        break;

    case AM_UART_CS7:
        cfg_flags |= AMHW_MM32_UART_DATA_7BIT;
        break;

    case AM_UART_CS8:
        cfg_flags |= AMHW_MM32_UART_DATA_8BIT;
        break;

    default:
        break;
    }

    /* ����ֹͣλ */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x1 << 2);
        cfg_flags |= AMHW_MM32_UART_STOP_2BIT;
    } else {
        cfg_flags &= ~(0x1 << 2);
        cfg_flags |= AMHW_MM32_UART_STOP_1BIT;
    }

    /* ���ü��鷽ʽ */
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x3 << 0);

        if (options & AM_UART_PARODD) {
            cfg_flags |= AMHW_MM32_UART_PARITY_ODD;
        } else {
            cfg_flags |= AMHW_MM32_UART_PARITY_EVEN;
        }
    } else {
        cfg_flags &= ~(0x3 << 0);
        cfg_flags |= AMHW_MM32_UART_PARITY_NO;
    }

    /* �������Ч���� */
    amhw_mm32_uart_stop_bit_sel(p_hw_uart, (cfg_flags & 0x4));
    amhw_mm32_uart_data_length(p_hw_uart, (cfg_flags & 0x30));
    amhw_mm32_uart_parity_bit_sel(p_hw_uart, (cfg_flags & 0x3));

    amhw_mm32_uart_enable(p_hw_uart);

    p_dev->options = options;

    return (AM_OK);
}

/*******************************************************************************
  UART interrupt request handler
*******************************************************************************/

/**
 * \brief ���ڽ����жϷ���
 */
void __uart_irq_rx_handler (am_mm32_uart_dev_t *p_dev)
{
    amhw_mm32_uart_t *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    char data;

    /* �Ƿ�Ϊ����Rx�ж� */
    if (amhw_mm32_uart_int_flag_check(p_hw_uart,AMHW_MM32_UART_INT_RX_VAL_FLAG) == AM_TRUE) {

        amhw_mm32_uart_int_flag_clr(p_hw_uart, AMHW_MM32_UART_INT_RX_VAL_FLAG_CLR);

        /* ��ȡ�½������� */
        data = amhw_mm32_uart_data_read(p_hw_uart);

        /* ����½������� */
        p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
    }
}

/**
 * \brief ���ڷ����жϷ���
 */
void __uart_irq_tx_handler (am_mm32_uart_dev_t *p_dev)
{
    amhw_mm32_uart_t *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    char data;

    if (amhw_mm32_uart_int_flag_check(p_hw_uart,AMHW_MM32_UART_INT_TX_EMPTY_FLAG) == AM_TRUE) {

        amhw_mm32_uart_int_flag_clr(p_hw_uart, AMHW_MM32_UART_INT_TX_EMPTY_FLAG_CLR);

        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_mm32_uart_data_write(p_hw_uart, data);
        } else {

            /* û�����ݴ��;͹رշ����ж� */
            amhw_mm32_uart_int_disable(p_hw_uart, AMHW_MM32_UART_INT_TX_EMPTY_ENABLE);

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
void __uart_irq_handler (void *p_arg)
{
    am_mm32_uart_dev_t  *p_dev     = (am_mm32_uart_dev_t *)p_arg;
    amhw_mm32_uart_t    *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    uint32_t uart_int_stat        = amhw_mm32_uart_int_flag_get(p_hw_uart);

    if (amhw_mm32_uart_int_flag_check(p_hw_uart,AMHW_MM32_UART_INT_RX_VAL_FLAG) == AM_TRUE) {
         __uart_irq_rx_handler(p_dev);
    } else if (amhw_mm32_uart_int_flag_check(p_hw_uart,AMHW_MM32_UART_INT_TX_EMPTY_FLAG) == AM_TRUE) {
        __uart_irq_tx_handler(p_dev);
    } else {

    }

    /* �����ж� */
    if ((p_dev->other_int_enable & uart_int_stat) != 0) {

        uart_int_stat &= p_dev->other_int_enable;

        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AM_MM32_UART_ERRCODE_UART_OTHER_INT,
                           (void *)p_hw_uart,
                           1);
        }
    }

}

#if 0
/**
 * \brief UART�жϺ������ӣ���ʹ���ж�ģʽʱ��Ҫ���ô˺���
 */
int __uart_connect (void *p_drv)
{
    am_mm32_uart_dev_t *p_dev = (am_mm32_uart_dev_t *)p_drv;

    /* �����ж������ţ������ж� */
    am_int_connect(p_dev->p_devinfo->inum, __uart_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    amhw_mm32_uart_int_enable(p_dev->p_devinfo->uart_reg_base,
                                p_dev->other_int_enable);

    return AM_OK;
}
#endif /* 0 */

/**
 * \brief Ĭ�ϻص�����
 *
 * \returns AW_ERROR
 */
static int __uart_dummy_callback (void *p_arg, char *p_outchar)
{
    return (AM_ERROR);
}

/**
 * \brief ���ڳ�ʼ������
 */
am_uart_handle_t am_mm32_uart_init (am_mm32_uart_dev_t           *p_dev,
                                      const am_mm32_uart_devinfo_t *p_devinfo)
{
    amhw_mm32_uart_t  *p_hw_uart;
    uint32_t          tmp;

    if (p_devinfo == NULL) {
        return NULL;
    }

    /* ��ȡ���ò��� */
    p_hw_uart                = (amhw_mm32_uart_t  *)p_devinfo->uart_reg_base;
    p_dev->p_devinfo         = p_devinfo;
    p_dev->uart_serv.p_funcs = (struct am_uart_drv_funcs *)&__g_uart_drv_funcs;
    p_dev->uart_serv.p_drv   = p_dev;
    p_dev->baud_rate         = p_devinfo->baud_rate;
    p_dev->options           = 0;

    /* ��ʼ��Ĭ�ϻص����� */
    p_dev->pfn_txchar_get    = (int (*) (void *, char*))__uart_dummy_callback;
    p_dev->txget_arg         = NULL;
    p_dev->pfn_rxchar_put    = (int (*) (void *, char ))__uart_dummy_callback;
    p_dev->rxput_arg         = NULL;
    p_dev->pfn_err           =
                     (int (*) (void *, int, void*, int))__uart_dummy_callback;

    p_dev->err_arg           = NULL;

    p_dev->other_int_enable  = p_devinfo->other_int_enable  &
                               ~(AMHW_MM32_UART_INT_TX_EMPTY_ENABLE |
                                 AMHW_MM32_UART_INT_RX_VAL_ENABLE);
    p_dev->rs485_en          = AM_FALSE;

    /* ��ȡ�������ݳ�������ѡ�� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 4) & 0x03;

    switch (tmp) {

    case 0:
        p_dev->options |= AM_UART_CS5;
        break;

    case 1:
        p_dev->options |= AM_UART_CS6;
        break;
    case 2:
        p_dev->options |= AM_UART_CS7;
        break;
    case 3:
        p_dev->options |= AM_UART_CS8;
        break;

    default:
        p_dev->options |= AM_UART_CS8;
        break;
    }

    /* ����UARTʱ�� */
    am_clk_enable(p_devinfo->clk_num);

    /* ��ȡ���ڼ��鷽ʽ����ѡ�� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 0) & 0x03;

    if (tmp == 1) {
        p_dev->options |= AM_UART_PARENB | AM_UART_PARODD;
    } else {
    }

    /* ��ȡ����ֹͣλ����ѡ�� */
    if (p_devinfo->cfg_flags & (AMHW_MM32_UART_STOP_2BIT)) {
        p_dev->options |= AM_UART_STOPB;
    } else {

    }

    /* �ȴ���һ�δ������ */
    while (amhw_mm32_uart_status_flag_check(p_hw_uart, AMHW_MM32_UART_TX_COMPLETE_FALG) == AM_FALSE);

    __uart_opt_set (p_dev, p_dev->options);

    /* ���ò����� */
    p_dev->baud_rate = amhw_mm32_uart_baudrate_set(
                                     p_hw_uart,
                                     am_clk_rate_get(p_dev->p_devinfo->clk_num),
                                     p_devinfo->baud_rate);
    /* Ĭ����ѯģʽ */
    __uart_mode_set(p_dev, AM_UART_MODE_POLL);

    /* uartʹ�� */

    amhw_mm32_uart_rx_enable(p_hw_uart,AM_TRUE);
    amhw_mm32_uart_tx_enable(p_hw_uart,AM_TRUE);
    amhw_mm32_uart_enable(p_hw_uart);

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    if (p_dev->p_devinfo->pfn_rs485_dir) {

        /* ��ʼ�� 485 Ϊ����ģʽ */
        p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
    }

    return &(p_dev->uart_serv);
}

/**
 * \brief ����ȥ��ʼ��
 */
void am_mm32_uart_deinit (am_mm32_uart_dev_t *p_dev)
{
    amhw_mm32_uart_t *p_hw_uart = (amhw_mm32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    p_dev->uart_serv.p_funcs   = NULL;
    p_dev->uart_serv.p_drv     = NULL;

    if (p_dev->channel_mode == AM_UART_MODE_INT) {

        /* Ĭ��Ϊ��ѯģʽ */
        __uart_mode_set(p_dev, AM_UART_MODE_POLL);
    }

    /* �رմ��� */
    amhw_mm32_uart_disable(p_hw_uart);

    am_int_disable(p_dev->p_devinfo->inum);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
