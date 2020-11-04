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
 * - 1.02 20-05-15  licl, rewrite irq handler
 * - 1.00 19-09-19  zp, first implementation
 * \endinternal
 */
#include "am_hc32_uart.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"
#include "hc32_clk.h"
#include "am_hc32.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/** \brief ����ģʽ����ѯ���жϣ����� */
static int __uart_mode_set (am_hc32_uart_dev_t *p_dev, uint32_t new_mode);

/** \brief ����Ӳ������ */
static int __uart_opt_set (am_hc32_uart_dev_t *p_dev, uint32_t opts);

/** \brief HC32 ���������������� */
static int __uart_ioctl (void *p_drv, int, void *);

static int __uart_tx_startup (void *p_drv);

static int __uart_callback_set (void *p_drv,
                                int   callback_type,
                                void *pfn_callback,
                                void *p_arg);

static int __uart_poll_getchar (void *p_drv, char *p_char);

static int __uart_poll_putchar (void *p_drv, char outchar);

static void __uart0_2_irq_handler (void *p_arg);
static void __uart1_3_irq_handler (void *p_arg);

/** \brief �����豸�� */
static am_hc32_uart_dev_t *g_dev_plist[4];

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
    am_hc32_uart_dev_t *p_dev     = (am_hc32_uart_dev_t *)p_drv;
    amhw_hc32_uart_t   *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    int status = AM_OK;

    switch (request) {

    /* ���������� */
    case AM_UART_BAUD_SET:

        /* ֻ���ڷ��ͿյĻ����ϲ������޸Ĳ����� */
        while (amhw_hc32_uart_flag_check(
                   p_hw_uart, AMHW_HC32_UART_FLAG_TX_EMPTY) == AM_FALSE);

        status = amhw_hc32_uart_baudrate_set(
                     p_hw_uart, p_dev->clk_rate, (uint32_t)p_arg);

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
        status = -AM_ENOTSUP;
        break;

    /* ���ý���������״̬ */
    case AM_UART_FLOWSTAT_RX_SET:
        status = -AM_ENOTSUP;
        break;

        /* ��ȡ����������״̬ */
    case AM_UART_FLOWSTAT_TX_GET:
        status = -AM_ENOTSUP;
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

    am_hc32_uart_dev_t *p_dev     = (am_hc32_uart_dev_t *)p_drv;
    amhw_hc32_uart_t   *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    /* ʹ�� 485 ���Ϳ������� */
    if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {
        p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
    }

    /* �ȴ���һ�δ������ */
    while (amhw_hc32_uart_flag_check(
               p_hw_uart, AMHW_HC32_UART_FLAG_TX_EMPTY) == AM_FALSE);

    /* �жϷ���״̬ */
    if (p_hw_uart->scon  & AMHW_HC32_UART_INT_TX_COMPLETE) {

    } else {

        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {

            amhw_hc32_uart_data_write(p_hw_uart, data);

            /* ʹ�ܷ�������ж� */
            amhw_hc32_uart_int_enable(p_hw_uart, AMHW_HC32_UART_INT_TX_COMPLETE);
        }
    }

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
    am_hc32_uart_dev_t *p_dev = (am_hc32_uart_dev_t *)p_drv;

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
    am_hc32_uart_dev_t *p_dev     = (am_hc32_uart_dev_t *)p_drv;
    amhw_hc32_uart_t   *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    /* ����ģ���Ƿ����, AM_FALSE:æ; TURE: ���� */
    if(amhw_hc32_uart_flag_check(
           p_hw_uart, AMHW_HC32_UART_FLAG_TX_EMPTY) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        if ((p_dev->rs485_en) && (p_dev->p_devinfo->pfn_rs485_dir != NULL)) {

            /* ���� 485 Ϊ����ģʽ */
            p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
        }

        /* ����һ���ַ� */
        amhw_hc32_uart_data_write(p_hw_uart, outchar);

        /* �ȴ�������� */
        while (amhw_hc32_uart_flag_check(
                   p_hw_uart, AMHW_HC32_UART_FLAG_TX_EMPTY) == AM_FALSE);

        if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {
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
    am_hc32_uart_dev_t *p_dev     = (am_hc32_uart_dev_t *)p_drv;
    amhw_hc32_uart_t   *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    uint8_t *p_inchar = (uint8_t *)p_char;

    /* ����ģ���Ƿ���У�AM_FALSE:æ,���ڽ���; TURE: �Ѿ����յ�һ���ַ� */
    if(amhw_hc32_uart_flag_check(
           p_hw_uart, AMHW_HC32_UART_FLAG_RX_COMPLETE) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        /* ����һ���ַ� */
        *p_inchar = amhw_hc32_uart_data_read(p_hw_uart);

        amhw_hc32_uart_flag_clr(p_hw_uart,
                                AMHW_HC32_UART_FLAG_RX_COMPLETE);
    }

    return (AM_OK);
}

/**
 * \brief ���ô���ģʽ
 */
static int __uart_mode_set (am_hc32_uart_dev_t *p_dev, uint32_t new_mode)
{
    amhw_hc32_uart_t *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    /* ��֧������ģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }

    if (new_mode == AM_UART_MODE_INT) {
        if (p_dev->p_devinfo->inum == 6){
            am_int_connect(p_dev->p_devinfo->inum,
                           __uart0_2_irq_handler,
                           (void *)g_dev_plist);
            if (p_dev->p_devinfo->uart_reg_base == HC32_UART0_BASE) {
                g_dev_plist[0] = p_dev;
            } else {
                g_dev_plist[2] = p_dev;
            }
        } else {
            am_int_connect(p_dev->p_devinfo->inum,
                           __uart1_3_irq_handler,
                           (void *)g_dev_plist);
            if (p_dev->p_devinfo->uart_reg_base == HC32_UART1_BASE) {
                g_dev_plist[1] = p_dev;
            } else {
                g_dev_plist[3] = p_dev;
            }
        }
        am_int_enable(p_dev->p_devinfo->inum);

        /* ʹ�ܽ�������ж� */
        amhw_hc32_uart_int_enable(p_hw_uart, AMHW_HC32_UART_INT_RX_COMPLETE);
    } else {

        /* �ر����д����ж� */
        amhw_hc32_uart_int_disable(p_hw_uart, AMHW_HC32_UART_INT_ALL);
    }

    p_dev->channel_mode = new_mode;

    return (AM_OK);
}

/**
 * \brief ����ѡ������
 */
static int __uart_opt_set (am_hc32_uart_dev_t *p_dev, uint32_t options)
{
    amhw_hc32_uart_t *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    uint32_t          cfg_flags = 0;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* ����ֹͣλ */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x3ul << 14);
        cfg_flags |= AMHW_HC32_UART_STOP_2_0_BIT;
    } else {
        cfg_flags &= ~(0x3ul << 14);
        cfg_flags |= AMHW_HC32_UART_STOP_1_0_BIT;
    }

    /* ���ü��鷽ʽ */
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x3ul << 2);

        if (options & AM_UART_PARODD) {
            cfg_flags |= AMHW_HC32_UART_HW_PARITY_ODD;
        } else {
            cfg_flags |= AMHW_HC32_UART_HW_PARITY_EVEN;
        }
        amhw_hc32_uart_mode_sel(p_hw_uart, AMHW_HC32_UART_WORK_MODE_3);
    } else {
        cfg_flags &= ~(0x3ul << 2);
        cfg_flags |= AMHW_HC32_UART_PARITY_NO;
        amhw_hc32_uart_mode_sel(p_hw_uart, AMHW_HC32_UART_WORK_MODE_1);
    }

    /* �������Ч���� */
    amhw_hc32_uart_stop_bit_sel(p_hw_uart  , (cfg_flags & (0x3ul << 14)));
    amhw_hc32_uart_parity_bit_sel(p_hw_uart, (cfg_flags & (0x3ul << 2)));

    p_dev->options = options;

    return (AM_OK);
}

