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
 * - 1.00 
 * \endinternal
 */

#include "am_hc32f460_usbd.h"
#include "amhw_hc32f460_usbd.h"
#include "am_usb.h"
#include "am_int.h"
#include "am_usb_spec.h"
#include "am_usbd_ch9.h"
#include "usb_core.h"
#include "usbd_desc.h"
#include "usbd_usr.h"
#include "usbd_msc_core.h"
#include "hc32f460_irq_handle.h"
#include "am_vdebug.h"
#include "usbd_msc_bot.h"
#include "string.h"
#include "usbd_hid_mouse_core.h"

#define USBFS_GLB       (1 << 19)
USB_OTG_CORE_HANDLE USB_OTG_dev;
extern MSC_BOT_CBW_TypeDef MSC_BOT_cbw;
extern uint8_t data_update_flag;

/* Interrupt Handlers */
//extern uint32_t DCD_ReadDevInEP (USB_OTG_CORE_HANDLE *pdev, uint8_t epnum);
extern uint32_t DCD_HandleInEP_ISR(am_hc32f460_usbd_dev_t *p_dev, USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleOutEP_ISR(am_hc32f460_usbd_dev_t *p_dev, USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleSof_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleRxStatusQueueLevel_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleUsbReset_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleEnumDone_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleResume_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_HandleUSBSuspend_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_IsoINIncomplete_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_IsoOUTIncomplete_ISR(USB_OTG_CORE_HANDLE *pdev);
extern uint32_t DCD_SessionRequest_ISR(USB_OTG_CORE_HANDLE *pdev);



/* ��Ҫ����USB��ʱ��ȥ��ע�ͣ������ڴ����д�ӡ������USB�жϺ��������� */
//#define USB_DEBUG
/**
 * \brief ͨ��wValue��ֵѰ��ָ����������
 *
 * \retval �ɹ�����������ָ�룬ʧ�ܷ���NULL
 *
 * \note �������������¼�����������ͨ���˷����
 */
static uint8_t * __find_desc_by_wValue1(const am_hc32f460_usbd_dev_t *p_dev,
        uint16_t w_value)
{
    int i;

    for (i = 0; i < p_dev->p_info->p_devinfo->descriptor_num; i++) {
        if (w_value == p_dev->p_info->p_devinfo->p_descriptor[i].desc_wValue) {
            return (uint8_t *) (p_dev->p_info->p_devinfo->p_descriptor[i].p_desc);
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
static am_usb_status_t __usb_device_endpoint_init(am_hc32f460_usbd_dev_t *p_dev,
        am_usbd_endpoint_init_t *epinit)
{
    uint16_t max_packet_size = epinit->max_packet_size;
    uint8_t endpoint = (epinit->endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK);
    int i;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        /* �˵��������б���ָ��������˵� */
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE
                && p_dev->device.endpoint_info[i].ep_address
                        == epinit->endpoint_address) {
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
static am_usb_status_t __usb_device_endpoint_deinit(USB_OTG_CORE_HANDLE *pdev,
        uint8_t ep_addr)
{
    USB_OTG_EP *ep;

    if ((ep_addr & 0x80u) == 0x80u) {
        ep = &pdev->dev.in_ep[ep_addr & 0x7Fu];
    }
    else {
        ep = &pdev->dev.out_ep[ep_addr & 0x7Fu];
    }
    ep->num = ep_addr & 0x7Fu;
    ep->is_in = ((0x80u & ep_addr) != 0u);
    USB_OTG_EPDeactivate(pdev, ep);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵�����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ
 */
static am_usb_status_t __usb_device_endpoint_stall(USB_OTG_CORE_HANDLE *pdev,
        uint8_t epnum)
{
    USB_OTG_EP *ep;
    if ((0x80u & epnum) == 0x80u) {
        ep = &pdev->dev.in_ep[epnum & 0x7Fu];
    }
    else {
        ep = &pdev->dev.out_ep[epnum];
    }

    ep->is_stall = 1u;
    ep->num = epnum & 0x7Fu;
    ep->is_in = ((epnum & 0x80u) == 0x80u);

    USB_OTG_EPSetStall(pdev, ep);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵㲻����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ  D7�� 1��USB_IN  0��USB_OUT
 */
static am_usb_status_t __usb_device_endpoint_unstall(USB_OTG_CORE_HANDLE *pdev,
        uint8_t epnum)
{
    USB_OTG_EP *ep;
    if ((0x80u & epnum) == 0x80u) {
        ep = &pdev->dev.in_ep[epnum & 0x7Fu];
    }
    else {
        ep = &pdev->dev.out_ep[epnum];
    }

    ep->is_stall = 0u;
    ep->num = epnum & 0x7Fu;
    ep->is_in = ((epnum & 0x80u) == 0x80u);

    USB_OTG_EPClearStall(pdev, ep);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ��ʼ��USB�豸
 */
static am_usb_status_t __usb_device_init(am_usbd_handle_t handle)
{
    int i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_hc32f460_usbd_dev_t *p_dev = (am_hc32f460_usbd_dev_t *) handle;

    p_dev->int_ep_union.int_ep_flag = 0;
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
            endpoint.endpoint_address =
                    p_dev->device.endpoint_info[i].ep_address;
            endpoint.max_packet_size =
                    p_dev->device.endpoint_info[i].max_packet_size;
            endpoint.transfer_type =
                    p_dev->device.endpoint_info[i].transfer_type;
            __usb_device_endpoint_init(p_dev, &endpoint);
        }
    }

    p_dev->device.device_address = 0;

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \bruef USBȥ��ʼ��
 *
 * \param[in] USB�������
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_deinit(am_usbd_handle_t handle)
{
    am_hc32f460_usbd_dev_t *p_dev = (am_hc32f460_usbd_dev_t *) handle;
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
uint8_t send_buf[64];
static am_usb_status_t __usb_device_send(am_usbd_handle_t handle,
        uint8_t endpoint_address, uint8_t *buffer, uint32_t length)
{
    USB_OTG_CORE_HANDLE *pdev = &USB_OTG_dev;
    memcpy(send_buf, buffer, length);
    DCD_EP_Tx(pdev, endpoint_address, send_buf, length);
    return AM_USB_STATUS_SUCCESS;
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
static uint8_t __usb_device_recv(am_usbd_handle_t handle,
        uint8_t endpoint_address, uint8_t *buffer, uint32_t length)
{
    USB_OTG_CORE_HANDLE *pdev = &USB_OTG_dev;
    USB_OTG_EP *ep;
    uint8_t avali_data_cnt = 0; /* fifo����Ч���ݸ��� */
    uint8_t endpoint = endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK;
    uint8_t *p_cbw = NULL;

    DCD_EP_PrepareRx(pdev, endpoint_address, (uint8_t *)&MSC_BOT_cbw, length);

    while (0 == data_update_flag)
        ;

    ep = &pdev->dev.out_ep[endpoint];
    p_cbw = (uint8_t *) &MSC_BOT_cbw;
    avali_data_cnt = ep->xfer_len;

    while (avali_data_cnt--) {
        *buffer++ = *p_cbw;
        p_cbw++;
    }
    return ep->xfer_count;
}

/**
 * \brief ��ֹĳ���˵����ڽ��еĴ���
 *
 * \param[in] handle        : �豸���
 * \param[in] endpoint_addr : �˵��ַ
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_cancel(am_usbd_handle_t handle,
        uint8_t endpoint_addr)
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
//static void __usb_device_setdefault_state(am_hc32f460_usbd_dev_t *p_dev)
//{
//}

/**
 * \brief USB���ƺ�������������USBΪָ����״̬
 *
 * \param[in] handle : USB�������
 * \param[in] type   : ��������
 * \param[in] param  : ���Ʋ���
 *
 * \retval USB������
 */
static am_usb_status_t __usb_device_control(am_usbd_handle_t handle,
        am_usbd_control_type_t type, void *param)
{
    am_hc32f460_usbd_dev_t *p_dev = (am_hc32f460_usbd_dev_t *) handle;
    am_usb_status_t error = AM_USB_STATUS_ERROR;
    uint8_t *temp8;
    am_usbd_ep_status_t *endpointStatus = NULL;
    uint8_t endpoint = 0;
    uint8_t *p_temp8;
    USB_OTG_CORE_HANDLE *pdev = &USB_OTG_dev;

    if (!handle)
        return AM_USB_STATUS_INVALID_HANDLE;

    switch ((int) type) {
    case AM_USBD_CONTROL_RUN:
        DCD_DevConnect(pdev);
        error = AM_USB_STATUS_SUCCESS;
        break;

    case AM_USBD_CONTROL_STOP:
        DCD_DevDisconnect(pdev);
        error = AM_USB_STATUS_SUCCESS;
        break;

    case AM_USBD_CONTROL_ENDPOINT_INIT: /* ��ĳ���˵��ʼ�� */
        if (param) {
            error = __usb_device_endpoint_init(p_dev,
                    (am_usbd_endpoint_init_t *) param);
        }
        break;

    case AM_USBD_CONTROL_ENDPOINT_DEINIT: /* ��ĳ���˵�ȥ��ʼ�� */
        if (param) {
            temp8 = (uint8_t *) param;
            error = __usb_device_endpoint_deinit((USB_OTG_CORE_HANDLE *)p_dev, *temp8);
        }
        break;

    case AM_USBD_CONTROL_ENDPOINT_STALL: /* ���ƶ˵����� */
        if (param) {
            temp8 = (uint8_t *) param;
            error = __usb_device_endpoint_stall((USB_OTG_CORE_HANDLE *)p_dev, *temp8);
        }
        break;

    case AM_USBD_CONTROL_ENDPOINT_UNSTALL: /* ���ƶ˵㲻���� */
        if (param) {
            temp8 = (uint8_t *) param;
            error = __usb_device_endpoint_unstall((USB_OTG_CORE_HANDLE *)p_dev, *temp8);
        }
        break;

    case AM_USBD_CONTROL_GET_DEVICE_STATUS: /* ��ȡ�豸״̬ */
        break;

    case AM_USBD_CONTROL_GET_ENDPOINT_STATUS: /* ͨ���˵��ַ��ȡ�˵�״̬ */
        if (param) {
            endpointStatus = (am_usbd_ep_status_t *) param;

            endpoint = (endpointStatus->endpoint_address)
                    & AM_USBD_ENDPOINT_NUMBER_MASK;

            if (endpoint < AM_USBD_MAX_EP_CNT) {
                endpointStatus->endpoint_status =
                        p_dev->device.endpoint_info[endpoint].stalled;
                error = AM_USB_STATUS_SUCCESS;
            }
            else {
                error = AM_USB_STATUS_INVALID_PARAMETER;
            }
        }
        break;

    case AM_USBD_CONTROL_SET_DEVICE_ADDRESS: /* ����USB�豸��ַ */
        if (param) {
            p_temp8 = (uint8_t *) param;
            DCD_EP_SetAddress(pdev, *p_temp8);
            error = AM_USB_STATUS_SUCCESS;
        }
        break;

    case AM_USBD_CONTROL_GET_SYNCH_FRAME:
        break;

    case AM_USBD_CONTROL_RESUME:
        break;

        /* ����Ĭ��״̬ */
    case AM_USBD_CONTROL_SET_DEFAULT_STATUS:
        error = AM_USB_STATUS_SUCCESS;
        break;

    case AM_USBD_CONTROL_GET_SPEED:
        if (param) {
            temp8 = (uint8_t *) param;
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
 * \brief USB�жϷ�����
 */
static void __usbd_isr_function(void *p_device)
{
    am_hc32f460_usbd_dev_t *p_dev = (am_hc32f460_usbd_dev_t *) p_device;

    USB_OTG_GINTSTS_TypeDef gintr_status;
    uint32_t retval = 0ul;
    uint32_t ReadCoreItrTemp = 0ul; /* C-STAT */

    USB_OTG_CORE_HANDLE *pdev = &USB_OTG_dev;

    uint32_t addr = (uint32_t)&ReadCoreItrTemp;

    if (USB_OTG_IsDeviceMode(pdev)) /* ensure that we are in device mode */
    {
        ReadCoreItrTemp = USB_OTG_ReadCoreItr(pdev);
        gintr_status.b = *(stc_bUSB_OTG_GINTSTS_t*) addr;
        /* avoid spurious interrupt */
        if (!*(uint32_t*) addr) {
            retval = 0ul;
        }
        /* Out endpoint interrupt */
        else if (gintr_status.b.outepintr) {
            retval |= DCD_HandleOutEP_ISR(p_dev, pdev);
        }
        /* In endpoint interrupt */
        else if (gintr_status.b.inepint) {
            retval |= DCD_HandleInEP_ISR(p_dev, pdev);
        }
        /* Mode mismatch interrupt */
        else if (gintr_status.b.modemismatch) {
            USB_OTG_GINTSTS_TypeDef gintsts;

            /* Clear interrupt */
            gintsts.d32 = 0ul;
            gintsts.b.modemismatch = 1u;
            USB_OTG_WRITE_REG32(&pdev->regs.GREGS->GINTSTS, gintsts.d32);
        }
        /* Resume/remote wakeup detected interrupt */
        else if (gintr_status.b.wkupintr) {
            retval |= DCD_HandleResume_ISR(pdev);
        }
        /* USB suspend interrupt */
        else if (gintr_status.b.usbsuspend) {
            retval |= DCD_HandleUSBSuspend_ISR(pdev);
        }
        /* Start of frame interrupt */
        else if (gintr_status.b.sofintr) {
            retval |= DCD_HandleSof_ISR(pdev);
        }
        /* RxFIFO non-empty interrupt */
        else if (gintr_status.b.rxstsqlvl) {
            retval |= DCD_HandleRxStatusQueueLevel_ISR(pdev);
        }
        /* USB reset interrupt */
        else if (gintr_status.b.usbreset) {
            retval |= DCD_HandleUsbReset_ISR(pdev);
        }
        /* Enumeration done interrupt */
        else if (gintr_status.b.enumdone) {
            retval |= DCD_HandleEnumDone_ISR(pdev);
        }
        /* Incomplete periodic transfer */
        else if (gintr_status.b.incomplisoin) {
            retval |= DCD_IsoINIncomplete_ISR(pdev);
        }
        /* Incomplete isochronous IN transfer */
        else if (gintr_status.b.incomplisoout) {
            retval |= DCD_IsoOUTIncomplete_ISR(pdev);
        }

#ifdef VBUS_SENSING_ENABLED
        /* VBUS valid interrupt */
        else if (gintr_status.b.vbusvint) {
            retval |= DCD_SessionRequest_ISR(pdev);
        }
        else {
            //
        }
#endif
    }
}

/**
 * \brief ��ͨ����������������ʼ���˵���Ϣ���˵����������������ԣ�֧�ֵ�������С��
 *
 * \retval �ɹ����ظ�ʹ�õĶ˵������ʧ�ܷ���-1
 */
static am_err_t __init_ep_info(am_hc32f460_usbd_dev_t *p_dev)
{
    uint8_t ret = 0; /* ���巵��ֵ */
    uint8_t *p_tmp = NULL; /* ���ݻ���ָ�� */
    uint8_t ep_num = 0; /* �˵�� */
    uint8_t tmp = 0; /* ��ʱ����*/
    uint8_t offset = 0; /* ƫ����*/
    uint8_t len = 0; /* �������ܳ��� */
    am_usb_descriptor_endpoint_t *p_desc_ep = NULL;
    /* ��ȡ���������� */
    p_tmp = __find_desc_by_wValue1(p_dev,
            (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
    if (p_tmp == NULL)
        return AM_ERROR;
    /*���������������������������ܳ���*/
    len = (uint8_t) ((*(p_tmp + 2)) | ((*(p_tmp + 3)) >> 8));
    /* �Ҷ˵�������*/
    while (tmp < len) {
        offset = *p_tmp; /* �����������ֽ���,��һ��Ϊ����������*/
        p_tmp += offset; /* ��ƫ�� */
        tmp += offset;
        /* ����Ƕ˵�������*/
        if ((*(p_tmp + 1) == AM_USB_DESC_TYPE_ENDPOINT)
                && (*p_tmp == AM_USB_DESC_LENGTH_ENDPOINT)) {
            p_desc_ep = (am_usb_descriptor_endpoint_t *) p_tmp;  // �˵�������
            // �˵��
            ep_num = p_desc_ep->b_endpoint_address
                    & AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK;
            p_dev->device.endpoint_info[ep_num].inuse = 1;  // ��ʾ�˵㱻ʹ��
            p_dev->device.endpoint_info[ep_num].ep_address =
                    p_desc_ep->b_endpoint_address;
            p_dev->device.endpoint_info[ep_num].max_packet_size =
                    (p_desc_ep->wmax_packet_size[1] << 8)
                            | p_desc_ep->wmax_packet_size[0];
            p_dev->device.endpoint_info[ep_num].transfer_type =
                    p_desc_ep->bm_attributes;
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
am_usbd_dev_t *am_hc32f460_usbd_init(am_hc32f460_usbd_dev_t *p_dev,
        const am_hc32f460_usbd_devinfo_t *p_info)
{
    int i = 0;

    if (NULL == p_dev || NULL == p_info) {
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
    p_dev->device.vendor_req.p_arg = NULL;

    p_dev->device.class_req.pfn_class = NULL;
    p_dev->device.class_req.p_arg = NULL;

    p_dev->device.device_address = 0;
    p_dev->device.state = AM_USBD_STATE_DEFAULT;

    p_dev->int_ep_union.int_ep_flag = 0;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++)
        p_dev->ep_int_type_union.ep_int_type[i] = 0;

    p_dev->device.setup_data.bm_request_type = 0;
    p_dev->device.setup_data.b_request = 0;
    p_dev->device.setup_data.w_value = 0;
    p_dev->device.setup_data.w_index = 0;
    p_dev->device.setup_data.w_length = 0;

    /**< \brief ���ö˵�0��Ĭ������ */
    p_dev->device.endpoint_info[0].stalled = 0;
    p_dev->device.endpoint_info[0].ep_address = 0;
    p_dev->device.endpoint_info[0].max_packet_size = AM_USBD_MAX_EP_DATA_CNT;
    p_dev->device.endpoint_info[0].transfer_type = AM_USB_ENDPOINT_CONTROL;
    p_dev->device.endpoint_info[0].inuse = 1;
    p_dev->device.endpoint_info[0].val_length = 0;

    for (i = 1; i < AM_USBD_MAX_EP_CNT; i++) {
        p_dev->device.endpoint_info[i].stalled = 0;
        p_dev->device.endpoint_info[i].ep_address = 0;
        p_dev->device.endpoint_info[i].max_packet_size = 0;
        p_dev->device.endpoint_info[i].transfer_type = 0;
        p_dev->device.endpoint_info[i].inuse = 0;
        p_dev->device.endpoint_info[i].val_length = 0;
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

    am_int_connect(p_info->inum, IRQ136_Handler, (void *) p_dev);
    amhw_hc32f460_intc_int_vssel_bits_set(p_info->inum, USBFS_GLB);
    am_int_enable(p_info->inum);
    am_usbd_init(&p_dev->device);

    return &(p_dev->device);
}

/**
 * \brief USB Device ȥ��ʼ��
 *
 * \param[in] p_info : ָ��USB�豸��Ϣ
 */
void am_hc32f460_usbd_deinit(const am_hc32f460_usbd_devinfo_t *p_info)
{
    if (p_info != NULL && p_info->pfn_plfm_deinit != NULL) {
        p_info->pfn_plfm_deinit();
    }
}

void UsbGlobal_IrqHandler(void *p_arg)
{
    __usbd_isr_function(p_arg);
}
