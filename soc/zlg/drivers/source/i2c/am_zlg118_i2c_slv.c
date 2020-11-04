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
 * \brief I2C�ӻ�����������I2C�ӻ���׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg_i2c_slv.h"
#include "hw/amhw_zlg118_i2c.h"

/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief I2CӲ����ʼ�� */
static int __i2c_slv_hard_init(am_zlg_i2c_slv_dev_t *p_dev);
/** \brief I2C�жϴ����� */
static void __i2c_slv_irq_handler (void *p_arg);
/** \brief ����I2C�ӻ��豸 */
static int __i2c_slv_setup (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev);
/** \brief �ر� I2C�ӻ��豸 */
static int __i2c_slv_shutdown (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev);
/** \brief ��ȡ���õĴӻ��豸���� */
static int __i2c_slv_num_get(void *p_drv);

/**
 * \brief I2C���豸 ������������
 */
static am_const struct am_i2c_slv_drv_funcs __g_i2c_slv_drv_funcs = {
    __i2c_slv_setup,
    __i2c_slv_shutdown,
    __i2c_slv_num_get,
};

/**
 *  \brief I2CӲ����ʼ��
 *  \note  1: ���ô��豸�ĵ�ַ ����ַλ��
 *         2�������ж�
 */
static int __i2c_slv_hard_init (am_zlg_i2c_slv_dev_t *p_dev)
{
    amhw_zlg118_i2c_t *p_hw_i2c  = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_zlg118_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* ���I2C���ƼĴ��� */
    p_hw_i2c->i2c_cr = 0;

    /* �ӻ�ģʽ������Ӧ�� */
    amhw_zlg118_i2c_cr_set(p_hw_i2c, AMHW_ZLG118_I2C_REPLY_ENABLE);

    /* ���ò����ʼ����� */
    amhw_zlg118_i2c_tm_disable(p_hw_i2c);

    return AM_OK;
}

/**
 * \brief ��ʼ�ӻ��豸
 */
