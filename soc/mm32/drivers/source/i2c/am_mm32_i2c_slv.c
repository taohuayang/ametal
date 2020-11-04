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
 * - 1.00 17-09-06  vir, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_mm32_i2c_slv.h"
#include "hw/amhw_mm32_i2c.h"

/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief I2CӲ����ʼ�� */
static int __i2c_slv_hard_init(am_mm32_i2c_slv_dev_t *p_dev);

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
static int __i2c_slv_hard_init (am_mm32_i2c_slv_dev_t *p_dev)
{
    amhw_mm32_i2c_t *p_hw_i2c  = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_mm32_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* �ر�I2C�����������ò��� */
    amhw_mm32_i2c_disable(p_hw_i2c);

    amhw_mm32_i2c_rx_tl_set(p_hw_i2c,0 );
    amhw_mm32_i2c_tx_tl_set(p_hw_i2c, 1);

    /*
     * һЩ�жϵ�����
     */

    /** ֻ���� �ӻ� �����ж� ��  �������ж� */
    amhw_mm32_i2c_intr_mask_clear(p_hw_i2c,0XFFF);
    amhw_mm32_i2c_intr_mask_set (p_hw_i2c,AMHW_MM32_INT_FLAG_RX_FULL   | 
	                                     AMHW_MM32_INT_FLAG_RD_REQ    |
                                         AMHW_MM32_INT_FLAG_START_DET);
    /* ����ж�״̬ */
    amhw_mm32_i2c_clr_intr_get (p_hw_i2c);
    amhw_mm32_i2c_enable(p_hw_i2c);

    return AM_OK;
}

/**
 * \brief ��ʼ�ӻ��豸
 */
