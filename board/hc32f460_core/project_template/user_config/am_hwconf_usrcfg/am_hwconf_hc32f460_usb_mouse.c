/*******************************************************************************
*                                 AMetal
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief hc32f460 USB_MSC �û������ļ�
 * \sa am_hc32f460_hwconfig_usb_mouse.c
 *
 * \internal
 * \par Modification history
 *
 * - 1.10 19-01-11  adw, add configuration macro
 * - 1.00 18-10-29  enf, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_types.h"
#include "am_clk.h"
#include "am_usb.h"
#include "am_gpio.h"
#include "am_usbd.h"
#include "am_hc32f460.h"
#include "am_hc32f460_usbd.h"
#include "amhw_hc32f460_usbd.h"
#include "usb_core.h"
#include "usbd_desc.h"
#include "usbd_hid_mouse_core.h"
#include "usbd_usr.h"
/**
 * \addtogroup am_hc32f460_if_hwconfig_src_usb_msc
 * \copydoc am_hc32f460_hwconfig_usb_mouse.c
 * @{
 */

/*******************************************************************************
 * �û�USB���������ú�,�û������������꼴��,�������USB��������
 ******************************************************************************/
/** \brief USB�豸�������ú�*/
#define __USBD_MOUSE_VENDOR_ID                 (0x4195) /**< \brief ���̱��,��Ϊ��Ʒ��������д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��*/
#define __USBD_MOUSE_PRODUCT_ID                (0x6515) /**< \brief ��Ʒ���*/
#define __USBD_MOUSE_DEVICE_ID                 (0x0101) /**< \brief �豸���*/
#define __USBD_MOUSE_VENDOR_STRING_INDEX       (0x01)   /**< \brief �������̵��ַ�������*/
#define __USBD_MOUSE_PRODUCT_STRING_INDEX      (0x02)   /**< \brief ������Ʒ���ַ������� */
#define __USBD_MOUSE_DEVICE_STRING_INDEX       (0x03)   /**< \brief �����豸���кŵ��ַ�������*/
#define __USBD_CONFIGURATION_COUNT           (1U)     /**< \brief ��������һ������ֻ��һ������*/

/** \brief USB�������������ú�*/
#define __USBD_MOUSE_INTERFACE_COUNT           (1U)               /**< \brief �ӿ���*/
#define __USBD_MOUSE_CONFIGURE_INDEX           (1U)               /**< \brief ��������������*/
#define __USBD_MOUSE_DEVICE_POWER               AM_USBD_MAX_POWER /**< \brief �豸����������ĵ�������λ2mA,���100mA*/
/** \brief �豸���ԣ��Թ��磬��֧��Զ�̻���*/
#define __USBD_MOUSE_DEVICE_ATTRIBUTE          \
              (AM_USBD_CONFIG_SELF_POWER | AM_USBD_CONFIG_REMOTE_WAKEUP)

/**\brief USB�˵����������ú�*/
#define __USBD_MOUSE_ENDPOINT_IN               (1U)                     /**< \brief ����˵��*/
#define __USBD_MOUSE_ENDPOINT_IN_PACKSIZE      AM_USBD_MAX_EP_DATA_CNT  /**< \brief �˵����С,����Ϊ64*/
#define __USBD_MOUSE_ENDPOINT_IN_ATTRIBUTE     AM_USB_ENDPOINT_BULK     /**< \brief ���ö˵�����Ϊ��������*/
#define __USBD_MOUSE_ENDPOINT_IN_QUERY_TIME    (0x01)                   /**< \brief ���ö˵��ѯʱ��Ϊ10ms,��λΪ1ms*/

#define __USBD_MOUSE_ENDPOINT_OUT              (2)
#define __USBD_MOUSE_ENDPOINT_OUT_PACKSIZE     AM_USBD_MAX_EP_DATA_CNT
#define __USBD_MOUSE_ENDPOINT_OUT_ATTRIBUTE    AM_USB_ENDPOINT_BULK
#define __USBD_MOUSE_ENDPOINT_OUT_QUERY_TIME   (0x01)

/**\brief USB�ӿ����������ú�*/
#define __USBD_MOUSE_ENDPOINT_COUNT            (1U)     /**< \brief �˵����,����˵�������˵�(���������ƶ˵�)*/

/*****************************************************************************
 * USB������(�豸������,�������������ӿ�������,�˵�������),�ò����û�ֻ�����������꼴��
 *****************************************************************************/
