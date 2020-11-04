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
 * \endinternal
 */

#include "am_int.h"

#include "am_hk32f103rbt6_can.h"
#include "hw/amhw_hk32f103rbt6_can.h"
#include "hk32f103rbt6_inum.h"

/** \brief CAN���� */
am_can_err_t __can_hk32f103rbt6_start (void *p_drv);
/** \brief CAN��λ��ֹͣ�� */
am_can_err_t __can_hk32f103rbt6_reset (void *p_drv);
/** \brief CAN����  */
am_can_err_t __can_hk32f103rbt6_sleep (void *p_drv);
/** \brief CAN���� */
am_can_err_t __can_hk32f103rbt6_wakeup (void *p_drv);
/** \brief �ж�ʹ�� */
am_can_err_t __can_hk32f103rbt6_int_enable (void *p_drv, am_can_int_type_t int_mask);
/** \brief �жϽ���*/
am_can_err_t __can_hk32f103rbt6_int_disable (void *p_drv, am_can_int_type_t int_mask);
/** \brief ģʽ���� */
am_can_err_t __can_hk32f103rbt6_mode_set (void *p_drv, am_can_mode_type_t mode);
/** \brief ���������� */
am_can_err_t __can_hk32f103rbt6_baudrate_set (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief �����ʻ�ȡ */
am_can_err_t __can_hk32f103rbt6_baudrate_get (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief ��ȡ������� */
am_can_err_t __can_hk32f103rbt6_err_cnt_get (void         *p_drv,
                                 am_can_err_cnt_t   *p_can_err_reg);
/** \brief ������Ϣ   */
am_can_err_t __can_hk32f103rbt6_msg_send (void *p_drv, am_can_message_t *p_txmsg);
/** \brief ������Ϣ   */
am_can_err_t __can_hk32f103rbt6_msg_recv (void *p_drv, am_can_message_t *p_rxmsg);
/** \brief ֹͣ������Ϣ   */
am_can_err_t __can_hk32f103rbt6_stop_msg_snd (void *p_drv);
/** \brief �����˲����� */
am_can_err_t __can_hk32f103rbt6_filter_tab_set (void    *p_drv,
                                   uint8_t *p_filterbuff,
                                   size_t   lenth);
/** \brief ��ȡ�˲�����*/
am_can_err_t __can_hk32f103rbt6_filter_tab_get (void    *p_drv,
                                   uint8_t *p_filterbuff,
                                   size_t  *p_lenth);

/** \brief CAN ״̬ */
am_can_err_t __can_hk32f103rbt6_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err);
/** \brief �ж����� */
am_can_err_t __can_hk32f103rbt6_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg);
/** \brief ɾ���ж����� */
am_can_err_t __can_hk32f103rbt6_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg);
/** \brief �жϻص����������� */
am_can_err_t __can_hk32f103rbt6_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg);


/** \brief ɾ���жϻص����������� */
am_can_err_t __can_hk32f103rbt6_intcb_disconnect (void              *p_drv,
                                            am_can_int_type_t  inttype);

struct am_can_drv_funcs __hk32f103rbt6_can_dev_func = {
    __can_hk32f103rbt6_start,
    __can_hk32f103rbt6_reset,
    __can_hk32f103rbt6_sleep,
    __can_hk32f103rbt6_wakeup,
    __can_hk32f103rbt6_int_enable,
    __can_hk32f103rbt6_int_disable,
    __can_hk32f103rbt6_mode_set,
    __can_hk32f103rbt6_baudrate_set,
    __can_hk32f103rbt6_baudrate_get,
    __can_hk32f103rbt6_err_cnt_get,
    NULL,
    __can_hk32f103rbt6_msg_send,
    __can_hk32f103rbt6_msg_recv,
    __can_hk32f103rbt6_stop_msg_snd,
    __can_hk32f103rbt6_filter_tab_set,
    __can_hk32f103rbt6_filter_tab_get,
    __can_hk32f103rbt6_status_get,
    __can_hk32f103rbt6_connect,
    __can_hk32f103rbt6_disconnect,
    __can_hk32f103rbt6_intcb_connect,
    __can_hk32f103rbt6_intcb_disconnect
};

/**
 * \brief CAN��ʼ��
 */