static int __i2c_slv_setup (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    int     i;
    uint8_t mm32_i2c_slv_dev_num ;
    am_mm32_i2c_slv_dev_t *p_dev      = NULL;
    amhw_mm32_i2c_t       *p_hw_i2c   = NULL;

    if ((p_drv         == NULL) ||
        (p_i2c_slv_dev == NULL)) {
        return -AM_EINVAL;
    }

    p_dev    = (am_mm32_i2c_slv_dev_t *)p_drv;
    p_hw_i2c = (amhw_mm32_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* ��ȡ�ܵĴ��豸���� */
    mm32_i2c_slv_dev_num = p_dev->mm32_i2c_slv_dev_num;

    for ( i = 0; i < mm32_i2c_slv_dev_num; i++) {
        if( NULL == p_dev->p_i2c_slv_dev[i]) {
            p_dev->p_i2c_slv_dev[i] = p_i2c_slv_dev;
            break ;
        }
    }

    /* �ӻ��豸���ù��ˣ��޷������ôӻ��豸 */
    if ( i == mm32_i2c_slv_dev_num) {
        return -AM_EAGAIN;
    }

    /* �ر�I2C�����������ò��� */
    amhw_mm32_i2c_disable (p_hw_i2c);

    /* �ж��Ƿ� ��Ҫ��Ӧ �㲥��ַ */
    if ( p_i2c_slv_dev->dev_flags & AM_I2C_SLV_GEN_CALL_ACK) {
        amhw_mm32_i2c_gen_call_ack(p_hw_i2c);
        amhw_mm32_i2c_intr_mask_set(p_hw_i2c,AMHW_MM32_INT_FLAG_GEN_CALL);
    } else {
        amhw_mm32_i2c_gen_call_nack(p_hw_i2c);
    }

    /**
     * \brief ����  i ��Ŵӻ��豸��ַ��
     *         i = 0 ,��ŵ���1���ӵ�ַ
     *         i = 1 ,��ŵ���2�ӵ�ַ ���Դ�����
     *
     * \note ZLGֻ��һ���ӻ���ַ ,ֱ�Ӵ�ż��� ��
     */
    amhw_mm32_i2c_slave_addr_set (p_hw_i2c, p_i2c_slv_dev->dev_addr);

    /* ���ôӻ��豸�ĵ�ַλ�� */
    if ( p_i2c_slv_dev->dev_flags  &  AM_I2C_SLV_ADDR_10BIT) {
        p_hw_i2c->ic_con = AMHW_MM32_I2C_SLAVE  |
                       AMHW_MM32_I2C_10BITADDR_SLAVE;
    } else {
        p_hw_i2c->ic_con = AMHW_MM32_I2C_SLAVE  |
                      AMHW_MM32_I2C_7BITADDR_SLAVE;
    }

    amhw_mm32_i2c_enable(p_hw_i2c);
    return AM_OK;
}

/**
 * \brief �ر� �ӻ��豸
 */
static int __i2c_slv_shutdown (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    am_mm32_i2c_slv_dev_t *p_dev    = (am_mm32_i2c_slv_dev_t *)p_drv;
    amhw_mm32_i2c_t   *p_hw_i2c_slv = NULL;

    if ( (p_dev              == NULL) ||
         (p_i2c_slv_dev      == NULL)) {
        return -AM_EINVAL;
    }
    p_hw_i2c_slv = (amhw_mm32_i2c_t *) p_dev->p_devinfo->i2c_regbase;

    /**
     * \brief ʧ�ܶ�Ӧ�ӵ�ַ ,���ݴӻ���ַ����ȷ���ùر���һ���ӻ��豸
     *
     * \note ZLGֻ������һ�����豸 ��ֱ�ӹر�ʧ��I2C����
     */
    p_dev->p_i2c_slv_dev[0] = NULL;
    amhw_mm32_i2c_disable (p_hw_i2c_slv);

    return AM_OK;
}

/**
 * \brief ��ȡ���ôӻ��豸����
 */
static int __i2c_slv_num_get (void *p_drv)
{
    int     i;
    int     count = 0;
    uint8_t mm32_i2c_slv_dev_num ;
    am_mm32_i2c_slv_dev_t *p_dev = (am_mm32_i2c_slv_dev_t *)p_drv;

    if ((p_dev == NULL)) {
        return -AM_EINVAL;
    }
    /* ��ȡ�ܵĴ��豸���� */
    mm32_i2c_slv_dev_num = p_dev->mm32_i2c_slv_dev_num;

    for (i = 0; i < mm32_i2c_slv_dev_num; i++) {
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
    am_mm32_i2c_slv_dev_t *p_dev = ( am_mm32_i2c_slv_dev_t *) p_arg;

#if 1
    amhw_mm32_i2c_t     *p_hw_i2c  = NULL;
    p_hw_i2c  = (amhw_mm32_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* ƽ̨��ʼ��֮�� �Ĵ�����ֵ��λ */
    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    /* �ر�I2C�����������ò��� */
    amhw_mm32_i2c_disable (p_hw_i2c);

    /** �ж��Ƿ� ��Ҫ��Ӧ �㲥��ַ */
    if ( p_dev->p_i2c_slv_dev[0]->dev_flags & AM_I2C_SLV_GEN_CALL_ACK) {
        amhw_mm32_i2c_gen_call_ack(p_hw_i2c);
        amhw_mm32_i2c_intr_mask_set(p_hw_i2c,AMHW_MM32_INT_FLAG_GEN_CALL);
    } else {
        amhw_mm32_i2c_gen_call_nack(p_hw_i2c);
    }

    amhw_mm32_i2c_slave_addr_set (p_hw_i2c, p_dev->p_i2c_slv_dev[0]->dev_addr);

    /* ���ôӻ��豸�ĵ�ַλ�� */
    if ( p_dev->p_i2c_slv_dev[0]->dev_flags  &  AM_I2C_SLV_ADDR_10BIT) {
        p_hw_i2c->ic_con = AMHW_MM32_I2C_SLAVE  |
                       AMHW_MM32_I2C_10BITADDR_SLAVE;
    } else {
        p_hw_i2c->ic_con = AMHW_MM32_I2C_SLAVE  |
                      AMHW_MM32_I2C_7BITADDR_SLAVE;
    }

    amhw_mm32_i2c_enable(p_hw_i2c);
#endif

    __i2c_slv_hard_init(p_dev);

    /** ֹͣ��ʱ */
    am_softimer_stop(&p_dev->softimer);
}

/**
 * \brief �ӻ���������
 */
void __i2c_slv_irq_rx_handler (am_mm32_i2c_slv_dev_t *p_dev)
{
    amhw_mm32_i2c_t *p_hw_i2c      = (amhw_mm32_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    am_i2c_slv_device_t *p_i2c_slv = p_dev->p_i2c_slv_dev[0];

    /* �������� */
    uint8_t rx_data = amhw_mm32_i2c_dat_read (p_hw_i2c);

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
void __i2c_slv_irq_tx_handler (am_mm32_i2c_slv_dev_t *p_dev)
{
    amhw_mm32_i2c_t   *p_hw_i2c  = (amhw_mm32_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    am_i2c_slv_device_t *p_i2c_slv = p_dev->p_i2c_slv_dev[0];

    uint8_t  tx_data = 0;

    /**
     * \brief ͨ�����ͻص�����ȡ���� ��
     *        ��FIFO�������ֽ� + ��λ�Ĵ�����һ���ֽ� ����˿�������ȡ�����ֽ�
     */
    if (NULL != p_i2c_slv->p_cb_funs->pfn_txbyte_get) {
         p_i2c_slv->p_cb_funs->pfn_txbyte_get( p_i2c_slv->p_arg, &tx_data);
    }
    amhw_mm32_i2c_dat_write(p_hw_i2c, tx_data);

    /* ��������� */
    amhw_mm32_i2c_clr_rd_req_get(p_hw_i2c);
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
        
    am_mm32_i2c_slv_dev_t  *p_dev              = (am_mm32_i2c_slv_dev_t *)p_arg;
    amhw_mm32_i2c_t        *p_hw_i2c_slv       = (amhw_mm32_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    am_i2c_slv_device_t   *p_i2c_slv_dev      = p_dev->p_i2c_slv_dev[0];
    amhw_mm32_int_flag_t    i2c_slv_int_status = amhw_mm32_i2c_intr_stat_get(p_hw_i2c_slv);

    /**
     * \brief ��ʼ�ź�
     *
     * \note  ֻҪ�������п�ʼ�źžͻᴥ�����ж�
     */
    if ( i2c_slv_int_status & AMHW_MM32_INT_FLAG_START_DET) {
        /** �����ʼ�ж� */
        amhw_mm32_i2c_clr_start_det_get(p_hw_i2c_slv);

        /**
         *  \brief �ж��ǲ��� �뱾�豸����ͨ��
         *
         *  \note ֻ�дӻ���ַƥ����  �ӻ�״̬���״̬λ �Ż���1
         */
        if ( p_hw_i2c_slv->ic_status & AMHW_MM32_STATUS_FLAG_SLV_ACTIVITY ) {
            /* ��ַƥ��ص� ,�Ƕ�����д��MCU�޷�ȷ�� */
            if( NULL != p_i2c_slv_dev->p_cb_funs->pfn_addr_match) {
                p_i2c_slv_dev->p_cb_funs->pfn_addr_match(p_i2c_slv_dev->p_arg, AM_TRUE);
            }

            /** ��ֹͣ�ж� */
            amhw_mm32_i2c_intr_mask_set (p_hw_i2c_slv,AMHW_MM32_INT_FLAG_STOP_DET);
            /* ��ʼ�������ʱ����ʱ 1000ms */
            am_softimer_start(&p_dev->softimer, 1000);
        }
    }

    /* �ж��Ƿ��ǹ㲥���� */
    if( i2c_slv_int_status & AMHW_MM32_INT_FLAG_GEN_CALL ) {
        amhw_mm32_i2c_clr_gen_call_get(p_hw_i2c_slv );
        p_dev->is_gen_call = AM_TRUE;
    }

    /**
     * \brief ���ܻ���ǿ�ʱ ���ӻ�׼����������
     */
    if ( i2c_slv_int_status & AMHW_MM32_INT_FLAG_RX_FULL) {
        /* ��ʼ�������� */
        __i2c_slv_irq_rx_handler (p_dev);
    }

    /**
     * \brief ��������
     */
    /** ���ж�����ʱ */
    if ( i2c_slv_int_status & AMHW_MM32_INT_FLAG_RD_REQ) {
        /* ��ʼ�������� */
        __i2c_slv_irq_tx_handler (p_dev);
        /**
         * \brief
         * \note ������ֵ�趨��Ϊ1ʱ��    FIFO���е��ֽ��� С�ڵ��� 1�;ͻᴥ�����Ϳ��ж�
         *       ������ֵ�趨��Ϊ0ʱ��    FIFO���е��ֽ��� С�ڵ��� 0�;ͻᴥ�����Ϳ��ж�
         */
        amhw_mm32_i2c_intr_mask_set(p_hw_i2c_slv, AMHW_MM32_INT_FLAG_TX_EMPTY);
    }
    /* �������п��������� */
    if (i2c_slv_int_status & AMHW_MM32_INT_FLAG_TX_EMPTY ) {
        __i2c_slv_irq_tx_handler (p_dev);
    }

    /**
     * \brief �������ݽ���ʱ
     */
    if( i2c_slv_int_status & AMHW_MM32_INT_FLAG_STOP_DET) {

        /** �����������������ʱ �����������ܻ������ݣ�������ֹ����1,��ʱ��� */
        if ( p_hw_i2c_slv->ic_raw_intr_stat & AMHW_MM32_INT_FLAG_TX_ABRT ) {
            amhw_mm32_i2c_clr_tx_abrt_get(p_hw_i2c_slv);
        }

        /** ���ֹͣ�ж� */
        amhw_mm32_i2c_clr_stop_det_get(p_hw_i2c_slv);
        /** �ر�ֹͣ�ж� */
        amhw_mm32_i2c_intr_mask_clear(p_hw_i2c_slv,AMHW_MM32_INT_FLAG_STOP_DET);
        p_dev->is_gen_call = AM_FALSE;

        /* ִ�д���ֹͣ�ص� */
        if ( NULL != p_i2c_slv_dev->p_cb_funs->pfn_tran_stop) {
            p_i2c_slv_dev->p_cb_funs->pfn_tran_stop(p_i2c_slv_dev->p_arg);
        }

        amhw_mm32_i2c_intr_mask_clear(p_hw_i2c_slv, AMHW_MM32_INT_FLAG_TX_EMPTY);

        /* �������ֹͣ��ʱ */
        am_softimer_stop(&p_dev->softimer);
    }
}

/**
 * \brief I2C��ʼ��
 *
 * \note Ӳ����ʼ�� ͨ���û����ÿ�ʼ���豸����ʼ��
 */
am_i2c_slv_handle_t am_mm32_i2c_slv_init (am_mm32_i2c_slv_dev_t           *p_dev,
                                         const am_mm32_i2c_slv_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL ) {
        return NULL;
    }

    p_dev->i2c_slv_serv.p_funcs = (struct am_i2c_slv_drv_funcs *)&__g_i2c_slv_drv_funcs;
    p_dev->i2c_slv_serv.p_drv   = p_dev;

    p_dev->p_devinfo   = p_devinfo;
    p_dev->mm32_i2c_slv_dev_num =1;  /* ֻ������һ���ӻ��豸 */

    /* p_dev->current_matching_num =0; Ĭ�ϵ�ǰƥ��Ϊ 0 */

    p_dev->is_gen_call = AM_FALSE;

    p_dev->p_i2c_slv_dev[0] = NULL;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* ��ʼ�������ʱ�� */
    am_softimer_init(&p_dev->softimer, __i2c_slv_timing_callback, p_dev);

    __i2c_slv_hard_init(p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __i2c_slv_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->i2c_slv_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_mm32_i2c_slv_deinit (am_i2c_slv_handle_t handle)
{
    amhw_mm32_i2c_t       *p_hw_i2c_slv = NULL;
    am_mm32_i2c_slv_dev_t *p_dev    = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev    = (am_mm32_i2c_slv_dev_t *)handle;
    p_hw_i2c_slv = (amhw_mm32_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    amhw_mm32_i2c_disable (p_hw_i2c_slv);

    /* ȥ���ж����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __i2c_slv_irq_handler, (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
