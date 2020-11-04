/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB DEVICE����
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-25  adw, first implementation.
 * \endinternal
 */
#ifndef __AM_HC32F460_USBD_H
#define __AM_HC32F460_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "amhw_hc32f460_usbd.h"
#include "am_usb_dci.h"


/**
 * \brief
 */
typedef struct am_hc32f460_usbd_devinfo{
    uint32_t usb_regbase;            /**< \brief usb ����ַ*/

    int      inum;                   /**< \brief �жϺ� */

    void   (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������  */

    void   (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */

    const am_usbd_devinfo_t *p_devinfo;

} am_hc32f460_usbd_devinfo_t;


typedef struct am_hc32f460_usbd_dev am_hc32f460_usbd_dev_t;

/**
 * \brief zlg USBD device structure
 */
struct am_hc32f460_usbd_dev {
    /** \brief Device handle used to identify the device object belongs to */
    am_usbd_dev_t  device;

    /** \brief �����жϵĶ˵㣬Ϊ1��ʾ�����жϣ�Ϊ0��ʾû�з����ж�
     *   D7:D5  ����
     *   D4~D0  ��Ӧ�����жϵĶ˵�4~�˵�0��
     */
    union {
        uint8_t int_ep_flag;
        struct {
            uint8_t ep0 : 1;
            uint8_t ep1 : 1;
            uint8_t ep2 : 1;
            uint8_t ep3 : 1;
            uint8_t ep4 : 1;
            uint8_t ep5 : 1;            
        }int_ep_flag_field;
    }int_ep_union;

    /**< \brief �˵��жϵ����ͣ�Ϊ1��ʾ�����жϣ�Ϊ0��ʾû�з����ж�
     *   D7:OUT_STALL
     *   D6:OUT_ACK
     *   D5:OUT_NACK
     *   D4:IN_STALL
     *   D3:IN_ACK
     *   D2:IN_NACK
     *   D1:END       �˵㴫�����
     *   D0:SETUP     ���յ�SETUP��
     */
    union {
        uint32_t ep_int_type[AM_USBD_MAX_EP_CNT];
        struct {
            uint8_t setup     : 1;
            uint8_t end       : 1;
            uint8_t in_nack   : 1;
            uint8_t in_ack    : 1;
            uint8_t in_stall  : 1;
            uint8_t out_nack  : 1;
            uint8_t out_ack   : 1;
            uint8_t out_stall : 1;
        }ep_int_type_field[AM_USBD_MAX_EP_CNT];
    }ep_int_type_union;

    /**< \brief �豸��Ϣ�ṹָ�� */
    const am_hc32f460_usbd_devinfo_t         *p_info;
};



/*******************************************************************************
**   �ⲿ��������
********************************************************************************/


am_usbd_dev_t *am_hc32f460_usbd_init (am_hc32f460_usbd_dev_t           *p_dev,
                                      const am_hc32f460_usbd_devinfo_t *p_info);

void am_hc32f460_usbd_deinit (const am_hc32f460_usbd_devinfo_t *p_info);

void UsbGlobal_IrqHandler(void *p_arg);

/**
 * @} mm32_if_usbd
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_HC32F460_USBD_H */

/* end of file */
