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
 * \brief I2C����������I2C��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 17-12-28  pea, add a timeout mechanism, enable TX_ABRT and STOP_DET
 *                  interrupt
 * - 1.00 17-04-24  sdy, first implementation
 * \endinternal
 */

/*******************************************************************************
  ͷ�ļ�
*******************************************************************************/
#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_zlg_i2c.h"
#include "hw/amhw_zlg_i2c.h"

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

#define __I2C_EVT_MST_IDLE         AM_SBF(0x0, 1)  /* ���������¼� */
#define __I2C_EVT_MST_RX           AM_SBF(0x1, 1)  /* ���Խ������� */
#define __I2C_EVT_MST_TX           AM_SBF(0x2, 1)  /* ���Է������� */

/* check if transfers empty */
#define __I2C_TRANS_EMPTY(p_dev) \
    ((p_dev)->p_cur_trans >= (p_dev)->p_cur_msg->p_transfers \
                             + (p_dev)->p_cur_msg->trans_num)

/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief I2C Ӳ����ʼ�� */
static int __i2c_hard_init (am_zlg_i2c_dev_t *p_dev);

/** \brief I2C �жϴ����� */
static void __i2c_irq_handler (void *p_arg);

/** \brief I2C ״̬������ */
static int __i2c_mst_sm_event (am_zlg_i2c_dev_t *p_dev, uint32_t event);

/** \brief I2C ��Ϣ������ */
static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_trans);

/** \brief �ӿ����������б��ͷȡ��һ�� message */
am_static_inline
struct am_i2c_message *__i2c_msg_out (am_zlg_i2c_dev_t *p_dev);

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
am_local int __i2c_hard_init (am_zlg_i2c_dev_t *p_dev)
{
    amhw_zlg_i2c_t *p_hw_i2c = NULL;
    uint16_t mode  = AMHW_ZLG_I2C_NORMAL_SPEED;
    uint16_t count = (am_clk_rate_get (p_dev->p_devinfo->clk_num) /
                                       p_dev->p_devinfo->speed) /
                                       2;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_zlg_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    amhw_zlg_i2c_disable (p_hw_i2c);

    if (p_dev->p_devinfo->speed <= 100000) {
        amhw_zlg_i2c_ss_scl_low_set(p_hw_i2c, count);
        amhw_zlg_i2c_ss_scl_high_set(p_hw_i2c, count);
        mode = AMHW_ZLG_I2C_NORMAL_SPEED;
    } else {
        amhw_zlg_i2c_fs_scl_low_set(p_hw_i2c, count);
        amhw_zlg_i2c_fs_scl_high_set(p_hw_i2c, count);
        mode = AMHW_ZLG_I2C_HIGH_SPEED;
    }

    p_hw_i2c->ic_con = (mode |
                        AMHW_ZLG_I2C_MASTER |
                        AMHW_ZLG_I2C_RESTART_ENABLE);

    amhw_zlg_i2c_rx_tl_set(p_hw_i2c, 0);
    amhw_zlg_i2c_tx_tl_set(p_hw_i2c, 1);

    amhw_zlg_i2c_intr_mask_clear (p_hw_i2c, 0xfff);

    return AM_OK;
}

