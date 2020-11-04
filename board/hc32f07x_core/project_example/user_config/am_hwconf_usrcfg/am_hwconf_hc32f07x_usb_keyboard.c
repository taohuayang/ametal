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
 * \brief hc32f07x USB_keyboard �û������ļ�
 * \sa am_hc32f07x_hwconfig_usb_keyboard.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-19  adw, first implementation.
 * \endinternal
 */

#include "hw/amhw_hc32f07x_rcc.h"
#include "ametal.h"
#include "am_hc32f07x.h"
#include "am_delay.h"
#include "am_types.h"
#include "am_clk.h"
#include "am_usb.h"
#include "am_gpio.h"
#include "am_usbd.h"
#include "am_usbd_keyboard.h"
#include "am_hc32f07x_usbd.h"

/**
 * \addtogroup am_hc32f07x_if_hwconfig_src_usb_keyboard
 * \copydoc am_hc32f07x_hwconfig_usb_keyboard.c
 * @{
 */

/*******************************************************************************
 * �û�USB���������ú�,�û������������꼴��,�������USB��������
 ******************************************************************************/

/** \brief USB�豸�������ú�*/
#define __USBD_KEYBOARD_VENDOR_ID                 (0x1FC9) /**< \brief ���̱��,��Ϊ��Ʒ��������д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��*/
#define __USBD_KEYBOARD_PRODUCT_ID                (0x7C03) /**< \brief ��Ʒ���*/
#define __USBD_KEYBOARD_DEVICE_ID                 (0x0002) /**< \brief �豸���*/
#define __USBD_KEYBOARD_VENDOR_STRING_INDEX       (0x01)   /**< \brief �������̵��ַ�������*/
#define __USBD_KEYBOARD_PRODUCT_STRING_INDEX      (0x02)   /**< \brief ������Ʒ���ַ������� */
#define __USBD_KEYBOARD_CONFIG_COUNT              (1U)     /**< \brief ��������һ������ֻ��һ������*/

/** \brief USB�������������ú�*/
#define __USBD_KEYBOARD_INTERFACE_COUNT           (1U)     /**< \brief �ӿ���*/
#define __USBD_KEYBOARD_CONFIGURE_INDEX           (1U)     /**< \brief ��������������*/
#define __USBD_KEYBOARD_DEVICE_POWER               AM_USBD_MAX_POWER /**< \brief �豸����������ĵ�������λ2mA,���100mA*/
/** \brief �豸���ԣ��Թ��磬��֧��Զ�̻���*/
#define __USBD_KEYBOARD_DEVICE_ATTRIBUTE          \
              (AM_USBD_CONFIG_SELF_POWER | AM_USBD_CONFIG_NOT_REMOTE_WAKEUP)

#define __USBD_KEYBOARD_COUNTRYCODE                (0x21U) /**< \brief ����\�������룬0x21��ʾ��������Ϊ����һ������ʽ���̣� */
#define __USBD_KEYBOARD_DESC_NUMBER                (1U)    /**< \brief �¼�����������*/


/**\brief USB�˵����������ú�*/
#define __USBD_KEYBOARD_ENDPOINT_IN                3       /**< \brief ����˵��*/
#define __USBD_KEYBOARD_ENDPOINT_IN_PACKSIZE       AM_USBD_MAX_EP_DATA_CNT       /**< \brief �˵����С,����Ϊ64*/
#define __USBD_KEYBOARD_ENDPOINT_IN_ATTRIBUTE      AM_USB_ENDPOINT_INTERRUPT     /**< \brief ���ö˵�����Ϊ��������*/
#define __USBD_KEYBOARD_ENDPOINT_IN_QUERY_TIME    (0x0A)                         /**< \brief ���ö˵��ѯʱ��Ϊ10ms,��λΪ1ms*/

#define __USBD_KEYBOARD_ENDPOINT_OUT               4
#define __USBD_KEYBOARD_ENDPOINT_OUT_PACKSIZE      AM_USBD_MAX_EP_DATA_CNT
#define __USBD_KEYBOARD_ENDPOINT_OUT_ATTRIBUTE     AM_USB_ENDPOINT_INTERRUPT
#define __USBD_KEYBOARD_ENDPOINT_OUT_QUERY_TIME   (0x0A)