/*******************************************************************************
  UART interrupt request handler
*******************************************************************************/

/**
 * \brief ���ڽ����жϷ���
 */
static void __uart_irq_rx_handler (am_hc32_uart_dev_t *p_dev)
{
    amhw_hc32_uart_t *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    char data;

    /* �Ƿ�Ϊ����Rx�ж� */
    if (amhw_hc32_uart_flag_check(
            p_hw_uart, AMHW_HC32_UART_FLAG_RX_COMPLETE) == AM_TRUE) {

        amhw_hc32_uart_flag_clr(p_hw_uart, AMHW_HC32_UART_FLAG_RX_COMPLETE);

        /* ��ȡ�½������� */
        data = amhw_hc32_uart_data_read(p_hw_uart);

        /* ����½������� */
        p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
    }
}

/**
 * \brief ���ڷ����жϷ���
 */
static void __uart_irq_tx_handler (am_hc32_uart_dev_t *p_dev)
{
    amhw_hc32_uart_t *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;

    char data;

    if (amhw_hc32_uart_flag_check(
            p_hw_uart, AMHW_HC32_UART_FLAG_TX_COMPLETE) == AM_TRUE) {

        amhw_hc32_uart_flag_clr(p_hw_uart, AMHW_HC32_UART_FLAG_TX_COMPLETE);

        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_hc32_uart_data_write(p_hw_uart, data);
        } else {

            /* û�����ݴ��;͹رշ����ж� */
            amhw_hc32_uart_int_disable(p_hw_uart,
                                         AMHW_HC32_UART_FLAG_TX_COMPLETE);

            /* ����485���Ϳ������� */
            if ((p_dev->rs485_en) && (p_dev->p_devinfo->pfn_rs485_dir)) {

                /* ���� 485 Ϊ����ģʽ */
                p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
            }
        }
    }
}

