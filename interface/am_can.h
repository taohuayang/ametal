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
 * \brief  CAN��׼�ӿ�ʵ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-06-02  anu, first implementation.
 * - 1.01 19-12-18  zc , add filter table extern api
 * \endinternal
 */
 

#ifndef __AM_CAN_H
#define __AM_CAN_H

#ifdef __cplusplus
extern "C" {
#endif
    

#include "am_types.h"

/** 
 * \addtogroup am_if_can
 * \copydoc am_can.h
 * @{
 */

/**
 * \name CAN��־�Ķ���
 * \anchor grp_am_can_flag
 * @{
 */

/** \brief flags ������Ϣ�ı�־
 * -----------------------------------------------------------
 * | 15:10                             | 9:8 controller type |
 * -----------------------------------------------------------
 * -----------------------------------------------------------
 * | 7:reseverd |6:reseverd | 5:SEF | 4:SDF | 3 : 0 sendtype |
 * -----------------------------------------------------------
 * bit7:reseverd ����
 * bit6:reseverd ����
 * bit5:SEF ֡��ʽ (1:extended��չ֡ 0:std ��׼֡)
 * bit4:SDF ֡���� (1:remoteԶ��֡   0:data����֡)
 * bit0~3:��������  (sendtype:���궨��)
 */
typedef uint16_t am_can_flag_t;            /**< \brief CAN��־             */
#define AM_CAN_NORMAL_SEND_FLAG     0X00   /**< \brief ��������           */
#define AM_CAN_ONCE_SEND_FLAG       0X01   /**< \brief ���η���           */
#define AM_CAN_SELF_SEND_FLAG       0X02   /**< \brief �Է�����           */
#define AM_CAN_SELFONCE_SEND_FLAG   0X03   /**< \brief �����Է����� */
#define AM_CAN_REMOTE_FLAG		    0X10   /**< \brief Զ��֡��־λ */
#define AM_CAN_EXTERN_FLAG		    0X20   /**< \brief ��չ֡��־λ */
#define AM_CAN_FD_CTRL_FLAG         0x0100 /**< \brief CANFD��־λ   */

/** @} */

/** \brief CAN ���շ��� ��Ϣ  */
typedef struct am_can_message {
	uint32_t	     id;                    /**< \brief id ֡ID              */
    am_can_flag_t    flags;                 /**< \brief flags      ��־λ     	 */
	uint16_t	     msglen;                /**< \brief msglen     ���ĳ���  	 */
	uint8_t		     msgdata[8];            /**< \brief msgdata    ���Ļ�����  */
} am_can_message_t;


/** \brief ������Ϣ  */
typedef struct am_canfd_message {
	am_can_message_t can_msg;               /**< \brief CAN��Ϣ                                   */
    uint8_t msgdata[64-8];                  /**< \brief CANFD ���ݳ���Ϊ64B	*/
} am_canfd_message_t;


/**
 * \name CAN��������
 * \anchor grp_am_can_err_t
 * @{
 */

typedef uint32_t am_can_err_t;                 /**< \brief ��������   */
#define AM_CAN_NOERROR                 	0x00   /**< \brief �޴���   */
#define AM_CAN_NOTINITIALIZED          	0x01   /**< \brief δ��ʼ��   */
#define AM_CAN_ILLEGAL_CHANNEL_NO      	0x02   /**< \brief �Ƿ�ͨ����   */
#define AM_CAN_ILLEGAL_CONFIG          	0x03   /**< \brief �Ƿ�����   */
#define AM_CAN_ILLEGAL_DATA_LENGTH     	0x04   /**< \brief �Ƿ����ݳ���   */
#define AM_CAN_ILLEGAL_MASK_VALUE      	0x05   /**< \brief �Ƿ�������   */
#define AM_CAN_NO_AVAIL_CHANNELS       	0x06   /**< \brief ͨ��������   */
#define AM_CAN_INVALID_PARAMETER       	0x07   /**< \brief ��Ч����  */
#define AM_CAN_ILLEGAL_OFFSET          	0x08   /**< \brief ��Ч��ƫ��   */
#define AM_CAN_CANNOT_SET_ERRINT       	0x09   /**< \brief δʹ�ܴ����ж�   */
#define AM_CAN_CANNOT_SET_BOFFINT      	0x10   /**< \brief δʹ�����߹ر��ж�   */
#define AM_CAN_CANNOT_SET_WAKEUPINT    	0x11   /**< \brief δʹ�ܻ����ж�   */
#define AM_CAN_INCOMPATIBLE_TYPE       	0x12   /**< \brief ���Ͳ�����   */
#define AM_CAN_BAUDRATE_ERROR          	0x13   /**< \brief �����ʴ���   */

/** @} */

/**
 * \name CAN���ߴ������� 
 * \anchor grp_am_can_bus_err
 * @{
 */
 
typedef uint32_t am_can_bus_err_t;              /**< \brief CAN���ߴ�������    */
#define AM_CAN_BUS_ERR_NONE    			0x00	/**< \brief �޴���   */
#define AM_CAN_BUS_ERR_BIT     			0x01	/**< \brief λ����   */
#define AM_CAN_BUS_ERR_ACK     			0x02	/**< \brief Ӧ����� */
#define AM_CAN_BUS_ERR_CRC     			0x04	/**< \brief CRC����  */
#define AM_CAN_BUS_ERR_FORM    			0x08	/**< \brief ��ʽ���� */
#define AM_CAN_BUS_ERR_STUFF  	 		0x10	/**< \brief ������ */
#define AM_CAN_BUS_ERR_UNKNOWN 			0x20	/**< \brief δ֪���� */

/** @} */

/**
 * \name CAN�ж�����
 * \anchor grp_am_can_int_type
 * @{
 */

typedef uint32_t am_can_int_type_t;                /**< \brief �ж�����             */
#define AM_CAN_INT_NONE     			0x00       /**< \brief ������                  */
#define AM_CAN_INT_ERROR    			0x01       /**< \brief �����ж�             */
#define AM_CAN_INT_BUS_OFF  			0x02       /**< \brief ���߹ر��ж�   */
#define AM_CAN_INT_WAKE_UP  			0x04       /**< \brief �����ж�             */
#define AM_CAN_INT_TX       			0x08       /**< \brief �����ж�             */
#define AM_CAN_INT_RX       			0x10       /**< \brief �����ж�             */
#define AM_CAN_INT_DATAOVER             0x20       /**< \brief ���߳����ж�   */
#define AM_CAN_INT_WARN    			    0x40       /**< \brief �����ж�             */
#define AM_CAN_INT_ERROR_PASSIVE        0x80       /**< \brief ���󱻶��ж�   */
#define AM_CAN_INT_ALL      			0xffffffff /**< \brief �����ж�             */

/** @} */

/**
 * \name CANģʽ���� 
 * \anchor grp_am_can_mode_type
 * @{
 */
 
typedef uint8_t am_can_mode_type_t;             /**< \brief CANģʽ����  */
#define AM_CAN_MODE_NROMAL				0x00	/**< \brief ��������ģʽ */
#define AM_CAN_MODE_LISTEN_ONLY		    0x01	/**< \brief ֻ������ģʽ */


/**
 * \name CAN֡����
 * \anchor grp_am_can_frame_type
 * @{
 */
typedef uint8_t am_can_frame_type_t;             /**< \brief CAN֡����  */
#define AM_CAN_FRAME_TYPE_STD            0x01    /**< \brief ��׼֡  */
#define AM_CAN_FRAME_TYPE_EXT            0x02    /**< \brief ��չ֡  */

/**
 * \name CAN֡��ʽ
 * \anchor grp����am_can_frame_format_t
 * @{
 */

typedef uint8_t am_can_frame_format_t;             /**< \brief CAN֡����  */
#define AM_CAN_FRAME_FORMAT_NOCARE       0x00    /**< \brief ����֡��Զ��֡���ɽ���  */
#define AM_CAN_FRAME_FORMAT_DATA         0x01    /**< \brief ����֡  */
#define AM_CAN_FRAME_FORMAT_REMOTE       0x02    /**< \brief Զ��֡  */




/** @} */

/** \brief ������� */
typedef struct am_can_err_cnt {
	uint8_t rx_error_cnt; 	                    /**< \brief ���մ�������� */
	uint8_t tx_error_cnt; 	                    /**< \brief ���ʹ�������� */
} am_can_err_cnt_t;

/** \brief �����ʲ��� */
typedef struct am_can_bps_param {
	uint8_t   	tesg1;  		                /**< \brief tseg1 ��λ��1    */
	uint8_t   	tesg2;  		                /**< \brief tseg2 ��λ��2    */   
	uint8_t   	sjw;    		                /**< \brief sjw ͬ����ת���  */
	uint8_t     smp;                            /**< \brief smp ����ģʽ            */
	uint16_t    brp;                            /**< \brief brp ��Ƶֵ                 */
} am_can_bps_param_t;

/** \brief �˲������� */
typedef struct am_can_filter {
    am_can_frame_type_t   ide;                     /**< \brief �˲���֡����   */
    am_can_frame_format_t rtr;                     /**< \brief �˲���֡��ʽ   */

    uint32_t id[4];                                /**< \brief ID������    */
    uint32_t mask[4];                              /**< \brief ID����    */

} am_can_filter_t;

/**
 * \brief CAN reconfigure information .
 */
typedef struct am_can_cfg_info {
    am_can_mode_type_t        can_mode;         /**< \brief CAN ģʽ    */
} am_can_cfg_info_t;

/**
 * \brief CAN drive functions.
 */
struct am_can_drv_funcs {

	/** \brief CAN���� */
	am_can_err_t (*pfn_can_start)(void *p_drv);
    
    /** \brief CAN��λ��ֹͣ�� */
	am_can_err_t (*pfn_can_reset)(void *p_drv);
    
    /** \brief CAN����  */
	am_can_err_t (*pfn_can_sleep)(void *p_drv);

    /** \brief CAN���� */
	am_can_err_t (*pfn_can_wakeup)(void *p_drv);

    /** \brief �ж�ʹ�� */
	am_can_err_t (*pfn_can_int_enable)(void *p_drv, am_can_int_type_t int_mask);

    /** \brief �жϽ���*/
	am_can_err_t (*pfn_can_int_disable)(void *p_drv, am_can_int_type_t int_mask);

	/** \brief ģʽ���� */
	am_can_err_t (*pfn_can_mode_set)(void *p_drv, am_can_mode_type_t mode);

    /** \brief ���������� */
	am_can_err_t (*pfn_can_baudrate_set)(void               *p_drv,
										 am_can_bps_param_t *p_can_baudrate);

    /** \brief �����ʻ�ȡ */
    am_can_err_t (*pfn_can_baudrate_get)(void               *p_drv,
                                         am_can_bps_param_t *p_can_baudrate);
   
    /** \brief ��ȡ������� */
	am_can_err_t (*pfn_can_err_cnt_get)(void             *p_drv,
										am_can_err_cnt_t *p_can_err_reg);
    
    /** \brief ���������� */
	am_can_err_t (*pfn_can_err_cnt_clr)(void *p_drv);

    /** \brief ������Ϣ   */
	am_can_err_t (*pfn_can_msg_send)(void *p_drv, am_can_message_t *p_txmsg);

    /** \brief ������Ϣ   */
	am_can_err_t (*pfn_can_msg_recv)(void *p_drv, am_can_message_t *p_rxmsg);

    /** \brief ֹͣ������Ϣ   */
	am_can_err_t (*pfn_can_stop_msg_snd)(void *p_drv);

    /** \brief �����˲����� */
	am_can_err_t (*pfn_can_filter_tab_set)(void    *p_drv,
	                                       uint8_t *p_filterbuff,
	                                       size_t   lenth);
    /** \brief ��ȡ�˲�����*/
	am_can_err_t (*pfn_can_filter_tab_get)(void    *p_drv,
	                                       uint8_t *p_filterbuff,
	                                       size_t  *p_lenth);

    /** \brief CAN ״̬ */
	am_can_err_t (*pfn_can_status_get)(void              *p_drv,
                                       am_can_int_type_t *p_int_type,
                                       am_can_bus_err_t  *p_bus_err);

    /** \brief �ж����� */
    am_can_err_t (*pfn_can_connect)(void 		 *p_drv,
    								am_pfnvoid_t  pfn_isr,
    								void         *p_arg);

    /** \brief ɾ���ж����� */
    am_can_err_t (*pfn_can_disconnect)(void         *p_drv,
                                       am_pfnvoid_t  pfn_isr,
                                       void         *p_arg);
		
    /** \brief �жϻص����������� */
    am_can_err_t (*pfn_can_intcb_connect)(void              *p_drv,
    									  am_can_int_type_t  inttype,
    									  am_pfnvoid_t       pfn_callback,
    									  void              *p_arg);
    /** \brief ɾ���жϻص����������� */
    am_can_err_t (*pfn_can_intcb_disconnect)(void              *p_drv,
    										 am_can_int_type_t  inttype);

    /** \brief �����˲�����(��չ) */
    am_can_err_t (*pfn_can_filter_tab_ext_set)(void            *p_drv,
                                               am_can_filter_t *p_filterbuff,
                                               size_t           lenth);

    /** \brief ��ȡ�˲�����(��չ)*/
    am_can_err_t (*pfn_can_filter_tab_ext_get)(void             *p_drv,
                                               am_can_filter_t  *p_filterbuff,
                                               size_t           *p_lenth);
};

/**
 * \brief CAN �豸.
 */
typedef struct am_can_serv {

    struct am_can_drv_funcs   *p_drv_funcs;    /**< \brief  �������� */
    void                      *p_drv;          /**< \brief  �����豸 */

} am_can_serv_t;

/** \brief handle ��׼���� */
typedef am_can_serv_t *am_can_handle_t;

/**
 * \brief CAN ����.
 *
 * \param[in] handle : CAN ��׼���� handle.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_start (am_can_handle_t handle)
{
    return handle->p_drv_funcs->pfn_can_start(handle->p_drv);
}

/**
 * \brief CAN ��λ.
 *
 * \param[in] handle : CAN ��׼���� handle.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_reset (am_can_handle_t handle)
{
    return handle->p_drv_funcs->pfn_can_reset(handle->p_drv);
}

/**
 * \brief CAN ˯��.
 *
 * \param[in] handle : CAN ��׼���� handle.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_sleep (am_can_handle_t handle)
{
    return handle->p_drv_funcs->pfn_can_sleep(handle->p_drv);
}

/**
 * \brief CAN ����.
 *
 * \param[in] handle : CAN ��׼���� handle.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_wakeup (am_can_handle_t handle)
{
    return handle->p_drv_funcs->pfn_can_wakeup(handle->p_drv);
}

/**
 * \brief CAN �ж�ʹ��.
 *
 * \param[in] handle : CAN ��׼���� handle.
 * \param[in] mask   : �ж�����
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_int_enable (am_can_handle_t handle, am_can_int_type_t mask)
{
    return handle->p_drv_funcs->pfn_can_int_enable(handle->p_drv, mask);
}

/**
 * \brief CAN �ж�ʧ��.
 *
 * \param[in] handle : CAN ��׼���� handle.
 * \param[in] mask   : �ж�����
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_int_disable (am_can_handle_t handle, am_can_int_type_t mask)
{
    return handle->p_drv_funcs->pfn_can_int_disable(handle->p_drv, mask);
}

/**
 * \brief CAN ����ģʽ.
 *
 * \param[in] handle : CAN ��׼���� handle.
 * \param[in] mode   : ����ģʽ
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_mode_set (am_can_handle_t    handle,
                              am_can_mode_type_t mode)
{
    return handle->p_drv_funcs->pfn_can_mode_set(handle->p_drv, mode);
}

/**
 * \brief CAN ���ò�����.
 *
 * \param[in] handle           : CAN ��׼���� handle.
 * \param[in] p_can_baudrate   : ������
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_baudrate_set (am_can_handle_t          handle,
                                  struct am_can_bps_param *p_can_baudrate)
{
    return handle->p_drv_funcs->pfn_can_baudrate_set(handle->p_drv, 
                                                     p_can_baudrate);
} 

/**
 * \brief CAN ��ȡ������.
 *
 * \param[in] handle           : CAN ��׼���� handle.
 * \param[out] p_can_baudrate   : ������
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_baudrate_get (am_can_handle_t          handle,
                                  struct am_can_bps_param *p_can_baudrate)
{
    return handle->p_drv_funcs->pfn_can_baudrate_get(handle->p_drv,
                                                     p_can_baudrate);
}

/**
 * \brief CAN ��ȡ�������
 *
 * \param[in] handle         : CAN ��׼���� handle.
 * \param[out] p_can_err_cnt : �������
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_err_cnt_get (am_can_handle_t        handle,
                                 struct am_can_err_cnt *p_can_err_cnt)
{
    return handle->p_drv_funcs->pfn_can_err_cnt_get(handle->p_drv,
                                                    p_can_err_cnt);
} 

/**
 * \brief CAN ����������
 *
 * \param[in] handle : CAN ��׼���� handle.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_err_cnt_clr (am_can_handle_t handle)
{
    return handle->p_drv_funcs->pfn_can_err_cnt_clr(handle->p_drv);
} 

/**
 * \brief CAN ������Ϣ.
 *
 * \param[in] handle  : CAN ��׼���� handle.
 * \param[in] p_txmsg : ���͵���Ϣ
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_msg_send (am_can_handle_t handle, am_can_message_t *p_txmsg)
{
    return handle->p_drv_funcs->pfn_can_msg_send(handle->p_drv, p_txmsg);
}

/**
 * \brief CAN ������Ϣ
 *
 * \param[in] handle   : CAN ��׼���� handle.
 * \param[out] p_rxmsg : ���յ���Ϣ
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_msg_recv(am_can_handle_t handle, am_can_message_t *p_rxmsg)
{
    return handle->p_drv_funcs->pfn_can_msg_recv(handle->p_drv, p_rxmsg);
}

/**
 * \brief CAN ֹͣ����
 *
 * \param[in] handle   : CAN ��׼���� handle.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_msg_stop_send(am_can_handle_t handle)
{
    return handle->p_drv_funcs->pfn_can_stop_msg_snd(handle->p_drv);
}

/**
 * \brief CAN �����˲�
 *
 * \param[in] handle  : CAN ��׼���� handle.
 * \param[in] p_filterbuff : �˲����׵�ַ
 * \param[in] lenth        : �˲�����
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_filter_tab_set (am_can_handle_t  handle,
                                    uint8_t         *p_filterbuff,
                                    size_t           lenth)
{
    return handle->p_drv_funcs->pfn_can_filter_tab_set(handle->p_drv,
                                                       p_filterbuff,
                                                       lenth);
}

/**
 * \brief CAN �����˲�(��չ)
 *
 * \param[in] handle  : CAN ��׼���� handle.
 * \param[in] p_filterbuff : �˲��� ��� am_can_filter_t
 * \param[in] lenth        : �����am_can_filter_t�ĸ���
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_filter_tab_ext_set (am_can_handle_t  handle,
                                        am_can_filter_t *p_filterbuff,
                                        size_t           lenth)
{
    return handle->p_drv_funcs->pfn_can_filter_tab_ext_set(handle->p_drv,
                                                           p_filterbuff,
                                                           lenth);
}

/**
 * \brief CAN ��ȡ�˲�������
 *
 * \param[in]  handle          : CAN ��׼���� handle.
 * \param[out] p_filterbuff    : �˲����׵�ַ
 * \param[out] p_lenth         : �˲�����
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_filter_tab_get (am_can_handle_t  handle,
                                    uint8_t         *p_filterbuff,
                                    size_t          *p_lenth)
{
    return handle->p_drv_funcs->pfn_can_filter_tab_get(handle->p_drv,
                                                       p_filterbuff,
                                                       p_lenth);
}

/**
 * \brief CAN ��ȡ�˲�������(��չ)
 *
 * \param[in]  handle          : CAN ��׼���� handle.
 * \param[out] p_filterbuff    : �˲��� ��� am_can_filter_t
 * \param[out] p_lenth         : ���õ�am_can_filter_t����
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_filter_tab_ext_get (am_can_handle_t  handle,
                                        am_can_filter_t *p_filterbuff,
                                         size_t         *p_lenth)
{
    return handle->p_drv_funcs->pfn_can_filter_tab_ext_get(handle->p_drv,
                                                           p_filterbuff,
                                                           p_lenth);
}

/**
 * \brief CAN ��ȡ״̬
 *
 * \param[in] handle      : CAN ��׼���� handle.
 * \param[out] p_int_type : �ж�����.
 * \param[out] p_bus_err  : ���ߴ�������.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_status_get (am_can_handle_t    handle,
                                am_can_int_type_t *p_int_type,
                                am_can_bus_err_t  *p_bus_err)
{
    return handle->p_drv_funcs->pfn_can_status_get(handle->p_drv,
                                                   p_int_type,
                                                   p_bus_err);
}

/**
 * \brief CAN �ж�����
 *
 * \param[in] handle  : CAN ��׼���� handle.
 * \param[in] pfn_isr : CAN �жϷ�������NULLʱ��ʹ���ڲ��жϷ���.
 * \param[in] p_arg   : CAN �жϷ���������.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_connect (am_can_handle_t  handle,
							 am_pfnvoid_t     pfn_isr,
							 void            *p_arg)
{
    return handle->p_drv_funcs->pfn_can_connect(handle->p_drv, pfn_isr, p_arg);
}

/**
 * \brief CAN ɾ���ж�����
 *
 * \param[in] handle  : CAN ��׼���� handle.
 * \param[in] pfn_isr : CAN �жϷ�����.
 * \param[in] p_arg   : CAN �жϷ���������.
 *
 * \retval  AM_CAN_NOERROR            :  �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER : ��������
 */
am_static_inline
am_can_err_t am_can_disconnect (am_can_handle_t  handle,
                                am_pfnvoid_t     pfn_isr,
                                void            *p_arg)
{
    return handle->p_drv_funcs->pfn_can_disconnect(handle->p_drv,
                                                   pfn_isr,
                                                   p_arg);
}

/**
 * \brief CAN ע���жϻص�����
 *
 * \param[in] handle			 : CAN ��׼���� handle.
 * \param[in] inttype			 : �ж�����
 * \param[in] pfn_callback       : �жϻص�����
 * \param[in] p_arg 			 : �ص���������
 *
 * \retval  AM_CAN_NOERROR              : �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER   : ��������
 * \retval  -AM_CAN_ILLEGAL_MASK_VALUE  : �ж����Ͳ��Ϸ�
 */
am_static_inline
am_can_err_t am_can_intcb_connect (am_can_handle_t    handle,
						           am_can_int_type_t  inttype,
                                   am_pfnvoid_t       pfn_callback,
                                   void              *p_arg)
{
	return handle->p_drv_funcs->pfn_can_intcb_connect(handle->p_drv, 
	                                                  inttype,
	                                                  pfn_callback, p_arg);
}

/**
 * \brief CAN ����жϻص�������ע��
 *
 * \param[in] handle			 : CAN ��׼���� handle.
 * \param[in] inttype			 : �ж�����
 *
 * \retval  AM_CAN_NOERROR                : �ɹ�.
 * \retval  -AM_CAN_INVALID_PARAMETER     : ��������
 * \retval  -AM_CAN_ILLEGAL_MASK_VALUE    : �ж����Ͳ��Ϸ�
 */
am_static_inline
am_can_err_t am_can_intcb_disconnect (am_can_handle_t    handle,
						              am_can_int_type_t  inttype)
{
	return handle->p_drv_funcs->pfn_can_intcb_disconnect(handle->p_drv,
	                                                     inttype);
}

/** 
 * @} am_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_CAN_H */

/*end of file */



