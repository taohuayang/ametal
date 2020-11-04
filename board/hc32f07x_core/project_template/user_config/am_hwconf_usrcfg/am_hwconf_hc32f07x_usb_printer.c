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
 * \brief zlg126 USB_printer �û������ļ�
 * \sa am_zlg126_hwconfig_usb_printer.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-12  adw, first implementation.
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
#include "am_usbd_printer.h"
#include "am_hc32f07x_usbd.h"
/**
 * \addtogroup am_zlg116_if_hwconfig_src_usb_printer
 * \copydoc am_zlg116_hwconfig_usb_printer.c
 * @{
 */

/*******************************************************************************
 * �û�USB���������ú�,�û������������꼴��,�������USB��������
 ******************************************************************************/

/** \brief USB�豸�������ú�*/
#define __USBD_PRINTER_VENDOR_ID                 (0x1F22) /**< \brief ���̱��,��Ϊ��Ʒ��������д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��*/
#define __USBD_PRINTER_PRODUCT_ID                (0x029B) /**< \brief ��Ʒ���*/
#define __USBD_PRINTER_DEVICE_ID                 (0x0101) /**< \brief �豸���*/
#define __USBD_PRINTER_VENDOR_STRING_INDEX       (0x01)   /**< \brief �������̵��ַ�������*/
#define __USBD_PRINTER_PRODUCT_STRING_INDEX      (0x02)   /**< \brief ������Ʒ���ַ������� */
#define __USBD_PRINTER_CONFIG_COUNT              (1U)     /**< \brief ��������һ������ֻ��һ������*/

/** \brief USB�������������ú�*/
#define __USBD_PRINTER_INTERFACE_COUNT           (1U)     /**< \brief �ӿ���*/
#define __USBD_PRINTER_CONFIGURE_INDEX           (1U)     /**< \brief ��������������*/
#define __USBD_PRINTER_DEVICE_POWER               AM_USBD_MAX_POWER /**< \brief �豸����������ĵ�������λ2mA,���100mA*/
/** \brief �豸���ԣ��Թ��磬��֧��Զ�̻���*/
#define __USBD_PRINTER_DEVICE_ATTRIBUTE          \
              (AM_USBD_CONFIG_SELF_POWER | AM_USBD_CONFIG_NOT_REMOTE_WAKEUP)

/**\brief USB�˵����������ú�*/
#define __USBD_PRINTER_ENDPOINT_IN                1  /**< \brief ����˵��*/
#define __USBD_PRINTER_ENDPOINT_IN_PACKSIZE       AM_USBD_MAX_EP_DATA_CNT       /**< \brief �˵����С,����Ϊ64*/
#define __USBD_PRINTER_ENDPOINT_IN_ATTRIBUTE      AM_USB_ENDPOINT_BULK          /**< \brief ���ö˵�����Ϊ��������*/
#define __USBD_PRINTER_ENDPOINT_IN_QUERY_TIME    (0x06)                         /**< \brief ���ö˵��ѯʱ��Ϊ10ms,��λΪ1ms*/

#define __USBD_PRINTER_ENDPOINT_OUT               2
#define __USBD_PRINTER_ENDPOINT_OUT_PACKSIZE      AM_USBD_MAX_EP_DATA_CNT
#define __USBD_PRINTER_ENDPOINT_OUT_ATTRIBUTE     AM_USB_ENDPOINT_BULK
#define __USBD_PRINTER_ENDPOINT_OUT_QUERY_TIME   (0x06)

/**\brief USB�ӿ����������ú�*/
#define __USBD_PRINTER_ENDPOINT_COUNT            (2U)     /**< \brief �˵����,����˵�������˵�(���������ƶ˵�)*/


/*****************************************************************************
 * ȫ�ֱ����ͳ���
 *****************************************************************************/

/**
 * \brief ��ӡ���豸id �ַ�������
 * ǰ�����ֽ�Ϊ�ַ������ݳ��ȣ���˶���.���Ա���ǰ�����ַ����ַ����ݣ���id������Ϊ������������ʹ�õı�ʶ��
 */
static uint8_t __g_printer_id[] = "xxMFG:ZLG;MDL: usb printer;CMD:POSTSCRIPT";

/**
 * \brief ��ӡ�����ݴ���buff����
 * \note ��buff��С������ڶ˵�������С������buff��СӦ�ô��ڴ�ӡ��id(__g_printer_id)�ַ�������,�����������
 */
