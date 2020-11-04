/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  CAN������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-31  zc, first implementation
 * - 1.01 19-12-18  add filter table extern api
 * \endinternal
 */

#include "am_int.h"
#include "am_can.h"
#include "am_zlg237_can.h"
#include "hw/amhw_zlg237_can.h"
#include "zlg237_inum.h"

/** \brief CAN���� */
am_can_err_t __can_zlg237_start (void *p_drv);
/** \brief CAN��λ��ֹͣ�� */
am_can_err_t __can_zlg237_reset (void *p_drv);
/** \brief CAN����  */
am_can_err_t __can_zlg237_sleep (void *p_drv);
/** \brief CAN���� */
am_can_err_t __can_zlg237_wakeup (void *p_drv);
/** \brief �ж�ʹ�� */
am_can_err_t __can_zlg237_int_enable (void *p_drv, am_can_int_type_t int_mask);
/** \brief �жϽ���*/
am_can_err_t __can_zlg237_int_disable (void *p_drv, am_can_int_type_t int_mask);
/** \brief ģʽ���� */
am_can_err_t __can_zlg237_mode_set (void *p_drv, am_can_mode_type_t mode);
/** \brief ���������� */
am_can_err_t __can_zlg237_baudrate_set (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief �����ʻ�ȡ */
am_can_err_t __can_zlg237_baudrate_get (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief ��ȡ������� */
am_can_err_t __can_zlg237_err_cnt_get (void         *p_drv,
                                 am_can_err_cnt_t   *p_can_err_reg);
/** \brief ������Ϣ   */
am_can_err_t __can_zlg237_msg_send (void *p_drv, am_can_message_t *p_txmsg);
/** \brief ������Ϣ   */
am_can_err_t __can_zlg237_msg_recv (void *p_drv, am_can_message_t *p_rxmsg);
/** \brief ֹͣ������Ϣ   */
am_can_err_t __can_zlg237_stop_msg_snd (void *p_drv);

/** \brief CAN ״̬ */
am_can_err_t __can_zlg237_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err);
/** \brief �ж����� */
am_can_err_t __can_zlg237_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg);
/** \brief ɾ���ж����� */
am_can_err_t __can_zlg237_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg);
/** \brief �жϻص����������� */
am_can_err_t __can_zlg237_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg);


/** \brief ɾ���жϻص����������� */
am_can_err_t __can_zlg237_intcb_disconnect (void              *p_drv,
                                            am_can_int_type_t  inttype);

/** \brief �����˲����� (��չ)*/
am_can_err_t __can_zlg237_filter_tab_ext_set (void            *p_drv,
                                              am_can_filter_t *p_filterbuff,
                                              size_t           lenth);
/** \brief ��ȡ�˲����� (��չ)*/
am_can_err_t __can_zlg237_filter_tab_ext_get (void             *p_drv,
                                              am_can_filter_t  *p_filterbuff,
                                              size_t           *p_lenth);

struct am_can_drv_funcs __zlg237_can_dev_func = {
    __can_zlg237_start,
    __can_zlg237_reset,
    __can_zlg237_sleep,
    __can_zlg237_wakeup,
    __can_zlg237_int_enable,
    __can_zlg237_int_disable,
    __can_zlg237_mode_set,
    __can_zlg237_baudrate_set,
    __can_zlg237_baudrate_get,
    __can_zlg237_err_cnt_get,
    NULL,
    __can_zlg237_msg_send,
    __can_zlg237_msg_recv,
    __can_zlg237_stop_msg_snd,
    NULL,
    NULL,
    __can_zlg237_status_get,
    __can_zlg237_connect,
    __can_zlg237_disconnect,
    __can_zlg237_intcb_connect,
    __can_zlg237_intcb_disconnect,
    __can_zlg237_filter_tab_ext_set,
    __can_zlg237_filter_tab_ext_get,
};

/**
 * \brief CAN��ʼ��
 */
uint8_t __can_zlg237_init (void *p_drv)
{
    am_zlg237_can_dev_t        *p_dev       = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t          *p_hw_can    = NULL;
    am_zlg237_can_init_info_t  *p_can_info  = NULL;
    uint8_t                     init_staus  = 0;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_can_info =(am_zlg237_can_init_info_t *)p_dev->p_devinfo->init_info;
    p_hw_can   =(amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* �˳�˯��   ��������ʼ��ģʽ */
    if (amhw_zlg237_can_operating_mode_request(
            p_hw_can, AMHW_ZLG237_CAN_OPERATING_MODE_INIT)) {

        /* ����ʱ�䴥��ͨ��ģʽ  */
        if (p_can_info->can_ttcm) {
            amhw_zlg237_can_ttcom_mode_set(p_hw_can, 1);
        } else {
            amhw_zlg237_can_ttcom_mode_set(p_hw_can, 0);
        }

        /* ��������Զ����߹���  */
        if (p_can_info->can_abom) {
            p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_ABOM;
        } else {
            p_hw_can->mcr &= (~AMHW_ZLG237_CAN_MCR_ABOM);
        }

        /* �����Զ�����ģʽ */
        if (p_can_info->can_awum) {
            p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_AWUM;
        } else {
            p_hw_can->mcr &= (~AMHW_ZLG237_CAN_MCR_AWUM);
        }

        /* ���� ��ֹ�����Զ��ش�  */
        if (p_can_info->can_nart) {
            p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_NART;
        } else {
            p_hw_can->mcr &= (~AMHW_ZLG237_CAN_MCR_NART);
        }

        /* ���� ����FIFO����ģʽ */
        if (p_can_info->can_rflm) {
            p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_RFLM;
        } else {
            p_hw_can->mcr &= (~AMHW_ZLG237_CAN_MCR_RFLM);
        }

        /* ���� ����FIFP���ȼ� */
        if (p_can_info->can_txfp) {
            p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_TXFP;
        } else {
            p_hw_can->mcr &= (~AMHW_ZLG237_CAN_MCR_TXFP);
        }


        p_hw_can->btr |= (uint32_t)(((uint32_t) p_can_info->can_mode << 30));

        /* ������ѹҺű�־λ  */
        p_hw_can->msr |= (uint32_t)0x08;

        /* ��������ģʽ */
        if (amhw_zlg237_can_operating_mode_request(
                    p_hw_can, AMHW_ZLG237_CAN_OPERATING_NORMAL)) {
            init_staus = 1;
        } else {
            init_staus = 0;
        }

    } else {
        init_staus = 0;
    }

    return init_staus;
}


/**
 * \brief CAN����
 */
am_can_err_t __can_zlg237_start (void *p_drv)
{

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* ��ʼ��CAN������Ϣ */
    __can_zlg237_init(p_drv);

    /* ʹ���ж� */
    am_int_enable(INUM_USB_HP_CAN_TX);
    am_int_enable(INUM_USB_HP_CAN_RX);
    am_int_enable(INUM_CAN1_RX1);
    am_int_enable(INUM_CAN1_SCE);

    return AM_CAN_NOERROR;
}

/**
 * \brief CAN��λ��ֹͣ��
 */
am_can_err_t __can_zlg237_reset (void *p_drv)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* ��CANǿ�Ƹ�λ  ��λ��CAN����˯��ģʽ */
    p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_RESET;


    /* �����ж� */
    am_int_disable(INUM_USB_HP_CAN_TX);
    am_int_disable(INUM_USB_HP_CAN_RX);
    am_int_disable(INUM_CAN1_RX1);
    am_int_disable(INUM_CAN1_SCE);

    return AM_CAN_NOERROR;
}

/**
 * \brief CAN����
 */
am_can_err_t __can_zlg237_sleep (void *p_drv)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* �л���˯��ģʽ*/
    amhw_zlg237_can_operating_mode_request(
            p_hw_can, AMHW_ZLG237_CAN_OPERATING_SLEEP);

    return AM_CAN_NOERROR;
}