static int __i2c_slv_setup (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    int                     i;
    uint8_t                 zlg_i2c_slv_dev_num ;
    am_zlg_i2c_slv_dev_t   *p_dev      = NULL;
    amhw_zlg118_i2c_t      *p_hw_i2c   = NULL;

    if ((p_drv == NULL) || (p_i2c_slv_dev == NULL)) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg_i2c_slv_dev_t *)p_drv;
    p_hw_i2c = (amhw_zlg118_i2c_t *)(p_dev->p_devinfo->i2c_regbase);

    /* ��ȡ�ܵĴ��豸���� */
    zlg_i2c_slv_dev_num = p_dev->zlg_i2c_slv_dev_num;

    for ( i = 0; i < zlg_i2c_slv_dev_num; i++) {
        if( NULL == p_dev->p_i2c_slv_dev[i]) {
            p_dev->p_i2c_slv_dev[i] = p_i2c_slv_dev;
            break ;
        }
    }

    /* �ӻ��豸���ù��ˣ��޷������ôӻ��豸 */
    if ( i == zlg_i2c_slv_dev_num) {
        return -AM_EAGAIN;
    }

    /* �ر�I2C�����������ò��� */
    amhw_zlg118_i2c_disable (p_hw_i2c);

    /* �ж��Ƿ� ��Ҫ��Ӧ �㲥��ַ */
    if ( p_i2c_slv_dev->dev_flags & AM_I2C_SLV_GEN_CALL_ACK) {
        amhw_zlg118_i2c_gen_call_ack(p_hw_i2c);
    } else {
        amhw_zlg118_i2c_gen_call_nack(p_hw_i2c);
    }

    /**
     * \brief ����  i ��Ŵӻ��豸��ַ��
     *         i = 0 ,��ŵ���1���ӵ�ַ
     *         i = 1 ,��ŵ���2�ӵ�ַ ���Դ�����
     *
     * \note ZLGֻ��һ���ӻ���ַ ,ֱ�Ӵ�ż��� ��
     */
    amhw_zlg118_i2c_slave_addr_set (p_hw_i2c, p_i2c_slv_dev->dev_addr);

    amhw_zlg118_i2c_enable(p_hw_i2c);
    am_int_enable(p_dev->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief �ر� �ӻ��豸
 */
static int __i2c_slv_shutdown (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    am_zlg_i2c_slv_dev_t *p_dev    = (am_zlg_i2c_slv_dev_t *)p_drv;
    amhw_zlg118_i2c_t   *p_hw_i2c_slv = NULL;

    if ( (p_dev              == NULL) ||
         (p_i2c_slv_dev      == NULL)) {
        return -AM_EINVAL;
    }
    p_hw_i2c_slv = (amhw_zlg118_i2c_t *) p_dev->p_devinfo->i2c_regbase;

    /**
     * \brief ʧ�ܶ�Ӧ�ӵ�ַ ,���ݴӻ���ַ����ȷ���ùر���һ���ӻ��豸
     *
     * \note ZLGֻ������һ�����豸 ��ֱ�ӹر�ʧ��I2C����
     */
    p_dev->p_i2c_slv_dev[0] = NULL;
    am_int_disable(p_dev->p_devinfo->inum);
    amhw_zlg118_i2c_disable (p_hw_i2c_slv);

    return AM_OK;
}

/**
 * \brief ��ȡ���ôӻ��豸����
 */
static int __i2c_slv_num_get (void *p_drv)
{
    int     i;
    int     count = 0;
    uint8_t zlg_i2c_slv_dev_num ;
    am_zlg_i2c_slv_dev_t *p_dev = (am_zlg_i2c_slv_dev_t *)p_drv;

    if ((p_dev == NULL)) {
        return -AM_EINVAL;
    }
    /* ��ȡ�ܵĴ��豸���� */
    zlg_i2c_slv_dev_num = p_dev->zlg_i2c_slv_dev_num;

    for (i = 0; i < zlg_i2c_slv_dev_num; i++) {
        if (NULL == p_dev->p_i2c_slv_dev[i]) {
            count++;
        }
    }
    return count;
}

/**
 * \brief �����ʱ���ص�����
 *
 * \note �ڿ�ʼ�ź�֮�� ������������1�뻹δ��ֹͣ�ź� ���򽫴ӻ����и�λ
 */
static void __i2c_slv_timing_callback (void *p_arg)
{
    am_zlg_i2c_slv_dev_t  *p_dev     = ( am_zlg_i2c_slv_dev_t *) p_arg;
    amhw_zlg118_i2c_t     *p_hw_i2c  = NULL;
    p_hw_i2c  = (amhw_zlg118_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* ƽ̨��ʼ��֮�� �Ĵ�����ֵ��λ */
    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    /* �ر�I2C�����������ò��� */
    amhw_zlg118_i2c_disable (p_hw_i2c);

    /** �ж��Ƿ� ��Ҫ��Ӧ �㲥��ַ */
    if ( p_dev->p_i2c_slv_dev[0]->dev_flags & AM_I2C_SLV_GEN_CALL_ACK) {
        amhw_zlg118_i2c_gen_call_ack(p_hw_i2c);
    } else {
        amhw_zlg118_i2c_gen_call_nack(p_hw_i2c);
    }

    amhw_zlg118_i2c_slave_addr_set(p_hw_i2c, p_dev->p_i2c_slv_dev[0]->dev_addr);

    amhw_zlg118_i2c_enable(p_hw_i2c);

    __i2c_slv_hard_init(p_dev);

    /** ֹͣ��ʱ */
    am_softimer_stop(&p_dev->softimer);
}

/**
 * \brief I2C �жϴ�����
 *
 * \param[in] p_arg : ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
static void __i2c_slv_irq_handler (void *p_arg)
{
    static uint8_t           rx_len = 0;
    uint8_t                  state;
    uint8_t                  rx_data;
    uint8_t                  tx_data;
    amhw_zlg118_i2c_t       *p_hw_i2c_slv;
    am_zlg_i2c_slv_dev_t    *p_dev          = (am_zlg_i2c_slv_dev_t *)p_arg;
    am_i2c_slv_device_t     *p_i2c_slv_dev  = p_dev->p_i2c_slv_dev[0];

    p_hw_i2c_slv = (amhw_zlg118_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    state = amhw_zlg118_i2c_status_get(p_hw_i2c_slv);

    switch(state) {
    case 0xa0:  /* ���յ�ֹͣ�������ظ���ʼ���� */
        if (NULL != p_i2c_slv_dev->p_cb_funs->pfn_tran_stop) {
            p_i2c_slv_dev->p_cb_funs->pfn_tran_stop(p_i2c_slv_dev->p_arg); /* ����read��ʼ */
        }
        rx_len = 0;
        amhw_zlg118_i2c_cr_set(p_hw_i2c_slv, AMHW_ZLG118_I2C_REPLY_ENABLE);
        break;

    case 0x60:  /* �ѽ��յ�(������ƥ���)SLA+W���ѽ���ACK */
    case 0x70:  /* �ѽ���ͨ�õ��õ�ַ��0x00�����ѽ���ACK */
        rx_len = 0;
        amhw_zlg118_i2c_cr_set(p_hw_i2c_slv, AMHW_ZLG118_I2C_REPLY_ENABLE);
        break;

    case 0x68:  /* ����ʱ��SLA+��д��ʧ�ٲã��ѽ��������SLA+W���ѷ���ACK */
    case 0x78:  /* ����ʱ��SLA+��д�ж�ʧ�ٲã��ѽ���ͨ�õ��õ�ַ���ѷ���ACK */
    case 0x88:  /* ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ��ط�ACK */
        amhw_zlg118_i2c_cr_set(p_hw_i2c_slv, AMHW_ZLG118_I2C_REPLY_ENABLE);
        break;

    case 0x80:  /* ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ���ACK */
    case 0x98:  /* ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ��ط�ACK */
    case 0x90:  /* ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ���ACK */
        amhw_zlg118_i2c_cr_set(p_hw_i2c_slv, AMHW_ZLG118_I2C_REPLY_ENABLE);
        rx_data = amhw_zlg118_i2c_dat_read(p_hw_i2c_slv);//��������
        if(rx_len) {    /* ���Խ��յĵ�һ������(�ӻ��豸�ӵ�ַ) */
            /* ���ܻص� */
            if (p_dev->is_gen_call == AM_TRUE) {
                /** ����ǹ㲥���� */
                if(p_i2c_slv_dev->p_cb_funs->pfn_gen_call) {
                    p_i2c_slv_dev->p_cb_funs->pfn_gen_call(p_i2c_slv_dev->p_arg, rx_data);
                }
            } else {
                if(p_i2c_slv_dev->p_cb_funs->pfn_rxbyte_put) {
                    p_i2c_slv_dev->p_cb_funs->pfn_rxbyte_put(p_i2c_slv_dev->p_arg, rx_data);
                }
            }
        }
        rx_len++;
        break;

    case 0xa8:  /* �ѽ��������SLA+R���ѷ���ACK,��Ҫ�������ݲ����յ�ACKλ */
    case 0xb0:  /* ������ʱ��SLA+��д�ж�ʧ�ٲã��ѽ�������SLA+R���ѷ���ACK */
    case 0xc8:  /* װ��������ֽ��ѱ����ͣ��ѽ���ACK */
    case 0xb8:  /* �ѷ������ݣ��ѽ���ACK */
        if (NULL != p_i2c_slv_dev->p_cb_funs->pfn_txbyte_get) {
            p_i2c_slv_dev->p_cb_funs->pfn_txbyte_get(p_i2c_slv_dev->p_arg, &tx_data);
        }
        amhw_zlg118_i2c_dat_write(p_hw_i2c_slv,tx_data);
        break;

    case 0xc0:  /* �������ݣ����շ�ACKn */
        if (NULL != p_i2c_slv_dev->p_cb_funs->pfn_tran_stop) {
            p_i2c_slv_dev->p_cb_funs->pfn_tran_stop(p_i2c_slv_dev->p_arg); /* ����read�� */
        }
        break;
    }

    /* ����жϱ�־ */
    amhw_zlg118_i2c_cr_clear(p_hw_i2c_slv, AMHW_ZLG118_I2C_INT_FLAG);
}

