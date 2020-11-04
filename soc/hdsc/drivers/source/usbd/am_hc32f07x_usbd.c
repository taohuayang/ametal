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

#include "am_hc32f07x_usbd.h"
#include "hw/amhw_hc32f07x_usbd.h"
#include "am_usb.h"
#include "am_int.h"
#include "am_usb_spec.h"
#include "am_usbd_ch9.h"
#include "ametal.h"
#include "am_board.h"
#include "string.h"
#include "am_mem.h"

/* ��Ҫ����USB��ʱ��ȥ��ע�ͣ������ڴ����д�ӡ������USB�жϺ��������� */
#define USB_DEBUG

static uint8_t __old_endpoint = 0;
__attribute__((section(".usb.buffer"))) uint8_t rec_data_buf[64];     /* ���ֽڶ��뷢�ͻ����� */
uint8_t           *rec_buff = rec_data_buf;
__attribute__((section(".usb.buffer"))) uint32_t send_data_buf[16];     /* ���ֽڶ��뷢�ͻ����� */
uint32_t           *send_buff = send_data_buf;
        
uint8_t state = AM_USBD_CTRL_IDLE;        
/**
 * \brief ͨ��wValue��ֵѰ��ָ����������
 *
 * \retval �ɹ�����������ָ�룬ʧ�ܷ���NULL
 *
 * \note �������������¼�����������ͨ���˷����
 */
