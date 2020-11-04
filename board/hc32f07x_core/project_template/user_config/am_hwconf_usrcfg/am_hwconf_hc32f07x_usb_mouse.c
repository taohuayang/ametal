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
 * \brief zmf159 USB_MSC �û������ļ�
 * \sa am_zmf159_hwconfig_usb_msc.c
 *
 * \internal
 * \par Modification history
 *
 * - 1.10 19-01-11  adw, add configuration macro
 * - 1.00 18-10-29  enf, first implementation.
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
#include "am_usbd_msc.h"
#include "am_hc32f07x_usbd.h"


/**
 * \addtogroup am_zmf159_if_hwconfig_src_usb_msc
 * \copydoc am_zmf159_hwconfig_usb_msc.c
 * @{
 */
/*******************************************************************************
 * �û�USB���������ú�,�û������������꼴��,�������USB��������
 ******************************************************************************/

#define __USBD_MSC_SYS_WIN7         (0)
#define __USBD_MSC_SYS_WIN10        (1)

#define __USBD_MSC_FILE_CREAT_TIME1    (15U)
#define __USBD_MSC_FILE_CREAT_TIME2    (48U)
#define __USBD_MSC_FILE_CREAT_TIME3    (26U)

#define __USBD_MSC_FILE_CREAT_DATE1    (2018U)
#define __USBD_MSC_FILE_CREAT_DATE2    (10U)
#define __USBD_MSC_FILE_CREAT_DATE3    (29U)

#define __USBD_MSC_FILE_MODIFIED_TIME1 (15U)
#define __USBD_MSC_FILE_MODIFIED_TIME2 (36U)
#define __USBD_MSC_FILE_MODIFIED_TIME3 (47U)

#define __USBD_MSC_FILE_MODIFIED_DATE1 (2018U)
#define __USBD_MSC_FILE_MODIFIED_DATE2 (11U)
#define __USBD_MSC_FILE_MODIFIED_DATE3 (2U)

/** \brief USB�豸�������ú�*/
#define __USBD_MSC_VENDOR_ID                 (0x4195) /**< \brief ���̱��,��Ϊ��Ʒ��������д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��*/
#define __USBD_MSC_PRODUCT_ID                (0x6515) /**< \brief ��Ʒ���*/
#define __USBD_MSC_DEVICE_ID                 (0x0101) /**< \brief �豸���*/
#define __USBD_MSC_VENDOR_STRING_INDEX       (0x01)   /**< \brief �������̵��ַ�������*/
#define __USBD_MSC_PRODUCT_STRING_INDEX      (0x02)   /**< \brief ������Ʒ���ַ������� */
#define __USBD_MSC_DEVICE_STRING_INDEX       (0x03)   /**< \brief �����豸���кŵ��ַ�������*/
#define __USBD_CONFIGURATION_COUNT           (1U)     /**< \brief ��������һ������ֻ��һ������*/

/** \brief USB�������������ú�*/
#define __USBD_MSC_INTERFACE_COUNT           (1U)     /**< \brief �ӿ���*/
#define __USBD_MSC_CONFIGURE_INDEX           (1U)     /**< \brief ��������������*/
#define __USBD_MSC_DEVICE_POWER               AM_USBD_MAX_POWER /**< \brief �豸����������ĵ�������λ2mA,���100mA*/
/** \brief �豸���ԣ��Թ��磬��֧��Զ�̻���*/
#define __USBD_MSC_DEVICE_ATTRIBUTE          \
              (AM_USBD_CONFIG_SELF_POWER | AM_USBD_CONFIG_REMOTE_WAKEUP)

/**\brief USB�˵����������ú�*/
#define __USBD_MSC_ENDPOINT_IN                (1U)  /**< \brief ����˵��*/
#define __USBD_MSC_ENDPOINT_IN_PACKSIZE       AM_USBD_MAX_EP_DATA_CNT       /**< \brief �˵����С,����Ϊ64*/
#define __USBD_MSC_ENDPOINT_IN_ATTRIBUTE      AM_USB_ENDPOINT_BULK          /**< \brief ���ö˵�����Ϊ��������*/
#define __USBD_MSC_ENDPOINT_IN_QUERY_TIME    (0x01)                         /**< \brief ���ö˵��ѯʱ��Ϊ10ms,��λΪ1ms*/