/**
 * \brief CAN����
 */
am_can_err_t __can_zlg237_wakeup (void *p_drv)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* �л���˯��ģʽ*/
    amhw_zlg237_can_operating_mode_request(
            p_hw_can, AMHW_ZLG237_CAN_OPERATING_NORMAL);

    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�ʹ��
 */
am_can_err_t __can_zlg237_int_enable (void *p_drv, am_can_int_type_t int_mask)
{
    am_zlg237_can_dev_t             *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t               *p_hw_can = NULL;
    amhw_zlg237_can_mode_t           mode     = p_dev->mode;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* �����ж� */
    if (int_mask & AM_CAN_INT_RX) {

        /* ʹ�� FIFO 0 1 ��Ϣ�Һ��ж�ʹ�� */
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FMPIE0, 1);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FMPIE1, 1);

        int_mask &= ~AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_TX) {

        /* ����������ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_TMEIE, 1);

        int_mask &= ~AM_CAN_INT_TX;
    }

    /* ����\�����ж�  */
    if ((int_mask & AM_CAN_INT_ERROR)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 1);

        int_mask &= ~AM_CAN_INT_ERROR;
    }

    /* �����ж�  */
    if ((int_mask & AM_CAN_INT_WARN)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 1);

        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_EWGIE, 1);

        int_mask &= ~AM_CAN_INT_WARN;
    }

    /* ���󱻶��ж�  */
    if ((int_mask & AM_CAN_INT_ERROR_PASSIVE)) {

        /* ���󱻶� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 1);

        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_EPVIE, 1);


        int_mask &= ~AM_CAN_INT_ERROR_PASSIVE;
    }

    /* ���߹ر��ж�  */
    if ((int_mask & AM_CAN_INT_BUS_OFF)) {

        /* �����ж� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 1);

        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_BOFIE, 1);

        int_mask &= ~AM_CAN_INT_BUS_OFF;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_WAKE_UP) {

        /* ʹ�ܻ����ж� */
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_WKUIE, 1);

        int_mask &= ~AM_CAN_INT_WAKE_UP;
    }

    /* ���߳����ж� */
    if (int_mask & AM_CAN_INT_DATAOVER) {

        /* ʹ����������ж�  FIFO 0 1 */
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FOVIE0, 1);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FOVIE1, 1);

        int_mask &= ~AM_CAN_INT_DATAOVER;
    }

    /* �ָ�CAN״̬ */
    if (mode != AMHW_ZLG237_CAN_OPERATING_MODE_INIT) {

        amhw_zlg237_can_operating_mode_request(p_hw_can, mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϽ���
 */
am_can_err_t __can_zlg237_int_disable (void *p_drv, am_can_int_type_t int_mask)
{
    am_zlg237_can_dev_t         *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t           *p_hw_can = NULL;
    amhw_zlg237_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;


    /* �����ж� */
    if (int_mask & AM_CAN_INT_RX) {

        /* ʹ�� FIFO 0 1 ��Ϣ�Һ��ж�ʹ�� */
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FMPIE0, 0);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FMPIE1, 0);

        int_mask &= ~AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_TX) {

        /* ����������ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_TMEIE, 0);

        int_mask &= ~AM_CAN_INT_TX;
    }

    /* ����\�����ж�  */
    if ((int_mask & AM_CAN_INT_ERROR)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 0);

        int_mask &= ~AM_CAN_INT_ERROR;
    }

    /* �����ж�  */
    if ((int_mask & AM_CAN_INT_WARN)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 0);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_EWGIE, 0);

        int_mask &= ~AM_CAN_INT_WARN;
    }

    /* ���󱻶��ж�  */
    if ((int_mask & AM_CAN_INT_ERROR_PASSIVE)) {

        /* ���󱻶� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 0);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_EPVIE, 0);

        int_mask &= ~AM_CAN_INT_ERROR_PASSIVE;
    }

    /* ���߹ر��ж�  */
    if ((int_mask & AM_CAN_INT_BUS_OFF)) {

        /* �����ж� �� �����ж�ʹ��*/
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_ERRIE, 0);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_BOFIE, 0);

        int_mask &= ~AM_CAN_INT_BUS_OFF;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_WAKE_UP) {
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_WKUIE, 0);

        int_mask &= ~AM_CAN_INT_WAKE_UP;
    }

    /* ���߳����ж� */
    if (int_mask & AM_CAN_INT_DATAOVER) {
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FOVIE0, 0);
        amhw_zlg237_can_itconfig(p_hw_can,
                AMHW_ZLG237_CAN_INT_FOVIE1, 0);

        int_mask &= ~AM_CAN_INT_DATAOVER;
    }
    /* �ָ�CAN״̬ */
    if (mode != AMHW_ZLG237_CAN_OPERATING_MODE_INIT) {

        amhw_zlg237_can_operating_mode_request(p_hw_can, mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ģʽ����
 */
am_can_err_t __can_zlg237_mode_set (void *p_drv, am_can_mode_type_t mode)
{
    am_zlg237_can_dev_t *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t   *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    if (AM_CAN_MODE_NROMAL == mode ) {

        /* ����ģʽ */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                AMHW_ZLG237_CAN_OPERATING_NORMAL);
    } else if (AM_CAN_MODE_LISTEN_ONLY == mode) {

        /* ��Ĭģʽ*/
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                AMHW_ZLG237_CAN_MODE_SILENT);
    } else {
        /* �ػ� �� �ػ���Ĭδ���� */

        return AM_CAN_INVALID_PARAMETER;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ����������
 */
am_can_err_t __can_zlg237_baudrate_set (void           *p_drv,
                                 am_can_bps_param_t    *p_can_baudrate)
{
    am_zlg237_can_dev_t         *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t           *p_hw_can = NULL;
    amhw_zlg237_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    if (AMHW_ZLG237_CAN_OPERATING_MODE_INIT != p_dev->mode) {

        /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                AMHW_ZLG237_CAN_OPERATING_MODE_INIT);
    }

    /* ���� �����ʷ�Ƶ��   ͬ����ת���   ����λ�� */
    amhw_zlg237_can_brp_set(p_hw_can, p_can_baudrate->brp);
    amhw_zlg237_can_sjw_set(p_hw_can, p_can_baudrate->sjw);

    amhw_zlg237_can_tseg1_set(p_hw_can, p_can_baudrate->tesg1);
    amhw_zlg237_can_tseg2_set(p_hw_can, p_can_baudrate->tesg2);

    if (mode != AMHW_ZLG237_CAN_OPERATING_MODE_INIT) {

        /* �л�������ģʽ */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �����ʻ�ȡ
 */
am_can_err_t __can_zlg237_baudrate_get (void           *p_drv,
                                 am_can_bps_param_t    *p_can_baudrate)
{
    am_zlg237_can_dev_t         *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t           *p_hw_can = NULL;
    amhw_zlg237_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    if (AMHW_ZLG237_CAN_OPERATING_MODE_INIT != p_dev->mode) {
        /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                AMHW_ZLG237_CAN_OPERATING_MODE_INIT);
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    p_can_baudrate->brp = amhw_zlg237_can_brp_get(p_hw_can);
    p_can_baudrate->sjw = amhw_zlg237_can_sjw_get(p_hw_can);

    p_can_baudrate->tesg1 = amhw_zlg237_can_tseg1_get(p_hw_can);
    p_can_baudrate->tesg2 = amhw_zlg237_can_tseg2_get(p_hw_can);


    if (mode != AMHW_ZLG237_CAN_OPERATING_MODE_INIT) {

        /* �л�������ģʽ */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�������
 */
am_can_err_t __can_zlg237_err_cnt_get (void        *p_drv,
                               am_can_err_cnt_t    *p_can_err_reg)
{
    am_zlg237_can_dev_t *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t   *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_can_err_reg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* �� TX/RX��������� */
    p_can_err_reg->rx_error_cnt = amhw_zlg237_can_get_recverrorcount(p_hw_can);
    p_can_err_reg->tx_error_cnt = amhw_zlg237_can_get_transerrorcount(p_hw_can);

    return AM_CAN_NOERROR;
}


/**
 * \brief ������Ϣ
 */
am_can_err_t __can_zlg237_msg_send (void *p_drv, am_can_message_t *p_txmsg)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can = NULL;
    am_bool_t               is_remote = AM_FALSE;
    am_bool_t               is_extern = AM_FALSE;

    uint8_t transmit_mailbox = 0;

    if (NULL == p_drv || NULL == p_txmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;


    if ((p_hw_can->tsr & AMHW_ZLG237_CAN_TSR_TME0) ==
                         AMHW_ZLG237_CAN_TSR_TME0) {

        transmit_mailbox = 0;
    } else if ((p_hw_can->tsr & AMHW_ZLG237_CAN_TSR_TME1) ==
                                AMHW_ZLG237_CAN_TSR_TME1) {
        transmit_mailbox = 1;
    } else if ((p_hw_can->tsr & AMHW_ZLG237_CAN_TSR_TME2) ==
                                AMHW_ZLG237_CAN_TSR_TME2) {
        transmit_mailbox = 2;
    } else {

        /* �������䲻Ϊ��  */
        transmit_mailbox = ZLG237_CAN_TX_STATUS_NOMAILBOX;
    }

    is_remote = ((p_txmsg->flags & AM_CAN_REMOTE_FLAG) ? AM_TRUE : AM_FALSE);
    is_extern = ((p_txmsg->flags & AM_CAN_EXTERN_FLAG) ? AM_TRUE : AM_FALSE);

    /* zlg237 can û��can fd���� */
    if (p_txmsg->flags & AM_CAN_FD_CTRL_FLAG) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* 8�ֽ����� */
     if (p_txmsg->msglen > 8) {
         p_txmsg->msglen = 8;
     }

    if (transmit_mailbox != ZLG237_CAN_TX_STATUS_NOMAILBOX) {

        /* ��ռĴ���*/
        p_hw_can->tx_mail[transmit_mailbox].tir &= AMHW_ZLG237_CAN_TIR_TXRQ;

        /* ��չ��ʶ�� */
        if (is_extern) {

            /* ������չ��ʶ��ID �� IDEλ */
            p_hw_can->tx_mail[transmit_mailbox].tir |= ((p_txmsg->id << 3)|
                                                        (uint32_t)0x4);
        } else {

            /* ���ñ�׼��ʶ��ID �� IDEλ */
            p_hw_can->tx_mail[transmit_mailbox].tir |= (p_txmsg->id << 21);
            p_hw_can->tx_mail[transmit_mailbox].tir &= (~(uint32_t)0x04);
        }

        /* Զ�̱�־ */
        if (is_remote) {
            /* Զ��֡ */
            p_hw_can->tx_mail[transmit_mailbox].tir |= (uint32_t)0x02;
        } else {
            /* ����֡ */
            p_hw_can->tx_mail[transmit_mailbox].tir &= (~(uint32_t)0x02);
        }

        /* ���� ���ݳ���*/
        p_hw_can->tx_mail[transmit_mailbox].tdtr &= (uint32_t)0xfffffff0;
        p_hw_can->tx_mail[transmit_mailbox].tdtr |= p_txmsg->msglen ;

            p_hw_can->tx_mail[transmit_mailbox].tdlr =
                    (((uint32_t)p_txmsg->msgdata[3] << 24) |
                     ((uint32_t)p_txmsg->msgdata[2] << 16) |
                     ((uint32_t)p_txmsg->msgdata[1] << 8)  |
                     ((uint32_t)p_txmsg->msgdata[0]));

            p_hw_can->tx_mail[transmit_mailbox].tdhr =
                    (((uint32_t)p_txmsg->msgdata[7] << 24) |
                     ((uint32_t)p_txmsg->msgdata[6] << 16) |
                     ((uint32_t)p_txmsg->msgdata[5] << 8)  |
                     ((uint32_t)p_txmsg->msgdata[4]));

        /* ������ */
        p_hw_can->tx_mail[transmit_mailbox].tir |= AMHW_ZLG237_CAN_TIR_TXRQ;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ������Ϣ
 */
am_can_err_t __can_zlg237_msg_recv (void *p_drv, am_can_message_t *p_rxmsg)
{
    am_zlg237_can_dev_t       *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_filter_t  *p_filter = NULL;
    amhw_zlg237_can_t         *p_hw_can = NULL;
    uint8_t         rx_mailbox = 0;

    if (NULL == p_drv || NULL == p_rxmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_filter= (amhw_zlg237_can_filter_t *)p_dev->p_devinfo->filter;
    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    /* ��ʼ�� */
    p_rxmsg->id     = 0;
    p_rxmsg->flags  = 0;
    p_rxmsg->msglen = 0;

    /* �жϽ��ջ������Ƿ�Ϊ�� */
    if (p_filter->can_fliter_fifo  == AMHW_ZLG237_CAN_FILTER_FIFO0 ) {
        if ((p_hw_can->rf_0r & (uint32_t)0x3)) {
            rx_mailbox = 0;
        } else {
            return AM_CAN_NOERROR;
        }
    } else if (p_filter->can_fliter_fifo  == AMHW_ZLG237_CAN_FILTER_FIFO1) {
        if ((p_hw_can->rf_1r & (uint32_t)0x3)) {
            rx_mailbox = 1;
        } else {
            return AM_CAN_NOERROR;
        }
    }

    if (p_hw_can->rx_mail[rx_mailbox].rir & (uint8_t)0x04 ) {

        /* ʹ����չ��ʶ��  */
        p_rxmsg->flags |= AM_CAN_EXTERN_FLAG;

        /* ��ȡID */
        p_rxmsg->id     = p_hw_can->rx_mail[rx_mailbox].rir >> 3;

    } else {
        /* ʹ�ñ�׼��ʶ��  */

        /* ��ȡID */
        p_rxmsg->id     = p_hw_can->rx_mail[rx_mailbox].rir >> 21;
    }

    /* Զ��֡���� */
    if (p_hw_can->rx_mail[rx_mailbox].rir & 0x02) {

        /* Զ��֡ */
        p_rxmsg->flags |= AM_CAN_REMOTE_FLAG;
        p_rxmsg->msglen = 0;
    }

        /* ��ȡ�������ݳ���*/
    p_rxmsg->msglen = (uint8_t)0x0f &
                       p_hw_can->rx_mail[rx_mailbox].rdtr;



    /* ��ȡ������ƥ����� */
    p_dev->fmi = (uint8_t)0xff & (p_hw_can->rx_mail[rx_mailbox].rdtr >> 8);

        /* ��ȡ���� */
        p_rxmsg->msgdata[0] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdlr);
        p_rxmsg->msgdata[1] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdlr >> 8);
        p_rxmsg->msgdata[2] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdlr >> 16);
        p_rxmsg->msgdata[3] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdlr >> 24);

        p_rxmsg->msgdata[4] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdhr);
        p_rxmsg->msgdata[5] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdhr >> 8);
        p_rxmsg->msgdata[6] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdhr >> 16);
        p_rxmsg->msgdata[7] = (uint8_t)0xff &
                              (p_hw_can->rx_mail[rx_mailbox].rdhr >> 24);

    /* �ͷ�FIFO  */
    /* �ͷ�FIFO 0 */
    if (rx_mailbox == 0) {
        p_hw_can->rf_0r |= AMHW_ZLG237_CAN_RF0R_RFOM0;
    } else {
    /* �ͷ�FIFO 1 */
        p_hw_can->rf_1r |= AMHW_ZLG237_CAN_RF1R_RFOM1;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ֹͣ������Ϣ
 */
am_can_err_t __can_zlg237_stop_msg_snd (void *p_drv)
{
    am_zlg237_can_dev_t    *p_dev            = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can         = NULL;
    uint8_t                 transmit_mailbox = 0;
    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    if ((p_hw_can->tsr & AMHW_ZLG237_CAN_TSR_TME0) !=
                         AMHW_ZLG237_CAN_TSR_TME0) {

        transmit_mailbox = 0;
    } else if ((p_hw_can->tsr & AMHW_ZLG237_CAN_TSR_TME1) !=
                                AMHW_ZLG237_CAN_TSR_TME1) {
        transmit_mailbox = 1;
    } else if ((p_hw_can->tsr & AMHW_ZLG237_CAN_TSR_TME2) !=
                                AMHW_ZLG237_CAN_TSR_TME2) {
        transmit_mailbox = 2;
    } else {
        /* ��������Ϊ��  */
        return AM_CAN_INVALID_PARAMETER;
    }

    switch (transmit_mailbox) {

    case (0):
        p_hw_can->tsr |= AMHW_ZLG237_CAN_TSR_ABRQ0;
        break;

    case (1):
        p_hw_can->tsr |= AMHW_ZLG237_CAN_TSR_ABRQ1;
        break;

    case (2):
        p_hw_can->tsr |= AMHW_ZLG237_CAN_TSR_ABRQ2;
        break;

    default:
        break;
    }

    return AM_CAN_NOERROR;
}

am_can_err_t __can_zlg237_filter_32bit_idmask(uint32_t         *reg_1,
                                              uint32_t         *reg_2,
                                              am_can_filter_t  *p_filterbuff)
{
    uint32_t reg_f_r1 = 0;
    uint32_t reg_f_r2 = 0;

    uint8_t  state = AM_CAN_NOERROR;
    if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_DATA ) {
        /* ����֡ */
        reg_f_r1 &= (~(uint32_t)(1 << 1));
        reg_f_r2 |= ( (uint32_t)(1 << 1));
    } else if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_REMOTE) {
        /* Զ��֡ */
        reg_f_r1 |= ((uint32_t)(1 << 1));
        reg_f_r2 |= ((uint32_t)(1 << 1));
    } else if(p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_NOCARE) {
        /* �����Խ��� */
        reg_f_r2 &= (~(uint32_t)(1 << 1));
    } else {
        /* �޴�ѡ�� */
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_STD) {
        /* ֻ���ձ�׼֡ */
        reg_f_r1 &= (~(uint32_t)(1 << 2));
        reg_f_r2 |= ( (uint32_t)(1 << 2));

        /* ��׼ID STID[10:0] */
        if ((p_filterbuff->id[0] >0x7ff) || (p_filterbuff->mask[0] >0x7ff) ) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1 |= ((uint32_t)p_filterbuff->id[0] << 21);
        reg_f_r2 |= ((uint32_t)p_filterbuff->mask[0] << 21);
    } else if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
        /* ֻ������չ֡ */
        reg_f_r1 |= ((uint32_t)(1 << 2));
        reg_f_r2 |= ((uint32_t)(1 << 2));

        /* EXID[28:0] */
        if ((p_filterbuff->id[0] > 0x1fffffff) ||
            (p_filterbuff->mask[0] > 0x1fffffff)) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1 |= ((uint32_t)p_filterbuff->id[0] << 3);
        reg_f_r2 |= ((uint32_t)p_filterbuff->mask[0] << 3);
    } else {
        /* �޴�ѡ�� */
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    *reg_1 = reg_f_r1;
    *reg_2 = reg_f_r2;

    return state;
}

am_can_err_t __can_zlg237_filter_32bit_idlist(uint32_t        *reg_1,
                                              uint32_t        *reg_2,
                                              am_can_filter_t *p_filterbuff)
{
    uint32_t reg_f_r1 = 0;
    uint32_t reg_f_r2 = 0;
    uint8_t  state    = AM_CAN_NOERROR;

    if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_DATA ) {
        /* ����֡ */
        reg_f_r1 &= (~(uint32_t)(1 << 1));
        reg_f_r2 &= (~(uint32_t)(1 << 1));
    } else if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_REMOTE) {
        /* Զ��֡ */
        reg_f_r1 |= ((uint32_t)(1 << 1));
        reg_f_r2 |= ((uint32_t)(1 << 1));
    } else {
        /* �б�ģʽ�� ���ز������� */
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_STD) {
        /* ֻ���ձ�׼֡ */
        reg_f_r1 &= (~(uint32_t)(1 << 2));
        reg_f_r2 &= (~(uint32_t)(1 << 2));

        /* ��׼ID STID[10:0] */
        if ((p_filterbuff->id[0] >0x7ff) || (p_filterbuff->id[1] > 0x7ff)) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1 |= ((uint32_t)p_filterbuff->id[0] << 21);
        reg_f_r2 |= ((uint32_t)p_filterbuff->id[1] << 21);
    } else if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
        /* ֻ������չ֡ */
        reg_f_r1 |= ((uint32_t)(1 << 2));
        reg_f_r2 |= ((uint32_t)(1 << 2));

        /* EXID[28:0] */
        if ((p_filterbuff->id[0] > 0x1fffffff) ||
            (p_filterbuff->id[1] > 0x1fffffff) ) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1 |= ((uint32_t)p_filterbuff->id[0] << 3);
        reg_f_r2 |= ((uint32_t)p_filterbuff->id[1] << 3);
    } else {
        /* �޴�ѡ�� */
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    *reg_1 = reg_f_r1;
    *reg_2 = reg_f_r2;

    return state;
}