static uint8_t * __find_desc_by_wValue1 (const am_hc32f07x_usbd_dev_t *p_dev,
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
static am_usb_status_t __usb_device_endpoint_init (am_hc32f07x_usbd_dev_t       *p_dev,
                                                   am_usbd_endpoint_init_t    *epinit)
{
    amhw_hc32_usbfs_t *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
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

    /* ʹ�ܶ˵� */
    if(epinit->endpoint_address & 0x80){

        amhw_hc32_usbfs_in_mpsiz_set(p_usb,
                                     epinit->max_packet_size,
                                     endpoint);
        amhw_hc32_usbfs_diepctl_set(p_usb,
//                                    AMHW_HC32F07X_USBFS_CTL_EPENA |
                                    AMHW_HC32F07X_USBFS_CTL_SD0PID,
                                    endpoint);
        if(endpoint == 0) {
            amhw_hc32_usbfs_in_txfnum_set(p_usb,
                                      endpoint,
                                      endpoint);
        }else {
            amhw_hc32_usbfs_in_txfnum_set(p_usb,
                                      1,
                                      endpoint);
        }    
        if(epinit->transfer_type == AMHW_HC32F07X_USBFS_EPTYPE_BULK)
            amhw_hc32_usbfs_in_txfnum_set(p_usb,
                                      0,
                                      endpoint);
        amhw_hc32_usbfs_in_eptyp_set(p_usb,
                                     (amhw_hc32f07x_usbfs_eptype_t)epinit->transfer_type,
                                     endpoint);
        amhw_hc32_usbfs_in_usbaep_set(p_usb,
                                      endpoint);

        amhw_hc32_usbfs_iepintm_enable(p_usb, endpoint);
    }else {

        amhw_hc32_usbfs_out_mpsiz_set(p_usb,
                                      epinit->max_packet_size,
                                      endpoint);            
        amhw_hc32_usbfs_doepctl_set(p_usb,
                                    AMHW_HC32F07X_USBFS_CTL_EPENA |
                                    AMHW_HC32F07X_USBFS_CTL_SD0PID,
                                    endpoint);
        amhw_hc32_usbfs_out_eptyp_set(p_usb,
                                      (amhw_hc32f07x_usbfs_eptype_t)epinit->transfer_type,
                                      endpoint);
        amhw_hc32_usbfs_out_usbaep_set(p_usb,
                                       endpoint);
        amhw_hc32_usbfs_oepintm_enable(p_usb, endpoint);

    }

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
static am_usb_status_t __usb_device_endpoint_deinit (am_hc32f07x_usbd_dev_t *p_dev,
                                                     uint8_t            endpoint)
{
    amhw_hc32_usbfs_t *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    endpoint &= AM_USBD_ENDPOINT_NUMBER_MASK;


    amhw_hc32_usbfs_doepctl_set(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_EPDIS,
                                endpoint);
    amhw_hc32_usbfs_diepctl_set(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_EPDIS,
                                endpoint);  /* ���ܶ˵� */

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵�����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ
 */
static am_usb_status_t __usb_device_endpoint_stall (am_hc32f07x_usbd_dev_t *p_dev,
                                                   uint8_t            endpoint_addr)
{
    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;
    amhw_hc32_usbfs_t *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    p_dev->device.endpoint_info[endpoint].stalled = 1;    /* ����������־ */

    amhw_hc32_usbfs_diepctl_set(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_STALL,
                                endpoint);
    amhw_hc32_usbfs_doepctl_set(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_STALL,
                                endpoint);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵㲻����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ  D7�� 1��USB_IN  0��USB_OUT
 */
static am_usb_status_t __usb_device_endpoint_unstall (am_hc32f07x_usbd_dev_t *p_dev,
                                                      uint8_t               endpoint_addr)
{
    amhw_hc32_usbfs_t *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;

    p_dev->device.endpoint_info[endpoint].stalled = 0;

    amhw_hc32_usbfs_diepctl_clr(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_STALL,
                                endpoint);
    amhw_hc32_usbfs_doepctl_clr(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_STALL,
                                endpoint);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ��ʼ��USB�豸
 */
static am_usb_status_t __usb_device_init (am_usbd_handle_t handle)
{
    uint32_t i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_hc32f07x_usbd_dev_t *p_dev = (am_hc32f07x_usbd_dev_t *)handle;
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;

    p_dev->device.state =    AM_USBD_CTRL_IDLE;
    p_dev->device.device_address = 0;

    p_dev->dma_enable = 1;

    /* ����ȫ���ж� */
    amhw_hc32_usbfs_gintmsk_disable (p_usb);

    while(amhw_hc32_usbfs_ahbidl_read (p_usb) == AM_FALSE);
    amhw_hc32_usbfs_csrst_enable(p_usb);
    while(amhw_hc32_usbfs_csrst_get(p_usb) == AM_TRUE){
        am_udelay(1);
        i++;
        if(i>100000) break;    
    };

    amhw_hc32_usbfs_physel_set (p_usb);

    /* ģ����λ */
    amhw_hc32_usbfs_csrst_enable(p_usb);
    while(amhw_hc32_usbfs_csrst_get(p_usb) == AM_TRUE){
        am_udelay(1);
        i++;
        if(i>100000)    break;
    };
    am_mdelay(20);
    p_usb->gusbcfg |=1<<6;
    if(p_dev->dma_enable == 1){        

        /* DMAģʽ */
        amhw_hc32_usbfs_hbstlen_set (p_usb, AMHW_HC32_USBFS_INCR8);
        amhw_hc32_usbfs_dma_enable (p_usb);        
    }

    /* ֡������� */
    amhw_hc32_usbfs_dfivl_set(p_usb, AMHW_HC32F07X_USBFS_PFIVL80);

    /* ȫ�� */
    amhw_hc32_usbfs_dspd_set(p_usb);

    amhw_hc32_usbfs_rxfd_set(p_usb,128);
    amhw_hc32_usbfs_nptfd_set(p_usb, 64);
    p_usb->gnptxfsiz = ((64 << 16));
    amhw_hc32_usbfs_ineptxfd_set(p_usb, 256, 1);
    amhw_hc32_usbfs_ineptxsa_set(p_usb,(128+64),1);

    amhw_hc32_usbfs_ineptxfd_set(p_usb, 256, 3);
    amhw_hc32_usbfs_ineptxsa_set(p_usb,(256+128+64),3);

    amhw_hc32_usbfs_ineptxfd_set(p_usb, 256, 5);
    amhw_hc32_usbfs_ineptxsa_set(p_usb,(256+256+128+64),5);
        
        amhw_hc32_usbfs_ineptxfd_set(p_usb, 256, 7);
    amhw_hc32_usbfs_ineptxsa_set(p_usb,(256+256+256+128+64),7);

    amhw_hc32_usbfs_diepmsk_disable(p_usb, AMHW_HC32F07X_USBFS_EP_IN_ALL);
    amhw_hc32_usbfs_doepmsk_disable(p_usb, AMHW_HC32F07X_USBFS_EP_OUT_ALL);
    p_usb->daint = 0xFFFFFFFF;
    p_usb->daintmsk = 0xFFFFFFFF;
    for (i = 0; i < 9; i++) {
        amhw_hc32_usbfs_oepint_set(p_usb,i);
        amhw_hc32_usbfs_iepint_set(p_usb,i);
        amhw_hc32_usbfs_diepint_clr(p_usb,AMHW_HC32F07X_USBFS_IN_ALL,i);
        amhw_hc32_usbfs_doepint_clr(p_usb,AMHW_HC32F07X_USBFS_EP_OUT_ALL,i);
        amhw_hc32_usbfs_oepintm_enable(p_usb, i);
        amhw_hc32_usbfs_iepintm_enable(p_usb, i);
    }

    p_usb->dcfg &= ~0x03ul<<12;
        
    /* ��Ͽ� */
    amhw_hc32_usbfs_dctl_disable(p_usb, AMHW_HC32F07X_USBFS_DCTL_SDIS);

    amhw_hc32_usbfs_int_disable(p_usb, AMHW_HC32F07X_USBFS_INT_ALL);
    amhw_hc32_usbfs_gintsts_clr(p_usb, AMHW_HC32F07X_USBFS_INT_ALL);

    if(p_dev->dma_enable == 0){
        amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_RXFNE);
    }
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_WKUOINT);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_USBSUSP);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_USBRST);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_ENUMDNE);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_ESUSP);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_SOF);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_OEPINT);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_IEPINT);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_INISOOUT);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_IISOIXFR);

    amhw_hc32_usbfs_gintmsk_enable (p_usb);

    p_dev->ep_int_type_union.ep_int_type[0] = 0;

    for (i = 0; i < AM_USBD_MAX_EP_CNT - 1; i++) {
        p_dev->ep_int_type_union.ep_int_type[i + 1] = 0;
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
    am_hc32f07x_usbd_dev_t *p_dev = (am_hc32f07x_usbd_dev_t *)handle;
    amhw_hc32_usbfs_t      *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    int i = 0;

    if (handle == NULL){
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    amhw_hc32_usbfs_gintmsk_disable (p_usb);
    for (i = 0; i < 9; i++) {
        amhw_hc32_usbfs_oepintm_disable(p_usb, i);
        amhw_hc32_usbfs_iepintm_disable(p_usb, i);
        amhw_hc32_usbfs_diepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPDIS, i);
        amhw_hc32_usbfs_doepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPDIS, i);
    }

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
    am_hc32f07x_usbd_dev_t *p_dev = (am_hc32f07x_usbd_dev_t *)handle;
    uint32_t send_once_size = 0;
    uint8_t endpoint = endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK;
    amhw_hc32_usbfs_t *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;

    if (endpoint >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;
    p_dev->data_info[endpoint].length = length;
        p_dev->data_info[endpoint].p_buf = buffer;

    if (p_dev->data_info[endpoint].length > AM_USBD_MAX_EP_DATA_CNT) {
        send_once_size = AM_USBD_MAX_EP_DATA_CNT;
    } else {
        send_once_size = p_dev->data_info[endpoint].length;
    }
    memset(send_data_buf, 0, send_once_size);
    length -= length;

    memcpy(send_data_buf, buffer, send_once_size);
    amhw_hc32_usbfs_in_xfrsiz_set(p_usb, send_once_size, endpoint);
    amhw_hc32_usbfs_in_pktcnt_set(p_usb, 1, endpoint);

    if(p_dev->dma_enable == 1){
    amhw_hc32_usbfs_in_dmaaddr_set(p_usb,
                                   (uint32_t )send_buff,
                                   endpoint);
    }
    if(endpoint!=0) {
        amhw_hc32_usbfs_nextep_set(p_usb,
                                   endpoint,
                                   0);
    }                               
//        amhw_hc32_usbfs_nextep_set(p_usb,
//                                   endpoint,
//                                   __old_endpoint);
    __old_endpoint = endpoint;
    amhw_hc32_usbfs_diepctl_set(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_EPENA |
                                AMHW_HC32F07X_USBFS_CTL_CNAK,
                                endpoint);

    if(p_dev->dma_enable == 0){
        amhw_hc32_usbfs_ineptxsa_set(p_usb,
                                     (uint16_t)send_buff,
                                     endpoint);
    }
        
    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief �˵�0���Ϳհ�
 */
static void __ep0_send_empty_packet (am_usbd_handle_t handle)
{
    am_hc32f07x_usbd_dev_t *p_dev = (am_hc32f07x_usbd_dev_t *)handle;
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;

    switch (p_dev->device.state) {
    case AM_USBD_CTRL_SETUP:
        p_dev->device.state = AM_USBD_CTRL_IN;
        break;

    case AM_USBD_CTRL_IN:
        __usb_device_send(p_usb, 0, NULL,0);
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
    am_hc32f07x_usbd_dev_t *p_dev = (am_hc32f07x_usbd_dev_t *)handle;
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    int i = 0;
    uint8_t endpoint = endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK;
    uint8_t avali_data_cnt = 0;     /* fifo����Ч���ݸ��� */

    /* �������ݵĶ˵㷽�������OUT_OUT */
    if ((endpoint_address & AM_USB_DESC_ENDPOINT_ADDR_DIR_MASK) !=
            AM_USB_DESC_ENDPOINT_ADDR_DIR_OUT)
        return AM_USB_STATUS_INVALID_REQUEST;

    if (endpoint >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    if(length > AM_USBD_MAX_EP_DATA_CNT){
        length = AM_USBD_MAX_EP_DATA_CNT;
    }
    avali_data_cnt = length - amhw_hc32_usbfs_out_xfrsiz_get(p_usb, endpoint);            

    for(i=0;i<avali_data_cnt;i++){
        buffer[i] = rec_data_buf[i];
    }

    amhw_hc32_usbfs_rxfflsh_enable (p_usb);
    while( ((p_usb->grstctl >>4)&0x01)==1){;}
    amhw_hc32_usbfs_out_xfrsiz_set(p_usb, length, endpoint);
    amhw_hc32_usbfs_out_pktcnt_set(p_usb, 1, endpoint);
    
    if(p_dev->dma_enable == 1){

        amhw_hc32_usbfs_out_dmaaddr_set(p_usb, 
                                        (uint32_t )rec_buff,
                                        endpoint);
    }

    amhw_hc32_usbfs_doepctl_set(p_usb, 
                                 AMHW_HC32F07X_USBFS_CTL_EPENA |
                                 AMHW_HC32F07X_USBFS_CTL_CNAK,
                                 endpoint);
    
    p_dev->device.endpoint_info[endpoint].val_length = avali_data_cnt;

    if (avali_data_cnt == 0)
        return (am_usb_status_t)0;

    return (am_usb_status_t)avali_data_cnt;
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
static void __usb_device_setdefault_state(am_hc32f07x_usbd_dev_t *p_dev)
{
    /* �����ַ */
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    int i = 0;

    amhw_hc32_usbfs_dad_set(p_usb,0); 

    /* ʹ�ܶ˵� */
    amhw_hc32_usbfs_diepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPENA, 0);    
    amhw_hc32_usbfs_diepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPENA, 1);
    amhw_hc32_usbfs_diepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPENA, 3);
    amhw_hc32_usbfs_diepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPENA, 5);
    amhw_hc32_usbfs_diepctl_set(p_usb, AMHW_HC32F07X_USBFS_CTL_EPENA, 7);

    /* ���ж�״̬ */
    amhw_hc32_usbfs_gintsts_clr(p_usb, AMHW_HC32F07X_USBFS_INT_ALL);
    amhw_hc32_usbfs_int_enable(p_usb, AMHW_HC32F07X_USBFS_INT_ALL);

    for (i = 0; i < 9; i++) {
        amhw_hc32_usbfs_diepint_clr(p_usb,AMHW_HC32F07X_USBFS_EP_IN_ALL,i);
        amhw_hc32_usbfs_doepint_clr(p_usb,AMHW_HC32F07X_USBFS_EP_OUT_ALL,i);

        /* ʹ�����ж˵��ж� */
        amhw_hc32_usbfs_oepintm_enable(p_usb, i);    
        amhw_hc32_usbfs_iepintm_enable(p_usb, i);    

        /* ʹ�ܶ˵�������ж� */
        amhw_hc32_usbfs_doepmsk_enable(p_usb, AMHW_HC32F07X_USBFS_EP_OUT_ALL);
        amhw_hc32_usbfs_diepmsk_enable(p_usb, AMHW_HC32F07X_USBFS_EP_IN_ALL);
    }
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
    am_hc32f07x_usbd_dev_t *p_dev = (am_hc32f07x_usbd_dev_t *)handle;
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    am_usb_status_t error = AM_USB_STATUS_ERROR;
    uint8_t *temp8;
    am_usbd_ep_status_t *endpointStatus = NULL;
    uint8_t endpoint = 0;

    if (!handle)
        return AM_USB_STATUS_INVALID_HANDLE;

    switch ((int)type) {
        case AM_USBD_CONTROL_RUN:
            amhw_hc32_usbfs_dctl_disable(p_usb, AMHW_HC32F07X_USBFS_DCTL_SDIS);    /* ���� */
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_STOP:
            amhw_hc32_usbfs_dctl_enable(p_usb, AMHW_HC32F07X_USBFS_DCTL_SDIS); /* �Ͽ����� */
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
            amhw_hc32_usbfs_dctl_enable(p_usb, AMHW_HC32F07X_USBFS_DCTL_RWUSIG);
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

/**
 * \brief ��ͨ����������������ʼ���˵���Ϣ���˵����������������ԣ�֧�ֵ�������С��
 *
 * \retval �ɹ����ظ�ʹ�õĶ˵������ʧ�ܷ���-1
 */
static am_err_t __init_ep_info (am_hc32f07x_usbd_dev_t *p_dev)
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
static void __ctrl_deal_handle (am_hc32f07x_usbd_dev_t *p_dev)
{
    am_usbd_dev_t   *p_usbd_dev = &p_dev->device;
    am_data_info_t  *p_ctrl     = &p_usbd_dev->ctrl_info;


    if(p_ctrl->p_buf != NULL){
        if(p_ctrl->length > p_usbd_dev->setup_data.w_length){
            p_ctrl->length = p_usbd_dev->setup_data.w_length;
        }
    __usb_device_send(p_usbd_dev, 0, p_ctrl->p_buf, p_ctrl->length);

    }else{
        __usb_device_send(p_usbd_dev, 0, NULL, 0);
    }
    p_usbd_dev->state = AM_USBD_CTRL_IDLE;
}

/**
 * \brief ����IN����
 */
static void __usb_in_handle(am_hc32f07x_usbd_dev_t *p_dev)
{
    if ((p_dev->device.setup_data.bm_request_type &
            AM_USB_REQ_TYPE_DIR_MASK) == AM_USB_REQ_TYPE_DIR_IN &&
            p_dev->device.state == AM_USBD_CTRL_SETUP) {
        __ctrl_deal_handle(p_dev);
    }else{
        __ep0_send_empty_packet(p_dev);
    }
}
int xfrc=0;
/**
 * \brief setup������
 */
static void __usb_setup_handle (am_hc32f07x_usbd_dev_t *p_dev)
{
    uint8_t ret = AM_USB_STATUS_NOT_SUPPORTED;
    uint8_t code = 0, type = 0;
    amhw_hc32_usbfs_t *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    am_usbd_dev_t      *p_usb_dev = &(p_dev->device);
    am_data_info_t     *p_data_info = &(p_usb_dev->ctrl_info);
    int i=0;

    p_data_info->offset = 0;
    p_data_info->p_buf  = NULL;

    if(p_usb_dev->state == AM_USBD_CTRL_IDLE) {  // ���״̬Ϊ����̬

        p_usb_dev->state = AM_USBD_CTRL_SETUP;   // ����״̬
        type = p_usb_dev->setup_data.bm_request_type;
        code = p_usb_dev->setup_data.b_request;    

//        am_kprintf("bm_request_type = %02x\r\n", p_dev->device.setup_data.bm_request_type);
//        am_kprintf("b_request = %02x\r\n", p_dev->device.setup_data.b_request);
//        am_kprintf("w_value = %02x\r\n", p_dev->device.setup_data.w_value);
//        am_kprintf("w_index = %02x\r\n", p_dev->device.setup_data.w_index);
//        am_kprintf("w_length = %02x\r\n", p_dev->device.setup_data.w_length);
    }

    if((type & 0x80) && (p_data_info->length != 0)){
        am_usbd_recv(p_usb_dev, 0, p_data_info->p_buf, p_data_info->length);
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
                ret = p_usb_dev->p_funcs->pfn_feature_set(p_usb_dev);                        

                break;
            case AM_USB_REQ_STANDARD_SET_FEATURE:
                ret = p_usb_dev->p_funcs->pfn_feature_set(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_SET_ADDRESS:
                p_usb_dev->device_address = p_usb_dev->setup_data.w_value;

                /* ���õ�ַ */
                amhw_hc32_usbfs_dad_set(p_usb,p_usb_dev->setup_data.w_value);
                __usb_device_send(p_usb_dev, 0, NULL,0);

                ret = AM_USB_STATUS_SUCCESS;
                break;
            case AM_USB_REQ_STANDARD_GET_DESCRIPTOR:
                ret = p_usb_dev->p_funcs->pfn_desc_get(
                             p_usb_dev, &p_data_info->p_buf, &p_data_info->length );

                /* steup������ */
                __ctrl_deal_handle(p_dev);

                break;
            case AM_USB_REQ_STANDARD_SET_DESCRIPTOR:
                ret = p_usb_dev->p_funcs->pfn_feature_set(p_usb_dev);
                break;
            case AM_USB_REQ_STANDARD_GET_CONFIGURATION:
                ret = p_usb_dev->p_funcs->pfn_config_get(
                        p_usb_dev, &p_data_info->p_buf, &p_data_info->length);
                ret = AM_USB_STATUS_SUCCESS;
                break;
            case AM_USB_REQ_STANDARD_SET_CONFIGURATION:
                ret = p_usb_dev->p_funcs->pfn_config_set(p_usb_dev);

                for (i = 1; i < AM_USBD_MAX_EP_CNT; i++) {
                    if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
                        if(p_dev->device.endpoint_info[i].ep_address & 0x80){
                                                    
                        }else{
                            am_usbd_recv(p_usb_dev, 
                                         p_dev->device.endpoint_info[i].ep_address, 
                                         NULL, 
                                         64);
                        }
                    }
                }

                __usb_device_send(p_usb_dev, 0, NULL, 0);
                p_usb_dev->state = AM_USBD_CTRL_IDLE;
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
        __ctrl_deal_handle(p_dev);
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

    if(ret == AM_USB_STATUS_SUCCESS){
        p_usb_dev->state = AM_USBD_CTRL_SETUP;
    }
}

/**
 * \brief �˵��ж�
 */
static void __usb_device_interrupt_endpoint (am_hc32f07x_usbd_dev_t *p_dev)
{
    int out_ep_index = 0;         /* �����жϵĶ˵� */
    int in_ep_index  = 0;
    uint16_t ep_int_type = 0;      /* ����Ķ˵��ж����� */
    uint32_t i = 0;
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    am_usbd_dev_t   *p_usbd_dev = &p_dev->device;

    out_ep_index = amhw_hc32_usbfs_oepint_get(p_usb)&0x155;
    in_ep_index  = amhw_hc32_usbfs_iepint_get(p_usb)&0xab;

    p_dev->int_ep_union.int_ep_flag = out_ep_index | in_ep_index;

    /* �˵�0�ж� */
    if (p_dev->int_ep_union.int_ep_flag_field.in_out_ep0) {

        /* ��ö˵�0�����ľ����ж����� */
        ep_int_type  = (amhw_hc32_usbfs_int_outstat_get(p_usb, 0) <<8 );
        p_usb->doepint0 |= 0xff;
        ep_int_type |= amhw_hc32_usbfs_int_instat_get(p_usb, 0)&0xff;
        p_usb->diepint0 |= 0xff;    

        p_dev->ep_int_type_union.ep_int_type[0] = ep_int_type;
                    
        /* ����˵�0�ж� */
        if (p_dev->ep_int_type_union.ep_int_type_field[0].out_stup ) {    
            __usb_setup_handle(p_dev);
        }

        if (p_dev->ep_int_type_union.ep_int_type_field[0].out_xfrc ) {

        }
        if (p_dev->ep_int_type_union.ep_int_type_field[0].in_xfrc ) {

            if(p_dev->data_info[0].length > 64){
                p_dev->data_info[0].length -= 64;
                p_dev->data_info[0].p_buf += 64;
                __usb_device_send (p_usbd_dev,
                                    0,
                                    p_dev->data_info[0].p_buf,
                                    p_dev->data_info[0].length);

            }else{
                p_dev->data_info[0].length = 0;
                state=AM_USBD_CTRL_IN;
            }
            p_usbd_dev->state = AM_USBD_CTRL_IDLE;
            if(state==AM_USBD_CTRL_IN){

                amhw_hc32_usbfs_out_pktcnt_set(p_usb, 1, 0);
                amhw_hc32_usbfs_out_xfrsiz_set(p_usb, 64, 0);
                amhw_hc32_usbfs_out_dmaaddr_set(p_usb,
                                            (uint32_t )&p_usbd_dev->setup_data,
                                            0);
                amhw_hc32_usbfs_doepctl_set(p_usb,
                                        AMHW_HC32F07X_USBFS_CTL_CNAK |                     
                                        AMHW_HC32F07X_USBFS_CTL_EPENA,
                                        0);
                state = AM_USBD_CTRL_IDLE;
            }
        }
                
        if (p_dev->ep_int_type_union.ep_int_type_field[0].in_timeout){

        }
        if (p_dev->device.endpoint_info[0].pfn_callback != NULL) {
            (p_dev->device.endpoint_info[0].pfn_callback)(p_dev->device.endpoint_info[0].p_arg);
        }

        p_dev->ep_int_type_union.ep_int_type[0] = 0;
        ep_int_type = 0; 
    }

    /* �˵�x */
    for (i = 1; i < 9; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {                        
            if (((p_dev->int_ep_union.int_ep_flag >> i) & 1)) {
				
                ep_int_type = amhw_hc32_usbfs_int_instat_get(p_usb, i);
                amhw_hc32_usbfs_diepint_clr(p_usb, ep_int_type & 0xff, i);       
                ep_int_type |= (amhw_hc32_usbfs_int_outstat_get(p_usb, i) << 8);
                amhw_hc32_usbfs_doepint_clr(p_usb, 0xff, i);

                p_dev->ep_int_type_union.ep_int_type[i] = ep_int_type;

                if (p_dev->ep_int_type_union.ep_int_type_field[i].out_xfrc ) {
                    amhw_hc32_usbfs_rxfflsh_enable (p_usb);
                    while( ((p_usb->grstctl >>4)&0x01)==1){;}
                }
                if (p_dev->ep_int_type_union.ep_int_type_field[i].in_xfrc ) {

                    if(p_dev->data_info[i].length > 64){
                        p_dev->data_info[i].length -= 64;
                        p_dev->data_info[i].p_buf += 64;
                        __usb_device_send (p_usbd_dev,
                                           i,
                                           p_dev->data_info[i].p_buf,
                                           p_dev->data_info[i].length);
                                            
                    } else{
                        p_dev->data_info[i].length=0;
                    }                                    
                    amhw_hc32_usbfs_txfnum_write (p_usb, (amhw_hc32_usbfs_txfifonum_type_t)1);
                    amhw_hc32_usbfs_txfflsh_enable (p_usb);
                    while( ((p_usb->grstctl >>5)&0x01)==1);
                }

                if (p_dev->device.endpoint_info[i].pfn_callback != NULL) {
                    (p_dev->device.endpoint_info[i].pfn_callback)(p_dev->device.endpoint_info[i].p_arg);
                }
                p_dev->ep_int_type_union.ep_int_type[i] = 0;
                ep_int_type = 0;
            }
        }
    }
    p_dev->ep_int_type_union.ep_int_type[0] = 0;
    p_dev->int_ep_union.int_ep_flag = 0;
}

static void __usb_device_reset_isr (am_hc32f07x_usbd_dev_t *p_dev)
{
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    am_usbd_dev_t      *p_usb_dev = &(p_dev->device);
    am_usbd_endpoint_init_t    epinit;
    uint32_t i = 0;

    amhw_hc32_usbfs_dctl_disable(p_usb,
                                 AMHW_HC32F07X_USBFS_DCTL_RWUSIG);


    amhw_hc32_usbfs_txfnum_write (p_usb,
                               AMHW_HC32_USBFS_TXFIFO0);
    amhw_hc32_usbfs_txfflsh_enable (p_usb);
    while((p_usb->grstctl >> 5) & 0x01){
        i++;am_udelay(1);
        if(i > 200000)  break;
    };
    am_udelay(3);

    for(i=0; i<9; i++){
        amhw_hc32_usbfs_diepint_clr(p_usb,
                                AMHW_HC32F07X_USBFS_IN_XFRC |
                                AMHW_HC32F07X_USBFS_IN_EPDISD |
                                AMHW_HC32F07X_USBFS_IN_TO |
                                AMHW_HC32F07X_USBFS_IN_ITTXFE |
                                AMHW_HC32F07X_USBFS_IN_INEPNE,
                                i);
        amhw_hc32_usbfs_doepint_clr(p_usb,
                                AMHW_HC32F07X_USBFS_OUT_XFRC |
                                AMHW_HC32F07X_USBFS_OUT_EPDISD |
                                AMHW_HC32F07X_USBFS_OUT_STUP |
                                AMHW_HC32F07X_USBFS_OUT_OTEPDIS |
                                AMHW_HC32F07X_USBFS_OUT_RECSTUP,
                                i);
    }

    amhw_hc32_usbfs_oepint_set(p_usb,0);
    amhw_hc32_usbfs_iepint_set(p_usb,0);
    amhw_hc32_usbfs_oepintm_enable(p_usb, 0);
    amhw_hc32_usbfs_iepintm_enable(p_usb, 0);
        
    amhw_hc32_usbfs_doepmsk_enable(p_usb, 
                                   AMHW_HC32F07X_USBFS_EP_OUT_ALL);
    amhw_hc32_usbfs_diepmsk_enable(p_usb, 
                                   AMHW_HC32F07X_USBFS_EP_IN_ALL );

    amhw_hc32_usbfs_dad_set(p_usb,0);                                                                                        
                                                                
    amhw_hc32_usbfs_gintsts_clr(p_usb,
                                AMHW_HC32F07X_USBFS_INT_USBRST);

    amhw_hc32_usbfs_in_txfnum_set(p_usb, 0, 0);

    p_usb->doepsiz0 |= 3 << 29;
    amhw_hc32_usbfs_in_txfnum_set(p_usb,
                                  0,
                                  0);
                                                                    
    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
            epinit.endpoint_address = p_dev->device.endpoint_info[i].ep_address;
            epinit.max_packet_size = p_dev->device.endpoint_info[i].max_packet_size;
            epinit.transfer_type = p_dev->device.endpoint_info[i].transfer_type;                                          
            __usb_device_endpoint_init(p_dev, &epinit);
        }
    }
    amhw_hc32_usbfs_out_pktcnt_set(p_usb, 1, 0);
    amhw_hc32_usbfs_out_xfrsiz_set(p_usb, 64, 0);
    amhw_hc32_usbfs_out_dmaaddr_set(p_usb,
                                    (uint32_t )&p_usb_dev->setup_data,
                                    0);
    amhw_hc32_usbfs_out_usbaep_set(p_usb, 0);    
    amhw_hc32_usbfs_doepctl_set(p_usb,
                                AMHW_HC32F07X_USBFS_CTL_EPENA |
                                AMHW_HC32F07X_USBFS_CTL_CNAK,
                                0);        
}


/**
 * \brief USB�жϷ�����
 */
static void __usbd_isr_function(void *p_device)
{
    am_hc32f07x_usbd_dev_t *p_dev =(am_hc32f07x_usbd_dev_t *) p_device;
    amhw_hc32_usbfs_t   *p_usb = (amhw_hc32_usbfs_t *)p_dev->p_info->usb_regbase;
    uint32_t int_status;

    if (NULL == p_dev)
        return;

    int_status = amhw_hc32_usbfs_gintsts_get(p_usb);
    amhw_hc32_usbfs_gintsts_clr(p_usb, AMHW_HC32F07X_USBFS_INT_ALL);

    if (!int_status ) {
         return;
    }
    /* �˵��ж� */
    if (int_status & AMHW_HC32F07X_USBFS_INT_OEPINT) {
        __usb_device_interrupt_endpoint(p_dev);

    }

    if (int_status & AMHW_HC32F07X_USBFS_INT_IEPINT) {            
        __usb_device_interrupt_endpoint(p_dev);
    }
    /* ���߸�λ0�ж� */
    if (int_status & AMHW_HC32F07X_USBFS_INT_USBRST) {
      __usb_device_reset_isr (p_dev);
    }

    /* ���߹��� */
    if (int_status & AMHW_HC32F07X_USBFS_INT_USBSUSP) {

//            amhw_hc32_usbfs_gatclk_set(p_usb, 1);
    }

    /* ���߻��� */
    if (int_status & AMHW_HC32F07X_USBFS_INT_WKUOINT) {

        amhw_hc32_usbfs_gatclk_set(p_usb, 1);
        amhw_hc32_usbfs_dctl_enable(p_usb, AMHW_HC32F07X_USBFS_DCTL_RWUSIG);
    }

    /* ���ö����� */
    if (int_status & AMHW_HC32F07X_USBFS_INT_ENUMDNE) {

      amhw_hc32_usbfs_trdt_set (p_usb, 9);
    }

    /* ��⵽SOF */
    if (int_status & AMHW_HC32F07X_USBFS_INT_SOF) {

    }

}

/**
 * \brief ��ʼ��USB
 *
 * \param[in] p_dev     : ָ��USB�豸
 * \param[in] p_info    : ָ��USB�豸��Ϣ
 *
 * \return USB��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_usbd_dev_t *am_hc32f07x_usbd_init (am_hc32f07x_usbd_dev_t           *p_dev,
                                    const am_hc32f07x_usbd_devinfo_t *p_info)
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
    am_usbd_init(&p_dev->device);
    am_int_enable(p_info->inum);

    return &(p_dev->device);
}

/**
 * \brief USB Device ȥ��ʼ��
 *
 * \param[in] p_info : ָ��USB�豸��Ϣ
 */
void am_hc32f07x_usbd_deinit (const am_hc32f07x_usbd_devinfo_t *p_info)
{
    if (p_info != NULL && p_info->pfn_plfm_deinit != NULL) {
        p_info->pfn_plfm_deinit();
    }
}