#define __USBD_MSC_ENDPOINT_OUT               (2)
#define __USBD_MSC_ENDPOINT_OUT_PACKSIZE      AM_USBD_MAX_EP_DATA_CNT
#define __USBD_MSC_ENDPOINT_OUT_ATTRIBUTE     AM_USB_ENDPOINT_BULK
#define __USBD_MSC_ENDPOINT_OUT_QUERY_TIME   (0x01)

/**\brief USB�ӿ����������ú�*/
#define __USBD_MSC_ENDPOINT_COUNT            (2U)     /**< \brief �˵����,����˵�������˵�(���������ƶ˵�)*/

/*****************************************************************************
 * USB������(�豸������,�������������ӿ�������,�˵�������),�ò����û�ֻ�����������꼴��
 *****************************************************************************/
/* �豸������ */
 static  uint8_t __g_usb_mouse_desc_dev[AM_USB_DESC_LENGTH_DEVICE]  = {
   AM_USB_DESC_LENGTH_DEVICE,       /* �豸���������ֽ��� */
    AM_USB_DESC_TYPE_DEVICE,         /* �豸���������ͱ�ţ��̶�Ϊ0x01 */

    /* USB�汾 USB2.0 */
    AM_USB_SHORT_GET_LOW(AM_USB_VERSION), AM_USB_SHORT_GET_HIGH(AM_USB_VERSION),

    AM_USBD_CLASS,                         /* ͨ���� */
    AM_USBD_SUBCLASS,                      /* �豸���� */
    AM_USBD_PROTOCOL,                      /* Э���� */
    AM_USBD_MAX_EP_DATA_CNT,               /* �˵�0��������С */

    /**
     * ���̱�š���Ҫ��USBЭ�����룬�����Ϊѧϰʹ�ÿ������ѡһ���Ѿ�ע����ģ�
     * ������Ϊ��Ʒ�����Ļ��ͱ���д�Լ���˾�ĳ��̱�ţ�������Ȩ���˴�����һ��û����USBЭ��ע��ı��
     */
    AM_USB_SHORT_GET_LOW(__USBD_MSC_VENDOR_ID), AM_USB_SHORT_GET_HIGH(__USBD_MSC_VENDOR_ID),

    /* ��Ʒ��� */
    AM_USB_SHORT_GET_LOW(__USBD_MSC_PRODUCT_ID), AM_USB_SHORT_GET_HIGH(__USBD_MSC_PRODUCT_ID),

    /* �豸������� */
    AM_USB_SHORT_GET_LOW(__USBD_MSC_DEVICE_ID), AM_USB_SHORT_GET_HIGH(__USBD_MSC_DEVICE_ID),

    __USBD_MSC_VENDOR_STRING_INDEX,         /* �������̵��ַ������� */
    __USBD_MSC_PRODUCT_STRING_INDEX,        /* ������Ʒ���ַ������� */
    __USBD_MSC_DEVICE_STRING_INDEX,         /* �����豸���кŵ��ַ������� */
    __USBD_CONFIGURATION_COUNT,             /* ���õ�������ֻ����һ���� */
};