am_can_err_t __can_zlg237_filter_16bit_idmask(uint32_t        *reg_1,
                                              uint32_t        *reg_2,
                                              am_can_filter_t *p_filterbuff)
{
    uint16_t reg_f_r1_h = 0;
    uint16_t reg_f_r1_l = 0;
    uint16_t reg_f_r2_h = 0;
    uint16_t reg_f_r2_l = 0;
    uint16_t state      = AM_CAN_NOERROR;

    if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_DATA ) {
        /* ����֡ */
        reg_f_r1_h &= (~(uint16_t)(1 << 4));
        reg_f_r1_l |= ((uint16_t)(1 << 4)); /* mask */
        reg_f_r2_h &= (~(uint16_t)(1 << 4));
        reg_f_r2_l |= ((uint16_t)(1 << 4)); /* mask */
    } else if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_REMOTE) {
        /* Զ��֡ */
        reg_f_r1_h |= ((uint16_t)(1 << 4));
        reg_f_r1_l |= ((uint16_t)(1 << 4));
        reg_f_r2_h |= ((uint16_t)(1 << 4));
        reg_f_r2_l |= ((uint16_t)(1 << 4));
    } else if(p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_NOCARE) {
        /* �����Խ��� */
        reg_f_r1_l &= (~(uint16_t)(1 << 4));
        reg_f_r2_l &= (~(uint16_t)(1 << 4));
    } else {
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_STD) {
        /* ֻ���ձ�׼֡ */
        reg_f_r1_h &= (~(uint16_t)(1 << 3));
        reg_f_r1_l |= ((uint16_t)(1 << 3));
        reg_f_r2_h &= (~(uint16_t)(1 << 3));
        reg_f_r2_l |= ((uint16_t)(1 << 3));

        if ((p_filterbuff->id[0] >0x7ff)   ||
            (p_filterbuff->mask[0] >0x7ff) ||
            (p_filterbuff->id[1] >0x7ff)   ||
            (p_filterbuff->mask[1] >0x7ff)) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1_h |= (p_filterbuff->id[0] & 0x7ff) << 5;
        reg_f_r1_l |= (p_filterbuff->mask[0] & 0x7ff) << 5;
        reg_f_r2_h |= (p_filterbuff->id[1] & 0x7ff) << 5;
        reg_f_r2_l |= (p_filterbuff->mask[1] & 0x7ff) << 5;
    } else if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
        /* ֻ������չ֡ */
        reg_f_r1_h |= ((uint16_t)(1 << 3));
        reg_f_r1_l |= ((uint16_t)(1 << 3));
        reg_f_r2_h |= ((uint16_t)(1 << 3));
        reg_f_r2_l |= ((uint16_t)(1 << 3));

        if ((p_filterbuff->id[0] > 0x3ffff)   ||
            (p_filterbuff->mask[0] > 0x3ffff) ||
            (p_filterbuff->id[1] > 0x3ffff)   ||
            (p_filterbuff->mask[1] > 0x3ffff)) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1_h |= (p_filterbuff->id[0] >> 15) |
                     ((p_filterbuff->id[0] & 0x7ff) << 5);
        reg_f_r1_l |= (p_filterbuff->mask[0] >> 15) |
                     ((p_filterbuff->mask[0] & 0x7ff) << 5);
        reg_f_r2_h |= (p_filterbuff->id[1] >> 15) |
                     ((p_filterbuff->id[1] & 0x7ff) << 5);
        reg_f_r2_l |= (p_filterbuff->mask[1] >> 15) |
                     ((p_filterbuff->mask[1] & 0x7ff) << 5);
    } else {
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    *reg_1 = ((uint32_t)reg_f_r1_h <<16) |
            ((uint32_t)reg_f_r1_l);
    *reg_2 = ((uint32_t)reg_f_r2_h <<16) |
            ((uint32_t)reg_f_r2_l);

    return state;
}