uint8_t __can_hk32f103rbt6_init (void *p_drv)
{
    am_hk32f103rbt6_can_dev_t        *p_dev       = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t          *p_hw_can    = NULL;
    am_hk32f103rbt6_can_init_info_t  *p_can_info  = NULL;
    uint8_t                     init_staus  = 0;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_can_info =(am_hk32f103rbt6_can_init_info_t *)p_dev->p_devinfo->init_info;
    p_hw_can   =(amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* �˳�˯��   ��������ʼ��ģʽ */
    if (amhw_hk32f103rbt6_can_operating_mode_request(
            p_hw_can, AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT)) {

        /* ����ʱ�䴥��ͨ��ģʽ  */
        if (p_can_info->can_ttcm) {
            amhw_hk32f103rbt6_can_ttcom_mode_set(p_hw_can, 1);
        } else {
            amhw_hk32f103rbt6_can_ttcom_mode_set(p_hw_can, 0);
        }

        /* ��������Զ����߹���  */
        if (p_can_info->can_abom) {
            p_hw_can->mcr |= AMHW_HK32F103RBT6_CAN_MCR_ABOM;
        } else {
            p_hw_can->mcr &= (~AMHW_HK32F103RBT6_CAN_MCR_ABOM);
        }

        /* �����Զ�����ģʽ */
        if (p_can_info->can_awum) {
            p_hw_can->mcr |= AMHW_HK32F103RBT6_CAN_MCR_AWUM;
        } else {
            p_hw_can->mcr &= (~AMHW_HK32F103RBT6_CAN_MCR_AWUM);
        }

        /* ���� ��ֹ�����Զ��ش�  */
        if (p_can_info->can_nart) {
            p_hw_can->mcr |= AMHW_HK32F103RBT6_CAN_MCR_NART;
        } else {
            p_hw_can->mcr &= (~AMHW_HK32F103RBT6_CAN_MCR_NART);
        }

        /* ���� ����FIFO����ģʽ */
        if (p_can_info->can_rflm) {
            p_hw_can->mcr |= AMHW_HK32F103RBT6_CAN_MCR_RFLM;
        } else {
            p_hw_can->mcr &= (~AMHW_HK32F103RBT6_CAN_MCR_RFLM);
        }

        /* ���� ����FIFP���ȼ� */
        if (p_can_info->can_txfp) {
            p_hw_can->mcr |= AMHW_HK32F103RBT6_CAN_MCR_TXFP;
        } else {
            p_hw_can->mcr &= (~AMHW_HK32F103RBT6_CAN_MCR_TXFP);
        }


        p_hw_can->btr |= (uint32_t)(((uint32_t) p_can_info->can_mode << 30));

        /* ������ѹҺű�־λ  */
        p_hw_can->msr |= (uint32_t)0x08;

        /* ��������ģʽ */
        if (amhw_hk32f103rbt6_can_operating_mode_request(
                    p_hw_can, AMHW_HK32F103RBT6_CAN_OPERATING_NORMAL)) {
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
am_can_err_t __can_hk32f103rbt6_start (void *p_drv)
{

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* ��ʼ��CAN������Ϣ */
    __can_hk32f103rbt6_init(p_drv);

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
am_can_err_t __can_hk32f103rbt6_reset (void *p_drv)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* ��CANǿ�Ƹ�λ  ��λ��CAN����˯��ģʽ */
    p_hw_can->mcr |= AMHW_HK32F103RBT6_CAN_MCR_RESET;


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
am_can_err_t __can_hk32f103rbt6_sleep (void *p_drv)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* �л���˯��ģʽ*/
    amhw_hk32f103rbt6_can_operating_mode_request(
            p_hw_can, AMHW_HK32F103RBT6_CAN_OPERATING_SLEEP);

    return AM_CAN_NOERROR;
}

/**
 * \brief CAN����
 */
am_can_err_t __can_hk32f103rbt6_wakeup (void *p_drv)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* �л���˯��ģʽ*/
    amhw_hk32f103rbt6_can_operating_mode_request(
            p_hw_can, AMHW_HK32F103RBT6_CAN_OPERATING_NORMAL);

    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�ʹ��
 */
am_can_err_t __can_hk32f103rbt6_int_enable (void *p_drv, am_can_int_type_t int_mask)
{
    am_hk32f103rbt6_can_dev_t             *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t               *p_hw_can = NULL;
    amhw_hk32f103rbt6_can_mode_t           mode     = p_dev->mode;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* �����ж� */
    if (int_mask & AM_CAN_INT_RX) {

        /* ʹ�� FIFO 0 1 ��Ϣ�Һ��ж�ʹ�� */
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FMPIE0, 1);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FMPIE1, 1);

        int_mask &= ~AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_TX) {

        /* ����������ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_TMEIE, 1);

        int_mask &= ~AM_CAN_INT_TX;
    }

    /* ����\�����ж�  */
    if ((int_mask & AM_CAN_INT_ERROR)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 1);

        int_mask &= ~AM_CAN_INT_ERROR;
    }

    /* �����ж�  */
    if ((int_mask & AM_CAN_INT_WARN)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 1);

        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_EWGIE, 1);

        int_mask &= ~AM_CAN_INT_WARN;
    }

    /* ���󱻶��ж�  */
    if ((int_mask & AM_CAN_INT_ERROR_PASSIVE)) {

        /* ���󱻶� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 1);

        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_EPVIE, 1);


        int_mask &= ~AM_CAN_INT_ERROR_PASSIVE;
    }

    /* ���߹ر��ж�  */
    if ((int_mask & AM_CAN_INT_BUS_OFF)) {

        /* �����ж� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 1);

        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_BOFIE, 1);

        int_mask &= ~AM_CAN_INT_BUS_OFF;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_WAKE_UP) {

        /* ʹ�ܻ����ж� */
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_WKUIE, 1);

        int_mask &= ~AM_CAN_INT_WAKE_UP;
    }

    /* ���߳����ж� */
    if (int_mask & AM_CAN_INT_DATAOVER) {

        /* ʹ����������ж�  FIFO 0 1 */
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FOVIE0, 1);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FOVIE1, 1);

        int_mask &= ~AM_CAN_INT_DATAOVER;
    }

    /* �ָ�CAN״̬ */
    if (mode != AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT) {

        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can, mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϽ���
 */
am_can_err_t __can_hk32f103rbt6_int_disable (void *p_drv, am_can_int_type_t int_mask)
{
    am_hk32f103rbt6_can_dev_t         *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t           *p_hw_can = NULL;
    amhw_hk32f103rbt6_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;


    /* �����ж� */
    if (int_mask & AM_CAN_INT_RX) {

        /* ʹ�� FIFO 0 1 ��Ϣ�Һ��ж�ʹ�� */
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FMPIE0, 0);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FMPIE1, 0);

        int_mask &= ~AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_TX) {

        /* ����������ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_TMEIE, 0);

        int_mask &= ~AM_CAN_INT_TX;
    }

    /* ����\�����ж�  */
    if ((int_mask & AM_CAN_INT_ERROR)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 0);

        int_mask &= ~AM_CAN_INT_ERROR;
    }

    /* �����ж�  */
    if ((int_mask & AM_CAN_INT_WARN)) {

        /* ���󾯸� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 0);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_EWGIE, 0);

        int_mask &= ~AM_CAN_INT_WARN;
    }

    /* ���󱻶��ж�  */
    if ((int_mask & AM_CAN_INT_ERROR_PASSIVE)) {

        /* ���󱻶� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 0);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_EPVIE, 0);

        int_mask &= ~AM_CAN_INT_ERROR_PASSIVE;
    }

    /* ���߹ر��ж�  */
    if ((int_mask & AM_CAN_INT_BUS_OFF)) {

        /* �����ж� �� �����ж�ʹ��*/
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_ERRIE, 0);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_BOFIE, 0);

        int_mask &= ~AM_CAN_INT_BUS_OFF;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_WAKE_UP) {
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_WKUIE, 0);

        int_mask &= ~AM_CAN_INT_WAKE_UP;
    }

    /* ���߳����ж� */
    if (int_mask & AM_CAN_INT_DATAOVER) {
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FOVIE0, 0);
        amhw_hk32f103rbt6_can_itconfig(p_hw_can,
                AMHW_HK32F103RBT6_CAN_INT_FOVIE1, 0);

        int_mask &= ~AM_CAN_INT_DATAOVER;
    }
    /* �ָ�CAN״̬ */
    if (mode != AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT) {

        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can, mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ģʽ����
 */
am_can_err_t __can_hk32f103rbt6_mode_set (void *p_drv, am_can_mode_type_t mode)
{
    am_hk32f103rbt6_can_dev_t *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t   *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    if (AM_CAN_MODE_NROMAL == mode ) {

        /* ����ģʽ */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                AMHW_HK32F103RBT6_CAN_OPERATING_NORMAL);
    } else if (AM_CAN_MODE_LISTEN_ONLY == mode) {

        /* ��Ĭģʽ*/
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
            (amhw_hk32f103rbt6_can_mode_t)AMHW_HK32F103RBT6_CAN_MODE_SILENT);
    } else {
        /* �ػ� �� �ػ���Ĭδ���� */

        return AM_CAN_INVALID_PARAMETER;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ����������
 */
am_can_err_t __can_hk32f103rbt6_baudrate_set (void           *p_drv,
                                 am_can_bps_param_t    *p_can_baudrate)
{
    am_hk32f103rbt6_can_dev_t         *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t           *p_hw_can = NULL;
    amhw_hk32f103rbt6_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    if (AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT != p_dev->mode) {

        /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT);
    }

    /* ���� �����ʷ�Ƶ��   ͬ����ת���   ����λ�� */
    amhw_hk32f103rbt6_can_brp_set(p_hw_can, p_can_baudrate->brp);
    amhw_hk32f103rbt6_can_sjw_set(p_hw_can, p_can_baudrate->sjw);

    amhw_hk32f103rbt6_can_tseg1_set(p_hw_can, p_can_baudrate->tesg1);
    amhw_hk32f103rbt6_can_tseg2_set(p_hw_can, p_can_baudrate->tesg2);

    if (mode != AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT) {

        /* �л�������ģʽ */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �����ʻ�ȡ
 */
am_can_err_t __can_hk32f103rbt6_baudrate_get (void           *p_drv,
                                 am_can_bps_param_t    *p_can_baudrate)
{
    am_hk32f103rbt6_can_dev_t         *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t           *p_hw_can = NULL;
    amhw_hk32f103rbt6_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    if (AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT != p_dev->mode) {
        /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT);
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    p_can_baudrate->brp = amhw_hk32f103rbt6_can_brp_get(p_hw_can);
    p_can_baudrate->sjw = amhw_hk32f103rbt6_can_sjw_get(p_hw_can);

    p_can_baudrate->tesg1 = amhw_hk32f103rbt6_can_tseg1_get(p_hw_can);
    p_can_baudrate->tesg2 = amhw_hk32f103rbt6_can_tseg2_get(p_hw_can);


    if (mode != AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT) {

        /* �л�������ģʽ */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�������
 */
am_can_err_t __can_hk32f103rbt6_err_cnt_get (void        *p_drv,
                               am_can_err_cnt_t    *p_can_err_reg)
{
    am_hk32f103rbt6_can_dev_t *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t   *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_can_err_reg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* �� TX/RX��������� */
    p_can_err_reg->rx_error_cnt = amhw_hk32f103rbt6_can_get_recverrorcount(p_hw_can);
    p_can_err_reg->tx_error_cnt = amhw_hk32f103rbt6_can_get_transerrorcount(p_hw_can);

    return AM_CAN_NOERROR;
}


/**
 * \brief ������Ϣ
 */
am_can_err_t __can_hk32f103rbt6_msg_send (void *p_drv, am_can_message_t *p_txmsg)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can = NULL;
    am_bool_t               is_remote = AM_FALSE;
    am_bool_t               is_extern = AM_FALSE;

    uint8_t transmit_mailbox = 0;

    if (NULL == p_drv || NULL == p_txmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;


    if ((p_hw_can->tsr & AMHW_HK32F103RBT6_CAN_TSR_TME0) ==
                         AMHW_HK32F103RBT6_CAN_TSR_TME0) {

        transmit_mailbox = 0;
    } else if ((p_hw_can->tsr & AMHW_HK32F103RBT6_CAN_TSR_TME1) ==
                                AMHW_HK32F103RBT6_CAN_TSR_TME1) {
        transmit_mailbox = 1;
    } else if ((p_hw_can->tsr & AMHW_HK32F103RBT6_CAN_TSR_TME2) ==
                                AMHW_HK32F103RBT6_CAN_TSR_TME2) {
        transmit_mailbox = 2;
    } else {

        /* �������䲻Ϊ��  */
        transmit_mailbox = HK32F103RBT6_CAN_TX_STATUS_NOMAILBOX;
    }

    is_remote = ((p_txmsg->flags & AM_CAN_REMOTE_FLAG) ? AM_TRUE : AM_FALSE);
    is_extern = ((p_txmsg->flags & AM_CAN_EXTERN_FLAG) ? AM_TRUE : AM_FALSE);

    /* hk32f103rbt6 can û��can fd���� */
    if (p_txmsg->flags & AM_CAN_FD_CTRL_FLAG) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* 8�ֽ����� */
     if (p_txmsg->msglen > 8) {
         p_txmsg->msglen = 8;
     }

    if (transmit_mailbox != HK32F103RBT6_CAN_TX_STATUS_NOMAILBOX) {

        /* ��ռĴ���*/
        p_hw_can->tx_mail[transmit_mailbox].tir &= AMHW_HK32F103RBT6_CAN_TIR_TXRQ;

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
        p_hw_can->tx_mail[transmit_mailbox].tir |= AMHW_HK32F103RBT6_CAN_TIR_TXRQ;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ������Ϣ
 */
am_can_err_t __can_hk32f103rbt6_msg_recv (void *p_drv, am_can_message_t *p_rxmsg)
{
    am_hk32f103rbt6_can_dev_t       *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_filter_t  *p_filter = NULL;
    amhw_hk32f103rbt6_can_t         *p_hw_can = NULL;
    uint8_t         rx_mailbox = 0;

    if (NULL == p_drv || NULL == p_rxmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_filter= (amhw_hk32f103rbt6_can_filter_t *)p_dev->p_devinfo->filter;
    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    /* ��ʼ�� */
    p_rxmsg->id     = 0;
    p_rxmsg->flags  = 0;
    p_rxmsg->msglen = 0;

    /* �жϽ��ջ������Ƿ�Ϊ�� */
    if (p_filter->can_fliter_fifo  == AMHW_HK32F103RBT6_CAN_FILTER_FIFO0 ) {
        if ((p_hw_can->rf_0r & (uint32_t)0x3)) {
            rx_mailbox = 0;
        } else {
            return AM_CAN_NOERROR;
        }
    } else if (p_filter->can_fliter_fifo  == AMHW_HK32F103RBT6_CAN_FILTER_FIFO1) {
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
    } else {

        /* ����֡  */

        /* ��ȡ�������ݳ���*/
        p_rxmsg->msglen = (uint8_t)0x0f &
                           p_hw_can->rx_mail[rx_mailbox].rdtr;

    }

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
        p_hw_can->rf_0r |= AMHW_HK32F103RBT6_CAN_RF0R_RFOM0;
    } else {
    /* �ͷ�FIFO 1 */
        p_hw_can->rf_1r |= AMHW_HK32F103RBT6_CAN_RF1R_RFOM1;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ֹͣ������Ϣ
 */
am_can_err_t __can_hk32f103rbt6_stop_msg_snd (void *p_drv)
{
    am_hk32f103rbt6_can_dev_t    *p_dev            = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can         = NULL;
    uint8_t                 transmit_mailbox = 0;
    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    if ((p_hw_can->tsr & AMHW_HK32F103RBT6_CAN_TSR_TME0) !=
                         AMHW_HK32F103RBT6_CAN_TSR_TME0) {

        transmit_mailbox = 0;
    } else if ((p_hw_can->tsr & AMHW_HK32F103RBT6_CAN_TSR_TME1) !=
                                AMHW_HK32F103RBT6_CAN_TSR_TME1) {
        transmit_mailbox = 1;
    } else if ((p_hw_can->tsr & AMHW_HK32F103RBT6_CAN_TSR_TME2) !=
                                AMHW_HK32F103RBT6_CAN_TSR_TME2) {
        transmit_mailbox = 2;
    } else {
        /* ��������Ϊ��  */
        return AM_CAN_INVALID_PARAMETER;
    }

    switch (transmit_mailbox) {

    case (0):
        p_hw_can->tsr |= AMHW_HK32F103RBT6_CAN_TSR_ABRQ0;
        break;

    case (1):
        p_hw_can->tsr |= AMHW_HK32F103RBT6_CAN_TSR_ABRQ1;
        break;

    case (2):
        p_hw_can->tsr |= AMHW_HK32F103RBT6_CAN_TSR_ABRQ2;
        break;

    default:
        break;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �����˲�����
 */
am_can_err_t __can_hk32f103rbt6_filter_tab_set (void    *p_drv,
                                          uint8_t *p_filterbuff,
                                          size_t   lenth)
{
    am_hk32f103rbt6_can_dev_t         *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_filter_t    *p_filter = NULL;
    amhw_hk32f103rbt6_can_t           *p_hw_can = NULL;
    uint8_t                      filt_num = 0;
    uint32_t                     filt_pos = 0;
    amhw_hk32f103rbt6_can_mode_t       mode     = p_dev->mode;

    if (NULL == p_drv || NULL == p_filterbuff || 0 == lenth) {
        return AM_CAN_INVALID_PARAMETER;
    }


    p_filter= (amhw_hk32f103rbt6_can_filter_t *)p_dev->p_devinfo->filter;
    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    if (AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT != p_dev->mode) {
        /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT);
    }


    /* �˲����������˲�����ʼ��ģʽ  */
    p_hw_can->fmr |= (uint32_t)0x01;

    for (int i = 0; i < (lenth / 8); i++) {

        filt_num = p_filter->can_filter_num + i;

        if (filt_num > 13) {
            /* �˲����� */
            filt_pos = (uint32_t)(1ul << (filt_num - 14));
        } else {
            /* �˲����� */
            filt_pos = (uint32_t)(1ul << filt_num);
        }

        /* �����˲���  */
        p_hw_can->fa_1r &= ~(uint32_t)filt_pos;

        /* �˲���ģʽ  */
        if (p_filter->can_filter_mode == AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDMASK) {
            /* ����λģʽ  */
            p_hw_can->fm_1r &= ~(uint32_t)filt_pos;
        } else {
            /* ��־λ�б�ģʽ  */
            p_hw_can->fm_1r |= (uint32_t)filt_pos;
        }

        /* �˲���λ�� ���� */
        if (p_filter->can_filter_scale ==
                AMHW_HK32F103RBT6_CAN_FILTER_SCALE_16BIT) {

            /* 16λ�� */
            p_hw_can->fs_1r &= ~(uint32_t)filt_pos;

            if (p_filter->can_filter_mode == AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDMASK) {

                /**
                 *  ��ʶ������λģʽ
                 *  2��16λ������
                 */
                /* ʹ����չID STD[10:3] STD[2:0] RTR IDE EXID[17:15] */

                /* id_l id_h  id_mask_l id_mask_h  id_l id_h  id_mask_l id_mask_h*/
                p_hw_can->fi_rx[filt_num].f_r1 =

                            /*ID*/
                            /* EXIT[17:15] */
                            ((p_filterbuff[0 + i*8] & 0x38) >> 3)   |

                            /* IDE RTR */
                             (p_filter->can_fliter_ide << 3)        |
                             (p_filter->can_fliter_rtr << 4)        |

                             /* STD[7:0] */
                            ((p_filterbuff[1 + i*8] ) << 5)         |

                            /* STD[10:8] */
                            ((p_filterbuff[0 + i*8] &0x7) << 13)     |

                             /* ID_mask */
                            /* STD[2:0] RTR IDE EXIT[17:15]  */
                            ((p_filterbuff[3 + i*8] ) << 16)        |

                            /* STD[10:3] */
                            ((p_filterbuff[2 + i*8] ) << 24);

                p_hw_can->fi_rx[filt_num].f_r2 =

                             /*ID*/
                             /* EXIT[17:15] */
                           ((p_filterbuff[4 + i*8] & 0x38) >> 3)    |

                             /* IDE  RTR */
                            (p_filter->can_fliter_ide << 3)         |
                            (p_filter->can_fliter_rtr << 4)         |

                            /* STD[7:0] */
                           ((p_filterbuff[5 + i*8] ) << 5)          |

                           /* STD[10:8] */
                           ((p_filterbuff[4 + i*8] &0x7) << 13)      |

                            /* ID_mask */
                           /* STD[2:0] RTR IDE EXIT[17:15]  */
                           ((p_filterbuff[7 + i*8] ) << 16)         |

                           /* STD[17:15] */
                           ((p_filterbuff[6 + i*8] ) << 24);
            } else {
                /**
                 *  ��־λ�б�ģʽ
                 *  4��16λ������
                 */

                       /* ʹ����չID STD[10:3] STD[2:0] RTR IDE EXID[17:15] */

                       /* id_l id_h  id_mask_l id_mask_h  id_l id_h  id_mask_l id_mask_h*/
                        p_hw_can->fi_rx[filt_num].f_r1 =

                                /*ID*/
                                /* EXIT[17:15] */
                               ((p_filterbuff[0 + i*8] & 0x38) >> 3)   |

                               /* IDE */
                                (p_filter->can_fliter_ide << 3)        |

                                /* RTR */
                                (p_filter->can_fliter_rtr << 4)        |

                                /* STD[7:0] */
                               ((p_filterbuff[1 + i*8] ) << 5)         |

                               /* STD[10:8] */
                               ((p_filterbuff[0 + i*8] &0x7) << 13)     |

                               /* ID */
                               /* EXIT[17:15] */
                               ((p_filterbuff[2 + i*8] & 0x38) << 13)   |

                               /* IDE */
                                (p_filter->can_fliter_ide << 19)        |

                                /* RTR */
                                (p_filter->can_fliter_rtr << 20)        |

                                /* STD[7:0] */
                               ((p_filterbuff[3 + i*8] ) << 21)         |

                               /* STD[10:8] */
                               ((p_filterbuff[2 + i*8] &0x7) << 29) ;

                       p_hw_can->fi_rx[filt_num].f_r2 =

                               /*ID*/
                               /* EXIT[17:15] */
                               ((p_filterbuff[4 + i*8] & 0x38) >> 3)   |

                               /* IDE  RTR*/
                                (p_filter->can_fliter_ide << 3)        |
                                (p_filter->can_fliter_rtr << 4)        |

                                /* STD[7:0] */
                               ((p_filterbuff[5 + i*8] ) << 5)         |

                               /* STD[10:8] */
                               ((p_filterbuff[4 + i*8] &0x7) << 13)     |

                               /* ID */
                               /* EXIT[17:15] */
                               ((p_filterbuff[6 + i*8] & 0x38) << 13)   |
                               /* IDE  RTR */
                                (p_filter->can_fliter_ide << 19)        |
                                (p_filter->can_fliter_rtr << 20)        |

                                /* STD[7:0] */
                               ((p_filterbuff[7 + i*8] ) << 21)         |

                               /* STD[10:8] */
                               ((p_filterbuff[6 + i*8] &0x7) << 29) ;
            }

        } else if (p_filter->can_filter_scale ==
                       AMHW_HK32F103RBT6_CAN_FILTER_SCALE_32BIT) {
            /* 32λ�� */
            p_hw_can->fs_1r |= (uint32_t)filt_pos;

            if (p_filter->can_filter_mode == AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDMASK) {

                /**
                 *  ��ʶ������λģʽ
                 *  1��32λ������
                 */
                if (p_filter->can_fliter_ide == CAN_ID_EXT) {

                    /* ʹ����չID */
                    /* ID */
                    p_hw_can->fi_rx[filt_num].f_r1 =

                            /* RTR IDE */
                            (p_filter->can_fliter_rtr << 1)   |
                            (p_filter->can_fliter_ide << 2)   |

                            /* EXID[0:28] */
                            (((p_filterbuff[3 + i*8])      |
                              (p_filterbuff[2 + i*8] << 8) |
                              (p_filterbuff[1 + i*8] << 16)|
                              (p_filterbuff[0 + i*8] << 24)) << 3);

                    /* ID_MASK */
                    p_hw_can->fi_rx[filt_num].f_r2 =

                            /* 0 RTR IDE EXID[0:28] */
                                          0x00 |
                            (((p_filterbuff[7 + i*8])      |
                              (p_filterbuff[6 + i*8] << 8) |
                              (p_filterbuff[5 + i*8] << 16)|
                              (p_filterbuff[4 + i*8] << 24)) << 1);

                } else {
                    /* ʹ�ñ�׼ID */
                    /* ID */
                    p_hw_can->fi_rx[filt_num].f_r1 =

                            /* RTR      IDE*/
                            (p_filter->can_fliter_rtr << 1)   |
                            (p_filter->can_fliter_ide << 2)   |

                            /* STID[0:10] */
                            (((p_filterbuff[3 + i*8] )    |
                              (p_filterbuff[2 + i*8] << 8)) << 21);

                    /* ID_MASK */
                    p_hw_can->fi_rx[filt_num].f_r2 =
                            /* RTR IDE */
                            ((p_filterbuff[7 + i*8] &0x3) << 1) |

                            /* STID[0:10] */
                             ((((p_filterbuff[7 + i*8] & 0xfc) >> 2) |
                                ((p_filterbuff[6 +i*8] & 0x1f)<< 6)) << 21);
                }
            } else {

                /**
                 *  ��־λ�б�ģʽ
                 *  2��32λ������
                 */
                if (p_filter->can_fliter_ide == CAN_ID_EXT) {
                    /* ID */
                    p_hw_can->fi_rx[filt_num].f_r1 =

                            /* RTR IDE */
                            (p_filter->can_fliter_rtr << 1)   |
                            (p_filter->can_fliter_ide << 2)   |

                            /* EXID[0:28] */
                            (((p_filterbuff[3 + i*8])      |
                              (p_filterbuff[2 + i*8] << 8) |
                              (p_filterbuff[1 + i*8] << 16)|
                              (p_filterbuff[0 + i*8] << 24)) << 3);

                    /* ID */
                    p_hw_can->fi_rx[filt_num].f_r2 =
                            (p_filter->can_fliter_rtr << 1)   |
                            (p_filter->can_fliter_ide << 2)   |
                            (((p_filterbuff[7 + i*8])      |   /* EXID[0:28] */
                              (p_filterbuff[6 + i*8] << 8) |
                              (p_filterbuff[5 + i*8] << 16)|
                              (p_filterbuff[4 + i*8] << 24)) << 3);
                } else {
                    /* ID */
                    p_hw_can->fi_rx[filt_num].f_r1 =
                            (p_filter->can_fliter_rtr << 1)   |
                            (p_filter->can_fliter_ide << 2)   |
                            (((p_filterbuff[3 + i*8])      |   /* STID[0:10] */
                              ((p_filterbuff[2 + i*8] &0X7) << 8) ) << 21);

                    /* ID */
                    p_hw_can->fi_rx[filt_num].f_r2 =
                            (p_filter->can_fliter_rtr << 1)   |     /* RTR */
                            (p_filter->can_fliter_ide << 2)   |     /* IDE */
                            (((p_filterbuff[7 + i*8])      |   /* STID[0:10] */
                              ((p_filterbuff[6 + i*8] & 0X7 ) << 8)) << 21);
                }

            }
        }

        /* �˲���FIFO����  */
        if (p_filter->can_fliter_fifo == AMHW_HK32F103RBT6_CAN_FILTER_FIFO0) {

            /* ������FIFO 0  */
            p_hw_can->ffa_1r &= ~(uint32_t)filt_pos;
        }

        if (p_filter->can_fliter_fifo == AMHW_HK32F103RBT6_CAN_FILTER_FIFO1) {

            /* ������FIFO 1  */
            p_hw_can->ffa_1r |= (uint32_t)filt_pos;
        }

        /* �����˲���  */
        if (p_filter->filter_state == 1) {

            p_hw_can->fa_1r |= (uint32_t)filt_pos;
        }
    }


    /* �˲�����ص�����ģʽ */
    p_hw_can->fmr &= ~0x01;

    if (mode != AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT) {

        /* �л�������ģʽ */
        amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
                mode);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�˲�����
 */
am_can_err_t __can_hk32f103rbt6_filter_tab_get (void    *p_drv,
                                          uint8_t *p_filterbuff,
                                          size_t  *p_lenth)
{
    am_hk32f103rbt6_can_dev_t         *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;

    amhw_hk32f103rbt6_can_t           *p_hw_can = NULL;
    uint8_t                      i        = 0;
    uint32_t                     id       = 0;
    uint32_t                     id_mask  = 0;
    if (NULL == p_drv ) {
        return AM_CAN_INVALID_PARAMETER;
    }


    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    for (i = 0; i < 13; i++ ) {

        /* �˲����Ѽ��� */
        if (p_hw_can->fa_1r & (1ul << i) ) {
            *p_lenth = *p_lenth + 8;
            /* �����������ڱ�ʶ���б�ģʽ�� */
            if (p_hw_can->fm_1r & (1ul << i)) {

                /* ������λ��Ϊ2��16λ */
                if ((p_hw_can->fs_1r & (1ul << i)) == 0) {

                    id = ((p_hw_can->fi_rx[i].f_r1 & 0x7) << 11) |
                         ((p_hw_can->fi_rx[i].f_r1 & 0xffe0) >> 5);
                    p_filterbuff[0 + i*8] = id >> 8;
                    p_filterbuff[1 + i*8] = id & 0xff;
                    id = (((p_hw_can->fi_rx[i].f_r1 >> 16) & 0x7 ) << 11) |
                         (((p_hw_can->fi_rx[i].f_r1 >> 16) & 0xffe0) >> 5);
                    p_filterbuff[2 + i*8] = id >> 8;
                    p_filterbuff[3 + i*8] = id & 0xff;

                    id = ((p_hw_can->fi_rx[i].f_r2 & 0x7) << 11) |
                         ((p_hw_can->fi_rx[i].f_r2 & 0xffe0) >> 5);
                    p_filterbuff[4 + i*8] = id >> 8;
                    p_filterbuff[5 + i*8] = id & 0xff;
                    id = (((p_hw_can->fi_rx[i].f_r2 >> 16) & 0x7 ) << 11) |
                         (((p_hw_can->fi_rx[i].f_r2 >> 16) & 0xffe0) >> 5);
                    p_filterbuff[6 + i*8] = id >> 8;
                    p_filterbuff[7 + i*8] = id & 0xff;

                } else {
                    /* ������λ��Ϊ����32λ */
                    if (p_hw_can->fi_rx[i].f_r1 & 0x4 ) {
                        /* ��չ��ʶ�� */
                        id = (p_hw_can->fi_rx[i].f_r1 >> 3);
                        p_filterbuff[0 + i*8] =
                                (uint8_t)((id & (~(uint32_t)0xffffff)) >> 24);
                        p_filterbuff[1 + i*8] =
                                (uint8_t)((id & 0xff0000) >> 16);
                        p_filterbuff[2 + i*8] =
                                (uint8_t)((id & 0xff00) >> 8);
                        p_filterbuff[3 + i*8] =
                                (uint8_t)(id & 0xff);

                        id = (p_hw_can->fi_rx[i].f_r2 >> 3);
                        p_filterbuff[4 + i*8] =
                                (uint8_t)((id & (~(uint32_t)0xffffff)) >> 24);
                        p_filterbuff[5 + i*8] =
                                (uint8_t)((id & 0xff0000) >> 16);
                        p_filterbuff[6 + i*8] =
                                (uint8_t)((id & 0xff00) >> 8);
                        p_filterbuff[7 + i*8] =
                                (uint8_t)(id & 0xff);



                     } else {
                        /* ��׼��ʶ�� */
                         id = (p_hw_can->fi_rx[i].f_r1 >> 21 );
                         p_filterbuff[2 + i*8] = (uint8_t)(id >> 8);
                         p_filterbuff[3 + i*8] = (uint8_t)(id & 0xff);

                         id = (p_hw_can->fi_rx[i].f_r2 >> 21 );
                         p_filterbuff[6 + i*8] = (uint8_t)(id >> 8);
                         p_filterbuff[7 + i*8] = (uint8_t)(id & 0xff);


                     }
                }

            /* �����������ڱ�ʶ������ģʽ�� */
            } else {


                /* ������λ��Ϊ2��16λ */
                if ((p_hw_can->fs_1r & (1ul << i)) == 0) {

                    id = ((p_hw_can->fi_rx[i].f_r1 & 0x7) << 11) |
                            ((p_hw_can->fi_rx[i].f_r1 & 0xffe0) >> 5);
                    p_filterbuff[0 + i*8] = id >> 8;
                    p_filterbuff[1 + i*8] = id & 0xff;
                    id_mask = ((p_hw_can->fi_rx[i].f_r1 >> 16) & 0x7 ) |
                            ((p_hw_can->fi_rx[i].f_r1 >> 16) & 0xfff8);
                    p_filterbuff[2 + i*8] = id_mask >> 8;
                    p_filterbuff[3 + i*8] = id_mask & 0xff;

                    id = ((p_hw_can->fi_rx[i].f_r2 & 0x7) << 11) |
                            ((p_hw_can->fi_rx[i].f_r2 & 0xffe0) >> 5);
                    p_filterbuff[4 + i*8] = id >> 8;
                    p_filterbuff[5 + i*8] = id & 0xff;
                    id_mask = ((p_hw_can->fi_rx[i].f_r2 >> 16) & 0x7 ) |
                            ((p_hw_can->fi_rx[i].f_r2 >> 16) & 0xfff8);
                    p_filterbuff[6 + i*8] = id_mask >> 8;
                    p_filterbuff[7 + i*8] = id_mask & 0xff;



                } else {
                    /* ������λ��Ϊ����32λ */
                    if (p_hw_can->fi_rx[i].f_r1 & 0x4) {
                        /* ��չ��ʶ�� */
                        id = (p_hw_can->fi_rx[i].f_r1 >> 3);
                        p_filterbuff[0 + i*8] =
                                (uint8_t)((id & (~(uint32_t)0xffffff)) >> 24);
                        p_filterbuff[1 + i*8] =
                                (uint8_t)((id & 0xff0000) >> 16);
                        p_filterbuff[2 + i*8] =
                                (uint8_t)((id & 0xff00) >> 8);
                        p_filterbuff[3 + i*8] =
                                (uint8_t)(id & 0xff);

                        id_mask = (p_hw_can->fi_rx[i].f_r2 >> 1);
                        p_filterbuff[4 + i*8] =
                                (uint8_t)(id_mask >> 24);
                        p_filterbuff[5 + i*8] =
                                (uint8_t)((id_mask & 0xff0000) >> 16);
                        p_filterbuff[6 + i*8] =
                                (uint8_t)((id_mask & 0xff00) >> 8);
                        p_filterbuff[7 + i*8] =
                                (uint8_t)(id_mask & 0xff);
                    } else {
                        /* ��׼��ʶ�� */
                        id = (p_hw_can->fi_rx[i].f_r1 >> 21 );
                        p_filterbuff[2 + i*8] =
                                (uint8_t)(id >> 8);
                        p_filterbuff[3 + i*8] =
                                (uint8_t)(id & 0xff);

                        id_mask = (p_hw_can->fi_rx[i].f_r2 >> 19 ) |
                                ((p_hw_can->fi_rx[i].f_r2 & 0x6) >> 1) ;
                        p_filterbuff[6 + i*8] =
                                (uint8_t)(id_mask >> 8);
                        p_filterbuff[7 + i*8] =
                                (uint8_t)(id_mask & 0xff);
                    }
                }
            }
        }
    }

    return AM_CAN_NOERROR;
}

static void __can_hk32f103rbt6_intcb_func_run (am_hk32f103rbt6_can_dev_t  *p_dev,
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
static void __can_hk32f103rbt6_int_handle (void *p_drv)
{
    am_hk32f103rbt6_can_dev_t    *p_dev     = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can  = NULL;

    if (NULL == p_drv) {
        return;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;


    /* �����жϲ���������rxfifo��Ϊ�� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_FMPIE0)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_FMPIE1))) {

        /* ִ�н��ջص����� */
        __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_RX);

        /*  */
        amhw_hk32f103rbt6_can_clear_itstatus(p_hw_can, AMHW_HK32F103RBT6_CAN_INT_FMPIE0);
        amhw_hk32f103rbt6_can_clear_itstatus(p_hw_can, AMHW_HK32F103RBT6_CAN_INT_FMPIE1);
    }

    /* �����жϲ��������ҷ������ */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_TMEIE))) {

        /* ִ�з��ͻص����� */
        __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_TX);
        amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can, AMHW_HK32F103RBT6_CAN_INT_TMEIE);
    }



    /* �����жϲ��� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_WKUIE))) {
        /* ִ�л����жϻص����� */
        __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_WAKE_UP);

        amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can, AMHW_HK32F103RBT6_CAN_INT_WKUIE);
    }

    /* ��������жϲ��� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_FOVIE0)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_FOVIE1)))  {

        /* ִ����������жϻص����� */
        __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_DATAOVER);

        /* �ͷ�FIFO  ���жϺ����д������  �ڴ˴��� FIFO  ���FIFO���� */
        for (int i = 0 ;i <3 ; i++) {
            p_hw_can->rf_0r |= AMHW_HK32F103RBT6_CAN_RF0R_RFOM0;
            p_hw_can->rf_1r |= AMHW_HK32F103RBT6_CAN_RF1R_RFOM1;
        }

        amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can, AMHW_HK32F103RBT6_CAN_INT_FOVIE0);
        amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can, AMHW_HK32F103RBT6_CAN_INT_FOVIE1);
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ���� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_ERRIE)))  {

        /* �ж������Ƿ����� */
        if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
                (AMHW_HK32F103RBT6_CAN_INT_BOFIE))) {

            /* ִ�����߹ر��жϻص����� */
            __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_BUS_OFF);

            amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can,
                                            AMHW_HK32F103RBT6_CAN_INT_ERRIE);
        } else if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
                (AMHW_HK32F103RBT6_CAN_INT_EWGIE))) {

           /* ִ�о����жϻص����� */
           __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_WARN);

           amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can,
                                           AMHW_HK32F103RBT6_CAN_INT_ERRIE);
        } else if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
                (AMHW_HK32F103RBT6_CAN_INT_EPVIE))) {

           /* ִ�о����жϻص����� */
           __can_hk32f103rbt6_intcb_func_run(p_dev, AM_CAN_INT_ERROR_PASSIVE);

           amhw_hk32f103rbt6_can_clear_itstatus (p_hw_can,
                                           AMHW_HK32F103RBT6_CAN_INT_ERRIE);
        }
    }
}

