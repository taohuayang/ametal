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
#include "am_zlg237_usart.h"
#include "am_delay.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

#define  __UART_CLK_RATE   24000000

/**
 * \brief ����ģʽ����ѯ���жϣ�����
 */
int __usart_mode_set (am_zlg237_usart_dev_t *p_dev, uint32_t new_mode);

/**
 * \brief ����Ӳ������
 */
int __usart_opt_set (am_zlg237_usart_dev_t *p_dev, uint32_t opts);

/**
 * \brief ���ؽ���������״̬����
 */
static int __usart_flow_rxstat_set (am_zlg237_usart_dev_t *p_dev, uint32_t ctrl);

/**
 * \brief ����ģʽ����
 */
static int __usart_flow_mode_set (am_zlg237_usart_dev_t *p_dev, uint32_t mode);

/**
 * \brief ���ط���������״̬��ȡ
 */
static int __usart_flow_txstat_get (am_zlg237_usart_dev_t *p_dev);

/* ZLG237 ���������������� */
static int __usart_ioctl (void *p_drv, int, void *);

static int __usart_tx_startup (void *p_drv);

static int __usart_callback_set (void *p_drv,
                                int   callback_type,
                                void *pfn_callback,
                                void *p_arg);

static int __usart_poll_getchar (void *p_drv, char *p_char);

static int __usart_poll_putchar (void *p_drv, char outchar);

#if 0
static int __usart_connect (void *p_drv);
#endif

static void __usart_irq_handler (void *p_arg);

/** \brief ��׼��ӿں���ʵ�� */
static const struct am_uart_drv_funcs __g_uart_drv_funcs = {
    __usart_ioctl,
    __usart_tx_startup,
    __usart_callback_set,
    __usart_poll_getchar,
    __usart_poll_putchar,
};

/******************************************************************************/

/**
 * \brief �豸���ƺ���
 *
 * ���а������û�ȡ�����ʣ�ģʽ���ã��ж�/��ѯ������ȡ֧�ֵ�ģʽ��Ӳ��ѡ�����õȹ��ܡ�
 */
