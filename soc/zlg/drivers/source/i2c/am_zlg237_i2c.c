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
 * \brief zlg237 I2C�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-24  zc, first implementation
 * \endinternal
 */

/*******************************************************************************
  ͷ�ļ�
*******************************************************************************/
#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_zlg237_i2c.h"
#include "hw/amhw_zlg237_i2c.h"
#include "zlg237_clk.h"
#include "am_gpio.h"
#include "zlg237_pin.h"
#include "amhw_zlg237_gpio.h"
/*******************************************************************************
  �궨��
*******************************************************************************/
#define __I2C_ST_IDLE             (0x10u)          /* ����״̬ */
#define __I2C_ST_MSG_START        (0x11u)          /* ��Ϣ���俪ʼ״̬ */
#define __I2C_ST_TRANS_START      (0x12u)          /* �������俪ʼ״̬ */
#define __I2C_ST_SEND_SLA_ADDR    (0x13u)          /* ���ʹӻ���ַ״̬ */
#define __I2C_ST_M_SEND_DATA      (0x14u)          /* ��������״̬ */
#define __I2C_ST_M_RECV_DATA      (0x15u)          /* ��������״̬ */

#define __I2C_EVT_NONE            (0xFFu)          /* ���¼� */
#define __I2C_EVT_MSG_LAUNCH      (0xFEu)          /* ��ʼ����һ���µ���Ϣ */
#define __I2C_EVT_TRANS_LAUNCH    (0xFDu)          /* ��ʼ����һ���µĴ��� */

#define __I2C_EVT_MST_IDLE        AM_SBF(0x0, 1)  /* ���������¼� */
#define __I2C_EVT_MST_START       AM_SBF(0X3, 1)  /* ������� */
#define __I2C_EVT_MST_ADDR        AM_SBF(0X4, 1)  /* ������� */
#define __I2C_EVT_MST_RX          AM_SBF(0x1, 1)  /* ���Խ������� */
#define __I2C_EVT_MST_TX          AM_SBF(0x2, 1)  /* ���Է������� */

/* check if transfers empty */
#define __I2C_TRANS_EMPTY(p_dev) \
    ((p_dev)->p_cur_trans >= (p_dev)->p_cur_msg->p_transfers \
                             + (p_dev)->p_cur_msg->trans_num)

/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief I2C Ӳ����ʼ�� */
static int __i2c_hard_init (am_zlg237_i2c_dev_t *p_dev);

/** \brief I2C �жϴ����� */
static void __i2c_irq_handler (void *p_arg);

/** \brief I2C ״̬������ */
static int __i2c_mst_sm_event (am_zlg237_i2c_dev_t *p_dev, uint32_t event);

/** \brief I2C ��Ϣ������ */
static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_trans);

/** \brief �ӿ����������б��ͷȡ��һ�� message */
am_static_inline
struct am_i2c_message *__i2c_msg_out (am_zlg237_i2c_dev_t *p_dev);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**
 * \brief I2C ������������
 */
static am_const struct am_i2c_drv_funcs __g_i2c_drv_funcs = {
    __i2c_msg_start
};

/******************************************************************************/

/** \brief I2C Ӳ����ʼ�� */
am_local int __i2c_hard_init (am_zlg237_i2c_dev_t *p_dev)
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

    /** \breif д��CR1 */
    p_hw_i2c->i2c_cr1 = tmpreg;

    /** \breif I2C OAR1 ���� */
    p_hw_i2c->i2c_oar1 = (p_dev->i2c_acknowledgedaddress |
                          (p_dev->i2c_ownaddress1 <<1 ) );

    /* Ĭ�ϲ�ʹ�� 10bit��ַ*/
    amhw_zlg237_i2c_endual(p_hw_i2c,DISABLE);
    amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                  I2C_CR2_ITERREN |
                                  I2C_CR2_ITEVTEN |
                                  I2C_CR2_ITBUFEN,
                                  DISABLE);

    /** ���� I2C����  */
    amhw_zlg237_i2c_enable(p_hw_i2c);

    return AM_OK;
}

am_local int __i2c_hard_re_init (am_zlg237_i2c_dev_t *p_dev)
/** \brief I2C Ӳ�����³�ʼ�� */
{
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }
    return __i2c_hard_init(p_dev);
}