/* ���������������¼�������������Խ���ϼ�������ֱ�ӵõ��¼��������� */
 static uint8_t __g_usb_mouse_desc_conf[AM_USB_DESC_LENGTH_ALL(__USBD_MSC_ENDPOINT_COUNT) + AM_USB_DESC_LENGTH_HID] = {

    /* ���������� */
    AM_USB_DESC_LENGTH_CONFIGURE,     /* �����������ֽ��� 0x09*/
    AM_USB_DESC_TYPE_CONFIGURE,       /* �������������ͱ�ţ��̶�Ϊ0x02 */

    /* �������������������������ܳ��� */
    34,
    0x00,
    __USBD_MSC_INTERFACE_COUNT,             /* �ӿ����������� */
    __USBD_MSC_CONFIGURE_INDEX,             /* ����ֵ */
    0x00,                                   /* ���������õ��ַ�������,0x00��ʾû�� */

    /* �豸���ԣ����߹��磬��֧��Զ�̻��� */
    0x80|(1<<6),
    __USBD_MSC_DEVICE_POWER,                /* �����߻�ȡ����������100mA�� 2mAһ����λ */

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
    0x01,       /* �˵����� 01��ʾ�ж�  */

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

     0x55, 0x00, /* U */
     0x42, 0x00, /* S */
     0x53, 0x00, /* B */
     0x21, 0x6a, /* ģ */
     0xdf, 0x62, /* �� */
     0x55, 0x00, /* U */
     0xd8, 0x76  /* �� */
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
    /* �豸������ */
    {
        (AM_USB_DESC_TYPE_DEVICE << 8) | (0x00),
        sizeof(__g_usb_mouse_desc_dev),
        __g_usb_mouse_desc_dev
    },

    /* ���������������¼������� */
    {
        (AM_USB_DESC_TYPE_CONFIGURE << 8) | (0x00),
        sizeof(__g_usb_mouse_desc_conf),
        __g_usb_mouse_desc_conf
    },

    /* �ַ�������������������id */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | (0x00),
        sizeof(__g_usb_mouse_desc_str_language_id),
        __g_usb_mouse_desc_str_language_id
    },

    /* �ַ������������������� */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_MSC_VENDOR_STRING_INDEX,
        sizeof(__g_usb_mouse_desc_str_imanufacturer),
        __g_usb_mouse_desc_str_imanufacturer
    },

    /* �ַ�����������������Ʒ */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_MSC_PRODUCT_STRING_INDEX,
        sizeof(__g_usb_mouse_desc_str_iproduct),
        __g_usb_mouse_desc_str_iproduct
    },

    /* �ַ����������������豸���к� */
    {
        (AM_USB_DESC_TYPE_STRING << 8)| __USBD_MSC_DEVICE_STRING_INDEX,
        sizeof(__g_usb_mouse_desc_str_iserialnumber),
        __g_usb_mouse_desc_str_iserialnumber
    },
		
		{
        (AM_USB_DESC_TYPE_HID_REPORT << 8)| (0x00),
        sizeof(__g_usb_mouse_desc_str_report),
        __g_usb_mouse_desc_str_report
    },
};

//static const uint8_t __g_readme_data[]= {
//    "**ZLGģ��U������**\r\n"
//     "1.���ж�ʹ��PC����ϵͳ�����ʹ��WIN10,�ǵ��޸�am_hwconf_zmf159_usb_msc.c�ļ���ϵͳ��������;\r\n"
//     "2.���ϴ��ڣ����ļ��϶���U���У����ӡ�϶��ļ�����Ϣ;\r\n"
//};


//static const uint8_t __g_fat_root_dir[64] = {

//    /* ���̱��zlgmcu �ļ�U�� */
//     'Z', 'L', 'G', 'M', 'C', 'U', 0x20, 0x20, 0x55, 0xC5, 0xCC,
//    0x08,                  /* �ļ����ԣ���ʾ���̱�� */
//    0x00,                  /* ���� */
//    0x00,                  /* ����ʱ�����ʱ��� */

//    /* �ļ�����ʱ�䣬15��48��26�� */
//    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),
//    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),

//     /* �ļ��������ڣ�2018��10��29�� */
//    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),
//    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),

//    /* ���������ڣ�2018��10��29�� */
//    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),
//    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),

//    0x00, 0x00,            /* ��ʼ�غŸ�λ�ֽڣ�FAT12/16����Ϊ0 */

//    /* ����޸�ʱ�䣬15��36��47�� */
//    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),
//    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),

//    /* ����޸����ڣ�2018��11��2�� */
//    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),
//    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),

//    0x00, 0x00,               /* ��ʼ�ص��� */
//    0x00, 0x00, 0x00, 0x00,   /* �ļ����� */
//    /* ��Ŀ¼�µĲ����ļ� */
//    /* �ļ�����README.TXT�� */
//    'R',  'E',   'A',  'D', 'M', 'E', ' ', ' ',  'T', 'X', 'T',
//    0x01,                  /*  �ļ����ԣ���ʾֻ���ļ�  */
//    0x00,                  /*  ���� */
//    0x00,                  /*  ����ʱ�����ʱ��� */

//    /* �ļ�����ʱ�䣬15��48��26�� */
//    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),
//    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),

//    /* �ļ���������,2018��10��29�� */
//    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),
//    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),

//    /* ���������� ,15��36��47�� */
//    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),
//    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),

//    0x00, 0x00,            /* ��ʼ�غŸ�λ�ֽڣ�FAT12/16����Ϊ0 */