am_can_err_t __can_zlg237_filter_16bit_idlist(uint32_t        *reg_1,
                                              uint32_t        *reg_2,
                                              am_can_filter_t *p_filterbuff)
{
    uint16_t reg_f_r1_h = 0;
    uint16_t reg_f_r1_l = 0;
    uint16_t reg_f_r2_h = 0;
    uint16_t reg_f_r2_l = 0;
    uint8_t  state      = AM_CAN_NOERROR;

    if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_DATA ) {
        /* ����֡ */
        reg_f_r1_h &= (~(uint16_t)(1 << 4));
        reg_f_r1_l &= (~(uint16_t)(1 << 4));
        reg_f_r2_h &= (~(uint16_t)(1 << 4));
        reg_f_r2_l &= (~(uint16_t)(1 << 4));
    } else if (p_filterbuff->rtr == AM_CAN_FRAME_FORMAT_REMOTE) {
        /* Զ��֡ */
        reg_f_r1_h |= ((uint16_t)(1 << 4));
        reg_f_r1_l |= ((uint16_t)(1 << 4));
        reg_f_r2_h |= ((uint16_t)(1 << 4));
        reg_f_r2_l |= ((uint16_t)(1 << 4));
    } else {
        /* �б�ģʽ�� ���ز������� */
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_STD) {
        /* ֻ���ձ�׼֡ */
        reg_f_r1_h &= (~(uint16_t)(1 << 3));
        reg_f_r1_l &= (~(uint16_t)(1 << 3));
        reg_f_r2_h &= (~(uint16_t)(1 << 3));
        reg_f_r2_l &= (~(uint16_t)(1 << 3));
        if ((p_filterbuff->id[0] > 0x7ff) ||
            (p_filterbuff->id[1] > 0x7ff) ||
            (p_filterbuff->id[2] > 0x7ff) ||
            (p_filterbuff->id[3] > 0x7ff) ) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }
        reg_f_r1_h |= (p_filterbuff->id[0] & 0x7ff) << 5;
        reg_f_r1_l |= (p_filterbuff->id[1] & 0x7ff) << 5;
        reg_f_r2_h |= (p_filterbuff->id[2] & 0x7ff) << 5;
        reg_f_r2_l |= (p_filterbuff->id[3] & 0x7ff) << 5;

    } else if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
        /* ֻ������չ֡ */
        reg_f_r1_h |= ((uint16_t)(1 << 3));
        reg_f_r1_l |= ((uint16_t)(1 << 3));
        reg_f_r2_h |= ((uint16_t)(1 << 3));
        reg_f_r2_l |= ((uint16_t)(1 << 3));

        if ((p_filterbuff->id[0] > 0x3ffff) ||
            (p_filterbuff->id[1] > 0x3ffff) ||
            (p_filterbuff->id[2] > 0x3ffff) ||
            (p_filterbuff->id[3] > 0x3ffff) ) {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }

        reg_f_r1_h |= ((p_filterbuff->id[0] & 0x7ff) << 5) |
                       (p_filterbuff->id[0] >> 15);
        reg_f_r1_l |= ((p_filterbuff->id[1] & 0x7ff) << 5) |
                       (p_filterbuff->id[1] >> 15);
        reg_f_r2_h |= ((p_filterbuff->id[2] & 0x7ff) << 5) |
                       (p_filterbuff->id[2] >> 15);
        reg_f_r2_l |= ((p_filterbuff->id[3] & 0x7ff) << 5) |
                       (p_filterbuff->id[3] >> 15);
    } else {
        state = AM_CAN_INVALID_PARAMETER;
        return state;
    }

    *reg_1 = ((uint32_t)reg_f_r1_h <<16) |
            ((uint32_t)reg_f_r1_l);
    *reg_2 = ((uint32_t)reg_f_r2_h <<16) |
            ((uint32_t)reg_f_r2_l);
    return state;
}