/**\brief USB�ӿ����������ú�*/
#define __USBD_KEYBOARD_ENDPOINT_COUNT            (2U)     /**< \brief �˵����,����˵�������˵�(���������ƶ˵�)*/

/*****************************************************************************
 * USB������(�豸������,�������������ӿ�������,�˵�������),�ò����û�ֻ�����������꼴��
 *****************************************************************************/

/* USB �豸������ */
static const uint8_t __g_am_usbd_keyboard_desc_dev[AM_USB_DESC_LENGTH_DEVICE]  = {
    AM_USB_DESC_LENGTH_DEVICE,        /* �豸���������ֽ��� */
    AM_USB_DESC_TYPE_DEVICE,          /* �豸���������ͱ�ţ��̶�Ϊ0x01 */

    /* USB�汾  */
    AM_USB_SHORT_GET_LOW(AM_USB_VERSION), AM_USB_SHORT_GET_HIGH(AM_USB_VERSION),
    AM_USBD_CLASS,                          /* ͨ���� */
    AM_USBD_SUBCLASS,                       /* �豸���� */
    AM_USBD_PROTOCOL,                       /* Э���� */
    AM_USBD_MAX_EP_DATA_CNT,                /* �˵�0��������С */

    /**
     * ���̱�š���Ҫ��USBЭ�����룬�����Ϊѧϰʹ�ÿ������ѡһ���Ѿ�ע����ģ�
     * ������Ϊ��Ʒ�����Ļ��ͱ���д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��
     */
    AM_USB_SHORT_GET_LOW(__USBD_KEYBOARD_VENDOR_ID), AM_USB_SHORT_GET_HIGH(__USBD_KEYBOARD_VENDOR_ID),

    /* ��Ʒ��� */
    AM_USB_SHORT_GET_LOW(__USBD_KEYBOARD_PRODUCT_ID), AM_USB_SHORT_GET_HIGH(__USBD_KEYBOARD_PRODUCT_ID),

    /* �豸������� */
    AM_USB_SHORT_GET_LOW(__USBD_KEYBOARD_DEVICE_ID), AM_USB_SHORT_GET_HIGH(__USBD_KEYBOARD_DEVICE_ID),
    __USBD_KEYBOARD_VENDOR_STRING_INDEX,     /* �������̵��ַ������� */
    __USBD_KEYBOARD_PRODUCT_STRING_INDEX,    /* ������Ʒ���ַ������� */
    0x00,                                   /* �����豸���кŵ��ַ������� */
    __USBD_KEYBOARD_CONFIG_COUNT,            /* ���õ�������ֻ����һ���� */
};