/** \brief I2C Ӳ�����³�ʼ�� */
am_local int __i2c_hard_re_init (am_zlg_i2c_dev_t *p_dev)
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
    am_zlg_i2c_dev_t *p_dev = (am_zlg_i2c_dev_t *)p_arg;
    uint32_t             key   = 0;

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
am_local void __softimer_start (am_zlg_i2c_dev_t *p_dev)
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
am_local void __softimer_stop (am_zlg_i2c_dev_t *p_dev)
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
void __i2c_msg_in (am_zlg_i2c_dev_t *p_dev, struct am_i2c_message *p_msg)
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
struct am_i2c_message *__i2c_msg_out (am_zlg_i2c_dev_t *p_dev)
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
    am_zlg_i2c_dev_t *p_dev = (am_zlg_i2c_dev_t *)p_arg;

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
    am_zlg_i2c_dev_t *p_dev    = NULL;
    amhw_zlg_i2c_t   *p_hw_i2c = NULL;
    amhw_zlg_int_flag_t  i2c_int_status;

    if (p_arg == NULL) {
        return;
    }

    p_dev    = (am_zlg_i2c_dev_t *)p_arg;
    p_hw_i2c = (amhw_zlg_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    i2c_int_status = amhw_zlg_i2c_intr_stat_get (p_hw_i2c);

    /* ����жϱ�־ */
    amhw_zlg_i2c_clr_intr_get(p_hw_i2c);

    /* ������ֹ */
    if (i2c_int_status & AMHW_ZLG_INT_FLAG_TX_ABRT) {
        amhw_zlg_i2c_intr_mask_clear(p_hw_i2c,
                                     AMHW_ZLG_INT_FLAG_TX_ABRT);

        amhw_zlg_i2c_clr_tx_abort(p_hw_i2c);
        p_hw_i2c->ic_clr_tx_abrt = 0;
        if (!__I2C_TRANS_EMPTY(p_dev)) {
            __softimer_stop(p_dev);
            __i2c_re_init(p_dev);
            return;
        }
    }

    /* ���շǿգ��������״̬ */
    if (i2c_int_status & AMHW_ZLG_INT_FLAG_RX_FULL) {
        amhw_zlg_i2c_intr_mask_clear(p_hw_i2c,
                                     AMHW_ZLG_INT_FLAG_RX_FULL);
        __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_RX);
    }

    /* ���ͻ���գ����뷢��״̬ */
    if (i2c_int_status & AMHW_ZLG_INT_FLAG_TX_EMPTY) {
        amhw_zlg_i2c_intr_mask_clear(p_hw_i2c,
                                     AMHW_ZLG_INT_FLAG_TX_EMPTY);
        __i2c_mst_sm_event(p_dev, __I2C_EVT_MST_TX);
    }

    /* ��⵽ֹͣλ */
    if (i2c_int_status & AMHW_ZLG_INT_FLAG_STOP_DET) {
        amhw_zlg_i2c_intr_mask_clear(p_hw_i2c,
                                     AMHW_ZLG_INT_FLAG_STOP_DET);
        __softimer_stop(p_dev);

        if (AM_FALSE != p_dev->is_complete) {
            p_dev->is_complete = AM_FALSE;

            amhw_zlg_i2c_intr_mask_clear(p_hw_i2c, 0);
            amhw_zlg_i2c_clr_intr_get(p_hw_i2c);

            /* �ص���Ϣ��ɺ��� */
            if (p_dev->p_cur_msg->pfn_complete != NULL) {
                p_dev->p_cur_msg->pfn_complete(p_dev->p_cur_msg->p_arg);
            }
            __i2c_mst_sm_event(p_dev, __I2C_EVT_MSG_LAUNCH);
        } else {
            __i2c_re_init(p_dev);
        }
    }
}

/******************************************************************************/

