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
 * - 1.00 17-09-05  zcb, first implementation.
 * - 1.01 19-12-18  zc , add filter table extern api
 * \endinternal
 */

#include "am_int.h"

#include "am_hc32f460_can.h"
#include "hw/amhw_hc32f460_can.h"
#include "string.h"
/** \brief CAN���� */
am_can_err_t __can_start (void *p_drv);
/** \brief CAN��λ��ֹͣ�� */
am_can_err_t __can_reset (void *p_drv);
/** \brief CAN����  */
am_can_err_t __can_sleep (void *p_drv);
/** \brief CAN���� */
am_can_err_t __can_wakeup (void *p_drv);
/** \brief �ж�ʹ�� */
am_can_err_t __can_int_enable (void *p_drv, am_can_int_type_t int_mask);
/** \brief �жϽ���*/
am_can_err_t __can_int_disable (void *p_drv, am_can_int_type_t int_mask);
/** \brief ģʽ���� */
am_can_err_t __can_mode_set (void *p_drv, am_can_mode_type_t mode);
/** \brief ���������� */
am_can_err_t __can_baudrate_set (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief �����ʻ�ȡ */
am_can_err_t __can_baudrate_get (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate);
/** \brief ��ȡ������� */
am_can_err_t __can_err_cnt_get (void *p_drv, am_can_err_cnt_t *p_can_err_reg);
/** \brief ���������� */
am_can_err_t __can_err_cnt_clr (void *p_drv);
/** \brief ������Ϣ   */
am_can_err_t __can_msg_send (void *p_drv, am_can_message_t *p_txmsg);
/** \brief ������Ϣ   */
am_can_err_t __can_msg_recv (void *p_drv, am_can_message_t *p_rxmsg);
/** \brief ֹͣ������Ϣ   */
am_can_err_t __can_stop_msg_snd (void *p_drv);
/** \brief �����˲����� */
am_can_err_t __can_filter_tab_set (void    *p_drv,
                                   uint8_t *p_filterbuff,
                                   size_t   lenth);
/** \brief ��ȡ�˲�����*/
am_can_err_t __can_filter_tab_get (void    *p_drv,
                                   uint8_t *p_filterbuff,
                                   size_t  *p_lenth);
/** \brief CAN ״̬ */
am_can_err_t __can_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err);
/** \brief �ж����� */
am_can_err_t __can_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg);
/** \brief ɾ���ж����� */
am_can_err_t __can_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg);
/** \brief �жϻص����������� */
am_can_err_t __can_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg);
/** \brief ɾ���жϻص����������� */
am_can_err_t __can_intcb_disconnect (void *p_drv, am_can_int_type_t  inttype);

/** \brief �����˲�����(��չ) */
am_can_err_t __can_filter_tab_ext_set (void             *p_drv,
                                       am_can_filter_t  *p_filterbuff,
                                       size_t            lenth);

/** \brief ��ȡ�˲�����(��չ) */
am_can_err_t __can_filter_tab_ext_get (void             *p_drv,
                                       am_can_filter_t  *p_filterbuff,
                                       size_t           *p_lenth);
struct am_can_drv_funcs dev_func = {
    __can_start,
    __can_reset,
    __can_sleep,
    __can_wakeup,
    __can_int_enable,
    __can_int_disable,
    __can_mode_set,
    __can_baudrate_set,
    __can_baudrate_get,
    __can_err_cnt_get,
    __can_err_cnt_clr,
    __can_msg_send,
    __can_msg_recv,
    __can_stop_msg_snd,
    __can_filter_tab_set,
    __can_filter_tab_get,
    __can_status_get,
    __can_connect,
    __can_disconnect,
    __can_intcb_connect,
    __can_intcb_disconnect,
    __can_filter_tab_ext_set,
    __can_filter_tab_ext_get
};


/**
 * \brief CAN����
 */
am_can_err_t __can_start (void *p_drv)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    amhw_hc32f460_can_irq_cmd(p_hw_can, CanRxIrqEn, CanEnable);

    return AM_CAN_NOERROR;
}

/**
 * \brief CAN��λ��ֹͣ��
 */
am_can_err_t __can_reset (void *p_drv)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief CAN����
 */
am_can_err_t __can_sleep (void *p_drv)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief CAN����
 */
am_can_err_t __can_wakeup (void *p_drv)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�ʹ��
 */
am_can_err_t __can_int_enable (void *p_drv, am_can_int_type_t int_mask)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief �жϽ���
 */
am_can_err_t __can_int_disable (void *p_drv, am_can_int_type_t int_mask)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief ģʽ����
 */