/**
 * \brief �����˲�����(��չ)
 */
am_can_err_t __can_zlg237_filter_tab_ext_set (void              *p_drv,
                                              am_can_filter_t   *p_filterbuff,
                                              size_t             lenth)
{
    am_zlg237_can_dev_t         *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_filter_t    *p_filter = NULL;
    amhw_zlg237_can_t           *p_hw_can = NULL;
    uint8_t                      filt_num = 0;
    uint32_t                     filt_pos = 0;
    amhw_zlg237_can_mode_t       mode     = p_dev->mode;
    am_can_err_t                 state    = AM_CAN_NOERROR;

    if (NULL == p_drv || NULL == p_filterbuff || 0 == lenth || (lenth > 14)) {
        return AM_CAN_INVALID_PARAMETER;
    }



    p_filter= (amhw_zlg237_can_filter_t *)p_dev->p_devinfo->filter;
    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    if (AMHW_ZLG237_CAN_OPERATING_MODE_INIT != p_dev->mode) {
        /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                AMHW_ZLG237_CAN_OPERATING_MODE_INIT);
    }


    /* �˲����������˲�����ʼ��ģʽ  */
    p_hw_can->fmr |= (uint32_t)0x01;
    for (int i = 0; i < lenth; i++) {

        /* �˲������  */
        filt_num = i;

        if (filt_num > 13 ) {
            /* ������ǰ */
            state = AM_CAN_ILLEGAL_CHANNEL_NO;
            break;
        } else {
            /* �˲����� */
            filt_pos = (uint32_t)(1ul << filt_num);
        }

        /* �����˲���  */
        p_hw_can->fa_1r &= ~(uint32_t)filt_pos;

        if (p_filter->can_filter_mode) {

            /* ��ʶ���б� */
            p_hw_can->fm_1r |= (uint32_t)filt_pos;
            if (p_filter->can_filter_scale) {
                uint32_t reg_f_r1 = 0;
                uint32_t reg_f_r2 = 0;

                reg_f_r1 = p_hw_can->fi_rx[filt_num].f_r1;
                reg_f_r2 = p_hw_can->fi_rx[filt_num].f_r2;
                /* 32λ */
                p_hw_can->fs_1r |= (uint32_t)filt_pos;
                state = __can_zlg237_filter_32bit_idlist(&reg_f_r1,
                                                         &reg_f_r2,
                                                          p_filterbuff);
                if (state != AM_CAN_NOERROR) {
                    return state;
                } else {
                    p_hw_can->fi_rx[filt_num].f_r1 = reg_f_r1;
                    p_hw_can->fi_rx[filt_num].f_r2 = reg_f_r2;
                }


            } else {

                /* 16λ */
                p_hw_can->fs_1r &= ~(uint32_t)filt_pos;

                uint32_t reg_f_r1 = 0;
                uint32_t reg_f_r2 = 0;

                reg_f_r1 = p_hw_can->fi_rx[filt_num].f_r1;
                reg_f_r2 = p_hw_can->fi_rx[filt_num].f_r2;

                state = __can_zlg237_filter_16bit_idlist(&reg_f_r1,
                                                         &reg_f_r2,
                                                          p_filterbuff);

                if (state != AM_CAN_NOERROR) {
                    return state;
                } else {
                    p_hw_can->fi_rx[filt_num].f_r1 = reg_f_r1;
                    p_hw_can->fi_rx[filt_num].f_r2 = reg_f_r2;
                }
            }
        } else {

            /* ��ʶ������λ */
            p_hw_can->fm_1r &= ~(uint32_t)filt_pos;

            if (p_filter->can_filter_scale) {

                /* 32λ */
                p_hw_can->fs_1r |= (uint32_t)filt_pos;

                uint32_t reg_f_r1 = 0;
                uint32_t reg_f_r2 = 0;

                reg_f_r1 = p_hw_can->fi_rx[filt_num].f_r1;
                reg_f_r2 = p_hw_can->fi_rx[filt_num].f_r2;

                state = __can_zlg237_filter_32bit_idmask(
                                                 &reg_f_r1,
                                                 &reg_f_r2,
                                                 p_filterbuff);
                if (state != AM_CAN_NOERROR) {
                    return state;
                } else {
                    p_hw_can->fi_rx[filt_num].f_r1 = reg_f_r1;
                    p_hw_can->fi_rx[filt_num].f_r2 = reg_f_r2;
                }
            } else {

                /* 16λ */
                p_hw_can->fs_1r &= ~(uint32_t)filt_pos;

                uint32_t reg_f_r1 = 0;
                uint32_t reg_f_r2 = 0;

                state = __can_zlg237_filter_16bit_idmask(
                            &reg_f_r1,
                            &reg_f_r2,
                            p_filterbuff);

                if (state != AM_CAN_NOERROR) {
                    return state;
                } else {
                    p_hw_can->fi_rx[filt_num].f_r1 = reg_f_r1;
                    p_hw_can->fi_rx[filt_num].f_r2 = reg_f_r2;
                }

            }
        }

        /* �˲���FIFO����  */
        if (p_filter->can_fliter_fifo == AMHW_ZLG237_CAN_FILTER_FIFO0) {

            /* ������FIFO 0  */
            p_hw_can->ffa_1r &= ~(uint32_t)filt_pos;
        }

        if (p_filter->can_fliter_fifo == AMHW_ZLG237_CAN_FILTER_FIFO1) {

            /* ������FIFO 1  */
            p_hw_can->ffa_1r |= (uint32_t)filt_pos;
        }

        /* �����˲���  */
        if (p_filter->filter_state == 1) {

            p_hw_can->fa_1r |= (uint32_t)filt_pos;
        }

        /* �˲�������� */
        p_filterbuff++;
    }

    /* �˲�����ص�����ģʽ */
    p_hw_can->fmr &= ~0x01;

    if (mode != AMHW_ZLG237_CAN_OPERATING_MODE_INIT) {

        /* �л�������ģʽ */
        amhw_zlg237_can_operating_mode_request(p_hw_can,
                mode);
    }

    return state;

}


