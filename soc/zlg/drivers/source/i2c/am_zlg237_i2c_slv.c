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
 * - 1.00 19-07-26  zc, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg237_i2c_slv.h"
#include "hw/amhw_zlg237_i2c.h"
#include "am_zlg237_clk.h"

/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief I2CӲ����ʼ�� */
static int __i2c_slv_hard_init(am_zlg237_i2c_slv_dev_t *p_dev);

/** \brief I2C�жϴ����� */
static void __zlg237_i2c_slv_irq_handler (void *p_arg);

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
static int __i2c_slv_hard_init (am_zlg237_i2c_slv_dev_t *p_dev)
{
    amhw_zlg237_i2c_t *p_hw_i2c = NULL;
    uint16_t tmpreg = 0, i2c_freq_value = 0;
    uint32_t pclk1 = 0;
    uint16_t result = 0x04;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_zlg237_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /** <breif ���� CR2 */
    tmpreg = p_hw_i2c->i2c_cr2;

    /** <brief ���� freq[5:0] */
    tmpreg &= 0xFFC0;

    /** <brief ���� pclk1  ����freqʱ�� */
    pclk1 = am_clk_rate_get(p_dev->p_devinfo->clk_num);

    i2c_freq_value = (uint16_t)(pclk1/1000000);
    tmpreg |= i2c_freq_value;

    /** <brief д��CR2 */
    p_hw_i2c->i2c_cr2 = tmpreg;

    /** <brief ���� CCR */

    /**
     *  \brief ���� I2C  ���� TRISE ���� F/S DUTY CCR[11:0]
     */
    amhw_zlg237_i2c_disable(p_hw_i2c);
    tmpreg = 0;

    /** <brief ���Ϊ 100khz */
    if (p_dev->i2c_clock_speed <= 100000) {
        /** <brief ��׼ģʽ�ٶȼ��� */
    result = (uint16_t)(pclk1 / (p_dev->i2c_clock_speed << 1));

        if (result < 0x04) {

            /** <brief ������С����ֵ */
            result = 0x04;
        }
        tmpreg |= result;
        /** \brief ���ñ�׼ģʽ������ riseֵ     */
        p_hw_i2c->i2c_trise = i2c_freq_value + 1;
        } else {

            /** <brief ���Ϊ 400khz */
            if (p_dev->i2c_dutycycle == AMHW_ZLG237_I2C_DUTY_CYCLE_2 ) {
                result = (uint16_t)(pclk1 / (p_dev->i2c_clock_speed *3));
            } else {
                result = (uint16_t)(pclk1 / (p_dev->i2c_clock_speed * 25));
                result |= AMHW_ZLG237_I2C_DUTY_CYCLE_16_9;
            }

            /** < ���� CCR[11:0] �Ƿ�С�� 0x01 */
            if ((result & 0x0FFF) == 0) {

                /** <brief ������С�� CCRֵ */
                result |= (uint16_t)0x0001;
            }

            /** <brief ����speedֵ  ��  F/SΪ ����ģʽ */
            tmpreg |= (uint16_t)(result | (uint16_t)0x8000);
            /** <brief ���ÿ���ģʽ�����riseʱ�� */
            p_hw_i2c->i2c_trise = (uint16_t) (((i2c_freq_value *(uint16_t)300) /
                                              (uint16_t)1000) + (uint16_t)1) ;
        }

        /** <brief д�� ccr */
        p_hw_i2c->i2c_ccr = tmpreg;

        /** <brief ����I2C���� */
        amhw_zlg237_i2c_enable(p_hw_i2c);

        /** <brief ���� CR1 */

        tmpreg = p_hw_i2c->i2c_cr1;

        /** \brief ���� ACK,SMBTYPE,SMBUS */
        tmpreg &= 0xFBF5;

        /**
         *  <brief ���� I2C ģʽ �� acknowledgement
         *  ����I2C��ģʽֵ ���� SMBTYPE �� SMBUS
         *  ����I2C��ACKֵ ����ACKλ
         */
        tmpreg |= (uint16_t)((uint16_t)p_dev->i2c_mode | p_dev->i2c_ack);

        /** \brief д��CR1 */
        p_hw_i2c->i2c_cr1 = tmpreg;

        /** \brief I2C OAR1 ���� */
        p_hw_i2c->i2c_oar1 = (p_dev->i2c_acknowledgedaddress |
                              ((p_dev->i2c_ownaddress1) << 1));

        /* Ĭ�ϲ�ʹ�� 10bit��ַ*/
        amhw_zlg237_i2c_endual(p_hw_i2c,DISABLE);
        amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                      I2C_CR2_ITEVTEN |
                                      I2C_CR2_ITBUFEN |
                                      I2C_CR2_ITERREN,
                                      ENABLE);

        /** ���� I2C����  */
        amhw_zlg237_i2c_enable(p_hw_i2c);

        return AM_OK;
}