/**\brief �豸������ */
static const uint8_t __g_usb_mouse_desc_dev[AM_USB_DESC_LENGTH_DEVICE]  = {
    AM_USB_DESC_LENGTH_DEVICE,       /**< \brief �豸���������ֽ��� */
    AM_USB_DESC_TYPE_DEVICE,         /**< \brief �豸���������ͱ�ţ��̶�Ϊ0x01 */

    /**\brief USB�汾 USB2.0 */
    AM_USB_SHORT_GET_LOW(AM_USB_VERSION), AM_USB_SHORT_GET_HIGH(AM_USB_VERSION),

    AM_USBD_CLASS,                   /**< \brief ͨ���� */
    AM_USBD_SUBCLASS,                /**< \brief �豸���� */
    AM_USBD_PROTOCOL,                /**< \brief Э���� */
    AM_USBD_MAX_EP_DATA_CNT,         /**< \brief �˵�0��������С */

    /**
     * ���̱�š���Ҫ��USBЭ�����룬�����Ϊѧϰʹ�ÿ������ѡһ���Ѿ�ע����ģ�
     * ������Ϊ��Ʒ�����Ļ��ͱ���д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��
     */
    AM_USB_SHORT_GET_LOW(__USBD_MOUSE_VENDOR_ID), AM_USB_SHORT_GET_HIGH(__USBD_MOUSE_VENDOR_ID),

    /**\brief ��Ʒ��� */
    AM_USB_SHORT_GET_LOW(__USBD_MOUSE_PRODUCT_ID), AM_USB_SHORT_GET_HIGH(__USBD_MOUSE_PRODUCT_ID),

    /**\brief �豸������� */
    AM_USB_SHORT_GET_LOW(__USBD_MOUSE_DEVICE_ID), AM_USB_SHORT_GET_HIGH(__USBD_MOUSE_DEVICE_ID),

    __USBD_MOUSE_VENDOR_STRING_INDEX,    /**< \brief �������̵��ַ������� */
    __USBD_MOUSE_PRODUCT_STRING_INDEX,   /**< \brief ������Ʒ���ַ������� */
    __USBD_MOUSE_DEVICE_STRING_INDEX,    /**< \brief �����豸���кŵ��ַ������� */
    __USBD_CONFIGURATION_COUNT,        /**< \brief ���õ�������ֻ����һ���� */
};

/**\brief ���������������¼�������������Խ���ϼ�������ֱ�ӵõ��¼��������� */
static uint8_t __g_usb_mouse_desc_conf[AM_USB_DESC_LENGTH_ALL(__USBD_MOUSE_ENDPOINT_COUNT) + AM_USB_DESC_LENGTH_HID] = {
    /* ���������� */
    AM_USB_DESC_LENGTH_CONFIGURE,     /* �����������ֽ��� 0x09*/
    AM_USB_DESC_TYPE_CONFIGURE,       /* �������������ͱ�ţ��̶�Ϊ0x02 */

    /* �������������������������ܳ��� */
    34,
    0x00,
    __USBD_MOUSE_INTERFACE_COUNT,             /* �ӿ����������� */
    __USBD_MOUSE_CONFIGURE_INDEX,             /* ����ֵ */
    0x00,                                   /* ���������õ��ַ�������,0x00��ʾû�� */

    /* �豸���ԣ����߹��磬��֧��Զ�̻��� */
    0x80|(1<<6),
    __USBD_MOUSE_DEVICE_POWER,                /* �����߻�ȡ����������100mA�� 2mAһ����λ */

    /* �ӿ������� */
    AM_USB_DESC_LENGTH_INTERFACE,     /* �ӿ��������ֽ��� */
    AM_USB_DESC_TYPE_INTERFACE,       /* �ӿ����������ͱ�ţ��̶�Ϊ0x04 */
    0x00,                                   /* �ýӿڱ��,�ӿ������������0��ʼ,�Դ����� */
    0x00,                                   /* ��ѡ���õ�����ֵ���ýӿڵı��ñ�ţ� */
    0x01,              /* �ýӿ�ʹ�õĶ˵������������˵�0�� */
    0x03,          /* MSC_CLASS�� */
    0x01,                   /* msc������ */
    0x02,                   /* mscЭ������ */
    0x00,                                   /* �����ýӿڵ��ַ�������, 0x00��ʾû�� */

    /* HID������ */
    0x09,            /* �˵��������ֽ��� */
    0x21,        /* �˵����������ͱ�ţ��̶�Ϊ0x05 */
    0x11,
    0x01,       /* �˵����� 02��ʾ����  */

    0x00,
    0x01, /* �˵�һ�����շ���������С */

    0x22, 
    74,
    0x00,

    /* ����˵������� */
    0x07,    
    0x05,
    0x81,
    0x03,
    4,
    0x00,
    0x0a,     /* ������ѯ�˵�ʱ��ʱ���� 10ms */
};