static int __usart_ioctl (void *p_drv, int request, void *p_arg)
{
    am_zlg237_usart_dev_t *p_dev     = (am_zlg237_usart_dev_t *)p_drv;
    amhw_zlg237_usart_t   *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    int status = AM_OK;

    switch (request) {

    /* ���������� */
    case AM_UART_BAUD_SET:

        /* ֻ���ڵ�ǰ������ɵĻ����ϲ������޸Ĳ����� */
        while (amhw_zlg237_usart_status_flag_check(p_hw_usart, AMHW_ZLG237_USART_TX_COMPLETE_FLAG) == AM_FALSE);

        status = amhw_zlg237_usart_baudrate_set(p_hw_usart,
                                               am_clk_rate_get(p_dev->p_devinfo->clk_num),
                                               (uint32_t)p_arg);

        if (status > 0) {

            /* �Ĵ�����Ҫ����ʹ�� UART ������Ч */
            amhw_zlg237_usart_disable(p_hw_usart);
            amhw_zlg237_usart_enable(p_hw_usart);

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
        status = (__usart_mode_set(p_dev, (int)p_arg) == AM_OK)
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
        status = (__usart_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    /* ����ѡ���ȡ */
    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_dev->options;
        break;

    /* ��������ģʽ */
    case AM_UART_FLOWMODE_SET:
        __usart_flow_mode_set(p_dev, (int)p_arg);
        break;

    /* ���ý���������״̬ */
    case AM_UART_FLOWSTAT_RX_SET:
        __usart_flow_rxstat_set(p_dev, (int)p_arg);
        break;

    /* ��ȡ����������״̬ */
    case AM_UART_FLOWSTAT_TX_GET:
        *(int *)p_arg = __usart_flow_txstat_get(p_dev);
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
int __usart_tx_startup (void *p_drv)
{
    char data  = 0;

    am_zlg237_usart_dev_t *p_dev     = (am_zlg237_usart_dev_t *)p_drv;
    amhw_zlg237_usart_t   *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    /* ʹ�� 485 ���Ϳ������� */
    if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {
        p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
    }

    /* �ȴ���һ�δ������ */
    while (amhw_zlg237_usart_status_flag_check(p_hw_usart, AMHW_ZLG237_USART_TX_COMPLETE_FLAG) == AM_FALSE);

    /* ��ȡ�������ݲ����� */
    if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
        amhw_zlg237_usart_data_write(p_hw_usart, data);
    }

    /* ʹ�ܷ����ж� */
    amhw_zlg237_usart_int_enable(p_hw_usart, AMHW_ZLG237_USART_INT_TX_EMPTY_ENABLE);
    return AM_OK;
}

/**
 * \brief �����жϷ���ص�����
 */
static int __usart_callback_set (void  *p_drv,
                                 int    callback_type,
                                 void  *pfn_callback,
                                 void  *p_arg)
{
    am_zlg237_usart_dev_t *p_dev = (am_zlg237_usart_dev_t *)p_drv;

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
static int __usart_poll_putchar (void *p_drv, char outchar)
{
    am_zlg237_usart_dev_t *p_dev     = (am_zlg237_usart_dev_t *)p_drv;
    amhw_zlg237_usart_t   *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    /* ����ģ���Ƿ����, AM_FALSE:æ; TURE: ���� */
    if(amhw_zlg237_usart_status_flag_check(p_hw_usart, AMHW_ZLG237_USART_TX_EMPTY_FLAG) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        if ((p_dev->rs485_en) && (p_dev->p_devinfo->pfn_rs485_dir != NULL)) {

            /* ���� 485 Ϊ����ģʽ */
            p_dev->p_devinfo->pfn_rs485_dir(AM_TRUE);
        }

        while(amhw_zlg237_usart_status_flag_check(p_hw_usart,
                                                  AMHW_ZLG237_USART_TX_EMPTY_FLAG)
                                                  == AM_FALSE);

        /* ����һ���ַ� */
        amhw_zlg237_usart_data_write(p_hw_usart, outchar);

        if (p_dev->rs485_en && p_dev->p_devinfo->pfn_rs485_dir) {

            /* �ȴ�������� */
            while (amhw_zlg237_usart_status_flag_check(p_hw_usart, AMHW_ZLG237_USART_TX_COMPLETE_FLAG) == AM_FALSE);

            p_dev->p_devinfo->pfn_rs485_dir(AM_FALSE);
        }
    }

    return (AM_OK);
}

/**
 * \brief ��ѯģʽ�½����ַ�
 */
static int __usart_poll_getchar (void *p_drv, char *p_char)
{
    am_zlg237_usart_dev_t *p_dev     = (am_zlg237_usart_dev_t *)p_drv;
    amhw_zlg237_usart_t   *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;
    uint8_t           *p_inchar  = (uint8_t *)p_char;

    /* ����ģ���Ƿ���У�AM_FALSE:æ,���ڽ���; TURE: �Ѿ����յ�һ���ַ� */
    if(amhw_zlg237_usart_status_flag_check(p_hw_usart, AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG) == AM_FALSE) {
        return (-AM_EAGAIN);
    } else {

        /* ����һ���ַ� */
        *p_inchar = amhw_zlg237_usart_data_read(p_hw_usart);
    }

    return (AM_OK);
}

/**
 * \brief ���ô���ģʽ
 */
int __usart_mode_set (am_zlg237_usart_dev_t *p_dev, uint32_t new_mode)
{
    amhw_zlg237_usart_t *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    /* ��֧������ģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }

    if (new_mode == AM_UART_MODE_INT) {

        am_int_connect(p_dev->p_devinfo->inum,
                       __usart_irq_handler,
                       (void *)p_dev);
        am_int_enable(p_dev->p_devinfo->inum);

        /* ʹ�ܽ���׼�ж� */
        amhw_zlg237_usart_int_enable(p_hw_usart, AMHW_ZLG237_USART_INT_RX_NOT_EMPTY_ENABLE);
    } else {

        /* �ر����д����ж� */
        amhw_zlg237_usart_int_disable(p_hw_usart, AMHW_ZLG237_USART_INT_ALL_ENABLE_MASK);
    }

    p_dev->channel_mode = new_mode;

    return (AM_OK);
}

/**
 * \brief ����ѡ������
 */
int __usart_opt_set (am_zlg237_usart_dev_t *p_dev, uint32_t options)
{
    amhw_zlg237_usart_t *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;
    uint8_t             cfg_flags = 0;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* ����ֹͣλ */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x1 << 2);
        cfg_flags |= AMHW_ZLG237_USART_STOP_20_BIT;
    } else {
        cfg_flags &= ~(0x1 << 2);
        cfg_flags |= AMHW_ZLG237_USART_STOP_10_BIT;
    }

    /* ���ü��鷽ʽ */
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x3 << 0);

        if (options & AM_UART_PARODD) {
            cfg_flags |= AMHW_ZLG237_USART_PARITY_ODD;
        } else {
            cfg_flags |= AMHW_ZLG237_USART_PARITY_EVEN;
        }
    } else {
        cfg_flags &= ~(0x3 << 0);
        cfg_flags |= AMHW_ZLG237_USART_PARITY_NO;
    }

    /* �������Ч���� */
    amhw_zlg237_usart_stop_bit_sel(p_hw_usart, (cfg_flags & 0x4));
    amhw_zlg237_usart_parity_bit_sel(p_hw_usart, (cfg_flags & 0x3));

    p_dev->options = options;

    return (AM_OK);
}