/**
 * \brief ��ʼ�ӻ��豸
 */
static int __i2c_slv_setup (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    int     i;
    uint8_t zlg_i2c_slv_dev_num ;
    am_zlg237_i2c_slv_dev_t *p_dev      = NULL;
    amhw_zlg237_i2c_t       *p_hw_i2c   = NULL;

    if ((p_drv         == NULL) ||
        (p_i2c_slv_dev == NULL)) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg237_i2c_slv_dev_t *)p_drv;
    p_hw_i2c = (amhw_zlg237_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* ��ȡ�ܵĴ��豸���� */
    zlg_i2c_slv_dev_num            = p_dev->zlg_i2c_slv_dev_num;
    p_dev->i2c_ack                 = AMHW_ZLG237_I2C_ACK_ENABLE;
    p_dev->i2c_acknowledgedaddress = AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT;
    p_dev->i2c_clock_speed         = 100000;
    p_dev->i2c_dutycycle           = AMHW_ZLG237_I2C_DUTY_CYCLE_2;
    p_dev->i2c_mode                = AMHW_ZLG237_I2C_MODE_I2C;

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

//    /* �ر�I2C�����������ò��� */
//    amhw_zlg237_i2c_disable (p_hw_i2c);

    /* �ж��Ƿ� ��Ҫ��Ӧ �㲥��ַ */
    if ( p_i2c_slv_dev->dev_flags & AM_I2C_SLV_GEN_CALL_ACK) {
        amhw_zlg237_i2c_engc(p_hw_i2c, ENABLE);
    } else {
        amhw_zlg237_i2c_engc(p_hw_i2c, DISABLE);
    }

    /**
     * \brief ����  i ��Ŵӻ��豸��ַ��
     *         i = 0 ,��ŵ���1���ӵ�ַ
     *         i = 1 ,��ŵ���2�ӵ�ַ ���Դ�����
     *
     * \note ZLGֻ��һ���ӻ���ַ ,ֱ�Ӵ�ż��� ��
     */
    p_hw_i2c->i2c_oar1 = (uint16_t)(p_i2c_slv_dev->dev_addr << 1);

    /* ���ôӻ��豸�ĵ�ַλ�� */
    if ( p_i2c_slv_dev->dev_flags  &  AM_I2C_SLV_ADDR_10BIT) {
        p_hw_i2c->i2c_oar1 |= 0x8000;
    } else {
        p_hw_i2c->i2c_oar1 &= 0x0fff;
    }

//    amhw_zlg237_i2c_enable(p_hw_i2c);
    return AM_OK;
}

/**
 * \brief �ر� �ӻ��豸
 */