/*******************************************************************************
 * �ַ���������,����û���Ҫ�޸���������Ϣ��ע��ʹ�õ���UINCODE��(ע���С��)
 ******************************************************************************/
/**< \brief ������Ʒ���ַ��������� */
 static const uint8_t __g_usb_mouse_desc_str_iproduct[16] = {
    sizeof(__g_usb_mouse_desc_str_iproduct), /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,         /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */

     0x55, 0x00, 
     0x42, 0x00, 
     0x53, 0x00,
     0x21, 0x6a, 
     0xdf, 0x62, 
     0x55, 0x00,
     0xd8, 0x76  
};

/**< \brief ����ID�ַ��������� */
/**< \brief ����ʹ����ʽӢ���ʹ�ü������ĵ�ԭ�������ʹ�ü������ģ�������������ӻ�Ҫ�ַ��������� */
/**< \brief ��ʽӢ�������IDΪ0x0409���������ĵ�����IDΪ0x0804��ע���С�ˡ� */
 static const uint8_t __g_usb_mouse_desc_str_language_id[4] = {
    sizeof(__g_usb_mouse_desc_str_language_id),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,       /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x09,
    0x04,       /* �������� */
};

/**< \brief �������̵��ַ��������� */
 static const uint8_t __g_usb_mouse_desc_str_imanufacturer[22] = {
    sizeof(__g_usb_mouse_desc_str_imanufacturer),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,       /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x7f, 0x5e, /* �� */
    0xde, 0x5d, /* �� */
    0xf4, 0x81, /* �� */
    0xdc, 0x8f, /* Զ */
    0x35, 0x75, /* �� */
    0x50, 0x5b, /* �� */
    0x09, 0x67, /* �� */
    0x50, 0x96, /* �� */
    0x6c, 0x51, /* �� */
    0xf8, 0x53, /* ˾ */
};

/**< \brief �����豸���кŵ��ַ��������� */
 static const uint8_t __g_usb_mouse_desc_str_iserialnumber[22] = {

    sizeof(__g_usb_mouse_desc_str_iserialnumber),    /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,                 /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x32, 0x00, /* 2 */
    0x30, 0x00, /* 0 */
    0x31, 0x00, /* 1 */
    0x38, 0x00, /* 8 */
    0x2d, 0x00, /* - */
    0x31, 0x00, /* 1 */
    0x30, 0x00, /* 0 */
    0x2d, 0x00, /* - */
    0x32, 0x00, /* 2 */
    0x39, 0x00, /* 9 */
};
 
/**< \brief ���������� */
static uint8_t __g_usb_mouse_desc_str_report[74] =
{
    0x05,   0x01,
    0x09,   0x02,
    0xA1,   0x01,
    0x09,   0x01,

    0xA1,   0x00,
    0x05,   0x09,
    0x19,   0x01,
    0x29,   0x03,

    0x15,   0x00,
    0x25,   0x01,
    0x95,   0x03,
    0x75,   0x01,

    0x81,   0x02,
    0x95,   0x01,
    0x75,   0x05,
    0x81,   0x01,

    0x05,   0x01,
    0x09,   0x30,
    0x09,   0x31,
    0x09,   0x38,

    0x15,   0x81,
    0x25,   0x7F,
    0x75,   0x08,
    0x95,   0x03,

    0x81,   0x06,
    0xC0,   0x09,
    0x3c,   0x05,
    0xff,   0x09,

    0x01,   0x15,
    0x00,   0x25,
    0x01,   0x75,
    0x01,   0x95,

    0x02,   0xb1,
    0x22,   0x75,
    0x06,   0x95,
    0x01,   0xb1,

    0x01,   0xc0
};

/******************************************************************************
 * ����������Ϣ
 *****************************************************************************/