/**
 * \brief ���³�ʼ�� I2C
 *
 * \param[in] p_arg ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
am_local void __i2c_re_init (void *p_arg)
{
    am_zlg237_i2c_dev_t *p_dev = (am_zlg237_i2c_dev_t *)p_arg;
    uint32_t          key   = 0;

    if (p_arg == NULL) {
        return;
    }

    key = am_int_cpu_lock();

    p_dev->is_abort = AM_TRUE;

    do {

        /* �ص���Ϣ��ɺ��� */
        if ((p_dev->p_cur_msg != NULL) &&
            (p_dev->p_cur_msg->pfn_complete != NULL)) {
            p_dev->p_cur_msg->status = -AM_ETIMEDOUT;
            p_dev->p_cur_msg->pfn_complete(p_dev->p_cur_msg->p_arg);
        }

        p_dev->p_cur_msg = __i2c_msg_out(p_dev);
        if (NULL == p_dev->p_cur_msg) {
            break;
        }
    } while (1);

    p_dev->p_cur_trans = NULL;
    p_dev->p_cur_msg   = NULL;
    p_dev->is_complete = AM_FALSE;
    p_dev->data_ptr    = 0;
    p_dev->trans_state = 0;
    p_dev->busy        = AM_FALSE;
    p_dev->state       = __I2C_ST_IDLE; /* ��ʼ��Ϊ����״̬ */
    p_dev->slave_addr  = 0;

    p_dev->i2c_clock_speed         = p_dev->p_devinfo->speed;
    p_dev->i2c_mode                = AMHW_ZLG237_I2C_MODE_I2C;
    p_dev->i2c_dutycycle           = AMHW_ZLG237_I2C_DUTY_CYCLE_2;
    p_dev->i2c_ownaddress1         = 0x01;
    p_dev->i2c_ack                 = AMHW_ZLG237_I2C_ACK_ENABLE;
    p_dev->i2c_acknowledgedaddress = AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT;

    am_list_head_init(&(p_dev->msg_list));

    __i2c_hard_re_init(p_dev);

    if (p_dev->p_devinfo->pfn_bus_clean) {
        p_dev->p_devinfo->pfn_bus_clean();
    }
    am_int_cpu_unlock(key);
}

/**
 * \brief ʹ�������ʱ��
 *
 * \param[in] p_arg ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
am_local void __softimer_start (am_zlg237_i2c_dev_t *p_dev)
{
    p_dev->is_abort = AM_FALSE;

    if (p_dev->p_devinfo->timeout_ms == 0) {
        return;
    }

    if (p_dev->softimer_state == AM_FALSE) {
        p_dev->softimer_state = AM_TRUE;
        am_softimer_start(&p_dev->softimer,
                           p_dev->p_devinfo->timeout_ms);
    } else {
        am_softimer_stop(&p_dev->softimer);
        am_softimer_start(&p_dev->softimer,
                           p_dev->p_devinfo->timeout_ms);
    }
}

/**
 * \brief ֹͣ�����ʱ��
 *
 * \param[in] p_arg ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
am_local void __softimer_stop (am_zlg237_i2c_dev_t *p_dev)
{
    if (p_dev->p_devinfo->timeout_ms == 0) {
        return;
    }

    am_softimer_stop(&p_dev->softimer);

    p_dev->softimer_state = AM_FALSE;
}

/******************************************************************************/

/**
 * \brief ���һ�� message �������������б�ĩβ
 *
 * \attention ���ô˺�����������������
 */
am_static_inline
void __i2c_msg_in (am_zlg237_i2c_dev_t *p_dev, struct am_i2c_message *p_msg)
{
    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
                    &(p_dev->msg_list));
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 *
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_i2c_message *__i2c_msg_out (am_zlg237_i2c_dev_t *p_dev)
{
    if (am_list_empty_careful(&(p_dev->msg_list))) {
        return NULL;
    } else {
        struct am_list_head *p_node = p_dev->msg_list.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_i2c_message, ctlrdata);
    }
}

/******************************************************************************/