static uint8_t __g_printer_buff[AM_USBD_MAX_EP_DATA_CNT + 1] = {0};

/*****************************************************************************
 * USB������(�豸������,�������������ӿ�������,�˵�������),�ò����û�ֻ�����������꼴��
 *****************************************************************************/

/* USB �豸������ */
static const uint8_t __g_am_usbd_printer_desc_dev[AM_USB_DESC_LENGTH_DEVICE]  = {
    AM_USB_DESC_LENGTH_DEVICE,        /* �豸���������ֽ��� */
    AM_USB_DESC_TYPE_DEVICE,          /* �豸���������ͱ�ţ��̶�Ϊ0x01 */

    /* USB�汾 USB2.0 */
    AM_USB_SHORT_GET_LOW(AM_USB_VERSION), AM_USB_SHORT_GET_HIGH(AM_USB_VERSION),
    AM_USBD_CLASS,                          /* ͨ���� */
    AM_USBD_SUBCLASS,                       /* �豸���� */
    AM_USBD_PROTOCOL,                       /* Э���� */
    AM_USBD_MAX_EP_DATA_CNT,                /* �˵�0��������С */

    /**
     * ���̱�š���Ҫ��USBЭ�����룬�����Ϊѧϰʹ�ÿ������ѡһ���Ѿ�ע����ģ�
     * ������Ϊ��Ʒ�����Ļ��ͱ���д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��
     */
    AM_USB_SHORT_GET_LOW(__USBD_PRINTER_VENDOR_ID), AM_USB_SHORT_GET_HIGH(__USBD_PRINTER_VENDOR_ID),

    /* ��Ʒ��� */
    AM_USB_SHORT_GET_LOW(__USBD_PRINTER_PRODUCT_ID), AM_USB_SHORT_GET_HIGH(__USBD_PRINTER_PRODUCT_ID),

    /* �豸������� */
    AM_USB_SHORT_GET_LOW(__USBD_PRINTER_DEVICE_ID), AM_USB_SHORT_GET_HIGH(__USBD_PRINTER_DEVICE_ID),
    __USBD_PRINTER_VENDOR_STRING_INDEX,     /* �������̵��ַ������� */
    __USBD_PRINTER_PRODUCT_STRING_INDEX,    /* ������Ʒ���ַ������� */
    0x00,                                   /* �����豸���кŵ��ַ������� */
    __USBD_PRINTER_CONFIG_COUNT,            /* ���õ�������ֻ����һ���� */
};