static int __i2c_slv_shutdown (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    am_zlg237_i2c_slv_dev_t *p_dev    = (am_zlg237_i2c_slv_dev_t *)p_drv;
    amhw_zlg237_i2c_t    *p_hw_i2c_slv = NULL;

    if ( (p_dev              == NULL) ||
         (p_i2c_slv_dev      == NULL)) {
        return -AM_EINVAL;
    }
    p_hw_i2c_slv = (amhw_zlg237_i2c_t *) p_dev->p_devinfo->i2c_regbase;

    /**
     * \brief ʧ�ܶ�Ӧ�ӵ�ַ ,���ݴӻ���ַ����ȷ���ùر���һ���ӻ��豸
     *
     * \note ZLGֻ������һ�����豸 ��ֱ�ӹر�ʧ��I2C����
     */
    p_dev->p_i2c_slv_dev[0] = NULL;
    amhw_zlg237_i2c_disable(p_hw_i2c_slv);

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
    am_zlg237_i2c_slv_dev_t *p_dev = (am_zlg237_i2c_slv_dev_t *)p_drv;

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
    am_zlg237_i2c_slv_dev_t *p_dev = ( am_zlg237_i2c_slv_dev_t *) p_arg;

#if 1

    amhw_zlg237_i2c_t     *p_hw_i2c  = NULL;
    p_hw_i2c  = (amhw_zlg237_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* ƽ̨��ʼ��֮�� �Ĵ�����ֵ��λ */
    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    __i2c_slv_hard_init(p_dev);

    /** �ж��Ƿ� ��Ҫ��Ӧ �㲥��ַ */
    if ( p_dev->p_i2c_slv_dev[0]->dev_flags & AM_I2C_SLV_GEN_CALL_ACK) {

        amhw_zlg237_i2c_engc(p_hw_i2c, ENABLE);
    } else {
        amhw_zlg237_i2c_engc(p_hw_i2c, DISABLE);
    }

    /* ���ôӻ���ַ */
    p_hw_i2c->i2c_oar1 = (uint16_t)(p_dev->p_i2c_slv_dev[0]->dev_addr << 1);


    /* ���ôӻ��豸�ĵ�ַλ�� */
    if ( p_dev->p_i2c_slv_dev[0]->dev_flags  &  AM_I2C_SLV_ADDR_10BIT) {
        p_hw_i2c->i2c_oar1 |= 0x8000;
    } else {
        p_hw_i2c->i2c_oar1 &= 0x0fff;
    }

#endif

    /** ֹͣ��ʱ */
    am_softimer_stop(&p_dev->softimer);
}

/**
 * \brief �ӻ���������
 */
void __zlg237_i2c_slv_irq_rx_handler (am_zlg237_i2c_slv_dev_t *p_dev)
{
    amhw_zlg237_i2c_t   *p_hw_i2c  = (amhw_zlg237_i2c_t *)
                                      p_dev->p_devinfo->i2c_regbase;
    am_i2c_slv_device_t *p_i2c_slv =  p_dev->p_i2c_slv_dev[0];

    /* �������� */
    uint8_t rx_data = amhw_zlg237_i2c_recv_data (p_hw_i2c);

    /* ���ܻص� */
    if ( p_dev->is_gen_call == AM_TRUE) {
        /** ����ǹ㲥���� */
        if( p_i2c_slv->p_cb_funs->pfn_gen_call) {
            p_i2c_slv->p_cb_funs->pfn_gen_call(p_i2c_slv->p_arg, rx_data);
        }
    } else {

       if ( p_i2c_slv->p_cb_funs->pfn_rxbyte_put) {
            p_i2c_slv->p_cb_funs->pfn_rxbyte_put( p_i2c_slv->p_arg, rx_data);
       }
    }
}

/**
 * \brief �ӻ���������
 */
void __zlg237_i2c_slv_irq_tx_handler (am_zlg237_i2c_slv_dev_t *p_dev)
{
    amhw_zlg237_i2c_t   *p_hw_i2c  = (amhw_zlg237_i2c_t *)
                                     p_dev->p_devinfo->i2c_regbase;
    am_i2c_slv_device_t *p_i2c_slv = p_dev->p_i2c_slv_dev[0];

    uint8_t  tx_data = 0;

    /**
     * \brief ͨ�����ͻص�����ȡ���� ��
     *        ��FIFO�������ֽ� + ��λ�Ĵ�����һ���ֽ� ����˿�������ȡ�����ֽ�
     */
    if (NULL != p_i2c_slv->p_cb_funs->pfn_txbyte_get) {
         p_i2c_slv->p_cb_funs->pfn_txbyte_get( p_i2c_slv->p_arg, &tx_data);
    }
    amhw_zlg237_i2c_send_data(p_hw_i2c, tx_data);

}

/**
 * \brief I2C �жϴ�����
 *
 * \param[in] p_arg : ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
static void __zlg237_i2c_slv_irq_handler (void *p_arg)
{
        
    am_zlg237_i2c_slv_dev_t *p_dev              = (am_zlg237_i2c_slv_dev_t *)
                                                   p_arg;
    amhw_zlg237_i2c_t       *p_hw_i2c_slv       = (amhw_zlg237_i2c_t *)
                                                  p_dev->p_devinfo->i2c_regbase;
    am_i2c_slv_device_t     *p_i2c_slv_dev      = p_dev->p_i2c_slv_dev[0];
    uint16_t                 i2c_slv_int_status = amhw_zlg237_i2c_getitstatus(
                                                      p_hw_i2c_slv);


    /* EV1 �¼�: �յ��ӵ�ַ*/
    if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__ADDR) {

        /* ��sr2 ����жϱ�־λ */
        amhw_zlg237_i2c_read_reg(p_hw_i2c_slv->i2c_sr2);

        if( NULL != p_i2c_slv_dev->p_cb_funs->pfn_addr_match) {
            p_i2c_slv_dev->p_cb_funs->pfn_addr_match(p_i2c_slv_dev->p_arg,
                                                         AM_TRUE);
        }

        /* �յ��㲥���дӵ�ַ  */
        if (amhw_zlg237_i2c_checkflagstaus(p_hw_i2c_slv,
                AMHW_ZLG_I2C_FLAG_GENCALL)) {
            p_dev->is_gen_call = AM_TRUE;
        }
        /* ��ʼ�������ʱ����ʱ 1000ms */
        am_softimer_start(&p_dev->softimer, 1000);
    }


    if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__BTF) {
        if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__RXNE) {

            /* ��ʼ�������� */
            __zlg237_i2c_slv_irq_rx_handler (p_dev);
        } else if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__TXE) {

            /* ��ʼ�������� */
            __zlg237_i2c_slv_irq_tx_handler (p_dev);
        }
    }

    /**
     * \brief ���ջ���ǿ�  EV2
     */
    if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__RXNE) {

        /* ��ʼ�������� */
        __zlg237_i2c_slv_irq_rx_handler (p_dev);
    }

    /**
     * \brief ���ջ���ǿ�   EV3 EV3_1
     */
    if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__TXE) {

        /* ��ʼ�������� */
        __zlg237_i2c_slv_irq_tx_handler (p_dev);
    }

    /* �������ݽ���ʱ */
    if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__STOPF) {
        if (i2c_slv_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__AF) {
            /* EV3_2 �ӷ�������� AF */
            amhw_zlg237_i2c_clearflag(p_hw_i2c_slv, AMHW_ZLG_I2C_FLAG_AF);
        } else {

            /* EV4  */
            amhw_zlg237_i2c_read_reg(p_hw_i2c_slv->i2c_sr1);
            p_hw_i2c_slv->i2c_cr1 &=0xffff;
        }

        p_dev->is_gen_call = AM_FALSE;

        /* ִ�д���ֹͣ�ص� */
        if ( NULL != p_i2c_slv_dev->p_cb_funs->pfn_tran_stop) {
            p_i2c_slv_dev->p_cb_funs->pfn_tran_stop(p_i2c_slv_dev->p_arg);
        }

        /* �������ֹͣ��ʱ */
        am_softimer_stop(&p_dev->softimer);
    }

}