/** \brief HID�豸����������,��USB_HID ����ѡ������ */
/** \brief �Ѹ�������д������������֮ǰ������Ϊ����������������Ҫ֪�������������еĳ��� */
static const uint8_t __g_keyboard_hid_report[] = {
    /* ÿ�п�ʼ��һ���ֽ�Ϊ����Ŀ��ǰ׺��[D7:D4]��bTag [D3:D2]��bType [D1:D0]��bSize */

    /* ȫ����Ŀ����;ҳѡ��Ϊ��ͨ����ҳ */
    0x05, 0x01, /* Usage Page (Generic Desktop) */

    /* �ֲ���Ŀ����;ѡ��Ϊ���� */
    0x09, 0x06, /* Usage (Keyboard) */

    /* ����Ŀ�������ϣ���ʾΪӦ�ü��ϣ�������������;ҳ����;����Ϊ����ͨ����ļ��� */
    0xa1, 0x01, /* Collection (Application) */

    /* ȫ����Ŀ��ѡ����;ҳΪ���� */
    0x05, 0x07, /* Usage Page (Keyboard/Keypad) */

    /* �ֲ���Ŀ����;����СֵΪ0xe0����ʵ�Ǽ�������ctrl�����������;ֵ����HID��;���в鿴 */
    0x19, 0xe0, /* Usage Minimum (Keyboard LeftControl) */

    /* �ֲ���Ŀ����;�����ֵΪ0xe7����ʵ�Ǽ�����GUI(windows)�� */
    0x29, 0xe7, /* Usage Maximum (Keyboard Right GUI) */

    /* ȫ����Ŀ��˵���������ݵ��߼�ֵ���������Ƿ����������е�ֵ������Сֵ */
    0x15, 0x00, /* Logical Mimimum (0) */

    /* ȫ����Ŀ��˵���������ݵ��߼�ֵ�����ֵ */
    0x25, 0x01, /* Logical Maximum (1) */

    /* ȫ����Ŀ��˵�������������Ϊ8�� */
    0x95, 0x08, /* Report Count (8) */

    /* ȫ����Ŀ��˵��ÿ��������ĳ���Ϊһ��λ */
    0x75, 0x01, /* Report Size (1) */

    /* ����Ŀ��˵����8������Ϊ1λ�������������ͳ�����ǰ����ȫ����Ŀ�����壩������Ϊ���� */
    0x81, 0x02, /* Input (Data,Var,Abs) ��Data��ʾ��Щ���ݿ��Ա䶯��Var��ʾ��Щ�������Ƕ����ģ�ÿ�����ʾһ����˼��Abs��ʾ����ֵ��*/
    /* ��������Ľ�����ǣ���ĳ�����ֵΪ1ʱ���ͱ�ʾ��Ӧ�İ��������£�λ0��Ӧ����;��Сֵ0xe0��λ7��Ӧ����;���ֵ0xe7 */

    /* ȫ����Ŀ��˵�������������Ϊ1�� */
    0x95, 0x01, /* Report Count (1)*/

    /* ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ8λ */
    0x75, 0x08, /* Report Size (8) */

    /* ����Ŀ�������á���ǰ������ȫ����Ŀ��֪������Ϊ8λ������Ϊ1�� */
    /* ��������Ϊ���������ص�����һֱ��0��������OEMʹ�ã� */
    0x81, 0x03, /* INPUT (Cnst,Var,Abs) */

    /* ȫ����Ŀ��˵�������������Ϊ6�� */
    0x95, 0x06, /* Report Count (6)*/

    /* ȫ����Ŀ��˵��ÿ��������ĳ���Ϊ8λ */
    /* ��ʵ�����Ŀ��ҪҲ�ǿ��Եģ���Ϊǰ���Ѿ���һ�����峤��Ϊ8�ҵ�ȫ����Ŀ�� */
    0x75, 0x08, /* Report Size (8) */

    /* ȫ����Ŀ�������߼���СֵΪ0 */
    /* �����ĿҲ���Բ�Ҫ����Ϊǰ���Ѿ���һ�������߼���СֵΪ0����Ŀ�� */
    0x15, 0x00, /* Logical Mimimum (0) */

    /* ȫ����Ŀ�������߼����ֵΪ255 */
    0x25, 0xff, /* Logical Maximum (255) */

    /* ȫ����Ŀ��������;ҳΪ���� */
    /* ǰ���Ѿ����ˣ���˸���Ŀ��ҪҲ���� */
    0x05, 0x07, /* Usage Page (Keyboard/Keypad) */

    /* �ֲ���Ŀ��������;��СֵΪ0��0��ʾû�м����� */
    0x19, 0x00, /* Usage Mimimum (Reserved(no event indicated)) */

    /* �ֲ���Ŀ��������;���ֵΪ0x65 */
    0x29, 0x65, /* Usage Maximum */

    /* ����Ŀ��˵����6��8λ�������������õģ�����ΪData,Ary,Abs */
    /* ������µļ�̫�ࣨ���糬�����ﶨ��ĳ��ȣ����߼��̱����޷�ɨ������������ʱ��������Щ����ȫ������ȫ0xff����ʾ������Ч */
    0x81, 0x00, /* Input(Data,Ary,Abs) */

    /* ����Ϊ������������ */

    /* �߼���Сֵǰ���Ѿ�������ˣ�����ʡ�� */
    /* ȫ����Ŀ���߼����ֵΪ1 */
    0x25, 0x01, /* Logical Maximum (1) */

    /* ȫ����Ŀ��˵���������������5�� */
    0x95, 0x05, /* Report Count (5) */

    /* ȫ����Ŀ��˵��������ĳ���Ϊ1λ */
    0x75, 0x01, /* Report Size (1) */

    /* ȫ����Ŀ��˵��ʹ�õ���;ҳΪLED�� */
    0x05, 0x08, /* Usage Page (LEDs) */

    /* �ֲ���Ŀ��˵����;��СֵΪ���ּ��̵� */
    0x19, 0x01, /* Usage Minimum (Num Lock) */

    /* �ֲ���Ŀ��˵����;���ֵΪKana�� */
    0x29, 0x05, /* Usage Maximum (Kana) */

    /* ����Ŀ������������� */
    0x91, 0x02, /* Output (Data,Var,Abs) */

    /* ȫ����Ŀ������λ������Ϊ1�� */
    0x95, 0x01, /* Report Count (1) */

    /* ȫ����Ŀ������λ�򳤶�Ϊ3λ */
    0x75, 0x03, /* Report Size (3) */

    /* ����Ŀ���������������ǰ������5��λ����������Ҫ������λ�ճ�1���ֽ� */
    0x91, 0x03, /* Output (Cnst,Var,Abs) */

    /* ����Ŀ�������ر�ǰ��ļ��ϣ�bSizeΪ0����ʾ����û������ */
    0xc0        /* END Collection */
};