/**
 * \brief I2C��ʼ��
 *
 * \note Ӳ����ʼ�� ͨ���û����ÿ�ʼ���豸����ʼ��
 */
am_i2c_slv_handle_t am_zlg_i2c_slv_init (
        am_zlg_i2c_slv_dev_t           *p_dev,
        const am_zlg_i2c_slv_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL ) {
        return NULL;
    }

    p_dev->i2c_slv_serv.p_funcs = \
            (struct am_i2c_slv_drv_funcs *)&__g_i2c_slv_drv_funcs;
    p_dev->i2c_slv_serv.p_drv   = p_dev;
    p_dev->p_devinfo            = p_devinfo;
    p_dev->zlg_i2c_slv_dev_num  = 1;  /* ֻ������һ���ӻ��豸 */
    p_dev->is_gen_call          = AM_FALSE;
    p_dev->p_i2c_slv_dev[0]     = NULL;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* ��ʼ�������ʱ�� */
    am_softimer_init(&p_dev->softimer, __i2c_slv_timing_callback, p_dev);

    __i2c_slv_hard_init(p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum,
                   __i2c_slv_irq_handler,
                   (void *)p_dev);

    return &(p_dev->i2c_slv_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_zlg_i2c_slv_deinit (am_i2c_slv_handle_t handle)
{
    amhw_zlg118_i2c_t    *p_hw_i2c_slv = NULL;
    am_zlg_i2c_slv_dev_t *p_dev        = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev        = (am_zlg_i2c_slv_dev_t *)handle;
    p_hw_i2c_slv = (amhw_zlg118_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    amhw_zlg118_i2c_disable (p_hw_i2c_slv);

    /* ȥ���ж����� */
    am_int_disable(p_dev->p_devinfo->inum);

    am_int_disconnect(p_dev->p_devinfo->inum,
                      __i2c_slv_irq_handler,
                      (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
