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
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USBD ������ʵ�ֺ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-29  sdq, first implementation.
 * \endinternal
 */

#include "am_zlg116_usbd.h"
#include "amhw_zlg116_usbd.h"
#include "am_usb.h"
#include "am_int.h"
#include "am_usb_spec.h"
#include "am_usbd_ch9.h"

/* ��Ҫ����USB��ʱ��ȥ��ע�ͣ������ڴ����д�ӡ������USB�жϺ��������� */
//#define USB_DEBUG

/**
 * \brief ͨ��wValue��ֵѰ��ָ����������
 *
 * \retval �ɹ�����������ָ�룬ʧ�ܷ���NULL
 *
 * \note �������������¼�����������ͨ���˷����
 */
static uint8_t * __find_desc_by_wValue1 (const am_zlg126_usbd_dev_t *p_dev,
                                         uint16_t                 w_value)
{
    int i;

    for (i = 0; i < p_dev->p_info->p_devinfo->descriptor_num; i++) {
        if (w_value == p_dev->p_info->p_devinfo->p_descriptor[i].desc_wValue) {
            return (uint8_t *)(p_dev->p_info->p_devinfo->p_descriptor[i].p_desc);
        }
    }
    return NULL;
}

/**
 * \brief ��ʼ��ָ���Ķ˵�
 *
 * \param[in] p_dev  : USB�豸
 * \param[in] epInit : �˵��ʼ����Ϣ
 *
 * \note �ú�������������ָ��һ��Ӳ���еĶ˵㣬��ʼ���Ķ˵����������������ָ�����ģ����ҵ�ַ�ʹ��䷽��
 *       ����һ�£�Ҳ����˵��p_dev->device.endpoint_info[i].endpoint_address��
 *       epInit->endpoint_address��ֵ������ȣ����ܽ��г�ʼ����
 */