/**
 * \brief ��ȡ�˲�����
 */
am_can_err_t __can_zlg237_filter_tab_ext_get (void              *p_drv,
                                              am_can_filter_t   *p_filterbuff,
                                              size_t            *p_lenth)
{
    am_zlg237_can_dev_t         *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t           *p_hw_can = NULL;
    uint32_t                     filter_group = 0;

    /* 1 list  0 mask */
    uint8_t                      filter_mode = 0;

    /* 1 32  0 16 */
    uint8_t                      filter_scale = 0;
    if (NULL == p_drv ) {
        return AM_CAN_INVALID_PARAMETER;
    }


    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    filter_group = p_hw_can->fa_1r & 0x3fff;

    for (int i = 0;i < 14;i++) {

        /* �жϵ�ǰ�˲������Ƿ񼤻� */
        if ( ( filter_group & ( (uint32_t)1ul<< i) ) ) {
            *p_lenth = *p_lenth + 1;
        } else {
            continue;
        }

        /* ģʽ�ж� */
        filter_mode  = (p_hw_can->fm_1r >> i) & 0x01;
        filter_scale = (p_hw_can->fs_1r >> i) & 0x01;

        if (filter_mode == AMHW_ZLG237_CAN_FILTER_MODE_IDMASK) {
                /* ����ģʽ 16λ */
            if (filter_scale == AMHW_ZLG237_CAN_FILTER_SCALE_16BIT) {
                uint16_t reg_f_r1_h = p_hw_can->fi_rx[i].f_r1 >> 16;
                uint16_t reg_f_r1_l = p_hw_can->fi_rx[i].f_r1 & 0xffff;
                uint16_t reg_f_r2_h = p_hw_can->fi_rx[i].f_r2 >> 16;
                uint16_t reg_f_r2_l = p_hw_can->fi_rx[i].f_r2 & 0xffff;

                /* ֡��ʽ ֡���� */
                p_filterbuff->ide = ((reg_f_r1_h >> 3) & 0x01) ?
                                        AM_CAN_FRAME_TYPE_EXT :
                                        AM_CAN_FRAME_TYPE_STD;
                p_filterbuff->rtr = ((reg_f_r1_l >> 4) & 0x01) ?
                                        (((reg_f_r1_h >> 4) & 0x01) ?
                                                AM_CAN_FRAME_FORMAT_REMOTE :
                                                AM_CAN_FRAME_FORMAT_DATA):
                                        AM_CAN_FRAME_FORMAT_NOCARE;

                p_filterbuff->id[0] = (reg_f_r1_h >> 5) |
                                        ((reg_f_r1_h & 0x07) << 15);
                p_filterbuff->id[1] = (reg_f_r2_h >> 5) | ((reg_f_r2_h & 0x07) << 15);

                p_filterbuff->mask[0] = (reg_f_r1_l >> 5) | ((reg_f_r1_l & 0x07) << 15);
                p_filterbuff->mask[1] = (reg_f_r2_l >> 5) | ((reg_f_r2_l & 0x07) << 15);

            } else {
                /* ����ģʽ 32λ */
                uint32_t reg_f_r1 = p_hw_can->fi_rx[i].f_r1;
                uint32_t reg_f_r2 = p_hw_can->fi_rx[i].f_r2;

                /* ֡��ʽ ֡���� */
                p_filterbuff->ide = ((reg_f_r1 >> 2) & 0x01) ?
                                        AM_CAN_FRAME_TYPE_EXT :
                                        AM_CAN_FRAME_TYPE_STD;

                p_filterbuff->rtr = ((reg_f_r2 >> 1) & 0x01) ?
                                        (((reg_f_r1 >> 1) & 0x01) ?
                                                AM_CAN_FRAME_FORMAT_REMOTE :
                                                AM_CAN_FRAME_FORMAT_DATA):
                                        AM_CAN_FRAME_FORMAT_NOCARE;

                    /* ��չ֡ */
                if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
                    p_filterbuff->id[0]    = (reg_f_r1 >> 3);
                    p_filterbuff->mask[0]  = (reg_f_r1 >> 3);
                } else {
                    /* ��׼֡ */
                    p_filterbuff->id[0]    = reg_f_r1 >> 21;
                    p_filterbuff->mask[0]  = reg_f_r2 >> 21;
                }
            }
        } else {
            if (filter_scale == AMHW_ZLG237_CAN_FILTER_SCALE_16BIT) {
                /* �б� 16λ */
                uint32_t reg_f_r1_h = p_hw_can->fi_rx[i].f_r1 >> 16;
                uint32_t reg_f_r1_l = p_hw_can->fi_rx[i].f_r1 & 0xffff;
                uint32_t reg_f_r2_h = p_hw_can->fi_rx[i].f_r2 >> 16;
                uint32_t reg_f_r2_l = p_hw_can->fi_rx[i].f_r2 & 0xffff;

                p_filterbuff->ide = ((reg_f_r1_h >> 3) & 0x01) ?
                                        AM_CAN_FRAME_TYPE_EXT :
                                        AM_CAN_FRAME_TYPE_STD;
                p_filterbuff->rtr = ((reg_f_r1_h >> 4) & 0x01) ?
                                        AM_CAN_FRAME_FORMAT_REMOTE :
                                        AM_CAN_FRAME_FORMAT_DATA;

                if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
                    p_filterbuff->id[0] = ((reg_f_r1_h & 0x07) << 15) |
                                           (reg_f_r1_h >> 5);
                    p_filterbuff->id[1] = ((reg_f_r1_l & 0x07) << 15) |
                                           (reg_f_r1_l >> 5);
                    p_filterbuff->id[2] = ((reg_f_r2_h & 0x07) << 15) |
                                           (reg_f_r2_h >> 5);
                    p_filterbuff->id[3] = ((reg_f_r2_l & 0x07) << 15) |
                                           (reg_f_r2_l >> 5);
                } else {
                    p_filterbuff->id[0] = reg_f_r1_h >> 5;
                    p_filterbuff->id[1] = reg_f_r1_l >> 5;
                    p_filterbuff->id[2] = reg_f_r2_h >> 5;
                    p_filterbuff->id[3] = reg_f_r2_l >> 5;
                }

            } else {
                /* �б� 32λ */
                uint32_t reg_f_r1 = p_hw_can->fi_rx[i].f_r1;
                uint32_t reg_f_r2 = p_hw_can->fi_rx[i].f_r2;

                p_filterbuff->ide = ((reg_f_r1 >> 2) & 0x01) ?
                                        AM_CAN_FRAME_TYPE_EXT :
                                        AM_CAN_FRAME_TYPE_STD;
                p_filterbuff->rtr = ((reg_f_r2 >> 1) & 0x01) ?
                                        AM_CAN_FRAME_FORMAT_REMOTE:
                                        AM_CAN_FRAME_FORMAT_DATA;

                if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
                    p_filterbuff->id[0] = reg_f_r1 >> 3;
                    p_filterbuff->id[1] = reg_f_r2 >> 3;
                } else {
                    p_filterbuff->id[0] = reg_f_r1 >> 21;
                    p_filterbuff->id[1] = reg_f_r2 >> 21;
                }
            }
        }
        p_filterbuff++;
    }
    return AM_CAN_NOERROR;
}


