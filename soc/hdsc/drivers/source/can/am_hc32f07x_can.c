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
 */

#include "am_int.h"
#include "am_can.h"
#include "am_hc32f07x_can.h"
#include "hw/amhw_hc32f07x_can.h"
#include "hc32f07x_inum.h"
#include "am_vdebug.h"
/** \brief CAN���� */
am_can_err_t __can_hc32f07x_start (void *p_drv);
/** \brief CAN��λ��ֹͣ�� */
am_can_err_t __can_hc32f07x_reset (void *p_drv);
///** \brief CAN����  */
//am_can_err_t __can_hc32f07x_sleep (void *p_drv);
///** \brief CAN���� */
//am_can_err_t __can_hc32f07x_wakeup (void *p_drv);
/** \brief �ж�ʹ�� */
am_can_err_t __can_hc32f07x_int_enable (void *p_drv, am_can_int_type_t int_mask);
/** \brief �жϽ���*/
am_can_err_t __can_hc32f07x_int_disable (void *p_drv, am_can_int_type_t int_mask);
/** \brief ģʽ���� */
am_can_err_t __can_hc32f07x_mode_set (void *p_drv, am_can_mode_type_t mode);
/** \brief ���������� */
am_can_err_t __can_hc32f07x_baudrate_set (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief �����ʻ�ȡ */
am_can_err_t __can_hc32f07x_baudrate_get (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief ��ȡ������� */
am_can_err_t __can_hc32f07x_err_cnt_get (void         *p_drv,
                                 am_can_err_cnt_t   *p_can_err_reg);
/** \brief ������Ϣ   */
am_can_err_t __can_hc32f07x_msg_send (void *p_drv, am_can_message_t *p_txmsg);
/** \brief ������Ϣ   */
am_can_err_t __can_hc32f07x_msg_recv (void *p_drv, am_can_message_t *p_rxmsg);
/** \brief ֹͣ������Ϣ   */
am_can_err_t __can_hc32f07x_stop_msg_snd (void *p_drv);

/** \brief CAN ״̬ */
am_can_err_t __can_hc32f07x_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err);
/** \brief �ж����� */
am_can_err_t __can_hc32f07x_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg);
/** \brief ɾ���ж����� */
am_can_err_t __can_hc32f07x_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg);
/** \brief �жϻص����������� */
am_can_err_t __can_hc32f07x_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg);


/** \brief ɾ���жϻص����������� */
am_can_err_t __can_hc32f07x_intcb_disconnect (void              *p_drv,
                                            am_can_int_type_t  inttype);

/** \brief �����˲����� (��չ)*/
am_can_err_t __can_hc32f07x_filter_tab_ext_set (void            *p_drv,
                                              am_can_filter_t *p_filterbuff,
                                              size_t           lenth);
/** \brief ��ȡ�˲����� (��չ)*/
am_can_err_t __can_hc32f07x_filter_tab_ext_get (void             *p_drv,
                                              am_can_filter_t  *p_filterbuff,
                                              size_t           *p_lenth);

struct am_can_drv_funcs __hc32f07x_can_dev_func = {
    __can_hc32f07x_start,
    __can_hc32f07x_reset,
    NULL,
    NULL,
    __can_hc32f07x_int_enable,
    __can_hc32f07x_int_disable,
    __can_hc32f07x_mode_set,
    __can_hc32f07x_baudrate_set,
    __can_hc32f07x_baudrate_get,
    __can_hc32f07x_err_cnt_get,
    NULL,
    __can_hc32f07x_msg_send,
    __can_hc32f07x_msg_recv,
    __can_hc32f07x_stop_msg_snd,
    NULL,
    NULL,
    __can_hc32f07x_status_get,
    __can_hc32f07x_connect,
    __can_hc32f07x_disconnect,
    __can_hc32f07x_intcb_connect,
    __can_hc32f07x_intcb_disconnect,
    __can_hc32f07x_filter_tab_ext_set,
    __can_hc32f07x_filter_tab_ext_get,
};

/**
 * \brief CAN��ʼ��
 */
