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
#ifndef __AM_HC32F07X_USBD_H
#define __AM_HC32F07X_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hw/amhw_hc32f07x_usbd.h"
#include "am_usb_dci.h"


/**
 * \brief
 */
typedef struct am_hc32f07x_usbd_devinfo{
    uint32_t usb_regbase;          /**< \brief usb ����ַ*/

    int inum;                      /**< \brief �жϺ� */

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������  */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */

    const am_usbd_devinfo_t *p_devinfo;

}am_hc32f07x_usbd_devinfo_t;


typedef struct am_hc32f07x_usbd_dev am_hc32f07x_usbd_dev_t;

/**
 * \brief zlg USBD device structure
 */
struct am_hc32f07x_usbd_dev {
    /**< \brief Device handle used to identify the device object belongs to */
    am_usbd_dev_t       device;

    uint8_t             dma_enable;
     
    /**< \brief �����жϵĶ˵㣬Ϊ1��ʾ�����жϣ�Ϊ0��ʾû�з����ж�
     *   D7:D5  ����
     *   D4~D0  ��Ӧ�����жϵĶ˵�4~�˵�0��
     */
    union {
        uint16_t int_ep_flag;
        struct {
            uint16_t in_out_ep0  : 1;
            uint16_t in_ep1      : 1;
            uint16_t out_ep2     : 1;
            uint16_t in_ep3      : 1;
            uint16_t out_ep4     : 1;
            uint16_t in_ep5      : 1;
            uint16_t out_ep6     : 1;
            uint16_t in_ep7      : 1;
            uint16_t out_ep8     : 1;
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
        uint16_t ep_int_type[AM_USBD_MAX_EP_CNT];
        struct {
            uint16_t in_xfrc      : 1;
            uint16_t in_epdisd    : 1;
            uint16_t in_reserved0 : 1;
            uint16_t in_timeout   : 1;
            uint16_t in_ittxfe    : 1;
            uint16_t in_reserved  : 1;
            uint16_t in_inepne    : 1;
            uint16_t in_txfe      : 1;
            uint16_t out_xfrc      : 1;
            uint16_t out_epdisd    : 1;
            uint16_t out_reserved0 : 1;
            uint16_t out_stup      : 1;
            uint16_t out_otepdis   : 1;
            uint16_t out_reserved1 : 1;
            uint16_t out_bstup     : 1;
            uint16_t out_reserved2 : 1;
        }ep_int_type_field[AM_USBD_MAX_EP_CNT];
    }ep_int_type_union;
        
    am_data_info_t    data_info[AM_USBD_MAX_EP_CNT];

    /**< \brief �豸��Ϣ�ṹָ�� */
    const am_hc32f07x_usbd_devinfo_t         *p_info;

};



///*******************************************************************************
//   �ⲿ��������
//*******************************************************************************/


am_usbd_dev_t *am_hc32f07x_usbd_init (am_hc32f07x_usbd_dev_t           *p_dev,
                                      const am_hc32f07x_usbd_devinfo_t *p_info);

void am_hc32f07x_usbd_deinit (const am_hc32f07x_usbd_devinfo_t *p_info);

/**
 * @} mm32_if_usbd
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_HC32F07X_USBD_H */

/* end of file */