static void __can_zlg237_intcb_func_run (am_zlg237_can_dev_t  *p_dev,
                                        am_can_int_type_t      can_int)
{
    uint32_t      temp      = (uint32_t)can_int;
    am_pfnvoid_t  intcb_fun = NULL;
    void         *intcb_arg = NULL;
    uint8_t       i = 0;

    if ((NULL == p_dev) || (AM_CAN_INT_ALL == can_int)) {
        return ;
    }

    while (temp >> 1) {
        i++;
        temp = temp >> 1;
    }

    intcb_fun = p_dev->p_devinfo->p_intcb_info[i].pfn_callback;
    intcb_arg = p_dev->p_devinfo->p_intcb_info[i].p_arg;

    if (NULL != intcb_fun) {
        intcb_fun(intcb_arg);
    }
}

/**
 * \brief can�жϷ�����
 */
static void __can_zlg237_int_handle (void *p_drv)
{
    am_zlg237_can_dev_t    *p_dev     = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can  = NULL;

    if (NULL == p_drv) {
        return;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;


    /* �����жϲ���������rxfifo��Ϊ�� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_FMPIE0)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_FMPIE1))) {

        /* ִ�н��ջص����� */
        __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_RX);

        /*  */
        amhw_zlg237_can_clear_itstatus(p_hw_can, AMHW_ZLG237_CAN_INT_FMPIE0);
        amhw_zlg237_can_clear_itstatus(p_hw_can, AMHW_ZLG237_CAN_INT_FMPIE1);
    }

    /* �����жϲ��������ҷ������ */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_TMEIE))) {

        /* ִ�з��ͻص����� */
        __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_TX);
        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_TMEIE);
    }



    /* �����жϲ��� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_WKUIE))) {
        /* ִ�л����жϻص����� */
        __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_WAKE_UP);

        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_WKUIE);
    }

    /* ��������жϲ��� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_FOVIE0)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_FOVIE1)))  {

        /* ִ����������жϻص����� */
        __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_DATAOVER);

        /* �ͷ�FIFO  ���жϺ����д������  �ڴ˴��� FIFO  ���FIFO���� */
        for (int i = 0 ;i <3 ; i++) {
            p_hw_can->rf_0r |= AMHW_ZLG237_CAN_RF0R_RFOM0;
            p_hw_can->rf_1r |= AMHW_ZLG237_CAN_RF1R_RFOM1;
        }

        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_FOVIE0);
        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_FOVIE1);
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ���� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_ERRIE)))  {

        /* �ж������Ƿ����� */
        if (amhw_zlg237_can_get_itstatus(p_hw_can,
                (AMHW_ZLG237_CAN_INT_BOFIE))) {

            /* ִ�����߹ر��жϻص����� */
            __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_BUS_OFF);

            amhw_zlg237_can_clear_itstatus (p_hw_can,
                                            AMHW_ZLG237_CAN_INT_ERRIE);
        } else if (amhw_zlg237_can_get_itstatus(p_hw_can,
                (AMHW_ZLG237_CAN_INT_EWGIE))) {

           /* ִ�о����жϻص����� */
           __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_WARN);

           amhw_zlg237_can_clear_itstatus (p_hw_can,
                                           AMHW_ZLG237_CAN_INT_ERRIE);
        } else if (amhw_zlg237_can_get_itstatus(p_hw_can,
                (AMHW_ZLG237_CAN_INT_EPVIE))) {

           /* ִ�о����жϻص����� */
           __can_zlg237_intcb_func_run(p_dev, AM_CAN_INT_ERROR_PASSIVE);

           amhw_zlg237_can_clear_itstatus (p_hw_can,
                                           AMHW_ZLG237_CAN_INT_ERRIE);
        }
    }
}

/**
 * \brief CAN ״̬
 */