/**
 * \brief ѡ�񴮿ڶ���
 */
static void __uart_irq_sel (am_hc32_uart_dev_t *p_dev)
{
    uint32_t uart_int_stat = 0;
    amhw_hc32_uart_t *p_hw_uart =
            (amhw_hc32_uart_t *)(p_dev->p_devinfo->uart_reg_base);

    /* �ж��ж����� */
    uart_int_stat = amhw_hc32_uart_flag_get(p_hw_uart);

    if (amhw_hc32_uart_flag_check(
            p_hw_uart, AMHW_HC32_UART_FLAG_RX_COMPLETE) == AM_TRUE) {
        __uart_irq_rx_handler(p_dev);
    } else if (amhw_hc32_uart_flag_check(
            p_hw_uart, AMHW_HC32_UART_FLAG_TX_COMPLETE) == AM_TRUE) {
        __uart_irq_tx_handler(p_dev);
    } else {
    }

    /* �����ж� */
    if ((p_dev->other_int_enable & uart_int_stat) != 0) {
        uart_int_stat &= p_dev->other_int_enable;
        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AM_HC32_UART_ERRCODE_UART_OTHER_INT,
                           (void *)p_hw_uart,
                           1);
        }
    }
}

/**
 * \brief ����0��2�жϷ�����
 */
static void __uart0_2_irq_handler (void *p_arg)
{
    int i;
    am_hc32_uart_dev_t  *p_dev = NULL;

    for (i = 0; i < 4; i += 2) {

        p_dev = g_dev_plist[i];

        if (p_dev == NULL) {
            continue;
        }

        __uart_irq_sel(p_dev);
    }
}

/**
 * \brief ����1��3�жϷ�����
 */