/* ���������������¼�������������Խ���ϼ�������ֱ�ӵõ��¼��������� */
static uint8_t __g_am_usbd_keyboard_desc_conf[AM_USB_DESC_LENGTH_ALL(__USBD_KEYBOARD_ENDPOINT_COUNT)
                                             + sizeof(am_usb_hid_descriptor_t)] = {
    /* ���������� */
    AM_USB_DESC_LENGTH_CONFIGURE,     /* �����������ֽ��� */
    AM_USB_DESC_TYPE_CONFIGURE,       /* �������������ͱ�ţ��̶�Ϊ0x02 */

    /* �������������������������ܳ���(�������������ӿ��������ţ��������˵�������) */
    AM_USB_SHORT_GET_LOW(sizeof(__g_am_usbd_keyboard_desc_conf)),
    AM_USB_SHORT_GET_HIGH(sizeof(__g_am_usbd_keyboard_desc_conf)),
    __USBD_KEYBOARD_INTERFACE_COUNT,        /* �ӿ����������� */
    __USBD_KEYBOARD_CONFIGURE_INDEX,        /* ����ֵ */
    0x00,                                   /* ���������õ��ַ������� */

    /* �豸���ԣ����߹��磬��֧��Զ�̻��� */
    __USBD_KEYBOARD_DEVICE_ATTRIBUTE,
    __USBD_KEYBOARD_DEVICE_POWER,           /* �����߻�ȡ����������100mA�� 2mAһ����λ */

    /* �ӿ������� */
    AM_USB_DESC_LENGTH_INTERFACE,           /* �ӿ��������ֽ��� */
    AM_USB_DESC_TYPE_INTERFACE,             /* �ӿ����������ͱ�ţ��̶�Ϊ0x04 */
    0x00,                                   /* �ýӿڱ�� */
    0x00,                                   /* ��ѡ���õ�����ֵ���ýӿڵı��ñ�ţ� */
    __USBD_KEYBOARD_ENDPOINT_COUNT,         /* �ýӿ�ʹ�õĶ˵������������˵�0�� */
    AM_USBD_CONFIG_KEYBOARD_CLASS_CODE,     /* HID�豸���� */
    AM_USBD_KEYBOARD_SUBCLASS,              /* HID������, 1������ 2�����*/
    AM_USBD_KEYBOARD_PROTOCOL,              /* 1��ʾ���� */
    0x00,                                   /* �����ýӿڵ��ַ������� */

    /* HID������ */
    AM_USB_DESC_LENGTH_HID,                 /* HID�������ֽ��� */
    AM_USB_DESC_TYPE_HID,       /* HID���������ͱ�ţ��̶�Ϊ0x21 */
    0x10, 0x01,  /* HIDЭ��汾�� */
    __USBD_KEYBOARD_COUNTRYCODE,       /* ����\�������� */
    __USBD_KEYBOARD_DESC_NUMBER,       /* �¼������������� */
    AM_USB_DESC_TYPE_HID_REPORT,       /* �¼������������ͣ�����������Ϊ0x22 */
    AM_USB_SHORT_GET_LOW(sizeof(__g_keyboard_hid_report)), /* �¼��������ĳ��� */
    AM_USB_SHORT_GET_HIGH(sizeof(__g_keyboard_hid_report)),

    /* ����˵������� */
    AM_USB_DESC_LENGTH_ENDPOINT,      /* �˵��������ֽ��� */
    AM_USB_DESC_TYPE_ENDPOINT,        /* �˵����������ͱ�ţ��̶�Ϊ0x05 */

    /* D7 1:USB_IN  0:USB_OUT D3:D0 �˵�� */
    (__USBD_KEYBOARD_ENDPOINT_IN | (AM_USB_IN << AM_USB_REQ_TYPE_DIR_SHIFT)),
    __USBD_KEYBOARD_ENDPOINT_IN_ATTRIBUTE,   /* �˵����� 02��ʾ����  */

    AM_USB_SHORT_GET_LOW(__USBD_KEYBOARD_ENDPOINT_IN_PACKSIZE),
    AM_USB_SHORT_GET_HIGH(__USBD_KEYBOARD_ENDPOINT_IN_PACKSIZE), /* �˵�һ�����շ���������С */

    __USBD_KEYBOARD_ENDPOINT_IN_QUERY_TIME,  /* ������ѯ�˵�ʱ��ʱ������10ms  */

    /* ����˵������� */
    AM_USB_DESC_LENGTH_ENDPOINT,            /* �˵��������ֽ��� */
    AM_USB_DESC_TYPE_ENDPOINT,        /* �˵����������ͱ�ţ��̶�Ϊ0x05 */

    /* �˵��ַ��������� */
    (__USBD_KEYBOARD_ENDPOINT_OUT | (AM_USB_OUT << AM_USB_REQ_TYPE_DIR_SHIFT)),

    __USBD_KEYBOARD_ENDPOINT_OUT_ATTRIBUTE,  /* �˵����� */

    AM_USB_SHORT_GET_LOW(__USBD_KEYBOARD_ENDPOINT_OUT_PACKSIZE),
    AM_USB_SHORT_GET_HIGH(__USBD_KEYBOARD_ENDPOINT_OUT_PACKSIZE), /* �˵�һ�����շ���������С */

    __USBD_KEYBOARD_ENDPOINT_OUT_QUERY_TIME  /* ������ѯ�˵�ʱ��ʱ���� 10ms */
};