/******************************************************************************/
/**
 * \brief ����������״̬���ã�����أ�
 */
static int __usart_flow_rxstat_set (am_zlg237_usart_dev_t *p_dev, uint32_t ctrl)
{
    amhw_zlg237_usart_t *p_hw_usart = NULL;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    if (AM_UART_FLOWCTL_NO == p_dev->flowctl_mode) {
        return -AM_ENOTSUP;

    /* �����Ӳ�����أ�����RTS������ŵ�λ */
    } else if (AM_UART_FLOWCTL_HW == p_dev->flowctl_mode) {
        if (AM_UART_FLOWSTAT_ON == ctrl) {
            /* ����RTS�ܽ�,����     */
            am_gpio_set(p_dev->p_devinfo->gpio_rts[0], 0);

        } else {
            /* ����RTS�ܽ�,����     */
            am_gpio_set(p_dev->p_devinfo->gpio_rts[0], 1);
        }
    } else {
        /* �����������أ�����XON/XOFF�����ַ� */
        if (AM_UART_FLOWSTAT_ON == ctrl) {
            amhw_zlg237_usart_data_write(p_hw_usart, AM_ZLG237_USART_XON);
        } else {
            amhw_zlg237_usart_data_write(p_hw_usart, AM_ZLG237_USART_XOFF);
        }
    }

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief ����ģʽ���ã������أ�������أ�Ӳ�����أ�
 */
static int __usart_flow_mode_set(am_zlg237_usart_dev_t *p_dev, uint32_t mode)
{
    amhw_zlg237_usart_t *p_hw_usart = NULL;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;
    p_dev->flowctl_mode = mode;

    if(AM_UART_FLOWCTL_NO == p_dev->flowctl_mode) {
        p_dev->flowctl_tx_stat = AM_UART_FLOWSTAT_ON;
        amhw_zlg237_usart_rts_disable(p_hw_usart);
        amhw_zlg237_usart_cts_disable(p_hw_usart);
        am_gpio_pin_cfg(p_dev->p_devinfo->gpio_rts[0], AM_GPIO_INPUT);
        am_gpio_pin_cfg(p_dev->p_devinfo->gpio_cts[0], AM_GPIO_INPUT);
    } else if (AM_UART_FLOWCTL_HW == p_dev->flowctl_mode) {

        /* Ӳ������ʹ��     */
        am_gpio_pin_cfg(p_dev->p_devinfo->gpio_rts[0], p_dev->p_devinfo->gpio_rts[1]);
        am_gpio_pin_cfg(p_dev->p_devinfo->gpio_cts[0], p_dev->p_devinfo->gpio_cts[1]);
        amhw_zlg237_usart_rts_enable(p_hw_usart);
        amhw_zlg237_usart_cts_enable(p_hw_usart);
    } else {
        amhw_zlg237_usart_rts_disable(p_hw_usart);
        amhw_zlg237_usart_cts_disable(p_hw_usart);
        am_gpio_pin_cfg(p_dev->p_devinfo->gpio_rts[0], AM_GPIO_INPUT);
        am_gpio_pin_cfg(p_dev->p_devinfo->gpio_cts[0], AM_GPIO_INPUT);
    }

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief ����������״̬��ȡ
 */
static int __usart_flow_txstat_get (am_zlg237_usart_dev_t *p_dev)
{
    amhw_zlg237_usart_t *p_hw_usart = NULL;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    if(AM_UART_FLOWCTL_HW == p_dev->flowctl_mode) {

        /* cts��״̬�����仯ʱ��״̬λ��Ч */
        if(amhw_zlg237_usart_status_flag_check(p_hw_usart,AMHW_ZLG237_USART_CTS_FLAG) == AM_TRUE) {

            /* ���cts״̬λ */
            amhw_zlg237_usart_status_flag_clr(p_hw_usart,AMHW_ZLG237_USART_CTS_FLAG);

            /* �ж�cts��ǰ�ߵ͵�ƽ */
            if (am_gpio_get(p_dev->p_devinfo->gpio_cts[0]) == 0) {
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
  USART interrupt request handler
*******************************************************************************/

/**
 * \brief ���ڽ����жϷ���
 */
void __usart_irq_rx_handler (am_zlg237_usart_dev_t *p_dev)
{
    amhw_zlg237_usart_t *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;
    char data;

    /* �Ƿ�Ϊ����Rx�ж� */
    if (amhw_zlg237_usart_status_flag_check(p_hw_usart,AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG) == AM_TRUE) {

        amhw_zlg237_usart_status_flag_clr(p_hw_usart, AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG);

        /* ��ȡ�½������� */
        data = amhw_zlg237_usart_data_read(p_hw_usart);

        /* ����½������� */
        p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
    }
}

/**
 * \brief ���ڷ����жϷ���
 */
void __usart_irq_tx_handler (am_zlg237_usart_dev_t *p_dev)
{
    amhw_zlg237_usart_t *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    char data;

    if (amhw_zlg237_usart_status_flag_check(p_hw_usart,AMHW_ZLG237_USART_TX_EMPTY_FLAG) == AM_TRUE) {

        amhw_zlg237_usart_status_flag_clr(p_hw_usart, AMHW_ZLG237_USART_TX_EMPTY_FLAG);
        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_zlg237_usart_data_write(p_hw_usart, data);
        } else {

            /* û�����ݴ��;͹رշ����ж� */
            amhw_zlg237_usart_int_disable(p_hw_usart, AMHW_ZLG237_USART_INT_TX_EMPTY_ENABLE);

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
void __usart_irq_handler (void *p_arg)
{
    am_zlg237_usart_dev_t  *p_dev     = (am_zlg237_usart_dev_t *)p_arg;
    amhw_zlg237_usart_t    *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;

    uint32_t usart_int_stat        = p_hw_usart->sr;

    if (amhw_zlg237_usart_status_flag_check(p_hw_usart,AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG) == AM_TRUE) {
         __usart_irq_rx_handler(p_dev);
    } else if (amhw_zlg237_usart_status_flag_check(p_hw_usart,AMHW_ZLG237_USART_TX_EMPTY_FLAG) == AM_TRUE) {
        __usart_irq_tx_handler(p_dev);
    } else {

    }

    /* �����ж� */
    if ((p_dev->other_int_enable & usart_int_stat) != 0) {

        usart_int_stat &= p_dev->other_int_enable;

        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AM_ZLG237_USART_ERRCODE_USART_OTHER_INT,
                           (void *)p_hw_usart,
                           1);
        }
    }

}

#if 0
/**
 * \brief UART�жϺ������ӣ���ʹ���ж�ģʽʱ��Ҫ���ô˺���
 */
int __usart_connect (void *p_drv)
{
    am_zlg237_usart_dev_t *p_dev = (am_zlg237_usart_dev_t *)p_drv;

    /* �����ж������ţ������ж� */
    am_int_connect(p_dev->p_devinfo->inum, __usart_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    amhw_zlg237_usart_int_enable(p_dev->p_devinfo->usart_reg_base,
                                p_dev->other_int_enable);

    return AM_OK;
}
#endif /* 0 */

/**
 * \brief Ĭ�ϻص�����
 *
 * \returns AW_ERROR
 */
static int __usart_dummy_callback (void *p_arg, char *p_outchar)
{
    return (AM_ERROR);
}

/**
 * \brief ���ڳ�ʼ������
 */
am_uart_handle_t am_zlg237_usart_init (am_zlg237_usart_dev_t           *p_dev,
                                       const am_zlg237_usart_devinfo_t *p_devinfo)
{
    amhw_zlg237_usart_t  *p_hw_usart;
    uint32_t              tmp;

    if (p_devinfo == NULL) {
        return NULL;
    }

    /* ��ȡ���ò��� */
    p_hw_usart                = (amhw_zlg237_usart_t  *)p_devinfo->usart_reg_base;
    p_dev->p_devinfo         = p_devinfo;
    p_dev->uart_serv.p_funcs = (struct am_uart_drv_funcs *)&__g_uart_drv_funcs;
    p_dev->uart_serv.p_drv   = p_dev;
    p_dev->baud_rate         = p_devinfo->baud_rate;
    p_dev->options           = 0;

    /* ��ʼ��Ĭ�ϻص����� */
    p_dev->pfn_txchar_get    = (int (*) (void *, char*))__usart_dummy_callback;
    p_dev->txget_arg         = NULL;
    p_dev->pfn_rxchar_put    = (int (*) (void *, char ))__usart_dummy_callback;
    p_dev->rxput_arg         = NULL;
    p_dev->pfn_err           = (int (*) (void *, int, void*, int))
                               __usart_dummy_callback;

    p_dev->err_arg           = NULL;

    p_dev->flowctl_mode      = AM_UART_FLOWCTL_NO;
    p_dev->flowctl_tx_stat   = AM_UART_FLOWSTAT_ON;

    p_dev->other_int_enable  = p_devinfo->other_int_enable  &
                               ~(AMHW_ZLG237_USART_TX_EMPTY_FLAG |
                                 AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG);
    p_dev->rs485_en          = AM_FALSE;

    /* ����UARTʱ�� */
    am_clk_enable(p_devinfo->clk_num);

    /* �ڸı�UART�Ĵ���ֵǰ���� */
    amhw_zlg237_usart_disable(p_hw_usart);

    /* ��ȡ�������ݳ�������ѡ��,���������� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 4) & 0x01;

    switch (tmp) {

    case 0:
        amhw_zlg237_usart_word_length_sel(p_hw_usart, AMHW_ZLG237_USART_DATA_8BIT);
        break;

    default:
        amhw_zlg237_usart_word_length_sel(p_hw_usart, AMHW_ZLG237_USART_DATA_8BIT);
        break;
    }

    /* ��ȡ���ڼ��鷽ʽ����ѡ�� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 0) & 0x03;

    if (tmp == 3) {
        p_dev->options |= AM_UART_PARENB | AM_UART_PARODD;
    } else {
    }

    /* ��ȡ����ֹͣλ����ѡ�� */
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 2) & 0x03;
    if (tmp == 3) {
        p_dev->options |= AM_UART_STOPB;
    } else {

    }

    __usart_opt_set(p_dev, p_dev->options);

    /* ���ò����� */
    p_dev->baud_rate = amhw_zlg237_usart_baudrate_set(
        p_hw_usart,
        am_clk_rate_get(p_dev->p_devinfo->clk_num),
        p_devinfo->baud_rate);

    /* Ĭ����ѯģʽ */
    __usart_mode_set(p_dev, AM_UART_MODE_POLL);

    /* ����ģʽ���ã������أ�������أ�Ӳ�����أ�*/
    __usart_flow_mode_set(p_dev, AM_UART_FLOWCTL_NO);

    /* usartʹ�� */
    amhw_zlg237_usart_receiver_enable(p_hw_usart);
    amhw_zlg237_usart_transmitter_enable(p_hw_usart);
    amhw_zlg237_usart_enable(p_hw_usart);

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
void am_zlg237_usart_deinit (am_zlg237_usart_dev_t *p_dev)
{
    amhw_zlg237_usart_t *p_hw_usart = (amhw_zlg237_usart_t *)p_dev->p_devinfo->usart_reg_base;
    p_dev->uart_serv.p_funcs   = NULL;
    p_dev->uart_serv.p_drv     = NULL;

    if (p_dev->channel_mode == AM_UART_MODE_INT) {

        /* Ĭ��Ϊ��ѯģʽ */
        __usart_mode_set(p_dev, AM_UART_MODE_POLL);
    }

    /* �رմ��� */
    amhw_zlg237_usart_disable(p_hw_usart);

    am_int_disable(p_dev->p_devinfo->inum);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