/* ���������������¼�������������Խ���ϼ�������ֱ�ӵõ��¼��������� */
static uint8_t __g_am_usbd_printer_desc_conf[AM_USB_DESC_LENGTH_ALL(__USBD_PRINTER_ENDPOINT_COUNT)] = {
    /* ���������� */
    AM_USB_DESC_LENGTH_CONFIGURE,     /* �����������ֽ��� */
    AM_USB_DESC_TYPE_CONFIGURE,       /* �������������ͱ�ţ��̶�Ϊ0x02 */

    /* �������������������������ܳ���(�������������ӿ��������ţ��������˵�������) */
    AM_USB_SHORT_GET_LOW(AM_USB_DESC_LENGTH_ALL(__USBD_PRINTER_ENDPOINT_COUNT)),
    AM_USB_SHORT_GET_HIGH(AM_USB_DESC_LENGTH_ALL(__USBD_PRINTER_ENDPOINT_COUNT)),
    __USBD_PRINTER_INTERFACE_COUNT,         /* �ӿ����������� */
    __USBD_PRINTER_CONFIGURE_INDEX,         /* ����ֵ */
    0x00,                                   /* ���������õ��ַ������� */

    /* �豸���ԣ����߹��磬��֧��Զ�̻��� */
    __USBD_PRINTER_DEVICE_ATTRIBUTE,
    __USBD_PRINTER_DEVICE_POWER,            /* �����߻�ȡ����������100mA�� 2mAһ����λ */

    /* �ӿ������� */
    AM_USB_DESC_LENGTH_INTERFACE,     /* �ӿ��������ֽ��� */
    AM_USB_DESC_TYPE_INTERFACE,       /* �ӿ����������ͱ�ţ��̶�Ϊ0x04 */
    0x00,                                   /* �ýӿڱ�� */
    0x00,                                   /* ��ѡ���õ�����ֵ���ýӿڵı��ñ�ţ� */
    __USBD_PRINTER_ENDPOINT_COUNT,          /* �ýӿ�ʹ�õĶ˵������������˵�0�� */
    AM_USBD_CONFIG_PRINTER_CLASS_CODE,      /* printer_CLASS�� */
    AM_USBD_PRINTER_SUBCLASS,               /* printer������ */
    AM_USBD_PRINTER_PROTOCOL,               /* printerЭ������ */
    0x00,                                   /* �����ýӿڵ��ַ������� */

    /* ����˵������� */
    AM_USB_DESC_LENGTH_ENDPOINT,            /* �˵��������ֽ��� */
    AM_USB_DESC_TYPE_ENDPOINT,        /* �˵����������ͱ�ţ��̶�Ϊ0x05 */

    /* D7 1:USB_IN  0:USB_OUT D3:D0 �˵�� */
    (__USBD_PRINTER_ENDPOINT_IN | (AM_USB_IN << AM_USB_REQ_TYPE_DIR_SHIFT)),
    __USBD_PRINTER_ENDPOINT_IN_ATTRIBUTE,   /* �˵����� 02��ʾ����  */

    AM_USB_SHORT_GET_LOW(__USBD_PRINTER_ENDPOINT_IN_PACKSIZE),
    AM_USB_SHORT_GET_HIGH(__USBD_PRINTER_ENDPOINT_IN_PACKSIZE), /* �˵�һ�����շ���������С */

    __USBD_PRINTER_ENDPOINT_IN_QUERY_TIME,  /* ������ѯ�˵�ʱ��ʱ������10ms  */

    /* ����˵������� */
    AM_USB_DESC_LENGTH_ENDPOINT,            /* �˵��������ֽ��� */
    AM_USB_DESC_TYPE_ENDPOINT,        /* �˵����������ͱ�ţ��̶�Ϊ0x05 */

    /* �˵��ַ��������� */
    (__USBD_PRINTER_ENDPOINT_OUT | (AM_USB_OUT << AM_USB_REQ_TYPE_DIR_SHIFT)),

    __USBD_PRINTER_ENDPOINT_OUT_ATTRIBUTE,  /* �˵����� */

    AM_USB_SHORT_GET_LOW(__USBD_PRINTER_ENDPOINT_OUT_PACKSIZE),
    AM_USB_SHORT_GET_HIGH(__USBD_PRINTER_ENDPOINT_OUT_PACKSIZE), /* �˵�һ�����շ���������С */

    __USBD_PRINTER_ENDPOINT_OUT_QUERY_TIME  /* ������ѯ�˵�ʱ��ʱ���� 10ms */
};

/*******************************************************************************
 * �ַ���������,����û���Ҫ�޸���������Ϣ��ע��ʹ�õ���UINCODE��(ע���С��)
 ******************************************************************************/
/**< \brief ������Ʒ���ַ��������� */
static const uint8_t __g_am_usbd_printer_desc_str_iproduct[18] = {
    sizeof(__g_am_usbd_printer_desc_str_iproduct),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,          /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */

     0x55, 0x00, /* U */
     0x42, 0x00, /* S */
     0x53, 0x00, /* B */
     0x21, 0x6a, /* ģ */
     0xdf, 0x62, /* �� */
     0x53, 0x62, /* �� */
     0x70, 0x53, /* ӡ */
     0x73, 0x67, /* �� */
};

/**< \brief ����ID�ַ��������� */
/**< \brief ����ʹ����ʽӢ���ʹ�ü������ĵ�ԭ�������ʹ�ü������ģ�������������ӻ�Ҫ�ַ��������� */
/**< \brief ��ʽӢ�������IDΪ0x0409���������ĵ�����IDΪ0x0804��ע���С�ˡ� */
static const uint8_t __g_am_usbd_printer_desc_str_language_id[4] = {
    sizeof(__g_am_usbd_printer_desc_str_language_id),       /* �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,          /* �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x04,
    0x08,       /* �������� */
};