/**
 * \brief CAN ״̬
 */
am_can_err_t __can_hk32f103rbt6_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
    amhw_hk32f103rbt6_can_t      *p_hw_can = NULL;
    uint8_t                 err_code = 0;  /* ����� */
    uint8_t                 err      = 0;  /* ����Ĵ���ֵ */

    if (NULL == p_drv || NULL == p_int_type || NULL == p_bus_err) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    *p_int_type = 0;

    /* �����ж� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_FMPIE0)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            ( AMHW_HK32F103RBT6_CAN_INT_FMPIE1))) {

        *p_int_type |= AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_TMEIE))){
        *p_int_type |= AM_CAN_INT_TX;
    }

    /* ��������ж� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            ( AMHW_HK32F103RBT6_CAN_INT_FOVIE0)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            ( AMHW_HK32F103RBT6_CAN_INT_FOVIE1))) {

        *p_int_type |= AM_CAN_INT_DATAOVER;
    }

    /* �����ж� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_WKUIE))) {
        *p_int_type |= AM_CAN_INT_WAKE_UP;
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ�ж� */
    if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            ( AMHW_HK32F103RBT6_CAN_INT_ERRIE)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            ( AMHW_HK32F103RBT6_CAN_INT_EWGIE)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_EPVIE)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            (AMHW_HK32F103RBT6_CAN_INT_LECIE)) ||
        amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
            ( AMHW_HK32F103RBT6_CAN_INT_BOFIE)) )  {

        *p_int_type |= AM_CAN_INT_ERROR;

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ���������߹ر� */
        if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
                (AMHW_HK32F103RBT6_CAN_INT_BOFIE))) {
            *p_int_type |= AM_CAN_INT_BUS_OFF;
        }

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ�����Ĵ��󾯸� */
        if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
                (AMHW_HK32F103RBT6_CAN_INT_EWGIE))) {
            *p_int_type |= AM_CAN_INT_WARN;
        }

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ�����Ĵ��󱻶� */
        if (amhw_hk32f103rbt6_can_get_itstatus(p_hw_can,
                (AMHW_HK32F103RBT6_CAN_INT_EPVIE))) {
            *p_int_type |= AM_CAN_INT_ERROR_PASSIVE;
        }
    }

    /* �ӼĴ�����ȡ������� */
    *p_bus_err = 0;
    err        = amhw_hk32f103rbt6_can_get_lasterrorcode(p_hw_can);
    err_code = (err >> 4);

    /* ��ʽ���� */
    if (AMHW_HK32F103RBT6_CAN_LEC_FORMER == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_FORM;
    }

    /* ������ */
    if (AMHW_HK32F103RBT6_CAN_LEC_STUFER == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_STUFF;
    }

    /* δ֪����     ���Դ���   ���Դ���  ��������ô���*/
    if ((AMHW_HK32F103RBT6_CAN_LEC_SOFTER == err_code) ||
        (AMHW_HK32F103RBT6_CAN_LEC_BRCER  == err_code) ||
        (AMHW_HK32F103RBT6_CAN_LEC_BDERR  == err_code)) {
        *p_bus_err |= AM_CAN_BUS_ERR_UNKNOWN;
    }

    /* ACK���� */
    if (err_code == AMHW_HK32F103RBT6_CAN_LEC_ACKER) {
        *p_bus_err |= AM_CAN_BUS_ERR_ACK;
    }

    /* CRC���� */
    if (err_code == AMHW_HK32F103RBT6_CAN_LEC_CRCER) {
        *p_bus_err |= AM_CAN_BUS_ERR_CRC;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�����
 */
am_can_err_t __can_hk32f103rbt6_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;

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
        am_int_connect(INUM_USB_HP_CAN_TX, __can_hk32f103rbt6_int_handle, p_dev);
        am_int_connect(INUM_USB_HP_CAN_RX, __can_hk32f103rbt6_int_handle, p_dev);
        am_int_connect(INUM_CAN1_RX1, __can_hk32f103rbt6_int_handle, p_dev);
        am_int_connect(INUM_CAN1_SCE, __can_hk32f103rbt6_int_handle, p_dev);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ɾ���ж�����
 */
am_can_err_t __can_hk32f103rbt6_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;

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
        am_int_disconnect(INUM_USB_HP_CAN_TX, __can_hk32f103rbt6_int_handle, p_dev);
        am_int_disconnect(INUM_USB_HP_CAN_RX, __can_hk32f103rbt6_int_handle, p_dev);
        am_int_disconnect(INUM_CAN1_RX1, __can_hk32f103rbt6_int_handle, p_dev);
        am_int_disconnect(INUM_CAN1_SCE, __can_hk32f103rbt6_int_handle, p_dev);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϻص�����������
 */
am_can_err_t __can_hk32f103rbt6_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
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
am_can_err_t __can_hk32f103rbt6_intcb_disconnect (void              *p_drv,
                                            am_can_int_type_t  inttype)
{
    am_hk32f103rbt6_can_dev_t    *p_dev    = (am_hk32f103rbt6_can_dev_t *)p_drv;
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
am_can_handle_t am_hk32f103rbt6_can_init (am_hk32f103rbt6_can_dev_t      *p_dev,
                               const am_hk32f103rbt6_can_devinfo_t *p_devinfo)
{
    uint8_t             i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    p_dev->handle.p_drv_funcs = &__hk32f103rbt6_can_dev_func;
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
void am_hk32f103rbt6_can_deinit (am_can_handle_t handle)
{
    amhw_hk32f103rbt6_can_t *p_hw_can = NULL;
    am_hk32f103rbt6_can_dev_t  *p_dev = (am_hk32f103rbt6_can_dev_t *)handle->p_drv;

    if (NULL == p_dev) {
        return;
    }

    p_hw_can = (amhw_hk32f103rbt6_can_t *)p_dev->p_devinfo->regbase;

    amhw_hk32f103rbt6_can_operating_mode_request(p_hw_can,
            AMHW_HK32F103RBT6_CAN_OPERATING_MODE_INIT);

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