/**
 * \brief I2C��ʼ��
 *
 * \note Ӳ����ʼ�� ͨ���û����ÿ�ʼ���豸����ʼ��
 */
am_i2c_slv_handle_t am_zlg237_i2c_slv_init (am_zlg237_i2c_slv_dev_t     *p_dev,
                                      const am_zlg237_i2c_slv_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL ) {
        return NULL;
    }

    p_dev->i2c_slv_serv.p_funcs = (struct am_i2c_slv_drv_funcs *)
                                       &__g_i2c_slv_drv_funcs;
    p_dev->i2c_slv_serv.p_drv   = p_dev;

    p_dev->p_devinfo   = p_devinfo;
    p_dev->zlg_i2c_slv_dev_num =1;  /* ֻ������һ���ӻ��豸 */



    /* p_dev->current_matching_num =0; Ĭ�ϵ�ǰƥ��Ϊ 0 */

    p_dev->is_gen_call = AM_FALSE;

    p_dev->p_i2c_slv_dev[0] = NULL;

    p_dev->i2c_clock_speed         = 100000;
    p_dev->i2c_mode                = AMHW_ZLG237_I2C_MODE_I2C;
    p_dev->i2c_dutycycle           = AMHW_ZLG237_I2C_DUTY_CYCLE_2;
    p_dev->i2c_ownaddress1         = 0;
    p_dev->i2c_ack                 = AMHW_ZLG237_I2C_ACK_ENABLE;
    p_dev->i2c_acknowledgedaddress = AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* ��ʼ�������ʱ�� */
    am_softimer_init(&p_dev->softimer, __i2c_slv_timing_callback, p_dev);

    __i2c_slv_hard_init(p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __zlg237_i2c_slv_irq_handler,
                       (void *)p_dev);

    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->i2c_slv_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_zlg237_i2c_slv_deinit (am_i2c_slv_handle_t handle)
{
    amhw_zlg237_i2c_t       *p_hw_i2c_slv = NULL;
    am_zlg237_i2c_slv_dev_t *p_dev        = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev    = (am_zlg237_i2c_slv_dev_t *)handle;
    p_hw_i2c_slv = (amhw_zlg237_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    amhw_zlg237_i2c_disable (p_hw_i2c_slv);

    /* ȥ���ж����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __zlg237_i2c_slv_irq_handler,
                         (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