uint8_t __can_hc32f07x_init (void *p_drv)
{
    am_hc32f07x_can_dev_t        *p_dev       = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t          *p_hw_can    = NULL;
    am_hc32f07x_can_init_info_t  *p_can_info  = NULL;
    uint8_t                     init_staus  = 0;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_can_info =(am_hc32f07x_can_init_info_t *)p_dev->p_devinfo->init_info;
    p_hw_can   =(amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    /* ʱ�䴥��ͨ�ŷ�ʽ�趨 */
    if(p_can_info->can_ttcm){
        amhw_hc32f07x_can_tt_enable(p_hw_can);
    }else {
        amhw_hc32f07x_can_tt_disable(p_hw_can);
    }

    /* ���ý��ջ��������ݴ洢ģʽ */
    if (p_can_info->rx_all) {
        amhw_hc32f07x_can_rxbuf_stores_all_set(p_hw_can,
                                               AMHW_HC32F07X_CAN_RXBUF_ALL);
    } else {
        amhw_hc32f07x_can_rxbuf_stores_all_set(p_hw_can,
                                              AMHW_HC32F07X_CAN_RXBUF_NORMAL);
    }

    /* ���ý��ջ���������ģʽ */
    if (p_can_info->over_mode) {
        amhw_hc32f07x_can_rxbuf_over_mode_set(p_hw_can,
                                            AMHW_HC32F07X_CAN_RXBUF_NOTSTORED);
    } else {
        amhw_hc32f07x_can_rxbuf_over_mode_set (p_hw_can,
                                          AMHW_HC32F07X_CAN_RXBUF_OVERWRITTEN);
    }

    /* ���û���������ģʽ */
    if (p_can_info->can_stb_mode) {
        amhw_hc32f07x_can_stb_mode_set(p_hw_can, 
                                       AMHW_HC32F07X_CAN_STB_MODE_PRIM);
    } else {
        amhw_hc32f07x_can_stb_mode_set(p_hw_can, 
                                       AMHW_HC32F07X_CAN_STB_MODE_FIFO);
    }

    /* ���ջ����������趨ֵ */
    amhw_hc32f07x_can_rxbuf_warning_set(p_hw_can, 
                                        p_can_info->warning_limitval);

    /* ���󾯸��޶�ֵ */
    amhw_hc32f07x_can_err_warning_set (p_hw_can, 
                                       p_can_info->error_warning_limitval);
    /* �ر������ж� */
    amhw_hc32f07x_can_int_all_disable (p_hw_can);

    return init_staus;
}


/**
 * \brief CAN����
 */
am_can_err_t __can_hc32f07x_start (void *p_drv)
{
am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* ��ʼ��CAN������Ϣ */
    __can_hc32f07x_init(p_drv);

    /* ʹ���ж� */
    am_int_enable(p_dev->p_devinfo->int_num );

    return AM_CAN_NOERROR;
}

/**
 * \brief CAN��λ��ֹͣ��
 */
am_can_err_t __can_hc32f07x_reset (void *p_drv)
{
    am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    /* ��CANǿ�Ƹ�λ */
    amhw_hc32f07x_can_reset_set (p_hw_can);


    /* �����ж� */
    am_int_disable(INUM_CAN);

    return AM_CAN_NOERROR;
}


/**
 * \brief �ж�ʹ��
 */
am_can_err_t __can_hc32f07x_int_enable (void *p_drv, am_can_int_type_t int_mask)
{
    am_hc32f07x_can_dev_t             *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t               *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    /* �����ж� */
    if (int_mask & AM_CAN_INT_RX) {

        /* ʹ�ܽ����ж� */
        amhw_hc32f07x_can_int_enable (p_hw_can, AMHW_HC32F07X_CAN_INT_RECV);

        int_mask &= ~AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_TX) {
			
        /* ʹ��PTB�����ж� */
        amhw_hc32f07x_can_int_enable (p_hw_can, AMHW_HC32F07X_CAN_INT_TX_PTB);

        /* ʹ��STB�����ж� */
        amhw_hc32f07x_can_int_enable (p_hw_can, AMHW_HC32F07X_CAN_INT_TX_STB);

        int_mask &= ~AM_CAN_INT_TX;
    }

    /* ����\�����ж�  */
    if ((int_mask & AM_CAN_INT_ERROR) || (int_mask & AM_CAN_INT_WARN)) {

        /* ʹ�ܴ����ж� */
        amhw_hc32f07x_can_int_enable(p_hw_can, AMHW_HC32F07X_CAN_INT_ERROR);

        /* ʹ�����ߴ����ж� */
        amhw_hc32f07x_can_int_enable(p_hw_can, AMHW_HC32F07X_CAN_INT_BUS_ERR);

        /* ʹ���ٲ�ʧ���ж� */
        amhw_hc32f07x_can_int_enable(p_hw_can, AMHW_HC32F07X_CAN_INT_ARBILOST);

        int_mask &= ~AM_CAN_INT_ERROR;
    }

    /* ���󱻶��ж�  */
    if ((int_mask & AM_CAN_INT_ERROR_PASSIVE)) {

        /* ʹ�ܴ��󱻶��ж�  */
        amhw_hc32f07x_can_int_enable (p_hw_can, AMHW_HC32F07X_CAN_INT_PASSIVE);

        int_mask &= ~AM_CAN_INT_ERROR_PASSIVE;
    }

    /* ���߳����ж� */
    if (int_mask & AM_CAN_INT_DATAOVER) {

        /* ʹ�ܽ��������ж�  */
        amhw_hc32f07x_can_int_enable(p_hw_can, AMHW_HC32F07X_CAN_INT_RX_OVER);

        /* ʹ�ܽ������ж�  */
        amhw_hc32f07x_can_int_enable(p_hw_can, AMHW_HC32F07X_CAN_INT_RX_FULL);

        /* ʹ�ܽ��ս����ж�  */
        amhw_hc32f07x_can_int_enable(p_hw_can, 
                                     AMHW_HC32F07X_CAN_INT_RX_ALMOSTFULL);

        int_mask &= ~AM_CAN_INT_DATAOVER;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϽ���
 */
am_can_err_t __can_hc32f07x_int_disable (void *p_drv, am_can_int_type_t int_mask)
{
    am_hc32f07x_can_dev_t         *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t           *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;


   /* �����ж� */
    if (int_mask & AM_CAN_INT_RX) {

        /* ���ܽ����ж� */
        amhw_hc32f07x_can_int_disable (p_hw_can, AMHW_HC32F07X_CAN_INT_RECV);

        int_mask &= ~AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (int_mask & AM_CAN_INT_TX) {

        /* ����PTB�����ж� */
        amhw_hc32f07x_can_int_disable (p_hw_can, AMHW_HC32F07X_CAN_INT_TX_PTB);

        /* ʹ��STB�����ж� */
        amhw_hc32f07x_can_int_disable (p_hw_can, AMHW_HC32F07X_CAN_INT_TX_STB);

        int_mask &= ~AM_CAN_INT_TX;
    }

    /* ����\�����ж�  */
   if ((int_mask & AM_CAN_INT_ERROR) || (int_mask & AM_CAN_INT_WARN)) {

        /* ���ܴ����ж� */
        amhw_hc32f07x_can_int_disable(p_hw_can, AMHW_HC32F07X_CAN_INT_ERROR);

        /* �������ߴ����ж� */
        amhw_hc32f07x_can_int_disable(p_hw_can, AMHW_HC32F07X_CAN_INT_BUS_ERR);

        /* �����ٲ�ʧ���ж� */
        amhw_hc32f07x_can_int_disable(p_hw_can, AMHW_HC32F07X_CAN_INT_ARBILOST);

        int_mask &= ~AM_CAN_INT_ERROR;
    }

    /* ���󱻶��ж�  */
    if ((int_mask & AM_CAN_INT_ERROR_PASSIVE)) {

        /* ���ܴ��󱻶��ж�  */
        amhw_hc32f07x_can_int_disable(p_hw_can, AMHW_HC32F07X_CAN_INT_PASSIVE);

        int_mask &= ~AM_CAN_INT_ERROR_PASSIVE;
    }

    /* ���߳����ж� */
    if (int_mask & AM_CAN_INT_DATAOVER) {

        /* ���ܽ��������ж�  */
        amhw_hc32f07x_can_int_disable(p_hw_can, AMHW_HC32F07X_CAN_INT_RX_OVER);

        /* ���ܽ������ж�  */
        amhw_hc32f07x_can_int_disable(p_hw_can, AMHW_HC32F07X_CAN_INT_RX_FULL);

        /* ���ܽ��ս����ж�  */
        amhw_hc32f07x_can_int_disable(p_hw_can, 
                                      AMHW_HC32F07X_CAN_INT_RX_ALMOSTFULL);

        int_mask &= ~AM_CAN_INT_DATAOVER;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ģʽ����
 */
am_can_err_t __can_hc32f07x_mode_set (void *p_drv, am_can_mode_type_t mode)
{
    am_hc32f07x_can_dev_t *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t   *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    if (AM_CAN_MODE_NROMAL == mode ) {

        /* ����ģʽ */
        amhw_hc32f07x_can_mode_disable (p_hw_can,
                                        AMHW_HC32F07X_CAN_LISTEN_ONLY_MODE);
        amhw_hc32f07x_can_mode_disable (p_hw_can,
                                        AMHW_HC32F07X_CAN_EXT_LOOPBACK_MODE);
        amhw_hc32f07x_can_mode_disable (p_hw_can,
                                        AMHW_HC32F07X_CAN_INT_LOOPBACK_MODE);
        amhw_hc32f07x_can_mode_disable (p_hw_can,
                                        AMHW_HC32F07X_CAN_SIG_PRIARY_MODE);
        amhw_hc32f07x_can_mode_disable (p_hw_can,
                                        AMHW_HC32F07X_CAN_SIG_SECONDARY_MODE);
    }else if (AM_CAN_MODE_LISTEN_ONLY == mode) {

        /* ��Ĭģʽ*/
        amhw_hc32f07x_can_mode_enable (p_hw_can,
                                       AMHW_HC32F07X_CAN_LISTEN_ONLY_MODE);
    }else {

        /* �ػ� �� �ػ���Ĭδ���� */
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ����������
 */
am_can_err_t __can_hc32f07x_baudrate_set (void           *p_drv,
                                 am_can_bps_param_t    *p_can_baudrate)
{
    am_hc32f07x_can_dev_t         *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t           *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    /* �����ʼĴ���ֻ�ڸ�λģʽ�¿ɽ��з��ʣ�����ǰ���븴λģʽ  */
    amhw_hc32f07x_can_reset_set(p_hw_can);

    /* ���� �����ʷ�Ƶ��   ͬ����ת���   ����λ�� */
    amhw_hc32f07x_can_brp_set(p_hw_can, p_can_baudrate->brp);
    amhw_hc32f07x_can_sjw_set(p_hw_can, p_can_baudrate->sjw);

    amhw_hc32f07x_can_tseg1_set(p_hw_can, p_can_baudrate->tesg1);
    amhw_hc32f07x_can_tseg2_set(p_hw_can, p_can_baudrate->tesg2);

    /* �˳���λģʽ */
    amhw_hc32f07x_can_reset_clr(p_hw_can);

    return AM_CAN_NOERROR;
}

/**
 * \brief �����ʻ�ȡ
 */
am_can_err_t __can_hc32f07x_baudrate_get (void           *p_drv,
                                 am_can_bps_param_t    *p_can_baudrate)
{
    am_hc32f07x_can_dev_t         *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t           *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* �����ʼĴ���ֻ�ڳ�ʼ��ģʽ�¿ɽ��з��ʣ�����ǰ�����ʼ��ģʽ  */
    amhw_hc32f07x_can_reset_set(p_hw_can);

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    p_can_baudrate->brp = amhw_hc32f07x_can_brp_get(p_hw_can);
    p_can_baudrate->sjw = amhw_hc32f07x_can_sjw_get(p_hw_can);

    p_can_baudrate->tesg1 = amhw_hc32f07x_can_tseg1_get(p_hw_can);
    p_can_baudrate->tesg2 = amhw_hc32f07x_can_tseg2_get(p_hw_can);

    amhw_hc32f07x_can_reset_set(p_hw_can);

    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�������
 */
am_can_err_t __can_hc32f07x_err_cnt_get (void        *p_drv,
                               am_can_err_cnt_t    *p_can_err_reg)
{
    am_hc32f07x_can_dev_t *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t   *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_can_err_reg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    /* �� TX/RX��������� */
    p_can_err_reg->rx_error_cnt = amhw_hc32f07x_can_get_recverrorcount(p_hw_can);
    p_can_err_reg->tx_error_cnt = amhw_hc32f07x_can_get_transerrorcount(p_hw_can);

    return AM_CAN_NOERROR;
}


/**
 * \brief ������Ϣ
 */
am_can_err_t __can_hc32f07x_msg_send (void *p_drv, am_can_message_t *p_txmsg)
{
    
    am_hc32f07x_can_dev_t    *p_dev     = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t      *p_hw_can  = NULL;
    amhw_hc32f07x_can_type_t  can_type;
    am_bool_t                 is_remote = AM_FALSE;
    am_bool_t                 is_extern = AM_FALSE;

    if (NULL == p_drv || NULL == p_txmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;
    can_type = p_dev->p_devinfo->type;

    /* �жϷ��ͻ������Ƿ��ͷ� */
    if (AMHW_HC32F07X_CAN_TB_FULL == amhw_hc32f07x_can_get_tb_status(p_hw_can)){
        return AM_CAN_INVALID_PARAMETER;
    }

    is_remote = ((p_txmsg->flags & AM_CAN_REMOTE_FLAG) ? AM_TRUE : AM_FALSE);
    is_extern = ((p_txmsg->flags & AM_CAN_EXTERN_FLAG) ? AM_TRUE : AM_FALSE);

    /* 8�ֽ����� */
    if (p_txmsg->msglen > 8) {
        p_txmsg->msglen = 8;
    }
    amhw_hc32f07x_can_txbuf_sel (p_hw_can,
                                 AMHW_HC32F07X_CAN_TXBUF_PTB);

    /* ��չ��ʶ�� */
    if (is_extern) {

        /* ������չ��ʶ��ID��IDEλ */
        p_hw_can->tbuf.tbuf0      = p_txmsg->id;
        p_hw_can->tbuf.txctrl.ide = 1;
    }else {

        /* ���ñ�׼��ʶ��ID��IDEλ */
        p_hw_can->tbuf.tbuf0      = p_txmsg->id;
        p_hw_can->tbuf.txctrl.ide = 0;
    }

    /* Զ�̱�־ */
    if (is_remote) {

        /* Զ��֡ */
        p_hw_can->tbuf.txctrl.rtr = 1;
    }else {

        /* ����֡ */
        p_hw_can->tbuf.txctrl.rtr = 0;
    }

    /* д�����ݳ��� */
    p_hw_can->tbuf.txctrl.dlc = p_txmsg->msglen;

    /* д������ */
    p_hw_can->tbuf.tbuf2 = p_txmsg->msgdata[3] << 24 |
                           p_txmsg->msgdata[2] << 16 |
                           p_txmsg->msgdata[1] << 8  |
                           p_txmsg->msgdata[0];
    p_hw_can->tbuf.tbuf3 = p_txmsg->msgdata[7] << 24 |
                           p_txmsg->msgdata[6] << 16 |
                           p_txmsg->msgdata[5] << 8  |
                           p_txmsg->msgdata[4];


    /* �������� */
    if(can_type == AMHW_HC32F07X_CAN_PTB){

        /* PTB�������� */
        amhw_hc32f07x_can_ptb_send_enable(p_hw_can);
    }else {

        /* STB�������� */
        if(p_txmsg->flags & AM_CAN_ONCE_SEND_FLAG){
            amhw_hc32f07x_can_stb_sendone_enable(p_hw_can);
        }else {
            amhw_hc32f07x_can_stb_sendall_enable(p_hw_can);
        }
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ������Ϣ
 */
am_can_err_t __can_hc32f07x_msg_recv (void *p_drv, am_can_message_t *p_rxmsg)
{
    am_hc32f07x_can_dev_t       *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t         *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_rxmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    /* ��ʼ�� */
    p_rxmsg->id     = 0;
    p_rxmsg->flags  = 0;
    p_rxmsg->msglen = 0;

    /* �жϽ��ջ������Ƿ�Ϊ�� */
    if (amhw_hc32f07x_can_get_rxbuf_status (p_hw_can)  == 
                                           AMHW_HC32F07X_CAN_RXBUF_FULL ) {
            return AM_CAN_NOERROR;
        }

    if (p_hw_can->rbuf.cst.ide == AMHW_HC32F07X_CAN_IDE_EXTENDED) {

        /* ʹ����չ��ʶ��  */
        p_rxmsg->flags |= AM_CAN_EXTERN_FLAG;

        /* ��ȡID */
        p_rxmsg->id     = p_hw_can->rbuf.rbuf0;

    } else {
        /* ʹ�ñ�׼��ʶ��  */

        /* ��ȡID */
        p_rxmsg->id     = p_hw_can->rbuf.rbuf0;
    }

    /* Զ��֡���� */
    if (p_hw_can->rbuf.cst.rtr == AMHW_HC32F07X_CAN_RTR_REMOTE) {

        /* Զ��֡ */
        p_rxmsg->flags |= AM_CAN_REMOTE_FLAG;
        p_rxmsg->msglen = 0;
    }

        /* ��ȡ�������ݳ���*/
    p_rxmsg->msglen = (uint8_t)0x0f &
                       p_hw_can->rbuf.cst.dlc;

    p_rxmsg->msgdata[3] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf2>>24;
    p_rxmsg->msgdata[2] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf2>>16;
    p_rxmsg->msgdata[1] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf2>>8;
    p_rxmsg->msgdata[0] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf2;

    p_rxmsg->msgdata[7] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf3>>24;
    p_rxmsg->msgdata[6] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf3>>16;
    p_rxmsg->msgdata[5] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf3>>8;
    p_rxmsg->msgdata[4] = (uint8_t)0xff &
                              p_hw_can->rbuf.rbuf3;
 
    /* �ͷŽ���BUF */
    amhw_hc32f07x_can_rxbuf_release (p_hw_can);

    return AM_CAN_NOERROR;
}

/**
 * \brief ֹͣ������Ϣ
 */
am_can_err_t __can_hc32f07x_stop_msg_snd (void *p_drv)
{
    am_hc32f07x_can_dev_t    *p_dev            = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t      *p_hw_can         = NULL;
    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    if(p_dev->p_devinfo->type == AMHW_HC32F07X_CAN_PTB){
        amhw_hc32f07x_can_ptb_abort_enable (p_hw_can);	
    }else {
        amhw_hc32f07x_can_stb_abort_enable (p_hw_can);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �����˲�����(��չ)
 */
am_can_err_t __can_hc32f07x_filter_tab_ext_set (void              *p_drv,
                                                am_can_filter_t   *p_filterbuff,
                                                size_t             lenth)
{
    am_hc32f07x_can_dev_t       *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t         *p_hw_can = NULL;
    uint8_t                      filt_num = 0;
    uint8_t                      filt_pos = 0;
    uint32_t                     id       = 0;
    uint32_t                     id_mask  = 0;
    am_can_err_t                 state    = AM_CAN_NOERROR;
    int                          i        = 0;
    if (NULL == p_drv || NULL == p_filterbuff || 0 == lenth || (lenth > 8)) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    amhw_hc32f07x_can_reset_set(p_hw_can);

    for ( i = 0; i < lenth; i++) {

        /* �˲������  */
        filt_num = i;

        if (filt_num > 7 ) {
            /* ������ǰ */
            state = AM_CAN_ILLEGAL_CHANNEL_NO;
            break;
        } else {
            /* �˲����� */
            filt_pos = (uint8_t)(1ul << filt_num);
        }

        /* �����˲���  */
        p_hw_can->acfen &= ~(uint32_t)filt_pos;

        if(p_filterbuff->ide == AM_CAN_FRAME_TYPE_STD){
            id      = (p_filterbuff->id[0] & 0x7ff);
            id_mask = (p_filterbuff->mask[0] & 0x7ff);
        }else {
            id      = (p_filterbuff->id[0] & 0x1fffffff);
            id_mask = (p_filterbuff->mask[0] & 0x1fffffff);
        }

        amhw_hc32f07x_can_filter_addr (p_hw_can,
                                       (amhw_hc32f07x_can_filter_t)filt_num);

        if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_STD) {

            /* ֻ���ձ�׼֡ */
            amhw_hc32f07x_can_ide_set (p_hw_can,
                                       AMHW_HC32F07X_CAN_AIDE_STD);
        }else if(p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
            amhw_hc32f07x_can_ide_set (p_hw_can,
                                       AMHW_HC32F07X_CAN_AIDE_EXT);
        }else {
            state = AM_CAN_INVALID_PARAMETER;
            return state;
        }
        /* �˲���id���� */
        amhw_hc32f07x_can_acf_select_set (p_hw_can, 
                                          AMHW_HC32F07X_CAN_ACF_ID);
        amhw_hc32f07x_can_filter_code_set (p_hw_can, id);

        /* �˲���mask���� */
        amhw_hc32f07x_can_acf_select_set (p_hw_can, 
                                          AMHW_HC32F07X_CAN_ACF_ID);
        amhw_hc32f07x_can_filter_code_set (p_hw_can, id_mask);

        /* �����˲���  */
            p_hw_can->acfen |= (uint32_t)filt_pos;

        /* �˲�������� */
        p_filterbuff++;
    }

    /* �л�������ģʽ */
    amhw_hc32f07x_can_reset_clr(p_hw_can);

    return state;
}


/**
 * \brief ��ȡ�˲�����
 */
am_can_err_t __can_hc32f07x_filter_tab_ext_get (void              *p_drv,
                                              am_can_filter_t   *p_filterbuff,
                                              size_t            *p_lenth)
{
    am_hc32f07x_can_dev_t         *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t           *p_hw_can = NULL;
    uint8_t                     filter_group = 0;
    int                         i = 0;
    if (NULL == p_drv ) {
        return AM_CAN_INVALID_PARAMETER;
    }


    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    filter_group = p_hw_can->acfen & 0xff;

    for (i = 0;i < 8;i++) {

        /* �жϵ�ǰ�˲������Ƿ񼤻� */
        if ( ( filter_group & ( (uint8_t)1ul<< i) ) ) {
            *p_lenth = *p_lenth + 1;
        } else {
            continue;
        }

        uint16_t reg_f_ide     = p_hw_can->acf >> 29;
        uint16_t reg_f_id      = p_hw_can->acf & 0x1fffffff;
        uint16_t reg_f_id_mask = p_hw_can->acf & 0x1fffffff;

        /* ֡��ʽ ֡���� */
        p_filterbuff->ide = (reg_f_ide & 0x01) ?
                            AM_CAN_FRAME_TYPE_EXT :
                            AM_CAN_FRAME_TYPE_STD;

        p_filterbuff->rtr = AM_CAN_FRAME_FORMAT_NOCARE;

        /* ��չ֡ */
        if (p_filterbuff->ide == AM_CAN_FRAME_TYPE_EXT) {
            p_filterbuff->id[0]   = (reg_f_id );
            p_filterbuff->mask[0] = (reg_f_id_mask );
        } else {
           /* ��׼֡ */
           p_filterbuff->id[0]   = reg_f_id & 0x7ff;
           p_filterbuff->mask[0] = reg_f_id_mask & 0x7ff;
        }

        p_filterbuff++;
    }
    return AM_CAN_NOERROR;
}


static void __can_hc32f07x_intcb_func_run (am_hc32f07x_can_dev_t  *p_dev,
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
static void __can_hc32f07x_int_handle (void *p_drv)
{
    am_hc32f07x_can_dev_t    *p_dev     = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t      *p_hw_can  = NULL;

    if (NULL == p_drv) {
        return;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;


    /* �����жϲ���������rxfifo��Ϊ�� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_RECV)) {

        /* ִ�н��ջص����� */
        __can_hc32f07x_intcb_func_run(p_dev, AM_CAN_INT_RX);

        /* ��־��� */
        amhw_hc32f07x_can_irq_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_RECV);
    }

    /* �����жϲ��������ҷ������ */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                           AMHW_HC32F07X_CAN_FLAG_TX_PTB)||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                           AMHW_HC32F07X_CAN_FLAG_TX_STB)) {

        /* ִ�з��ͻص����� */
        __can_hc32f07x_intcb_func_run(p_dev, AM_CAN_INT_TX);

        /* ��־��� */
        amhw_hc32f07x_can_irq_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_TX_PTB);
        amhw_hc32f07x_can_irq_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_TX_STB);
    }

    /* ��������жϲ��� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                           AMHW_HC32F07X_CAN_FLAG_RX_OVER))  {

        /* ִ����������жϻص����� */
        __can_hc32f07x_intcb_func_run(p_dev, AM_CAN_INT_DATAOVER);

        amhw_hc32f07x_can_irq_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_RX_OVER);
    }

    /* ���󱻶��ж� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                        AMHW_HC32F07X_CAN_ERR_FLAG_PASSIVE)) {

        /* ִ�о����жϻص����� */
        __can_hc32f07x_intcb_func_run(p_dev, AM_CAN_INT_ERROR_PASSIVE);

        amhw_hc32f07x_can_irq_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_ERR_FLAG_PASSIVE);
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ���� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_ERROR) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                        AMHW_HC32F07X_CAN_ERR_FLAG_ARBILOST) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                        AMHW_HC32F07X_CAN_ERR_FLAG_BUS_ERR) ) {

        /* �ж������Ƿ����� */
        if (amhw_hc32f07x_can_status_get (p_hw_can, 
                                       AMHW_HC32F07X_CAN_FLAG_BUSOFF_ACTIVE)) {

            /* ִ�����߹ر��жϻص����� */
            __can_hc32f07x_intcb_func_run(p_dev, AM_CAN_INT_BUS_OFF);

            amhw_hc32f07x_can_err_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_ERR_FLAG_BUS_ERR);
        } else {

           /* ִ�д����жϻص����� */
            __can_hc32f07x_intcb_func_run(p_dev, AM_CAN_INT_ERROR);

            amhw_hc32f07x_can_irq_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_ERROR);
            amhw_hc32f07x_can_err_status_clr (p_hw_can,
                                          AMHW_HC32F07X_CAN_ERR_FLAG_ARBILOST);
        }
    }
}