static const am_usbd_descriptor_t __g_usb_mouse_descriptor[] = {
    /**\brief �豸������ */
    {
        (AM_USB_DESC_TYPE_DEVICE << 8) | (0x00),
        sizeof(__g_usb_mouse_desc_dev),
        __g_usb_mouse_desc_dev
    },

    /**\brief ���������������¼������� */
    {
        (AM_USB_DESC_TYPE_CONFIGURE << 8) | (0x00),
        sizeof(__g_usb_mouse_desc_conf),
        __g_usb_mouse_desc_conf
    },

    /**\brief �ַ�������������������id */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | (0x00),
        sizeof(__g_usb_mouse_desc_str_language_id),
        __g_usb_mouse_desc_str_language_id
    },

    /**\brief �ַ������������������� */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_MOUSE_VENDOR_STRING_INDEX,
        sizeof(__g_usb_mouse_desc_str_imanufacturer),
        __g_usb_mouse_desc_str_imanufacturer
    },

    /**\brief �ַ�����������������Ʒ */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_MOUSE_PRODUCT_STRING_INDEX,
        sizeof(__g_usb_mouse_desc_str_iproduct),
        __g_usb_mouse_desc_str_iproduct
    },

    /**\brief �ַ����������������豸���к� */
    {
        (AM_USB_DESC_TYPE_STRING << 8)| __USBD_MOUSE_DEVICE_STRING_INDEX,
        sizeof(__g_usb_mouse_desc_str_iserialnumber),
        __g_usb_mouse_desc_str_iserialnumber
    },

    {
        (AM_USB_DESC_TYPE_HID_REPORT << 8)| (0x00),
        sizeof(__g_usb_mouse_desc_str_report),
        __g_usb_mouse_desc_str_report
    },
};

/******************************************************************************
 * ƽ̨��ʼ�����������ʼ�������Ѿ��豸��Ϣ
 ******************************************************************************/ 
extern USB_OTG_CORE_HANDLE USB_OTG_dev;
/**
 * \brief ƽ̨��ʼ��
 */
static void __usb_mouse_init (void) {
    /**\brief ʹ��ʱ�� */
    am_clk_enable(CLK_USBFS);

    am_gpio_pin_cfg(PIOA_9, GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));/**< \brief VBUS */
    /**\brief ����PIOA_11 PIOA_12ΪUSB����   */
    am_gpio_pin_cfg(PIOA_11, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) |
                             GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));/**< \brief USBDM */
    am_gpio_pin_cfg(PIOA_12, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) |
                             GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));/**< \brief USBDP */
    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_HID_cb,
            &USR_cb);                             
}

/**
 * \brief ƽ̨ȥ��ʼ��
 */
static void __usb_mouse_deinit (void) {
    am_clk_disable(CLK_USBFS);                 /**< \brief ����USBʱ�� */
}

/**\brief �豸��Ϣ*/
static const am_usbd_devinfo_t __g_usbd_mouse_info = {
        __g_usb_mouse_descriptor,                                                 /**< \brief ��������ַ */
        sizeof(__g_usb_mouse_descriptor) / sizeof(__g_usb_mouse_descriptor[0]),     /**< \brief ���������� */
};

/**\brief ����USB�豸��Ϣ */
static const am_hc32f460_usbd_devinfo_t  __g_hc32f460_usbd_mouse_info = {
    HC32F460_USB_OTG_FS_BASE,                  /**< \brief �Ĵ�������ַ */
    INUM_USBFS_GLB,                            /**< \brief �жϺ� */
    __usb_mouse_init,                            /**< \brief ƽ̨��ʼ�� */
    __usb_mouse_deinit,                          /**< \brief ƽ̨ȥ��ʼ�� */
    &__g_usbd_mouse_info,
};

/** \brief USB MSC�豸ʵ�� */
//am_usbd_msc_t      __g_usb_msc_dev;

/** \brief USB�豸ʵ�� */
am_hc32f460_usbd_dev_t  __g_hc32f460_usbd;

/** \brief usb_mscʵ����ʼ�������usb_msc��׼������ */
am_usbd_dev_t am_hc32f460_usb_mouse_inst_init (void)
{
    return *am_hc32f460_usbd_init(&__g_hc32f460_usbd, &__g_hc32f460_usbd_mouse_info);
}

/** \brief usb_msc���ʼ�� */
void am_hc32f460_usb_mouse_inst_deinit (void)
{
    am_hc32f460_usbd_deinit(&__g_hc32f460_usbd_mouse_info);   
}

/**
 * @}
 */

/* end of file */