/**
 * \brief ��ʱ�����ʱ���ص�����
 *
 * \param[in] p_arg ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
am_local void __softimer_callback (void *p_arg)
{
    am_zlg237_i2c_dev_t *p_dev = (am_zlg237_i2c_dev_t *)p_arg;

    if (p_arg == NULL) {
        return;
    }

    __softimer_stop(p_dev);
    __i2c_re_init(p_arg);
}

/**
 * \brief I2C �жϴ�����
 *
 * \param[in] p_arg : ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
static void __i2c_irq_handler (void *p_arg)
{
    am_zlg237_i2c_dev_t *p_dev          = NULL;
    amhw_zlg237_i2c_t   *p_hw_i2c       = NULL;
    uint16_t             i2c_int_status = 0;

    p_dev    = (am_zlg237_i2c_dev_t *)p_arg;
    p_hw_i2c = (amhw_zlg237_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;
    if (p_arg == NULL) {
        return;
    }

     i2c_int_status = amhw_zlg237_i2c_getitstatus(p_hw_i2c);


     /* �ȴ�BTF�¼��ж� �����ͺͶ�ȡ���� */
     if (i2c_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__BTF) {
         if (i2c_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__RXNE) {
             __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_RX);
             return ;
         } else if (i2c_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__TXE) {
             __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_TX);
             return;
         }
     }
     /* ��ֻ��ȡһ������ʱ RXNE = 1 ��ȡ���� */
     if ( p_cur_trans->flags & AM_I2C_M_RD) {
         if (p_cur_trans->nbytes == 1)
        /* ���շǿգ��������״̬ */
        if (i2c_int_status & (uint16_t)AMHW_ZLG_INT_FLAG__RXNE) {

            /** \brief ����ģʽ  ��ȡ DR�Ĵ���  ����жϱ�־λ */
            __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_RX);
        }
    }

}

/******************************************************************************/