/**
 * \brief CAN ״̬
 */
am_can_err_t __can_hc32f07x_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err)
{
    am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
    amhw_hc32f07x_can_t      *p_hw_can = NULL;
    uint8_t                 err      = 0;  /* ����Ĵ���ֵ */

    if (NULL == p_drv || NULL == p_int_type || NULL == p_bus_err) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    *p_int_type = 0;

    /* �����ж� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_RECV)) {

        *p_int_type |= AM_CAN_INT_RX;
    }

    /* �����ж� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_TX_PTB) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_TX_STB)) {
        *p_int_type |= AM_CAN_INT_TX;
    }

    /* ��������ж� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_RX_OVER)) {

        *p_int_type |= AM_CAN_INT_DATAOVER;
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ�ж� */
    if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                          AMHW_HC32F07X_CAN_FLAG_ERROR) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                   AMHW_HC32F07X_CAN_ERR_FLAG_ARBILOST) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                    AMHW_HC32F07X_CAN_ERR_FLAG_PASSIVE) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                    AMHW_HC32F07X_CAN_ERR_FLAG_BUS_ERR) ||
        amhw_hc32f07x_can_get_irq_status (p_hw_can,
                                    AMHW_HC32F07X_CAN_ERR_FLAG_EWARN))  {

        *p_int_type |= AM_CAN_INT_ERROR;

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ���������߹ر� */
        if (amhw_hc32f07x_can_status_get (p_hw_can, 
                                  AMHW_HC32F07X_CAN_FLAG_BUSOFF_ACTIVE)) {
            *p_int_type |= AM_CAN_INT_BUS_OFF;
        }

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ�����Ĵ��󾯸� */
        if (amhw_hc32f07x_can_get_err_status (p_hw_can,
                                 AMHW_HC32F07X_CAN_ERR_FLAG_EWARN)) {
            *p_int_type |= AM_CAN_INT_WARN;
        }

        /* �ж��Ƿ�����Ϊ����������ﵽ���ƶ�����Ĵ��󱻶� */
        if (amhw_hc32f07x_can_get_irq_status (p_hw_can,
                           AMHW_HC32F07X_CAN_ERR_FLAG_PASSIVE)) {
            *p_int_type |= AM_CAN_INT_ERROR_PASSIVE;
        }
    }

    /* �ӼĴ�����ȡ������� */
    *p_bus_err = 0;
    err        = amhw_hc32f07x_can_error_status_get (p_hw_can );

    /* ��ʽ���� */
    if (AMHW_HC32F07X_CAN_ERROR_FORM == err) {
        *p_bus_err |= AM_CAN_BUS_ERR_FORM;
    }

    /* ������ */
    if (AMHW_HC32F07X_CAN_ERROR_STUFF == err) {
        *p_bus_err |= AM_CAN_BUS_ERR_STUFF;
    }

    /* δ֪����     ���Դ���   ���Դ���  ��������ô���*/
    if (AMHW_HC32F07X_CAN_ERROR_UNKOWN  == err) {
        *p_bus_err |= AM_CAN_BUS_ERR_UNKNOWN;
    }
		
		/* λ���� */
    if (AMHW_HC32F07X_CAN_ERROR_BIT == err) {
        *p_bus_err |= AM_CAN_BUS_ERR_BIT;
    }

    /* ACK���� */
    if (err == AMHW_HC32F07X_CAN_ERROR_ACK) {
        *p_bus_err |= AM_CAN_BUS_ERR_ACK;
    }

    /* CRC���� */
    if (err == AMHW_HC32F07X_CAN_ERROR_CRC) {
        *p_bus_err |= AM_CAN_BUS_ERR_CRC;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�����
 */
am_can_err_t __can_hc32f07x_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg)
{
    am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    if (NULL != pfn_isr) {
        /* ���Ӵ��뺯�� */
        am_int_connect(p_dev->p_devinfo->int_num, pfn_isr, p_arg);
    } else {
        /* ����Ĭ�Ϻ��� */
        am_int_connect(p_dev->p_devinfo->int_num, __can_hc32f07x_int_handle, p_dev);

    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ɾ���ж�����
 */
am_can_err_t __can_hc32f07x_disconnect (void         *p_drv,
                                        am_pfnvoid_t  pfn_isr,
                                        void         *p_arg)
{
    am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    /* �жϽ��� */
    am_int_disable(p_dev->p_devinfo->int_num);

    if (NULL != pfn_isr) {
        /* ɾ�����Ӻ��� */
        am_int_disconnect(p_dev->p_devinfo->int_num, pfn_isr, p_arg);

    } else {
        /* ɾ�����Ӻ��� */
        am_int_disconnect(p_dev->p_devinfo->int_num, __can_hc32f07x_int_handle, p_dev);

    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϻص�����������
 */
am_can_err_t __can_hc32f07x_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg)
{
    am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
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
am_can_err_t __can_hc32f07x_intcb_disconnect (void              *p_drv,
                                            am_can_int_type_t  inttype)
{
    am_hc32f07x_can_dev_t    *p_dev    = (am_hc32f07x_can_dev_t *)p_drv;
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
am_can_handle_t am_hc32f07x_can_init (am_hc32f07x_can_dev_t      *p_dev,
                               const am_hc32f07x_can_devinfo_t *p_devinfo)
{
    uint8_t             i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    p_dev->handle.p_drv_funcs = &__hc32f07x_can_dev_func;
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
void am_hc32f07x_can_deinit (am_can_handle_t handle)
{
    amhw_hc32f07x_can_t *p_hw_can = NULL;
    am_hc32f07x_can_dev_t  *p_dev = (am_hc32f07x_can_dev_t *)handle->p_drv;

    if (NULL == p_dev) {
        return;
    }

    p_hw_can = (amhw_hc32f07x_can_t *)p_dev->p_devinfo->regbase;

    amhw_hc32f07x_can_reset_set(p_hw_can);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

    /* �жϽ��� */
    am_int_disable(p_dev->p_devinfo->int_num);

}

/* end of file */