//    /* ����޸�ʱ��,15��36��47�� */
//    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),
//    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),

//    /* ����޸����ڣ�2018��11��2�� */
//    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),
//    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),

//    0x02, 0x00,            /* ��ʼ�ص��֣���2��(������) */

//    /* �ļ����� */
//    (sizeof(__g_readme_data) - 1), ((sizeof(__g_readme_data) - 1) >> 8), 0x00, 0x00,
//};
/******************************************************************************
 * ƽ̨��ʼ�����������ʼ�������Ѿ��豸��Ϣ
 ******************************************************************************/
/**
 * \brief ƽ̨��ʼ��
 */
static void __usb_mouse_init (void) {
    /* ʹ��ʱ�� */
	amhw_hc32f07x_rcc_set_start(0x5A5A);
	amhw_hc32f07x_rcc_set_start(0xA5A5);
	amhw_hc32f07x_rcc_usbclk_adjust_set (AMHW_HC32F07X_USBCLK_ADJUST_PLL);
  am_clk_enable(CLK_USB);
}

/**
 * \brief ƽ̨ȥ��ʼ��
 */
static void __usb_mouse_deinit (void) {
    am_clk_disable(CLK_USB);
    amhw_hc32f07x_rcc_peripheral_disable (AMHW_HC32F07X_RCC_USB);
}

/**< \brief �豸��Ϣ*/
static const am_usbd_devinfo_t __g_usbd_mouse_info = {
        __g_usb_mouse_descriptor,                                                 /* ��������ַ */
        sizeof(__g_usb_mouse_descriptor) / sizeof(__g_usb_mouse_descriptor[0]),     /* ���������� */
};

/**< \brief ����USB�豸��Ϣ */
static const am_hc32f07x_usbd_devinfo_t  __g_hc32f07x_usbd_mouse_info = {
    HC32F07X_USB_BASE,                  /**< \brief �Ĵ�������ַ */
    INUM_USB,                      /**< \brief �жϺ� */
    __usb_mouse_init,                   /**< \brief ƽ̨��ʼ�� */
    __usb_mouse_deinit,                 /**< \brief ƽ̨ȥ��ʼ�� */
    &__g_usbd_mouse_info,
};

/** \brief USB MSC�豸ʵ�� */
static am_usbd_msc_t      __g_usb_mouse_dev;

///** \brief ZMF159 USB�豸ʵ�� */
//static am_hc32f07x_usbd_dev_t  __g_zlg_usbd_msc;

///**< \brief ����SCSI������� */
//static uint8_t __g_sici_cmd_buff[AM_USBD_MAX_EP_DATA_CNT + 1] = {0};

//static const am_usbd_msc_diskinfo_t __g_usbd_msc_disk_info = {
//    __USBD_MSC_SYS_WIN7,
//    0,

//    AM_USBD_MSC_DISD_SIZE,
//    AM_USBD_MSC_SECTOR_SIZE,
//    AM_USBD_MSC_DISD_SIZE / AM_USBD_MSC_SECTOR_SIZE,
//    (AM_USBD_MSC_DISD_SIZE / 256 / 1024 + 1) * 512,
//    (AM_USBD_MSC_DISD_SIZE / 256 / 1024 * 2 + 1) * 512,
//    (AM_USBD_MSC_DISD_SIZE / 256 / 1024 * 2 + 17) * 512,

//    /* ָ�����  */
//    __g_sici_cmd_buff,

//    /* FAT��Ŀ¼ */
//    __g_fat_root_dir,
//    sizeof(__g_fat_root_dir),

//    /* README�ļ����� */
//    __g_readme_data,
//    sizeof(__g_readme_data),
//};
am_hc32f07x_usbd_dev_t           am_hc32f07x_usbd_dev;
/** \brief usb_mscʵ����ʼ�������usb_msc��׼������ */
am_usbd_dev_t am_hc32f07x_usbd_mouse_inst_init (void)
{
    return *am_hc32f07x_usbd_init (&am_hc32f07x_usbd_dev,
                                   &__g_hc32f07x_usbd_mouse_info);
}

/** \brief usb_msc���ʼ�������usb_msc��׼������ */
void am_hc32f07x_usbd_mouse_inst_deinit (void)
{
    am_usb_msc_deinit(&__g_usb_mouse_dev);
}

/**
 * @}
 */

/* end of file */