am_can_err_t __can_mode_set (void *p_drv, am_can_mode_type_t mode)
{
    am_hc32f460_can_dev_t *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t   *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    if (AM_CAN_MODE_NROMAL == mode) {

        /* ����ģʽ */
        amhw_hc32f460_can_mode_config(p_hw_can, CanListenOnlyMode, CanDisable);

    } else if ((AM_CAN_MODE_LISTEN_ONLY == mode) &&
                 (p_dev->p_devinfo->type == AMHW_HC32F460_CAN_PELI_CAN)) {

        /* ֻ��ģʽ */
        amhw_hc32f460_can_mode_config(p_hw_can, CanListenOnlyMode, CanEnable);
    } else {
        /* basic can��ֻ��ģʽ */
        return AM_CAN_INVALID_PARAMETER;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ����������
 */
am_can_err_t __can_baudrate_set (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;
    stc_can_init_config_t   stcCanInitCfg;
    
    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;        
    memset(&stcCanInitCfg, 0, sizeof(stcCanInitCfg));

    stcCanInitCfg.stcCanBt.PRESC = p_can_baudrate->brp;
    stcCanInitCfg.stcCanBt.SEG_1 = p_can_baudrate->tesg1;
    stcCanInitCfg.stcCanBt.SEG_2 = p_can_baudrate->tesg2;
    stcCanInitCfg.stcCanBt.SJW   = p_can_baudrate->sjw;
    stcCanInitCfg.stcWarningLimit.CanErrorWarningLimitVal = 10u;
    stcCanInitCfg.stcWarningLimit.CanWarningLimitVal = 16u-1u;
    stcCanInitCfg.enCanRxBufAll  = CanRxNormal;
    stcCanInitCfg.enCanRxBufMode = CanRxBufNotStored;
    stcCanInitCfg.enCanSAck      = CanSelfAckEnable;
    stcCanInitCfg.enCanSTBMode   = CanSTBFifoMode;

    amhw_hc32f460_can_lowlevel_set(p_hw_can, &stcCanInitCfg);

    return AM_CAN_NOERROR;
}

/**
 * \brief �����ʻ�ȡ
 */
am_can_err_t __can_baudrate_get (void               *p_drv,
                                 am_can_bps_param_t *p_can_baudrate)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;
    stc_can_init_config_t   stcCanInitCfg;
    
    if (NULL == p_drv || NULL == p_can_baudrate) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;
    memset(&stcCanInitCfg, 0, sizeof(stcCanInitCfg));

    amhw_hc32f460_can_lowlevel_get(p_hw_can, &stcCanInitCfg);
    
    p_can_baudrate->brp = stcCanInitCfg.stcCanBt.PRESC;
    p_can_baudrate->sjw = stcCanInitCfg.stcCanBt.SJW;
    p_can_baudrate->tesg1 = stcCanInitCfg.stcCanBt.SEG_1;
    p_can_baudrate->tesg2 = stcCanInitCfg.stcCanBt.SEG_2;

    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�������
 */
am_can_err_t __can_err_cnt_get (void *p_drv, am_can_err_cnt_t *p_can_err_reg)
{
    am_hc32f460_can_dev_t *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t   *p_hw_can = NULL;

    if (NULL == p_drv || NULL == p_can_err_reg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    /* �� CAN TX/RX��������� */
    p_can_err_reg->rx_error_cnt = amhw_hc32f460_can_rx_error_cnt_get(p_hw_can);
    p_can_err_reg->tx_error_cnt = amhw_hc32f460_can_tx_error_cnt_get(p_hw_can);

    return AM_CAN_NOERROR;
}

/**
 * \brief ����������
 */
am_can_err_t __can_err_cnt_clr (void *p_drv)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    amhw_hc32f460_can_rx_error_cnt_clr(p_hw_can);
    amhw_hc32f460_can_tx_error_cnt_clr(p_hw_can);
    
    return AM_CAN_NOERROR;
}

/**
 * \brief ������Ϣ
 */
am_can_err_t __can_msg_send (void *p_drv, am_can_message_t *p_txmsg)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;
    uint8_t u8Idx = 0u;
    stc_can_txframe_t       stcTxFrame;

    if (NULL == p_drv || NULL == p_txmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    memset(&stcTxFrame, 0, sizeof(stcTxFrame));

    stcTxFrame.TBUF32_0      = p_txmsg->id;
    stcTxFrame.Control_f.DLC = p_txmsg->msglen;

    if (p_txmsg->flags & AM_CAN_REMOTE_FLAG) {
        stcTxFrame.Control_f.RTR = 1;
    }

    if (p_txmsg->flags & AM_CAN_EXTERN_FLAG) {
        stcTxFrame.Control_f.IDE = 1;
    }
    
    for(u8Idx = 0u; u8Idx < p_txmsg->msglen; u8Idx++)
    {
        stcTxFrame.Data[u8Idx] = p_txmsg->msgdata[u8Idx];
    }
    
    amhw_hc32f460_can_set_frame(p_hw_can, &stcTxFrame);
    amhw_hc32f460_can_transmit_cmd(p_hw_can, CanPTBTxCmd);
    
    return AM_CAN_NOERROR;
}


/**
 * \brief ������Ϣ
 */
am_can_err_t __can_msg_recv (void *p_drv, am_can_message_t *p_rxmsg)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;
    uint8_t                  i;
    stc_can_rxframe_t       stcRxFrame;

    if (NULL == p_drv || NULL == p_rxmsg) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    /* ��ʼ�� */
    p_rxmsg->id     = 0;
    p_rxmsg->flags  = 0;
    p_rxmsg->msglen = 0;
    memset(&stcRxFrame, 0, sizeof(stcRxFrame));
    
    /* �жϽ��ջ������Ƿ�Ϊ�� */
    if(AM_FALSE == amhw_hc32f460_can_irq_flag_get(p_hw_can, CanRxIrqFlg)) {
        return AM_CAN_NOERROR;
    }

    amhw_hc32f460_can_irq_flag_clr(p_hw_can, CanRxIrqFlg);
    
    amhw_hc32f460_can_receive(p_hw_can, &stcRxFrame);
    p_rxmsg->id = stcRxFrame.RBUF32_0;
    
    if(1u == stcRxFrame.Cst.Control_f.RTR)
    {
        p_rxmsg->flags |= AM_CAN_REMOTE_FLAG;
        p_rxmsg->msglen = 0;
        return AM_CAN_NOERROR;
    }  
    
    if(1u == stcRxFrame.Cst.Control_f.IDE)    {
        p_rxmsg->flags |= AM_CAN_EXTERN_FLAG;
    }  
    
    p_rxmsg->msglen = stcRxFrame.Cst.Control_f.DLC;
    /* ��ȡ���� */
    for (i = 0 ; i < p_rxmsg->msglen ; i++) {
        p_rxmsg->msgdata[i] = stcRxFrame.Data[i];
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ֹͣ������Ϣ
 */
am_can_err_t __can_stop_msg_snd (void *p_drv)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;
   
    amhw_hc32f460_can_transmit_cmd(p_hw_can, CanPTBTxAbortCmd);
    amhw_hc32f460_can_transmit_cmd(p_hw_can, CanSTBTxAbortCmd);
   
    return AM_CAN_NOERROR;
}

/**
 * \brief �����˲�����
 */
am_can_err_t __can_filter_tab_set (void    *p_drv,
                                   uint8_t *p_filterbuff,
                                   size_t   lenth)
{
    am_hc32f460_can_dev_t    *p_dev     = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can  = NULL;
    stc_can_filter_t        stcFilter;
    if (NULL == p_drv || NULL == p_filterbuff || 0 == lenth) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;

    /* Can filter config */
    stcFilter.enAcfFormat = CanAllFrames;
    stcFilter.enFilterSel = CanFilterSel1;
    stcFilter.u32CODE     = 0x00000000ul;
    stcFilter.u32MASK     = 0x1FFFFFFFul;
    amhw_hc32f460_can_filter_config(p_hw_can, &stcFilter, CanEnable);

    return AM_CAN_NOERROR;
}

/**
 * \brief �����˲�����(��չ) ֻ��һ���˲��� ��֧����չ�ͱ�׼������λ
 */
am_can_err_t __can_filter_tab_ext_set (void             *p_drv,
                                       am_can_filter_t  *p_filterbuff,
                                       size_t            lenth)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�˲�����
 */
am_can_err_t __can_filter_tab_get (void    *p_drv,
                                   uint8_t *p_filterbuff,
                                   size_t  *p_lenth)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief ��ȡ�˲�����(��չ) �����޷��б��������չ���Ǳ�׼֡
 *  ���ñ�׼֡����չ֡�ֱ����
 */

am_can_err_t __can_filter_tab_ext_get (void             *p_drv,
                                       am_can_filter_t  *p_filterbuff,
                                       size_t           *p_lenth)
{
    return AM_CAN_NOERROR;
}

/**
 * \brief can�жϷ�����
 */
static void __can_int_handle (void *p_drv)
{

}

/**
 * \brief CAN ״̬
 */
am_can_err_t __can_status_get (void              *p_drv,
                               am_can_int_type_t *p_int_type,
                               am_can_bus_err_t  *p_bus_err)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
    amhw_hc32f460_can_t      *p_hw_can = NULL;
    uint8_t                  int_flags = 0;  /* �жϱ�־ */
    uint8_t                  err_code  = 0;  /* ����� */

    if (NULL == p_drv || NULL == p_int_type || NULL == p_bus_err) {
        return AM_CAN_INVALID_PARAMETER;
    }

    p_hw_can = (amhw_hc32f460_can_t *)p_dev->p_devinfo->regbase;
    
    int_flags = amhw_hc32f460_can_int_status_get(p_hw_can);

    *p_int_type = 0;

    /* �����ж� */
    if (int_flags & AMHW_HC32F460_CAN_INT_RECV) {
        *p_int_type |= AM_CAN_INT_RX;
    }

    /* �����ж� */
    if ((int_flags & AMHW_HC32F460_CAN_INT_PTB_TRAN) || (int_flags & AMHW_HC32F460_CAN_INT_STB_TRAN)) {
        *p_int_type |= AM_CAN_INT_TX;
    }

    /* ��������ж� */
    if (int_flags & AMHW_HC32F460_CAN_INT_OVER) {
        *p_int_type |= AM_CAN_INT_DATAOVER;
    }

    /* �����жϡ����ߴ����жϡ������ٲö�ʧ�ж� */
    if ((int_flags & AMHW_HC32F460_CAN_INT_ERR)) {

        *p_int_type |= AM_CAN_INT_ERROR;
    }
    
    if (AM_TRUE == amhw_hc32f460_can_status_get(p_hw_can, CanBusoff)) {
        *p_int_type |= AM_CAN_INT_BUS_OFF;
    }
   
////////////////////////////////////////////////////////////////////////////////
    /* �ӼĴ�����ȡ������� */
    *p_bus_err = 0;
    err_code  = amhw_hc32f460_can_error_status_get(p_hw_can);

    /* ���ش��� */
    if (BIT_ERROR == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_BIT;
    }

    /* ��ʽ���� */
    if (FORM_ERROR == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_FORM;
    }

    /* ������ */
    if (STUFF_ERROR == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_STUFF;
    }

    /* δ֪���� */
    if (UNKOWN_ERROR == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_UNKNOWN;
    }

    /* ACK���� */
    if (ACK_ERROR == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_ACK;
    }

    /* CRC���� */
    if (CRC_ERROR == err_code) {
        *p_bus_err |= AM_CAN_BUS_ERR_CRC;
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �ж�����
 */
am_can_err_t __can_connect (void         *p_drv,
                            am_pfnvoid_t  pfn_isr,
                            void         *p_arg)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;

    if (NULL == p_drv) {
        return AM_CAN_INVALID_PARAMETER;
    }

    if (NULL != pfn_isr) {
        /* ���Ӵ��뺯�� */
        am_int_connect(p_dev->p_devinfo->int_num, pfn_isr, p_arg);
    } else {
        /* ����Ĭ�Ϻ��� */
        am_int_connect(p_dev->p_devinfo->int_num, __can_int_handle, p_dev);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief ɾ���ж�����
 */
am_can_err_t __can_disconnect (void         *p_drv,
                               am_pfnvoid_t  pfn_isr,
                               void         *p_arg)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;

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
        am_int_disconnect(p_dev->p_devinfo->int_num, __can_int_handle, p_dev);
    }

    return AM_CAN_NOERROR;
}

/**
 * \brief �жϻص�����������
 */
am_can_err_t __can_intcb_connect (void              *p_drv,
                                  am_can_int_type_t  inttype,
                                  am_pfnvoid_t       pfn_callback,
                                  void              *p_arg)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
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
am_can_err_t __can_intcb_disconnect (void *p_drv, am_can_int_type_t  inttype)
{
    am_hc32f460_can_dev_t    *p_dev    = (am_hc32f460_can_dev_t *)p_drv;
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
am_can_handle_t am_hc32f460_can_init (am_hc32f460_can_dev_t           *p_dev,
                               const am_hc32f460_can_devinfo_t *p_devinfo)
{
    uint8_t             i = 0;
    if (NULL == p_dev || NULL == p_devinfo) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    p_dev->handle.p_drv_funcs = &dev_func;
    p_dev->handle.p_drv       = (void *)p_dev;

    p_dev->mode               = AMHW_HC32F460_CAN_MODE_RESET;

    for (i = 0 ; i < p_devinfo->p_intcb_num ; i++) {
        p_devinfo->p_intcb_info[i].pfn_callback = NULL;
        p_devinfo->p_intcb_info[i].p_arg        = NULL;
    }

    return (am_can_handle_t)&(p_dev->handle);
}

/**
 * \brief ���ʼ��
 */
void am_hc32f460_can_deinit (am_can_handle_t handle)
{
    am_hc32f460_can_dev_t  *p_dev = (am_hc32f460_can_dev_t *)handle->p_drv;

    if (NULL == p_dev) {
        return;
    }

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

    /* �жϽ��� */
    am_int_disable(p_dev->p_devinfo->int_num);
}

/* end of file */