static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_msg)
{
    am_zlg237_i2c_dev_t  *p_dev    = (am_zlg237_i2c_dev_t *)p_drv;
    amhw_zlg237_i2c_t *p_hw_i2c    = (amhw_zlg237_i2c_t *)
                                      p_dev->p_devinfo->i2c_regbase;
    int key;

    /** \brief �ж��豸�� ��Ϣ �������Ϣ�Ĵ��� ��������Ĵ�������Ƿ�Ϊ�� */
    if ( (p_dev              == NULL) ||
         (p_msg              == NULL) ||
         (p_msg->p_transfers == NULL) ||
         (p_msg->trans_num   == 0)) {

        return -AM_EINVAL;
    }
    /** \brief �رձ���CPU�ж� */
    key = am_int_cpu_lock();

    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
    if (p_dev->busy == AM_TRUE) {

        __i2c_msg_in(p_dev, p_msg);

        am_int_cpu_unlock(key);

        return AM_OK;

    } else {
        /** \brief ���߿��� */
        p_dev->busy = AM_TRUE;
        __i2c_msg_in(p_dev, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        am_int_cpu_unlock(key);

        /** \brief �豸״̬  ת��Ϊ  ��ʼ����һ���µ���Ϣ */
        return __i2c_mst_sm_event(p_dev, __I2C_EVT_MSG_LAUNCH);
    }
}

/**
 * \brief I2C��ʼ��
 */
am_i2c_handle_t am_zlg237_i2c_init (am_zlg237_i2c_dev_t           *p_dev,
                                 const am_zlg237_i2c_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->i2c_serv.p_funcs = (struct am_i2c_drv_funcs *)&__g_i2c_drv_funcs;
    p_dev->i2c_serv.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    p_dev->p_cur_trans             = NULL;
    p_dev->p_cur_msg               = NULL;
    p_dev->is_complete             = AM_FALSE;
    p_dev->data_ptr                = 0;
    p_dev->trans_state             = 0;
    p_dev->busy                    = AM_FALSE;
    p_dev->state                   = __I2C_ST_IDLE; /* ��ʼ��Ϊ����״̬ */
    p_dev->slave_addr              = 0;

    p_dev->i2c_clock_speed         = p_devinfo->speed;
    p_dev->i2c_mode                = AMHW_ZLG237_I2C_MODE_I2C;
    p_dev->i2c_dutycycle           = AMHW_ZLG237_I2C_DUTY_CYCLE_2;
    p_dev->i2c_ownaddress1         = 0x01;
    p_dev->i2c_ack                 = AMHW_ZLG237_I2C_ACK_ENABLE;
    p_dev->i2c_acknowledgedaddress = AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT;


    if (p_devinfo->timeout_ms != 0) {
        p_dev->softimer_state = AM_FALSE;
        if (am_softimer_init(&p_dev->softimer,
                              __softimer_callback,
                              p_dev) != AM_OK) {
            return NULL;
        }
    }

    p_dev->is_abort = AM_FALSE;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    am_list_head_init(&(p_dev->msg_list));

    __i2c_hard_init(p_dev);

//    if (p_dev->p_devinfo->pfn_bus_clean) {
//        p_dev->p_devinfo->pfn_bus_clean();
//    }

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_dev);
    am_int_connect(p_dev->p_devinfo->inum + 1, __i2c_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    am_int_enable(p_dev->p_devinfo->inum + 1);

    return &(p_dev->i2c_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_zlg237_i2c_deinit (am_i2c_handle_t handle)
{
    amhw_zlg237_i2c_t   *p_hw_i2c = NULL;
    am_zlg237_i2c_dev_t *p_dev    = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev    = (am_zlg237_i2c_dev_t *)handle;
    p_hw_i2c = (amhw_zlg237_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    p_dev->i2c_serv.p_funcs = NULL;
    p_dev->i2c_serv.p_drv   = NULL;

    amhw_zlg237_i2c_disable(p_hw_i2c);

    /* ȥ���ж����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum,
                      __i2c_irq_handler,
                      (void *)p_dev);

    __softimer_stop(p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/******************************************************************************/

/*  ״̬���ڲ�״̬�л� */
#define __I2C_NEXT_STATE(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/*
 * \brief ����SCL
 */
am_static_inline
void i2c_pulldown_scl (am_zlg237_i2c_dev_t *p_dev) {

    int i2c_num = p_dev->p_devinfo->clk_num;
    amhw_zlg237_gpio_reg_t *p_hw_gpio = NULL;
    p_hw_gpio = (amhw_zlg237_gpio_reg_t *)ZLG237_GPIOB_BASE;
    if (i2c_num == CLK_I2C1) {
        p_hw_gpio->brr |= (uint32_t)(1 << 6);
        p_hw_gpio->crl &= ~0x8000000;
    } else if (i2c_num == CLK_I2C2) {
        p_hw_gpio->brr |= (uint32_t)(1 << 10);
        p_hw_gpio->crh &= ~0x800;
    }
}

/*
 * \brief �ͷ�SCL
 */
am_static_inline
void i2c_release_scl (am_zlg237_i2c_dev_t *p_dev) {
    int i2c_num = p_dev->p_devinfo->clk_num;
    amhw_zlg237_gpio_reg_t *p_hw_gpio = NULL;
    p_hw_gpio = (amhw_zlg237_gpio_reg_t *)ZLG237_GPIOB_BASE;
    if (i2c_num == CLK_I2C1) {
        p_hw_gpio->crl |= 0x8000000;
    } else if (i2c_num == CLK_I2C2) {
        p_hw_gpio->crh |= 0x800;
    }
}
/**
 * \brief I2C ״̬������
 */
static int __i2c_mst_sm_event (am_zlg237_i2c_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t  new_event = __I2C_EVT_NONE;
    amhw_zlg237_i2c_t *p_hw_i2c = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_zlg237_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    /* �������� */
    (void)event;

    while (1) {

        /* ����Ƿ����µ��¼���״̬���ڲ����� */
        if (new_event != __I2C_EVT_NONE) {
            event     = new_event;
            new_event = __I2C_EVT_NONE;
        }

        /* ���豸��״̬Ϊ��׼����״̬������ */
        switch (p_dev->state) {

        /*
         * ����״̬������I2CģʽΪ����ģʽ
         * ����״̬�Ϳ�ʼ��Ϣ����״̬Ҫ�����������һ�����¼�ֻӦ�ǣ�
         * __I2C_EVT_TRANS_LAUNCH
         */

        case __I2C_ST_IDLE:
        {
            /* �� ��BUSYλ�Ƿ��  0*/
            while(amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                                                 AMHW_ZLG_I2C_FLAG_BUSY));
        }
        case __I2C_ST_MSG_START:
        {
            am_i2c_message_t *p_cur_msg = NULL;
            int key;

            /** ����Ϣ������ȡ�����������Ϣ */
            key = am_int_cpu_lock();

            p_cur_msg        = __i2c_msg_out(p_dev);
            p_dev->p_cur_msg = p_cur_msg;

            /* �����δ������õĴӻ���ַ �� p_dev�е�ֵ��ƥ��   ���´ӵ�ַ*/
            if (p_dev->p_cur_msg->p_transfers->addr != p_dev->slave_addr) {
                p_dev->slave_addr = p_dev->p_cur_msg->p_transfers->addr;
            }

            /* �ж�ȡ����Ϣ�������� */
            if (p_cur_msg) {

                /* ������Ϣ��״̬  */
                p_cur_msg->status = -AM_EINPROGRESS;
            } else {

                p_dev->busy = AM_FALSE;
            }
            am_int_cpu_unlock(key);

            /* ���账�����Ϣ */
            if (p_cur_msg == NULL) {

                __I2C_NEXT_STATE(__I2C_ST_IDLE, __I2C_EVT_NONE);

                break;
            } else {

                /*��һ�δ�������*/
                p_cur_msg->done_num = 0;
                p_dev->p_cur_trans  = p_cur_msg->p_transfers;
                p_dev->data_ptr     = 0;


                __I2C_NEXT_STATE(__I2C_ST_TRANS_START,
                        __I2C_EVT_TRANS_LAUNCH);

                /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
                event     = new_event;
                new_event = __I2C_EVT_NONE;

                __softimer_start(p_dev);
            }
        }
        /* no break */
        case __I2C_ST_TRANS_START:
        {
            /* �¼���������״̬ƥ�� */
            if (event != __I2C_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;
            }

            struct am_i2c_message *p_cur_msg = p_dev->p_cur_msg;

            if (NULL == p_cur_msg) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);

                return -AM_EINVAL;
            }

            /* ��ǰ��Ϣ�������  */
            if (__I2C_TRANS_EMPTY(p_dev)) {

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                p_dev->is_complete = AM_TRUE;

                /*�ж��Ǵ��������ջ��Ƿ���ģʽ*/
                am_bool_t is_send = amhw_zlg237_i2c_checkflagstaus(
                    p_hw_i2c, AMHW_ZLG_I2C_FLAG_TRA);

                /* ����EV8_2 �¼�ʱ   ����ֹͣ����   ������*/
                if (is_send == AM_TRUE) {

                    /* ������ģʽ�²���ֹͣ�źź�I2C�Զ��ص��ӻ�ģʽ */
                    amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);

                    /* �ر��ж�TXE RXNE */
                    amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                                  I2C_CR2_ITEVTEN |
                                                  I2C_CR2_ITBUFEN,
                                                  DISABLE);

                    __softimer_stop(p_dev);

                    if (AM_FALSE != p_dev->is_complete) {
                        __I2C_NEXT_STATE(__I2C_ST_IDLE, __I2C_EVT_NONE);
                        p_dev->is_complete = AM_FALSE;
                        p_dev->busy = AM_FALSE;

                        /* �ص���Ϣ��ɺ��� */
                        if (p_dev->p_cur_msg->pfn_complete != NULL) {
                            p_dev->p_cur_msg->pfn_complete(
                                p_dev->p_cur_msg->p_arg);
                        }

                    } else {
                        __i2c_re_init(p_dev);
                    }
                    break;

                } else {

                    /* ����ģʽ  ����ֹͣ����ǰ  ��Ӧ�ڵ����ڶ������� ������    EV7: RXE = 1 ��DR������¼� */

                    amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                                  I2C_CR2_ITEVTEN |
                                                  I2C_CR2_ITBUFEN,
                                                  DISABLE);

                    __softimer_stop(p_dev);

                    if (AM_FALSE != p_dev->is_complete) {
                        __I2C_NEXT_STATE(__I2C_ST_IDLE, __I2C_EVT_NONE);
                        p_dev->is_complete = AM_FALSE;
                        p_dev->busy = AM_FALSE;

                        /* �ص���Ϣ��ɺ��� */
                        if (p_dev->p_cur_msg->pfn_complete != NULL) {
                            p_dev->p_cur_msg->pfn_complete(
                                p_dev->p_cur_msg->p_arg);
                        }

                    } else {
                        __i2c_re_init(p_dev);
                    }
                    break;
                }

            } else {    /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */

                    struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

                    if (NULL == p_cur_trans) {
                        __softimer_stop(p_dev);
                        __i2c_re_init(p_dev);

                        return -AM_EINVAL;
                    }

                    p_dev->data_ptr = 0;

                    /*
                      * ����Ҫ�����źţ�ֱ�Ӵ��䣬����ͬʱ������������������
                      * 1.�����˱�־ AM_I2C_M_NOSTART
                      * 2./��ǰ���䲻��һ����Ϣ�еĵ�һ������
                      * 3.��ǰ��������һ������ķ���һ��
                      */
                    if ((p_cur_trans->flags & AM_I2C_M_NOSTART) &&
                        ((p_cur_trans->flags & AM_I2C_M_RD) ==
                        ((p_cur_trans - 1)->flags & AM_I2C_M_RD))) {

                        am_bool_t is_read = (p_cur_trans->flags & AM_I2C_M_RD) ?
                                         AM_TRUE : AM_FALSE;

                        /* ��ǰ����״̬����һ״̬ �ӻ���ַ�ڿ���״̬�Դ���*/
                        p_dev->trans_state = 1;

                        if (is_read == AM_TRUE) {

                            /* ������������ */
                            __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA,
                                    __I2C_EVT_NONE);
                            break;
                        } else {
                            /* ������������ */
                            __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA,
                                    __I2C_EVT_NONE);
                            break;
                        }
                    /* ���ʹӻ���ַ */
                    } else {
                        /* �˴������˴ӻ���ַ */
                        p_dev->trans_state = 0;
                        /* ��һ�������Ƿ��͵�ַ */
                        __I2C_NEXT_STATE(__I2C_ST_SEND_SLA_ADDR,
                                __I2C_EVT_MST_START);
                        event     = new_event;
                        new_event = __I2C_EVT_NONE;
                    }
            }
        }

        case __I2C_ST_SEND_SLA_ADDR:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            if ((NULL == p_cur_msg) || (NULL == p_cur_trans)) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);
                return -AM_EINVAL;
            }

            /* �ݲ�֧��10bit ģʽ */
            if (p_cur_trans->flags & AM_I2C_ADDR_10BIT) {

                /* ������Ϣ״̬ */
                p_cur_msg->status = -AM_ENOTSUP;

                /* ����ʣ�µ�transfer */
                p_dev->p_cur_trans = p_cur_msg->p_transfers +
                                     p_cur_msg->trans_num;

                /* ������ǰ����Ϣ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START,
                                 __I2C_EVT_TRANS_LAUNCH);

                break;
            }

            /* ������ʼ���� �л�����ģʽ */
            amhw_zlg237_i2c_genstrat(p_hw_i2c, ENABLE);

            /* EV5�¼� �� �ȴ�SB */
            while (!amhw_zlg237_i2c_checkevent(p_hw_i2c,
                    I2C_EVENT_MASTER_MODE_SELECT ));

            /* ���SB */
            amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);

            /* ���ʹӻ���ַ */
            if ( p_cur_trans->flags & AM_I2C_M_RD) {

                __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA,
                        __I2C_EVT_NONE);
                /* ��*/
                amhw_zlg237_i2c_send7bit_address(
                    p_hw_i2c, p_dev->slave_addr, 1);
            } else {

                __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA,
                        __I2C_EVT_NONE);
                /* д */
                amhw_zlg237_i2c_send7bit_address(
                    p_hw_i2c, p_dev->slave_addr, 0);
            }

            /* �ȴ�EV6�¼���־λ */
            while (1) {
                if (p_hw_i2c->i2c_sr1 & 0x0002) {
                    break;
                }
            }

            if ( p_cur_trans->flags & AM_I2C_M_RD) {
                if (p_cur_trans->nbytes == 1) {
                    i2c_pulldown_scl(p_dev);

                    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);

                    amhw_zlg237_i2c_ack_en(p_hw_i2c, DISABLE);
                    amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);
                    i2c_release_scl(p_dev);
                } else if (p_cur_trans->nbytes == 2) {
                    amhw_zlg237_i2c_ack_en(p_hw_i2c, ENABLE);

                    /* ����POSλ */
                    amhw_zlg237_i2c_pos(p_hw_i2c, ENABLE);

                    i2c_pulldown_scl(p_dev);

                    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);
                    amhw_zlg237_i2c_ack_en(p_hw_i2c, DISABLE);

                    i2c_release_scl(p_dev);
                } else {

                    /* ��ȡsr2�Ĵ������EV6�¼� */
                    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);
                }
            } else {

                /* ��ȡsr2�Ĵ������EV6�¼� */
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);
                if ( ((p_cur_trans->flags & 0x01) == 0) && (p_dev->data_ptr == 0)) {
                    amhw_zlg237_i2c_send_data(p_hw_i2c,
                         (p_cur_trans->p_buf)[p_dev->data_ptr++]);
                }
            }

            /* ��TXE RXNE�ж�ʹ�� */
            amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                          I2C_CR2_ITEVTEN |
                                          I2C_CR2_ITBUFEN ,
                                          ENABLE);
            break;

        }
        case __I2C_ST_M_RECV_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            if ((NULL == p_cur_msg) || (NULL == p_cur_trans)) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);

                return -AM_EINVAL;
            }

            if (p_cur_trans->nbytes ==1) {

                /* ��ȡһ������ */
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);
            } else if (p_cur_trans->nbytes ==2) {

                /* ��ȡ�������� */
                i2c_pulldown_scl(p_dev);

                /* ���POSλ */
                amhw_zlg237_i2c_pos(p_hw_i2c, DISABLE);

                amhw_zlg237_i2c_ack_en(p_hw_i2c, ENABLE);
                amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);

                i2c_release_scl(p_dev);
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);
            }else if (p_dev->data_ptr == (p_cur_trans->nbytes - 3) &&
                     (p_cur_trans->nbytes !=1) &&
                     (p_cur_trans->nbytes !=2)) {

                /* ��ȡ��N-2 ������ */
                i2c_pulldown_scl(p_dev);
                amhw_zlg237_i2c_ack_en(p_hw_i2c, DISABLE);
                i2c_release_scl(p_dev);
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);
            } else if (p_dev->data_ptr == (p_cur_trans->nbytes - 2) &&
                      (p_cur_trans->nbytes !=1) &&
                      (p_cur_trans->nbytes !=2)) {

                /* ��ȡ��N-1 ��N ������ */
                i2c_pulldown_scl(p_dev);
                amhw_zlg237_i2c_ack_en(p_hw_i2c, ENABLE);
                amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);
                i2c_release_scl(p_dev);
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);
            } else {

                /* ��ȡ������� */
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                        amhw_zlg237_i2c_recv_data(p_hw_i2c);
            }


            if (p_dev->data_ptr != p_cur_trans->nbytes) {

                __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA,
                        __I2C_EVT_NONE);
            } else { /* ����������ϣ��ô������ */

                /* ����ӻ���ַ */
                p_dev->slave_addr =p_dev->p_cur_trans->addr;

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

                /* �ر� TXE RXNE�ж� */
                amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                              I2C_CR2_ITEVTEN |
                                              I2C_CR2_ITBUFEN ,
                                              DISABLE);
                /* �ȴ�Ӳ����� stop λ */
                while((p_hw_i2c->i2c_cr1 & 0x200));

                /* �ڶ����ݽ�����ʹ��ACKλ*/
                amhw_zlg237_i2c_ack_en(p_hw_i2c, ENABLE);

                /* ��������ϣ�������һ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START,
                                 __I2C_EVT_TRANS_LAUNCH);
            }
            break;
        }
        case __I2C_ST_M_SEND_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;
            if (event != __I2C_EVT_MST_TX) {
                return -AM_EINVAL;    /* �¼���������״̬ƥ�� */
            }
            if ((NULL == p_cur_msg) ||(NULL == p_cur_trans)) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);

                return -AM_EINVAL;
            }

            if (p_dev->data_ptr < p_cur_trans->nbytes) {

                amhw_zlg237_i2c_send_data(p_hw_i2c,
                     (p_cur_trans->p_buf)[p_dev->data_ptr++]);

            } else {
                /* ����ӻ���ַ */
                p_dev->slave_addr =p_dev->p_cur_trans->addr;

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

                /*
                 * ��һ�δ���Ϊ write ���δ���Ϊ readʱ �ر��ж�ʹ�� ���ⷢ�ʹӵ�ַ ����addr�ж�
                 */
                if((p_dev->p_cur_trans->flags & AM_I2C_M_RD) &&
                    (!((p_dev->p_cur_trans - 1)->flags & AM_I2C_M_RD))) {
                    amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);
                    amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                            I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN , DISABLE);

                }
                /* �ȴ�Ӳ����� stop λ */
                while((p_hw_i2c->i2c_cr1 & 0x200));
                /* ��������ϣ�������һ���� */
                __I2C_NEXT_STATE(__I2C_ST_TRANS_START,
                                 __I2C_EVT_TRANS_LAUNCH);
            }
            break;
        }

        default:
            break;
        }

        if (p_dev->is_abort != AM_FALSE) {
            p_dev->is_abort = AM_FALSE;
            return -AM_FALSE;
        }

        if (new_event == __I2C_EVT_NONE) {
            break;
        }
    }

    return AM_OK;
}
/* end of file */