/*******************************************************************************
 * �ַ���������,����û���Ҫ�޸���������Ϣ��ע��ʹ�õ���UINCODE��(ע���С��)
 ******************************************************************************/
/**< \brief ������Ʒ���ַ��������� */
static const uint8_t __g_am_usbd_keyboard_desc_str_iproduct[16] = {
    sizeof(__g_am_usbd_keyboard_desc_str_iproduct),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,          /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */

     0x55, 0x00, /* U */
     0x42, 0x00, /* S */
     0x53, 0x00, /* B */
     0x21, 0x6a, /* ģ */
     0xdf, 0x62, /* �� */
     0x2e, 0x95, /* �� */
     0xd8, 0x76, /* �� */
};

/**< \brief ����ID�ַ��������� */
/**< \brief ����ʹ����ʽӢ���ʹ�ü������ĵ�ԭ�������ʹ�ü������ģ�������������ӻ�Ҫ�ַ��������� */
/**< \brief ��ʽӢ�������IDΪ0x0409���������ĵ�����IDΪ0x0804��ע���С�ˡ� */
static const uint8_t __g_am_usbd_keyboard_desc_str_language_id[4] = {
    sizeof(__g_am_usbd_keyboard_desc_str_language_id),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,          /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x04,
    0x08,       /* �������� */
};