am_can_err_t __can_zlg237_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    amhw_zlg237_can_t      *p_hw_can = NULL;
    uint8_t                 err_code = 0;  /* ����� */
    uint8_t                 err      = 0;  /* ����Ĵ���ֵ */

    if (NULL == p_drv || NULL == p_int_type || NULL == p_bus_err) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    *p_int_type = 0;

    /* �����ж� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_FMPIE0)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            ( AMHW_ZLG237_CAN_INT_FMPIE1))) {

        *p_int_type |= AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_TMEIE))){
        *p_int_type |= AM_CAN_INT_TX;
    }

    /* ��������ж� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            ( AMHW_ZLG237_CAN_INT_FOVIE0)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            ( AMHW_ZLG237_CAN_INT_FOVIE1))) {

        *p_int_type |= AM_CAN_INT_DATAOVER;
    }

    /* �����ж� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_WKUIE))) {
        *p_int_type |= AM_CAN_INT_WAKE_UP;
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ�ж� */
    if (amhw_zlg237_can_get_itstatus(p_hw_can,
            ( AMHW_ZLG237_CAN_INT_ERRIE)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            ( AMHW_ZLG237_CAN_INT_EWGIE)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_EPVIE)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            (AMHW_ZLG237_CAN_INT_LECIE)) ||
        amhw_zlg237_can_get_itstatus(p_hw_can,
            ( AMHW_ZLG237_CAN_INT_BOFIE)) )  {

        *p_int_type |= AM_CAN_INT_ERROR;

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ���������߹ر� */
        if (amhw_zlg237_can_get_itstatus(p_hw_can,
                (AMHW_ZLG237_CAN_INT_BOFIE))) {
            *p_int_type |= AM_CAN_INT_BUS_OFF;
        }

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ�����Ĵ��󾯸� */
        if (amhw_zlg237_can_get_itstatus(p_hw_can,
                (AMHW_ZLG237_CAN_INT_EWGIE))) {
            *p_int_type |= AM_CAN_INT_WARN;
        }

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ�����Ĵ��󱻶� */
        if (amhw_zlg237_can_get_itstatus(p_hw_can,
                (AMHW_ZLG237_CAN_INT_EPVIE))) {
            *p_int_type |= AM_CAN_INT_ERROR_PASSIVE;
        }
    }

    /* �ӼĴ�����ȡ������� */
    *p_bus_err = 0;
    err        = amhw_zlg237_can_get_lasterrorcode(p_hw_can);
    err_code = (err >> 4);

    /* ��ʽ���� */
    if (AMHW_ZLG237_CAN_LEC_FORMER == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_FORM;
    }

    /* ������ */
    if (AMHW_ZLG237_CAN_LEC_STUFER == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_STUFF;
    }

    /* δ֪����     ���Դ���   ���Դ���  ��������ô���*/
    if ((AMHW_ZLG237_CAN_LEC_SOFTER == err_code) ||
        (AMHW_ZLG237_CAN_LEC_BRCER  == err_code) ||
        (AMHW_ZLG237_CAN_LEC_BDERR  == err_code)) {
        *p_bus_err |= AM_CAN_BUS_ERR_UNKNOWN;
    }

    /* ACK���� */
    if (err_code == AMHW_ZLG237_CAN_LEC_ACKER) {
        *p_bus_err |= AM_CAN_BUS_ERR_ACK;
    }

    /* CRC���� */
    if (err_code == AMHW_ZLG237_CAN_LEC_CRCER) {
        *p_bus_err |= AM_CAN_BUS_ERR_CRC;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�����
 */
am_can_err_t __can_zlg237_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    if (NULL != pfn_isr) {
        /* ���Ӵ��뺯�� */
        am_int_connect(INUM_USB_HP_CAN_TX, pfn_isr, p_arg);
        am_int_connect(INUM_USB_HP_CAN_RX, pfn_isr, p_arg);
        am_int_connect(INUM_CAN1_RX1, pfn_isr, p_arg);
        am_int_connect(INUM_CAN1_SCE, pfn_isr, p_arg);
    } else {
        /* ����Ĭ�Ϻ��� */
        am_int_connect(INUM_USB_HP_CAN_TX, __can_zlg237_int_handle, p_dev);
        am_int_connect(INUM_USB_HP_CAN_RX, __can_zlg237_int_handle, p_dev);
        am_int_connect(INUM_CAN1_RX1, __can_zlg237_int_handle, p_dev);
        am_int_connect(INUM_CAN1_SCE, __can_zlg237_int_handle, p_dev);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ɾ���ж�����
 */
am_can_err_t __can_zlg237_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* �жϽ��� */
    am_int_disable(INUM_USB_HP_CAN_TX);
    am_int_disable(INUM_USB_HP_CAN_RX);
    am_int_disable(INUM_CAN1_RX1);
    am_int_disable(INUM_CAN1_SCE);
    if (NULL != pfn_isr) {
        /* ɾ�����Ӻ��� */
        am_int_disconnect(INUM_USB_HP_CAN_TX, pfn_isr, p_arg);
        am_int_disconnect(INUM_USB_HP_CAN_RX, pfn_isr, p_arg);
        am_int_disconnect(INUM_CAN1_RX1, pfn_isr, p_arg);
        am_int_disconnect(INUM_CAN1_SCE, pfn_isr, p_arg);
    } else {
        /* ɾ�����Ӻ��� */
        am_int_disconnect(INUM_USB_HP_CAN_TX, __can_zlg237_int_handle, p_dev);
        am_int_disconnect(INUM_USB_HP_CAN_RX, __can_zlg237_int_handle, p_dev);
        am_int_disconnect(INUM_CAN1_RX1, __can_zlg237_int_handle, p_dev);
        am_int_disconnect(INUM_CAN1_SCE, __can_zlg237_int_handle, p_dev);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϻص�����������
 */
am_can_err_t __can_zlg237_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    uint8_t  i = 0;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    while (inttype >> 1) {
        i++;
        inttype = inttype >> 1;
    }

    if (i >= p_dev->p_devinfo->p_intcb_num) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_dev->p_devinfo->p_intcb_info[i].pfn_callback = pfn_callback;
    p_dev->p_devinfo->p_intcb_info[i].p_arg        = p_arg;

    return AM_CAN_NOERROR;
}

/**
 * \brief ɾ���жϻص�����������
 */
am_can_err_t __can_zlg237_intcb_disconnect (void              *p_drv,
                                            am_can_int_type_t  inttype)
{
    am_zlg237_can_dev_t    *p_dev    = (am_zlg237_can_dev_t *)p_drv;
    uint8_t  i = 0;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    while (inttype >> 1) {
        i++;
        inttype = inttype >> 1;
    }

    if (i >= p_dev->p_devinfo->p_intcb_num) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_dev->p_devinfo->p_intcb_info[i].pfn_callback = NULL;
    p_dev->p_devinfo->p_intcb_info[i].p_arg        = NULL;

    return AM_CAN_NOERROR;
}

/**
 * \brief  CAN��ʼ��
 */
am_can_handle_t am_zlg237_can_init (am_zlg237_can_dev_t      *p_dev,
                               const am_zlg237_can_devinfo_t *p_devinfo)
{
    uint8_t             i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    p_dev->handle.p_drv_funcs = &__zlg237_can_dev_func;
    p_dev->handle.p_drv       = (void *)p_dev;

    for (i = 0 ; i < p_devinfo->p_intcb_num ; i++) {
        p_devinfo->p_intcb_info[i].pfn_callback = NULL;
        p_devinfo->p_intcb_info[i].p_arg        = NULL;
    }

    return (am_can_handle_t)&(p_dev->handle);
}

/**
 * \brief ���ʼ��
 */
void am_zlg237_can_deinit (am_can_handle_t handle)
{
    amhw_zlg237_can_t *p_hw_can = NULL;
    am_zlg237_can_dev_t  *p_dev = (am_zlg237_can_dev_t *)handle->p_drv;

    if (NULL == p_dev) {
        return;
    }

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    amhw_zlg237_can_operating_mode_request(p_hw_can,
            AMHW_ZLG237_CAN_OPERATING_MODE_INIT);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

    /* �жϽ��� */
    am_int_disable(INUM_USB_HP_CAN_TX);
    am_int_disable(INUM_USB_HP_CAN_RX);
    am_int_disable(INUM_CAN1_RX1);
    am_int_disable(INUM_CAN1_SCE);
}

/* end of file */