/**< \brief �������̵��ַ��������� */
static uint8_t __g_am_usbd_printer_desc_str_imanufacturer[22] = {
    sizeof(__g_am_usbd_printer_desc_str_imanufacturer),       /* �ַ����������ֽ��� */
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
static const am_usbd_descriptor_t __g_am_usbd_printer_descriptor[] = {
    /* �豸������ */
    {
        (AM_USB_DESC_TYPE_DEVICE << 8) | (0x00),
        sizeof(__g_am_usbd_printer_desc_dev),
        __g_am_usbd_printer_desc_dev
    },

    /* ���������������¼������� */
    {
        (AM_USB_DESC_TYPE_CONFIGURE << 8) | (0x00),
        sizeof(__g_am_usbd_printer_desc_conf),
        __g_am_usbd_printer_desc_conf
    },

    /* �ַ���������0����������id */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | (0x00),
        sizeof(__g_am_usbd_printer_desc_str_language_id),
        __g_am_usbd_printer_desc_str_language_id
    },

    /* �ַ���������1���������� */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_PRINTER_VENDOR_STRING_INDEX,
        sizeof(__g_am_usbd_printer_desc_str_imanufacturer),
        __g_am_usbd_printer_desc_str_imanufacturer
    },

    /* �ַ���������2��������Ʒ */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_PRINTER_PRODUCT_STRING_INDEX,
        sizeof(__g_am_usbd_printer_desc_str_iproduct),
        __g_am_usbd_printer_desc_str_iproduct
    },
};

/******************************************************************************
 * ƽ̨��ʼ�����������ʼ�������Ѿ��豸��Ϣ
 ******************************************************************************/
/**
 * \brief ƽ̨��ʼ��
 */
static void __am_usbd_printer_init (void) {
	
    /* ʹ��ʱ�� */
    amhw_hc32f07x_rcc_set_start(0x5A5A);
    amhw_hc32f07x_rcc_set_start(0xA5A5);
    amhw_hc32f07x_rcc_usbclk_adjust_set (AMHW_HC32F07X_USBCLK_ADJUST_PLL);
    am_clk_enable(CLK_USB);
}

/**
 * \brief ƽ̨ȥ��ʼ��
 */
static void __am_usbd_printer_deinit (void) {
    am_clk_disable(CLK_USB);
    amhw_hc32f07x_rcc_peripheral_disable (AMHW_HC32F07X_RCC_USB);       /* ����USBʱ�� */                            /* ����USBʱ�� */
}

static const am_usbd_devinfo_t __g_usbd_info = {
        __g_am_usbd_printer_descriptor,                                                         /* ��������ַ */
        sizeof(__g_am_usbd_printer_descriptor) / sizeof(__g_am_usbd_printer_descriptor[0]),     /* ���������� */
};

/**< \brief ����USB�豸��Ϣ */
static const am_hc32f07x_usbd_devinfo_t  __g_hc32f07x_usbd_printer_info = {
    HC32F07X_USB_BASE,                           /* �Ĵ�������ַ */
    INUM_USB,                                  /* �жϺ� */
    __am_usbd_printer_init,           /**< \brief ƽ̨��ʼ�� */
    __am_usbd_printer_deinit,         /**< \brief ƽ̨ȥ��ʼ�� */
    &__g_usbd_info,
};

/** \brief USB��ӡ����Ϣ�ṹ��*/
static am_usbd_printer_info_t __g_usbd_printer_info = {
        __g_printer_id,               /**< \brief ��ӡ��id */
        sizeof(__g_printer_id) - 1,   /**< \brief ��ӡ��id����,(��һΪ��������\0��)*/
        __g_printer_buff,             /**< \brief ��ӡ��ʹ��buff */
};

/** \brief ��ӡ��ʹ��handle(USB�豸��) */
static am_usbd_printer_t     __g_usb_printer_dev;

/** \brief ����hc32f07x ��USB handle*/
static am_hc32f07x_usbd_dev_t  __g_hc32f07x_usb_printer_dev;

/** \brief usb_printerʵ����ʼ�������usb_printer��׼������ */
am_usbd_printer_handle am_hc32f07x_usbd_printer_inst_init (void)
{
    return am_usbd_printer_init(&__g_usb_printer_dev,
                                &__g_usbd_printer_info,
                                 am_hc32f07x_usbd_init(&__g_hc32f07x_usb_printer_dev, &__g_hc32f07x_usbd_printer_info));
}

/** \brief usb_printer���ʼ�������usb_printer��׼������ */
void am_hc32f07x_usbd_printer_inst_deinit (void)
{
    am_usbd_printer_deinit(&__g_usb_printer_dev);
}

/**
 * @}
 */

/* end of file */