/**< \brief �������̵��ַ��������� */
static uint8_t __g_am_usbd_keyboard_desc_str_imanufacturer[22] = {
    sizeof(__g_am_usbd_keyboard_desc_str_imanufacturer),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,          /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */
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


/******************************************************************************
 * ����������Ϣ
 *****************************************************************************/
static const am_usbd_descriptor_t __g_am_usbd_keyboard_descriptor[] = {
    /* �豸������ */
    {
        (AM_USB_DESC_TYPE_DEVICE << 8) | (0x00),
        sizeof(__g_am_usbd_keyboard_desc_dev),
        __g_am_usbd_keyboard_desc_dev
    },

    /* ���������������¼������� */
    {
        (AM_USB_DESC_TYPE_CONFIGURE << 8) | (0x00),
        sizeof(__g_am_usbd_keyboard_desc_conf),
        __g_am_usbd_keyboard_desc_conf
    },

    /* �ַ���������0����������id */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | (0x00),
        sizeof(__g_am_usbd_keyboard_desc_str_language_id),
        __g_am_usbd_keyboard_desc_str_language_id
    },

    /* �ַ���������1���������� */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_KEYBOARD_VENDOR_STRING_INDEX,
        sizeof(__g_am_usbd_keyboard_desc_str_imanufacturer),
        __g_am_usbd_keyboard_desc_str_imanufacturer
    },

    /* �ַ���������2��������Ʒ */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_KEYBOARD_PRODUCT_STRING_INDEX,
        sizeof(__g_am_usbd_keyboard_desc_str_iproduct),
        __g_am_usbd_keyboard_desc_str_iproduct
    },

    /* HID ���������� */
    {
        (AM_USB_DESC_TYPE_HID_REPORT << 8) | (0x00),
        sizeof(__g_keyboard_hid_report),
        __g_keyboard_hid_report
    },
};

/******************************************************************************
 * ƽ̨��ʼ�����������ʼ�������Ѿ��豸��Ϣ
 ******************************************************************************/
/**
 * \brief ƽ̨��ʼ��
 */
static void __am_usbd_keyboard_init (void) {
	
    /* ʹ��ʱ�� */
    amhw_hc32f07x_rcc_set_start(0x5A5A);
    amhw_hc32f07x_rcc_set_start(0xA5A5);
    amhw_hc32f07x_rcc_usbclk_adjust_set (AMHW_HC32F07X_USBCLK_ADJUST_PLL);
    am_clk_enable(CLK_USB);
}

/**
 * \brief ƽ̨ȥ��ʼ��
 */
static void __am_usbd_keyboard_deinit (void) {
    am_clk_disable(CLK_USB);
    amhw_hc32f07x_rcc_peripheral_disable (AMHW_HC32F07X_RCC_USB);       /* ����USBʱ�� */         
}

static const am_usbd_devinfo_t __g_usbd_info = {
        __g_am_usbd_keyboard_descriptor,                                                         /* ��������ַ */
        sizeof(__g_am_usbd_keyboard_descriptor) / sizeof(__g_am_usbd_keyboard_descriptor[0]),     /* ���������� */
};

/**< \brief ����USB�豸��Ϣ */
static const am_hc32f07x_usbd_devinfo_t  __g_hc32f07x_usbd_keyboard_info = {
    HC32F07X_USB_BASE,                           /* �Ĵ�������ַ */
    INUM_USB,                                  /* �жϺ� */
    __am_usbd_keyboard_init,          /**< \brief ƽ̨��ʼ�� */
    __am_usbd_keyboard_deinit,        /**< \brief ƽ̨ȥ��ʼ�� */
    &__g_usbd_info,
};

/** \brief USB��ӡ����Ϣ�ṹ��*/
static am_usbd_keyboard_info_t __g_usbd_keyboard_info = {
	__USBD_KEYBOARD_ENDPOINT_IN,
	__USBD_KEYBOARD_ENDPOINT_OUT
};

/** \brief USB keyboard �豸ʵ�� */
static am_usbd_keyboard_t __g_usbd_keyboard_dev;

/** \brief hc32f07x USB�豸ʵ�� */
static am_hc32f07x_usbd_dev_t  __g_hc32f07x_usbd_keyboard;


/** \brief usb_keyboardʵ����ʼ�������usb_keyboard��׼������ */
am_usbd_keyboard_handle am_hc32f07x_usbd_keyboard_inst_init (void)
{
    return am_usbd_keyboard_init (&__g_usbd_keyboard_dev,
                                  &__g_usbd_keyboard_info,
								                  am_hc32f07x_usbd_init(&__g_hc32f07x_usbd_keyboard, &__g_hc32f07x_usbd_keyboard_info));
}

/** \brief usb_keyboard���ʼ�������usb_keyboard��׼������ */
void am_hc32f07x_usbd_keyboard_inst_deinit (void)
{
    am_usbd_keyboard_deinit (&__g_usbd_keyboard_dev);
}

/**
 * @}
 */

/* end of file */