static void __uart1_3_irq_handler (void *p_arg)
{
    int i;
    am_hc32_uart_dev_t  *p_dev           = NULL;

    for (i = 1; i < 4; i += 2) {

        p_dev = g_dev_plist[i];

        if (p_dev == NULL) {
            continue;
        }

        __uart_irq_sel(p_dev);
    }
}

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
am_uart_handle_t am_hc32_uart_init (am_hc32_uart_dev_t           *p_dev,
                                    const am_hc32_uart_devinfo_t *p_devinfo)
{
    amhw_hc32_uart_t  *p_hw_uart;

    if (p_devinfo == NULL) {
        return NULL;
    }

    /* ��ȡ���ò��� */
    p_hw_uart                = (amhw_hc32_uart_t  *)p_devinfo->uart_reg_base;
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
                               ~(AMHW_HC32_UART_INT_TX_COMPLETE |
                                 AMHW_HC32_UART_INT_RX_COMPLETE);

    p_dev->rs485_en          = AM_FALSE;

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    /* ʹ���첽��˫�������ߣ�ģʽ */
    if (AM_TRUE == p_devinfo->asyn_hd) {
        amhw_hc32_uart_single_line_half_enable(p_hw_uart);
    }

    /* ��ȡ���ڼ��鷽ʽ����ѡ�� */
    if ((p_devinfo->cfg_flags & (0xc)) == (AMHW_HC32_UART_HW_PARITY_ODD)) {
        p_dev->options |= AM_UART_PARENB | AM_UART_PARODD;
    } else if ((p_devinfo->cfg_flags & (0xc)) == (AMHW_HC32_UART_HW_PARITY_EVEN)){
        p_dev->options |= AM_UART_PARENB;
    } else {

    }

    /* ��ȡ����ֹͣλ����ѡ�� */
    if (p_devinfo->cfg_flags & (AMHW_HC32_UART_STOP_2_0_BIT)) {
        p_dev->options |= AM_UART_STOPB;
    } else {

    }

    /* �ȴ����Ϳ���� */
    while (amhw_hc32_uart_flag_check(
            p_hw_uart, AMHW_HC32_UART_FLAG_TX_EMPTY) == AM_FALSE);

    __uart_opt_set (p_dev, p_dev->options);

    p_dev->clk_rate = am_clk_rate_get(CLK_PCLK);

    /* ���ò����� */
    p_dev->baud_rate = amhw_hc32_uart_baudrate_set(
                                     p_hw_uart,
                                     p_dev->clk_rate,
                                     p_devinfo->baud_rate);
    /* Ĭ����ѯģʽ */
    __uart_mode_set(p_dev, AM_UART_MODE_POLL);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_hc32_uart_enable(p_hw_uart, AMHW_HC32_UART_RX);

    if (p_dev->p_devinfo->pfn_rs485_dir) {

        /* ��ʼ�� 485 Ϊ����ģʽ */
        p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
    }

    return &(p_dev->uart_serv);
}

/**
 * \brief ����ȥ��ʼ��
 */
void am_hc32_uart_deinit (am_hc32_uart_dev_t *p_dev)
{
    amhw_hc32_uart_t *p_hw_uart =
            (amhw_hc32_uart_t *)p_dev->p_devinfo->uart_reg_base;
    p_dev->uart_serv.p_funcs    = NULL;
    p_dev->uart_serv.p_drv      = NULL;

    if (p_dev->channel_mode == AM_UART_MODE_INT) {

        /* Ĭ��Ϊ��ѯģʽ */
        __uart_mode_set(p_dev, AM_UART_MODE_POLL);
    }

    amhw_hc32_uart_disable(p_hw_uart,AMHW_HC32_UART_RX);
    amhw_hc32_uart_disable(p_hw_uart,AMHW_HC32_UART_CTS);
    amhw_hc32_uart_disable(p_hw_uart,AMHW_HC32_UART_RTS);
    amhw_hc32_uart_disable(p_hw_uart,AMHW_HC32_UART_DMA_TX);
    amhw_hc32_uart_disable(p_hw_uart,AMHW_HC32_UART_DMA_RX);
    amhw_hc32_uart_disable(p_hw_uart,AMHW_HC32_UART_MUT_ADR_AUTO);

    am_int_disable(p_dev->p_devinfo->inum);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