static int __i2c_msg_start (void *p_drv, am_i2c_message_t *p_msg)
{
    am_zlg_i2c_dev_t *p_dev    = (am_zlg_i2c_dev_t *)p_drv;
    amhw_zlg_i2c_t   *p_hw_i2c = (amhw_zlg_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    int key;

    if ( (p_dev              == NULL) ||
         (p_msg              == NULL) ||
         (p_msg->p_transfers == NULL) ||
         (p_msg->trans_num   == 0)) {

        return -AM_EINVAL;
    }

    key = am_int_cpu_lock();

    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
    if (p_dev->busy == AM_TRUE) {

        __i2c_msg_in(p_dev, p_msg);

        am_int_cpu_unlock(key);

        return AM_OK;

    } else {
        p_dev->busy = AM_TRUE;
        __i2c_msg_in(p_dev, p_msg);
        p_msg->status = -AM_EISCONN; /* �����Ŷ��� */
        am_int_cpu_unlock(key);

        /* ��������ж� */
        amhw_zlg_i2c_intr_mask_clear(p_hw_i2c, 0xfff);

        return __i2c_mst_sm_event(p_dev, __I2C_EVT_MSG_LAUNCH);
    }
}

/**
 * \brief I2C��ʼ��
 */
am_i2c_handle_t am_zlg_i2c_init (am_zlg_i2c_dev_t           *p_dev,
                                 const am_zlg_i2c_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->i2c_serv.p_funcs = (struct am_i2c_drv_funcs *)&__g_i2c_drv_funcs;
    p_dev->i2c_serv.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    p_dev->p_cur_trans = NULL;
    p_dev->p_cur_msg   = NULL;
    p_dev->is_complete = AM_FALSE;
    p_dev->data_ptr    = 0;
    p_dev->trans_state = 0;
    p_dev->busy        = AM_FALSE;
    p_dev->state       = __I2C_ST_IDLE; /* ��ʼ��Ϊ����״̬ */
    p_dev->slave_addr  = 0;

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

    if (p_dev->p_devinfo->pfn_bus_clean) {
        p_dev->p_devinfo->pfn_bus_clean();
    }

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->i2c_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_zlg_i2c_deinit (am_i2c_handle_t handle)
{
    amhw_zlg_i2c_t   *p_hw_i2c = NULL;
    am_zlg_i2c_dev_t *p_dev    = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev    = (am_zlg_i2c_dev_t *)handle;
    p_hw_i2c = (amhw_zlg_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    p_dev->i2c_serv.p_funcs = NULL;
    p_dev->i2c_serv.p_drv   = NULL;

    amhw_zlg_i2c_disable (p_hw_i2c);

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

/**
 * \brief I2C ״̬������
 */
static int __i2c_mst_sm_event (am_zlg_i2c_dev_t *p_dev, uint32_t event)
{
    volatile uint32_t  new_event = __I2C_EVT_NONE;
    amhw_zlg_i2c_t *p_hw_i2c  = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_zlg_i2c_t *)p_dev->p_devinfo->i2c_regbase;
    
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
         * ����״̬�Ϳ�ʼ��Ϣ����״̬Ҫ�����������һ�����¼�ֻӦ�ǣ�
         * __I2C_EVT_TRANS_LAUNCH
         */
        case __I2C_ST_IDLE:
        case __I2C_ST_MSG_START:
        {
            am_i2c_message_t *p_cur_msg = NULL;

            int key;

            key = am_int_cpu_lock();
            p_cur_msg        = __i2c_msg_out(p_dev);
            p_dev->p_cur_msg = p_cur_msg;

            if (p_cur_msg) {

                p_cur_msg->status = -AM_EINPROGRESS;

            } else {

                /* �ر��ж� */
                amhw_zlg_i2c_intr_mask_clear (p_hw_i2c, 0xfff);

                p_dev->busy = AM_FALSE;
            }

            am_int_cpu_unlock(key);

            /* ����Ҫ�������Ϣ */
            if (p_cur_msg == NULL) {

                __I2C_NEXT_STATE(__I2C_ST_IDLE, __I2C_EVT_NONE);

                break;
            } else {

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
            struct am_i2c_message *p_cur_msg = p_dev->p_cur_msg;

            if (NULL == p_cur_msg) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);

                return -AM_EINVAL;
            }

            /* ��ǰ��Ϣ������� */
            if (__I2C_TRANS_EMPTY(p_dev)) {

                /* ��Ϣ���ڴ����� */
                if (p_cur_msg->status == -AM_EINPROGRESS) {
                    p_cur_msg->status = AM_OK;
                }

                p_dev->is_complete = AM_TRUE;
                amhw_zlg_i2c_con_set(p_hw_i2c, 1 << 9); /* ����һ��ֹͣ�ź� */
                __I2C_NEXT_STATE(__I2C_ST_IDLE,
                                 __I2C_EVT_NONE);

            } else {                    /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */

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
                 * 2.��ǰ���䲻��һ����Ϣ�еĵ�һ������
                 * 3.��ǰ��������һ������ķ���һ��
                 */
                if ((p_cur_trans->flags & AM_I2C_M_NOSTART) &&
                    (p_cur_trans != p_cur_msg->p_transfers) &&
                    ((p_cur_trans->flags & AM_I2C_M_RD) ==
                    ((p_cur_trans - 1)->flags & AM_I2C_M_RD))) {

                    am_bool_t is_read = (p_cur_trans->flags & AM_I2C_M_RD) ?
                                     AM_TRUE : AM_FALSE;

                    p_dev->trans_state = 1;
                    if (is_read == AM_TRUE) {

                        /* ������������ */
                        __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA,
                                         __I2C_EVT_NONE);

                        amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                                  AMHW_ZLG_INT_FLAG_RX_FULL);
                    } else {

                        /* ������������ */
                        __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA,
                                         __I2C_EVT_NONE);
                        amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                                   AMHW_ZLG_INT_FLAG_TX_EMPTY);
                    }

                /* ���ʹӻ���ַ */
                } else {
                    p_dev->trans_state = 0;

                    /* ��һ�������Ƿ��ʹӻ���ַ */
                    __I2C_NEXT_STATE(__I2C_ST_SEND_SLA_ADDR,
                                     __I2C_EVT_MST_IDLE);
                }
            }
            break;
        }

        case __I2C_ST_SEND_SLA_ADDR:         /* ���ʹӻ���ַ */
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            if ((NULL == p_cur_msg) ||(NULL == p_cur_trans)) {
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

            if (p_cur_trans->addr != p_dev->slave_addr) {
                __i2c_hard_re_init(p_dev);

                amhw_zlg_i2c_disable(p_hw_i2c);

                /* �����豸��ַ */
                amhw_zlg_i2c_tar_set(p_hw_i2c, p_cur_trans->addr);

                /* ����7bit��ַ��ʽ */
                amhw_zlg_i2c_con_clear(p_hw_i2c,
                                       AMHW_ZLG_I2C_7BITADDR_MASTER);

                amhw_zlg_i2c_enable(p_hw_i2c);
            }

            amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                       AMHW_ZLG_INT_FLAG_TX_ABRT);
            amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                       AMHW_ZLG_INT_FLAG_STOP_DET);

            /* ���������ź� + �ӻ���ַ */
            if (p_cur_trans->flags & AM_I2C_M_RD) {

                /* ��һ���ǽ������� */
                __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA, __I2C_EVT_NONE);
                if (p_cur_trans->nbytes <= 1) {

                    amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0300);
                } else {
                    amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0100);
                }
                amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                           AMHW_ZLG_INT_FLAG_RX_FULL);
            } else {

                /* ������������ģʽ */
                __I2C_NEXT_STATE(__I2C_ST_M_SEND_DATA, __I2C_EVT_NONE);
                amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                           AMHW_ZLG_INT_FLAG_TX_EMPTY);
            }

            break;
        }

        /* ��ǰ���ڽ�������״̬ */
        case __I2C_ST_M_RECV_DATA:
        {
            struct am_i2c_message  *p_cur_msg   = p_dev->p_cur_msg;
            struct am_i2c_transfer *p_cur_trans = p_dev->p_cur_trans;

            if ((NULL == p_cur_msg) ||(NULL == p_cur_trans)) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);

                return -AM_EINVAL;
            }

            if (p_dev->data_ptr < p_cur_trans->nbytes) {
                (p_cur_trans->p_buf)[p_dev->data_ptr++] = \
                                            amhw_zlg_i2c_dat_read(p_hw_i2c);
                if (p_dev->data_ptr < (p_cur_trans->nbytes - 1)){
                    amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0100);
                    amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                               AMHW_ZLG_INT_FLAG_RX_FULL);
                } else if (p_dev->data_ptr == (p_cur_trans->nbytes - 1)) {

                    amhw_zlg_i2c_dat_write(p_hw_i2c, 0x0300);
#ifdef ZML165
                    amhw_zlg_i2c_trans_abort(p_hw_i2c);
#endif
                    amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                               AMHW_ZLG_INT_FLAG_RX_FULL);
                } else {
                    __I2C_NEXT_STATE(__I2C_ST_M_RECV_DATA,
                                        __I2C_EVT_MST_RX);
                    p_hw_i2c->ic_enable |= 0x02;
                    amhw_zlg_i2c_intr_mask_clear(p_hw_i2c,
                                                 AMHW_ZLG_INT_FLAG_RX_FULL);
                }
            } else {  /* ���ݽ�����ϣ� �ô������ */

                /* ����ӻ���ַ */
                p_dev->slave_addr =p_dev->p_cur_trans->addr;

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

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

            if ((NULL == p_cur_msg) ||(NULL == p_cur_trans)) {
                __softimer_stop(p_dev);
                __i2c_re_init(p_dev);

                return -AM_EINVAL;
            }

            if (p_dev->data_ptr < p_cur_trans->nbytes) {

                if ((p_dev->data_ptr == (p_cur_trans->nbytes - 1)) &&
                     p_dev->trans_state) {

                    amhw_zlg_i2c_dat_write(p_hw_i2c,
                               (p_cur_trans->p_buf)[p_dev->data_ptr++] | 0x200);
                } else {
                    amhw_zlg_i2c_dat_write(p_hw_i2c,
                                       (p_cur_trans->p_buf)[p_dev->data_ptr++]);
                }

                amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
                                           AMHW_ZLG_INT_FLAG_TX_EMPTY);
            } else {
                amhw_zlg_i2c_intr_mask_clear(p_hw_i2c,
                                             AMHW_ZLG_INT_FLAG_TX_EMPTY);

                /* ����ӻ���ַ */
                p_dev->slave_addr =p_dev->p_cur_trans->addr;

                p_cur_msg->done_num++;
                p_dev->p_cur_trans++;

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
            return -AM_EINVAL;
        }

        /* �ڲ�û�����¼����������� */
        if (new_event == __I2C_EVT_NONE) {
            break;
        }
    }

    return AM_OK;
}

/* end of file */