static am_usb_status_t __usb_device_endpoint_init (am_zlg126_usbd_dev_t       *p_dev,
                                                   am_usbd_endpoint_init_t    *epinit)
{
    amhw_zlg116_usbd_t *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    uint16_t max_packet_size = epinit->max_packet_size;
    uint8_t  endpoint = (epinit->endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK);
    int i;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        /* �˵��������б���ָ��������˵� */
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE &&
            p_dev->device.endpoint_info[i].ep_address == epinit->endpoint_address) {
            break;
        }
    }
    if (i == AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_REQUEST;

    if (endpoint >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;
    if (epinit->transfer_type > AM_USB_ENDPOINT_INTERRUPT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    /* ���ö˵��ܴ��������ֽڸ��� */
    if (max_packet_size > AM_USBD_MAX_EP_DATA_CNT)
        max_packet_size = AM_USBD_MAX_EP_DATA_CNT;

    amhw_zlg116_usbd_ep_halt_reset(p_usb, 1 << endpoint);     /* ����˵���ͣ */
    amhw_zlg116_usbd_ep_enable(p_usb, 1 << endpoint);         /* ʹ�ܶ˵� */

    p_dev->device.endpoint_info[endpoint].stalled = 0;
    p_dev->device.endpoint_info[endpoint].max_packet_size = max_packet_size;
    p_dev->device.endpoint_info[endpoint].transfer_type = epinit->transfer_type;

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ��ĳ���˵�ȥ��ʼ��
 *
 *  \param[in] p_dev       : USB�豸
 *  \param[in] endpoint    : ָ���Ķ˵�
 */
static am_usb_status_t __usb_device_endpoint_deinit (am_zlg126_usbd_dev_t *p_dev,
                                                    uint8_t            endpoint)
{
    amhw_zlg116_usbd_t *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    endpoint &= AM_USBD_ENDPOINT_NUMBER_MASK;

    amhw_zlg116_usbd_ep_disable(p_usb, 1 << endpoint);  /* ���ܶ˵� */

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵�����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ
 */
static am_usb_status_t __usb_device_endpoint_stall (am_zlg126_usbd_dev_t *p_dev,
                                                   uint8_t            endpoint_addr)
{
    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;
    amhw_zlg116_usbd_t *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    p_dev->device.endpoint_info[endpoint].stalled = 1;    /* ����������־ */

    amhw_zlg116_usbd_ep_halt_set(p_usb, 1 << endpoint);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵㲻����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ  D7�� 1��USB_IN  0��USB_OUT
 */
static am_usb_status_t __usb_device_endpoint_unstall (am_zlg126_usbd_dev_t *p_dev,
                                                      uint8_t               endpoint_addr)
{
    amhw_zlg116_usbd_t *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;

    p_dev->device.endpoint_info[endpoint].stalled = 0;

    amhw_zlg116_usbd_dtog_data0(p_usb, endpoint);

    amhw_zlg116_usbd_ep_halt_reset(p_usb, 1 << endpoint);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ��ʼ��USB�豸
 */
static am_usb_status_t __usb_device_init (am_usbd_handle_t handle)
{
    int i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_zlg126_usbd_dev_t *p_dev = (am_zlg126_usbd_dev_t *)handle;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    /* ��λUSB�������Ķ˵��FIFO */
    amhw_zlg116_usbd_connect_set(p_usb, ZLG116_USB_DISCONNECT);
    amhw_zlg116_usbd_reset_set(p_usb, ZLG116_USB_RESET);
    amhw_zlg116_usbd_reset_set(p_usb, ZLG116_USB_NORESET);
    amhw_zlg116_usbd_connect_set(p_usb, ZLG116_USB_DISCONNECT);

    /* ���ж�״̬ */
    amhw_zlg116_usbd_int_state_clear(p_usb, AMHW_ZLG116_USB_INT_STATE_ALL);

    /* ��˵��ж�״̬ */
    amhw_zlg116_usbd_ep_int_state_clear(p_usb, AMHW_ZLG116_EP_INT_STATE_EP_ALL);
    p_dev->int_ep_union.int_ep_flag = 0;

    amhw_zlg116_usbd_ep0_int_state_clear(p_usb, AMHW_ZLG116_EP0_INT_STATE_ALL);
    p_dev->ep_int_type_union.ep_int_type[0] = 0;

    for (i = 0; i < AM_USBD_MAX_EP_CNT - 1; i++) {
        amhw_zlg116_usbd_epx_int_state_clear(p_usb, (zlg116_usb_epx_t)i, AMHW_ZLG116_EPX_INT_STATE_ALL);
        p_dev->ep_int_type_union.ep_int_type[i + 1] = 0;
    }

    /* ʹ��USB�жϣ�δʹ��SOF����жϣ� */
    /* ���ʹ����SOF�жϵĻ���ÿ��1ms�ͻ����һ���жϣ������ʹ��SOF�жϣ��жϱ�־Ҳ����λ�����ǲ���
                 �����ж�     */
    amhw_zlg116_usbd_int_enable(p_usb,
                                AMHW_ZLG116_USB_INT_EN_RSTIE |
                                AMHW_ZLG116_USB_INT_EN_SUSPENDIE |
                                AMHW_ZLG116_USB_INT_EN_RESUMIE |
                                AMHW_ZLG116_USB_INT_EN_EPIE);

    /* ʹ�ܶ˵��ж� */
    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE)
            amhw_zlg116_usbd_ep_int_enable(p_usb, 1 << i);
    }

    /* ʹ�ܶ˵�0�������ж� */
    amhw_zlg116_usbd_ep0_int_enable(p_usb, AMHW_ZLG116_EP0_INT_EN_ALL);
    /* ʹ�������˵�������ж� */
    for (i = 0; i < AM_USBD_MAX_EP_CNT - 1; i++) {
        if (p_dev->device.endpoint_info[i + 1].inuse == AM_TRUE)
            amhw_zlg116_usbd_epx_int_enable(p_usb, (zlg116_usb_epx_t)i, AMHW_ZLG116_EPX_INT_EN_ALL);
    }

    /* ���SETUP���� */
    p_dev->device.setup_data.bm_request_type = 0;
    p_dev->device.setup_data.b_request = 0;
    p_dev->device.setup_data.w_value = 0;
    p_dev->device.setup_data.w_index = 0;
    p_dev->device.setup_data.w_length = 0;


    /**< \brief ��ʼ���˵� */
    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
            endpoint.endpoint_address = p_dev->device.endpoint_info[i].ep_address;
            endpoint.max_packet_size = p_dev->device.endpoint_info[i].max_packet_size;
            endpoint.transfer_type = p_dev->device.endpoint_info[i].transfer_type;
            __usb_device_endpoint_init(p_dev, &endpoint);
        }
    }


    /* ���õ�ַΪ0 */
    amhw_zlg116_usbd_addr_set(p_usb, 0);
    p_dev->device.device_address = 0;

    amhw_zlg116_usbd_active_set(p_usb, ZLG116_USB_ACTIVE);      /* ��Ծ */
    amhw_zlg116_usbd_speed_set(p_usb, ZLG116_USB_SPEED_FULL);   /* ȫ�� */
    amhw_zlg116_usbd_connect_set(p_usb, ZLG116_USB_CONNECT);    /* ���� */

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \bruef USBȥ��ʼ��
 *
 * \param[in] USB�������
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_deinit (am_usbd_handle_t handle)
{
    am_zlg126_usbd_dev_t *p_dev = (am_zlg126_usbd_dev_t *)handle;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    if (handle == NULL){
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    amhw_zlg116_usbd_int_disable(p_usb, AMHW_ZLG116_USB_INT_EN_ALL); /* ����USB�ж� */
    amhw_zlg116_usbd_ep_int_disable(p_usb, AMHW_ZLG116_EP_INT_EN_ALL);   /* ���ܶ˵��ж� */
    amhw_zlg116_usbd_ep0_int_disable(p_usb, AMHW_ZLG116_EP0_INT_EN_ALL); /* ���ܶ˵�0���ж� */
    amhw_zlg116_usbd_ep_disable(p_usb, AMHW_ZLG116_USB_EP_ALL);      /* �������ж˵� */

    /* ���ܶ˵���ж� */
    amhw_zlg116_usbd_epx_int_disable(p_usb, ZLG116_USB_EP1,
                                  AMHW_ZLG116_EPX_INT_EN_ALL);
    amhw_zlg116_usbd_epx_int_disable(p_usb, ZLG116_USB_EP2,
                                  AMHW_ZLG116_EPX_INT_EN_ALL);
    amhw_zlg116_usbd_epx_int_disable(p_usb, ZLG116_USB_EP3,
                                  AMHW_ZLG116_EPX_INT_EN_ALL);
    amhw_zlg116_usbd_epx_int_disable(p_usb, ZLG116_USB_EP4,
                                  AMHW_ZLG116_EPX_INT_EN_ALL);

    if (p_dev->p_info->pfn_plfm_deinit)
        p_dev->p_info->pfn_plfm_deinit();

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief USB�豸��������
 *
 * \param[in] handle           : USB���ƾ��
 * \param[in] endpoint_address : ָ���Ķ˵��ַ
 * \param[in] buffer           : ָ��Ҫ���͵�����
 * \param[in] length           : Ҫ���͵����ݳ���
 *
 * \note ��������lengthΪ0�����Ϳհ�����������bufferΪNULL����length��Ϊ0������length
 *       ��0
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_send (am_usbd_handle_t handle,
                                          uint8_t          endpoint_address,
                                          uint8_t         *buffer,
                                          uint32_t         length)
{
    am_zlg126_usbd_dev_t *p_dev = (am_zlg126_usbd_dev_t *)handle;
    uint32_t send_once_size = 0;
    uint8_t endpoint = endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK;
    amhw_zlg116_usbd_t *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    int i = 0;

    if (endpoint >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    if (length == 0) {  /* ���Ϳհ� */
        while (!amhw_zlg116_usbd_transfer_end(p_usb, (zlg116_usb_epx2_t)endpoint));
        amhw_zlg116_usbd_epx_transfer(p_usb, (zlg116_usb_epx2_t)endpoint, 0);
    } else {
        while (length) {        /* ���һ�β�����ȫ������ֶ�δ��� */
            if (length > AM_USBD_MAX_EP_DATA_CNT) {
                send_once_size = AM_USBD_MAX_EP_DATA_CNT;
            } else {
                send_once_size = length;
            }
            length -= send_once_size;
            while (!amhw_zlg116_usbd_transfer_end(p_usb, (zlg116_usb_epx2_t)endpoint));
            if (buffer) {
                for (i = 0; i < send_once_size; i++) {
                    amhw_zlg116_usbd_epx_fifo_write(p_usb, (zlg116_usb_epx2_t)endpoint, *buffer++);
                }
            } else {
                for (i = 0; i < send_once_size; i++) {
                    amhw_zlg116_usbd_epx_fifo_write(p_usb, (zlg116_usb_epx2_t)endpoint, 0);
                }
            }
            amhw_zlg116_usbd_epx_transfer(p_usb, (zlg116_usb_epx2_t)endpoint, send_once_size);
        }
    }

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief �˵�0���Ϳհ�
 */
static void __ep0_send_empty_packet (am_usbd_handle_t handle)
{
    am_zlg126_usbd_dev_t *p_dev = (am_zlg126_usbd_dev_t *)handle;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    switch (p_dev->device.state) {
    case AM_USBD_CTRL_SETUP:
        p_dev->device.state = AM_USBD_CTRL_IN;
        break;

    case AM_USBD_CTRL_IN:
        while (!amhw_zlg116_usbd_transfer_end(p_usb, ZLG116_USB_EPX0));
        amhw_zlg116_usbd_epx_transfer(p_usb, ZLG116_USB_EPX0, 0);
        p_dev->device.state = AM_USBD_CTRL_IDLE;
        break;

    default:
        p_dev->device.state = AM_USBD_CTRL_IDLE;
    }
}

/**
 * \brief USB�豸��������
 *
 * \param[in] handle           : USB���ƾ��
 * \param[in] endpoint_address : ָ���Ķ˵��ַ
 * \param[in] buffer           : ָ��Ҫ���͵�����
 * \param[in] length           : Ҫ���յ����ݳ���
 *
 * \retval USB������
 *
 * \note �ú�����fifo��ȡ������.
 *       ���fifo��û�����ݣ��򷵻�AM_USB_STATUS_ERROR.
 *       ���fifo�������ݵ������ݸ�������ָ�������ݳ��ȣ��򷵻�AM_USB_STATUS_ALLOC_FAIL����仺������
 *       ���fifo�������ݲ������ݸ�������ָ�������ݳ��ȣ��򷵻�AM_USB_STATUS_SUCCESS����仺������
 *       ���fifo�������ݲ������ݸ�������ָ�������ݳ��ȣ��򷵻�AM_USB_STATUS_SUCCESS�����ָ�������ݳ��ȡ�
 */
static am_usb_status_t __usb_device_recv (am_usbd_handle_t handle,
                                          uint8_t                   endpoint_address,
                                          uint8_t                  *buffer,
                                          uint32_t                  length)
{
    am_zlg126_usbd_dev_t *p_dev = (am_zlg126_usbd_dev_t *)handle;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    am_usb_status_t error = AM_USB_STATUS_ERROR;
    uint8_t endpoint = endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK;
    uint8_t avali_data_cnt = 0;     /* fifo����Ч���ݸ��� */

    /* �������ݵĶ˵㷽�������OUT_OUT */
    if ((endpoint_address & AM_USB_DESC_ENDPOINT_ADDR_DIR_MASK) !=
            AM_USB_DESC_ENDPOINT_ADDR_DIR_OUT)
        return AM_USB_STATUS_INVALID_REQUEST;

    if (endpoint >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    avali_data_cnt = amhw_zlg116_usbd_epx_avail_size_get(p_usb, (zlg116_usb_epx2_t)endpoint);
    p_dev->device.endpoint_info[endpoint].val_length = avali_data_cnt;

    if (avali_data_cnt == 0)
        return AM_USB_STATUS_ERROR;
    else if (avali_data_cnt < length)
        error = AM_USB_STATUS_ALLOC_FAIL;
    else if (avali_data_cnt == length)
        error = AM_USB_STATUS_SUCCESS;
    else if (avali_data_cnt > length) {
        error = AM_USB_STATUS_SUCCESS;
        avali_data_cnt = length;
    }

    while (avali_data_cnt--) {
        *buffer++ = amhw_zlg116_usbd_epx_fifo_read(p_usb, (zlg116_usb_epx2_t)endpoint);
    }

    return error;
}

/**
 * \brief ��ֹĳ���˵����ڽ��еĴ���
 *
 * \param[in] handle        : �豸���
 * \param[in] endpoint_addr : �˵��ַ
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_cancel (am_usbd_handle_t handle,
                                            uint8_t          endpoint_addr)
{

    return AM_USB_STATUS_ERROR;
}

/**
 * \brief �����豸ΪĬ��״̬
 *
 * \param[in] p_dev:�豸ʵ�������������
 *
 * \note Ĭ��״̬Ϊʹ�������жϲ�ʹ�����ж˵㣬���豸��ַ��0
 */
static void __usb_device_setdefault_state(am_zlg126_usbd_dev_t *p_dev)
{
    /* �����ַ */
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    amhw_zlg116_usbd_addr_set(p_usb, 0);

    amhw_zlg116_usbd_ep_enable(p_usb, AMHW_ZLG116_USB_EP_ALL);  /* ʹ�ܶ˵� */

    /* ���ж�״̬ */
    amhw_zlg116_usbd_int_state_clear(p_usb, AMHW_ZLG116_USB_INT_STATE_ALL);
    amhw_zlg116_usbd_ep0_int_state_clear(p_usb, AMHW_ZLG116_EP0_INT_STATE_ALL);
    amhw_zlg116_usbd_epx_int_state_clear(p_usb, ZLG116_USB_EP1,
                                         AMHW_ZLG116_EPX_INT_STATE_ALL);
    amhw_zlg116_usbd_epx_int_state_clear(p_usb, ZLG116_USB_EP2,
                                         AMHW_ZLG116_EPX_INT_STATE_ALL);
    amhw_zlg116_usbd_epx_int_state_clear(p_usb, ZLG116_USB_EP3,
                                         AMHW_ZLG116_EPX_INT_STATE_ALL);
    amhw_zlg116_usbd_epx_int_state_clear(p_usb, ZLG116_USB_EP4,
                                         AMHW_ZLG116_EPX_INT_STATE_ALL);

    /* ʹ��USB�ж� */
    amhw_zlg116_usbd_int_enable(p_usb, AMHW_ZLG116_USB_INT_EN_ALL);

    /* ʹ�����ж˵��ж� */
    amhw_zlg116_usbd_ep_int_enable(p_usb, AMHW_ZLG116_EP_INT_EN_ALL);

    /* ʹ�ܶ˵�0�������ж� */
    amhw_zlg116_usbd_ep0_int_enable(p_usb, AMHW_ZLG116_EP0_INT_EN_ALL);

    /* ʹ�������˵�������ж� */
    amhw_zlg116_usbd_epx_int_enable(p_usb, ZLG116_USB_EP1,
                                 AMHW_ZLG116_EPX_INT_EN_ALL);
    amhw_zlg116_usbd_epx_int_enable(p_usb, ZLG116_USB_EP2,
                                 AMHW_ZLG116_EPX_INT_EN_ALL);
    amhw_zlg116_usbd_epx_int_enable(p_usb, ZLG116_USB_EP3,
                                 AMHW_ZLG116_EPX_INT_EN_ALL);
    amhw_zlg116_usbd_epx_int_enable(p_usb, ZLG116_USB_EP4,
                                 AMHW_ZLG116_EPX_INT_EN_ALL);
}


/**
 * \brief USB���ƺ�������������USBΪָ����״̬
 *
 * \param[in] handle : USB�������
 * \param[in] type   : ��������
 * \param[in] param  : ���Ʋ���
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_control(am_usbd_handle_t          handle,
                                            am_usbd_control_type_t    type,
                                            void                     *param)
{
    am_zlg126_usbd_dev_t *p_dev = (am_zlg126_usbd_dev_t *)handle;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    am_usb_status_t error = AM_USB_STATUS_ERROR;
    uint8_t *temp8;
    am_usbd_ep_status_t *endpointStatus = NULL;
    uint8_t endpoint = 0;

    if (!handle)
        return AM_USB_STATUS_INVALID_HANDLE;

    switch ((int)type) {
        case AM_USBD_CONTROL_RUN:
            amhw_zlg116_usbd_connect_set(p_usb, ZLG116_USB_CONNECT);    /* ���� */
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_STOP:
            amhw_zlg116_usbd_connect_set(p_usb, ZLG116_USB_DISCONNECT); /* �Ͽ����� */
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_ENDPOINT_INIT:     /* ��ĳ���˵��ʼ�� */
            if (param) {
                error = __usb_device_endpoint_init(p_dev,
                                                  (am_usbd_endpoint_init_t *)param);
            }
            break;

        case AM_USBD_CONTROL_ENDPOINT_DEINIT:   /* ��ĳ���˵�ȥ��ʼ�� */
            if (param) {
                temp8 = (uint8_t *)param;
                error = __usb_device_endpoint_deinit(p_dev, *temp8);
            }
            break;

        case AM_USBD_CONTROL_ENDPOINT_STALL:    /* ���ƶ˵����� */
            if (param) {
                temp8 = (uint8_t *)param;
                error = __usb_device_endpoint_stall(p_dev, *temp8);
            }
            break;

        case AM_USBD_CONTROL_ENDPOINT_UNSTALL:  /* ���ƶ˵㲻���� */
            if (param) {
                temp8 = (uint8_t *)param;
                error = __usb_device_endpoint_unstall(p_dev, *temp8);
            }
            break;

        case AM_USBD_CONTROL_GET_DEVICE_STATUS: /* ��ȡ�豸״̬ */

            break;

        case AM_USBD_CONTROL_GET_ENDPOINT_STATUS:   /* ͨ���˵��ַ��ȡ�˵�״̬ */
            if (param) {
                endpointStatus = (am_usbd_ep_status_t *)param;

                endpoint = (endpointStatus->endpoint_address) & AM_USBD_ENDPOINT_NUMBER_MASK;

                if (endpoint < AM_USBD_MAX_EP_CNT) {
                    endpointStatus->endpoint_status = p_dev->device.endpoint_info[endpoint].stalled;
                    error = AM_USB_STATUS_SUCCESS;
                } else {
                    error = AM_USB_STATUS_INVALID_PARAMETER;
                }
            }
            break;

        case AM_USBD_CONTROL_SET_DEVICE_ADDRESS:    /* ����USB�豸��ַ */
            if (param) {
                error = AM_USB_STATUS_SUCCESS;
            }
            break;

        case AM_USBD_CONTROL_GET_SYNCH_FRAME:
            break;

        case AM_USBD_CONTROL_RESUME:
            amhw_zlg116_usbd_wakeup(p_usb);
            break;

            /* ����Ĭ��״̬ */
        case AM_USBD_CONTROL_SET_DEFAULT_STATUS:
            __usb_device_setdefault_state(p_dev);
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_GET_SPEED:
            if (param) {
                temp8 = (uint8_t *)param;
                *temp8 = AM_USB_SPEED_FULL;
                error = AM_USB_STATUS_SUCCESS;
            }
            break;

        case AM_USBD_CONTROL_GET_OTG_STATUS:
            break;
        case AM_USBD_CONTROL_SET_OTG_STATUS:
            break;
        case AM_USBD_CONTROL_SET_TEST_MODE:
            break;
        default:
            break;
    }
    return error;
}

static const am_usbd_interface_t __g_usb_device_interface = {
    __usb_device_init,
    __usb_device_deinit,
    __usb_device_send,
    __usb_device_recv,
    __usb_device_cancel,
    __usb_device_control
};

/**
 * \brief ������
 */
static void __ctrl_deal_handle (am_zlg126_usbd_dev_t *p_dev)
{
    am_usbd_dev_t   *p_usbd_dev = &p_dev->device;
    am_data_info_t  *p_ctrl     = &p_usbd_dev->ctrl_info;

    if(p_ctrl->p_buf != NULL){
        if(p_ctrl->length > p_usbd_dev->setup_data.w_length){
            p_ctrl->length = p_usbd_dev->setup_data.w_length;
        }
        am_usbd_send(p_usbd_dev, 0, p_ctrl->p_buf, p_ctrl->length);
    }else{
        __ep0_send_empty_packet(p_dev);
    }
    p_usbd_dev->state = AM_USBD_CTRL_IDLE;
}

/**
 * \brief ����IN����
 */
static void __usb_in_handle(am_zlg126_usbd_dev_t *p_dev)
{
    if ((p_dev->device.setup_data.bm_request_type &
            AM_USB_REQ_TYPE_DIR_MASK) == AM_USB_REQ_TYPE_DIR_IN &&
            p_dev->device.state == AM_USBD_CTRL_SETUP) {
        __ctrl_deal_handle(p_dev);
    }else{
        __ep0_send_empty_packet(p_dev);
    }
}

/**
 * \brief setup������
 */
static void __usb_setup_handle (am_zlg126_usbd_dev_t *p_dev)
{
    uint8_t ret = AM_USB_STATUS_NOT_SUPPORTED;
    uint8_t code = 0, type = 0;
    amhw_zlg116_usbd_t *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    am_usbd_dev_t      *p_usb_dev = &(p_dev->device);
    am_data_info_t     *p_data_info = &(p_usb_dev->ctrl_info);

    p_data_info->offset = 0;
    p_data_info->p_buf  = NULL;

    if(p_usb_dev->state == AM_USBD_CTRL_IDLE) {  // ���״̬Ϊ����̬
        amhw_zlg116_usbd_setupdata_get(p_usb, (uint8_t *)&(p_usb_dev->setup_data)); // �������ݰ�
        p_usb_dev->state = AM_USBD_CTRL_SETUP;   // ����״̬
        type = p_usb_dev->setup_data.bm_request_type;
        code = p_usb_dev->setup_data.b_request;
        //am_kprintf("bm_request_type = %02x\r\n", p_dev->device.setup_data.bm_request_type);
        //am_kprintf("b_request = %02x\r\n", p_dev->device.setup_data.b_request);
        //am_kprintf("w_value = %02x\r\n", p_dev->device.setup_data.w_value);
        //am_kprintf("w_index = %02x\r\n", p_dev->device.setup_data.w_index);
        //am_kprintf("w_length = %02x\r\n", p_dev->device.setup_data.w_length);
    }


    /* �ж��������͵����� */
    switch (type & AM_USB_REQ_TYPE_MASK) {
    /* ��׼�������� */
    case AM_USB_REQ_TYPE_STANDARD:
        /* �Ϸ������ж� */
        switch (code) {
            case AM_USB_REQ_STANDARD_GET_STATUS:
                ret = p_usb_dev->p_funcs->pfn_status_get(
                        p_usb_dev, &p_data_info->p_buf, &p_data_info->length);
                break;
            case AM_USB_REQ_STANDARD_CLEAR_FEATURE:
                ret = p_usb_dev->p_funcs->pfn_feature_clr(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_SET_FEATURE:
                ret = p_usb_dev->p_funcs->pfn_feature_set(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_SET_ADDRESS:
                p_usb_dev->device_address = p_usb_dev->setup_data.w_value;
                ret = AM_USB_STATUS_SUCCESS;
                break;
            case AM_USB_REQ_STANDARD_GET_DESCRIPTOR:
                ret = p_usb_dev->p_funcs->pfn_desc_get(
                        p_usb_dev, &p_data_info->p_buf, &p_data_info->length);
                break;
            case AM_USB_REQ_STANDARD_SET_DESCRIPTOR:
//                ret = p_usb_dev->p_funcs->pfn_feature_set(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_GET_CONFIGURATION:
                ret = p_usb_dev->p_funcs->pfn_config_get(
                        p_usb_dev, &p_data_info->p_buf, &p_data_info->length);
                break;
            case AM_USB_REQ_STANDARD_SET_CONFIGURATION:
                ret = p_usb_dev->p_funcs->pfn_config_set(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_GET_INTERFACE:
                ret = p_usb_dev->p_funcs->pfn_interface_get(
                        p_usb_dev, &p_data_info->p_buf, &p_data_info->length);
                break;
            case AM_USB_REQ_STANDARD_SET_INTERFACE:
                ret = p_usb_dev->p_funcs->pfn_interface_set(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_SYNCH_FRAME:

                break;
            default:
                break;
        }
        break;
    /* ������ */
    case AM_USB_REQ_TYPE_CLASS:
        if(p_usb_dev->class_req.pfn_class) {
            ret = p_usb_dev->class_req.pfn_class(p_usb_dev->class_req.p_arg, code);
        }
        break;
    /* �������� */
    case AM_USB_REQ_TYPE_VENDOR:
        if(p_usb_dev->vendor_req.pfn_vendor) {
            ret = p_usb_dev->vendor_req.pfn_vendor(p_usb_dev->vendor_req.p_arg, code);
        }
        break;
    default:
        break;
    }

    if((type & 0x80) && (p_data_info->length != 0)){
        am_usbd_recv(p_usb_dev, 0, p_data_info->p_buf, p_data_info->length);
    }

    if(ret == AM_USB_STATUS_SUCCESS){
        p_usb_dev->state = AM_USBD_CTRL_SETUP;
    }
}

/**
 * \brief �˵��ж�
 */
static void __usb_device_interrupt_endpoint (am_zlg126_usbd_dev_t *p_dev)
{
    int ep_index = 0;         /* �����жϵĶ˵� */
    int ep_int_type = 0;      /* ����Ķ˵��ж����� */
    int i = 0;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;

    ep_index = amhw_zlg116_usbd_ep_int_state_get(p_usb);     /* ��÷����жϵĶ˵� */
    amhw_zlg116_usbd_ep_int_state_clear(p_usb, ep_index);    /* ��˵��ж� */
    p_dev->int_ep_union.int_ep_flag = ep_index;

    /* �˵�0�ж� */
    if (p_dev->int_ep_union.int_ep_flag_field.ep0) {

        /* ��ö˵�0�����ľ����ж����� */
        ep_int_type = amhw_zlg116_usbd_ep0_int_state_get(p_usb);
        amhw_zlg116_usbd_ep0_int_state_clear(p_usb, ep_int_type);
        p_dev->ep_int_type_union.ep_int_type[0] = ep_int_type;

        /* ����˵�0�ж� */
        if (p_dev->ep_int_type_union.ep_int_type_field[0].setup) {
            __usb_setup_handle(p_dev);
        }
        /* ������Ӧ����ô��֮ǰ���͹��������ٷ���һ�� */
        if (p_dev->ep_int_type_union.ep_int_type_field[0].in_nack) {
            __usb_in_handle(p_dev);
        }
        if (p_dev->ep_int_type_union.ep_int_type_field[0].out_ack){

        }
        if (p_dev->device.endpoint_info[0].pfn_callback != NULL) {
            (p_dev->device.endpoint_info[0].pfn_callback)(p_dev->device.endpoint_info[0].p_arg);
        }

        p_dev->ep_int_type_union.ep_int_type[0] = 0;
    }

    /* �˵�x */
    for (i = 1; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
            if ((p_dev->int_ep_union.int_ep_flag >> i) & 1) {

                ep_int_type = amhw_zlg116_usbd_epx_int_state_get(p_usb, (zlg116_usb_epx_t)(i - 1));
                amhw_zlg116_usbd_epx_int_state_clear(p_usb, (zlg116_usb_epx_t)(i - 1), ep_int_type);
                p_dev->ep_int_type_union.ep_int_type[i] = ep_int_type;

                if (p_dev->device.endpoint_info[i].pfn_callback != NULL) {
                    (p_dev->device.endpoint_info[i].pfn_callback)(p_dev->device.endpoint_info[i].p_arg);
                }
                p_dev->ep_int_type_union.ep_int_type[i] = 0;
            }
        }
    }
    p_dev->ep_int_type_union.ep_int_type[0] = 0;
    p_dev->int_ep_union.int_ep_flag = 0;
}

/**
 * \brief USB�жϷ�����
 */
static void __usbd_isr_function(void *p_device)
{
    am_zlg126_usbd_dev_t *p_dev =(am_zlg126_usbd_dev_t *) p_device;
    amhw_zlg116_usbd_t   *p_usb = (amhw_zlg116_usbd_t *)p_dev->p_info->usb_regbase;
    uint8_t int_status;

    if (NULL == p_dev)
        return;

    int_status = amhw_zlg116_usbd_int_state_get(p_usb);     /* ����ж�״̬ */
    amhw_zlg116_usbd_int_state_clear(p_usb, int_status);    /* ����ж�״̬ */

    /* �˵��ж� */
    if (int_status & AMHW_ZLG116_USB_INT_STATE_EPINTF) {
        __usb_device_interrupt_endpoint(p_dev);
    }

    /* ���߸�λ0�ж� */
    if (int_status & AMHW_ZLG116_USB_INT_STATE_RSTF) {
        am_usbd_init(&(p_dev->device));
    }

    /* ���߹��� */
    if (int_status & AMHW_ZLG116_USB_INT_STATE_SUSPENDF) {
        amhw_zlg116_usbd_int_state_clear(p_usb, AMHW_ZLG116_USB_INT_STATE_SUSPENDF);
    }

    /* ���߻��� */
    if (int_status & AMHW_ZLG116_USB_INT_STATE_RESUMF) {
        amhw_zlg116_usbd_int_state_clear(p_usb, AMHW_ZLG116_USB_INT_STATE_RESUMF);
    }

    /* ��⵽SOF */
    if (int_status & AMHW_ZLG116_USB_INT_STATE_SOFF) {

    }
}

/**
 * \brief ��ͨ����������������ʼ���˵���Ϣ���˵����������������ԣ�֧�ֵ�������С��
 *
 * \retval �ɹ����ظ�ʹ�õĶ˵������ʧ�ܷ���-1
 */
static am_err_t __init_ep_info (am_zlg126_usbd_dev_t *p_dev)
{
   uint8_t   ret     = 0;       /* ���巵��ֵ */
    uint8_t  *p_tmp  = NULL;    /* ���ݻ���ָ�� */
    uint8_t   ep_num = 0;       /* �˵�� */
    uint8_t  tmp     = 0;       /* ��ʱ����*/
    uint8_t  offset  = 0;       /* ƫ����*/
    uint8_t  len     = 0;       /* �������ܳ��� */
    am_usb_descriptor_endpoint_t  *p_desc_ep   = NULL;
    /* ��ȡ���������� */
    p_tmp = __find_desc_by_wValue1(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
    if (p_tmp == NULL)
        return AM_ERROR;
    /*���������������������������ܳ���*/
    len = (uint8_t)( ( *(p_tmp + 2) ) | ( ( *(p_tmp + 3)) >> 8 ) );
    /* �Ҷ˵�������*/
    while (tmp < len) {
        offset  =  *p_tmp;    /* �����������ֽ���,��һ��Ϊ����������*/
        p_tmp  +=   offset;   /* ��ƫ�� */
        tmp    +=   offset;
        /* ����Ƕ˵�������*/
        if ((*(p_tmp + 1) == AM_USB_DESC_TYPE_ENDPOINT) && (*p_tmp == AM_USB_DESC_LENGTH_ENDPOINT)) {
            p_desc_ep = (am_usb_descriptor_endpoint_t *)p_tmp;  // �˵�������
            // �˵��
            ep_num = p_desc_ep->b_endpoint_address & AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK;
            p_dev->device.endpoint_info[ep_num].inuse = 1;  // ��ʾ�˵㱻ʹ��
            p_dev->device.endpoint_info[ep_num].ep_address = p_desc_ep->b_endpoint_address;
            p_dev->device.endpoint_info[ep_num].max_packet_size = (p_desc_ep->wmax_packet_size[1] << 8) |
                                                                   p_desc_ep->wmax_packet_size[0];
            p_dev->device.endpoint_info[ep_num].transfer_type = p_desc_ep->bm_attributes;
            p_dev->device.endpoint_info[ep_num].stalled = 0;
            ret++;
        }
    }
    return ret;
}

/**
 * \brief ��ʼ��USB
 *
 * \param[in] p_dev     : ָ��USB�豸
 * \param[in] p_info    : ָ��USB�豸��Ϣ
 *
 * \return USB��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_usbd_dev_t *am_zlg126_usbd_init (am_zlg126_usbd_dev_t           *p_dev,
                                    const am_zlg126_usbd_devinfo_t *p_info)
{
    int i = 0;

    if (NULL == p_dev  || NULL == p_info) {
        return NULL;
    }

    p_dev->p_info = p_info;

    p_dev->device.p_info = p_info->p_devinfo;

    p_dev->device.ctrl_handle = p_dev;
    p_dev->device.p_interface = &__g_usb_device_interface;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        p_dev->device.endpoint_info[i].pfn_callback = NULL;
        p_dev->device.endpoint_info[i].p_arg = NULL;
    }

    /* ��ʼ����������*/
    p_dev->device.vendor_req.pfn_vendor = NULL;
    p_dev->device.vendor_req.p_arg      = NULL;

    p_dev->device.class_req.pfn_class   = NULL;
    p_dev->device.class_req.p_arg       = NULL;

    p_dev->device.device_address = 0;
    p_dev->device.state          = AM_USBD_STATE_DEFAULT;

    p_dev->int_ep_union.int_ep_flag = 0;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++)
        p_dev->ep_int_type_union.ep_int_type[i] = 0;

    p_dev->device.setup_data.bm_request_type    = 0;
    p_dev->device.setup_data.b_request          = 0;
    p_dev->device.setup_data.w_value            = 0;
    p_dev->device.setup_data.w_index            = 0;
    p_dev->device.setup_data.w_length           = 0;


    /**< \brief ���ö˵�0��Ĭ������ */
    p_dev->device.endpoint_info[0].stalled          = 0;
    p_dev->device.endpoint_info[0].ep_address       = 0;
    p_dev->device.endpoint_info[0].max_packet_size  = AM_USBD_MAX_EP_DATA_CNT;
    p_dev->device.endpoint_info[0].transfer_type    = AM_USB_ENDPOINT_CONTROL;
    p_dev->device.endpoint_info[0].inuse = 1;
    p_dev->device.endpoint_info[0].val_length       = 0;

    for (i = 1 ;i < AM_USBD_MAX_EP_CNT; i++) {
        p_dev->device.endpoint_info[i].stalled          = 0;
        p_dev->device.endpoint_info[i].ep_address       = 0;
        p_dev->device.endpoint_info[i].max_packet_size  = 0;
        p_dev->device.endpoint_info[i].transfer_type    = 0;
        p_dev->device.endpoint_info[i].inuse            = 0;
        p_dev->device.endpoint_info[i].val_length       = 0;
    }
    if (__init_ep_info(p_dev) == -1) {
#ifdef USB_DEBUG
        am_kprintf("fail to init endpoint\n");
#endif
    }

    p_dev->device.state = AM_USBD_CTRL_IDLE;

    am_usbd_ch9_std_request_init(&(p_dev->device));

    if (p_info->pfn_plfm_init) {
        p_info->pfn_plfm_init();
    }

    am_int_connect(p_info->inum, __usbd_isr_function, (void *)p_dev);
    am_int_enable(p_info->inum);
    am_usbd_init(&p_dev->device);

    return &(p_dev->device);
}

/**
 * \brief USB Device ȥ��ʼ��
 *
 * \param[in] p_info : ָ��USB�豸��Ϣ
 */
void am_zlg126_usbd_deinit (const am_zlg126_usbd_devinfo_t *p_info)
{
    if (p_info != NULL && p_info->pfn_plfm_deinit != NULL) {
        p_info->pfn_plfm_deinit();
    }
}
