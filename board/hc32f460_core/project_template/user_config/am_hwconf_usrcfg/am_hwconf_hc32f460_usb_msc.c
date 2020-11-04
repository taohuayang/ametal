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
 * \sa am_hc32f460_hwconfig_usb_msc.c
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
#include "am_usbd_msc.h"
#include "am_hc32f460.h"
#include "am_hc32f460_usbd.h"
#include "amhw_hc32f460_usbd.h"
#include "am_usbd_msc.h"
#include "usb_core.h"
#include "usbd_desc.h"
#include "usbd_usr.h"
#include "usbd_msc_core.h"
/**
 * \addtogroup am_hc32f460_if_hwconfig_src_usb_msc
 * \copydoc am_hc32f460_hwconfig_usb_msc.c
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
#define __USBD_MSC_INTERFACE_COUNT           (1U)               /**< \brief �ӿ���*/
#define __USBD_MSC_CONFIGURE_INDEX           (1U)               /**< \brief ��������������*/
#define __USBD_MSC_DEVICE_POWER               AM_USBD_MAX_POWER /**< \brief �豸����������ĵ�������λ2mA,���100mA*/
/** \brief �豸���ԣ��Թ��磬��֧��Զ�̻���*/
#define __USBD_MSC_DEVICE_ATTRIBUTE          \
              (AM_USBD_CONFIG_SELF_POWER | AM_USBD_CONFIG_NOT_REMOTE_WAKEUP)

/**\brief USB�˵����������ú�*/
#define __USBD_MSC_ENDPOINT_IN               (1U)                     /**< \brief ����˵��*/
#define __USBD_MSC_ENDPOINT_IN_PACKSIZE      AM_USBD_MAX_EP_DATA_CNT  /**< \brief �˵����С,����Ϊ64*/
#define __USBD_MSC_ENDPOINT_IN_ATTRIBUTE     AM_USB_ENDPOINT_BULK     /**< \brief ���ö˵�����Ϊ��������*/
#define __USBD_MSC_ENDPOINT_IN_QUERY_TIME    (0x01)                   /**< \brief ���ö˵��ѯʱ��Ϊ10ms,��λΪ1ms*/

#define __USBD_MSC_ENDPOINT_OUT              (2)
#define __USBD_MSC_ENDPOINT_OUT_PACKSIZE     AM_USBD_MAX_EP_DATA_CNT
#define __USBD_MSC_ENDPOINT_OUT_ATTRIBUTE    AM_USB_ENDPOINT_BULK
#define __USBD_MSC_ENDPOINT_OUT_QUERY_TIME   (0x01)

/**\brief USB�ӿ����������ú�*/
#define __USBD_MSC_ENDPOINT_COUNT            (2U)     /**< \brief �˵����,����˵�������˵�(���������ƶ˵�)*/

/*****************************************************************************
 * USB������(�豸������,�������������ӿ�������,�˵�������),�ò����û�ֻ�����������꼴��
 *****************************************************************************/
/**\brief �豸������ */
static const uint8_t __g_usb_msc_desc_dev[AM_USB_DESC_LENGTH_DEVICE]  = {
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
    AM_USB_SHORT_GET_LOW(__USBD_MSC_VENDOR_ID), AM_USB_SHORT_GET_HIGH(__USBD_MSC_VENDOR_ID),

    /**\brief ��Ʒ��� */
    AM_USB_SHORT_GET_LOW(__USBD_MSC_PRODUCT_ID), AM_USB_SHORT_GET_HIGH(__USBD_MSC_PRODUCT_ID),

    /**\brief �豸������� */
    AM_USB_SHORT_GET_LOW(__USBD_MSC_DEVICE_ID), AM_USB_SHORT_GET_HIGH(__USBD_MSC_DEVICE_ID),

    __USBD_MSC_VENDOR_STRING_INDEX,    /**< \brief �������̵��ַ������� */
    __USBD_MSC_PRODUCT_STRING_INDEX,   /**< \brief ������Ʒ���ַ������� */
    __USBD_MSC_DEVICE_STRING_INDEX,    /**< \brief �����豸���кŵ��ַ������� */
    __USBD_CONFIGURATION_COUNT,        /**< \brief ���õ�������ֻ����һ���� */
};

/**\brief ���������������¼�������������Խ���ϼ�������ֱ�ӵõ��¼��������� */
static uint8_t __g_usb_msc_desc_conf[AM_USB_DESC_LENGTH_ALL(__USBD_MSC_ENDPOINT_COUNT)] = {
    /**\brief ���������� */
    AM_USB_DESC_LENGTH_CONFIGURE,     /**< \brief �����������ֽ��� */
    AM_USB_DESC_TYPE_CONFIGURE,       /**< \brief �������������ͱ�ţ��̶�Ϊ0x02 */

    /**\brief �������������������������ܳ��� */
    AM_USB_SHORT_GET_LOW(AM_USB_DESC_LENGTH_ALL(__USBD_MSC_ENDPOINT_COUNT)),
    AM_USB_SHORT_GET_HIGH(AM_USB_DESC_LENGTH_ALL(__USBD_MSC_ENDPOINT_COUNT)),
    __USBD_MSC_INTERFACE_COUNT,       /**< \brief �ӿ����������� */
    __USBD_MSC_CONFIGURE_INDEX,       /**< \brief ����ֵ */
    0x00,                             /**< \brief ���������õ��ַ�������,0x00��ʾû�� */

    /**\brief �豸���ԣ����߹��磬��֧��Զ�̻��� */
    __USBD_MSC_DEVICE_ATTRIBUTE,
    __USBD_MSC_DEVICE_POWER,          /**< \brief �����߻�ȡ����������100mA�� 2mAһ����λ */

    /**\brief �ӿ������� */
    AM_USB_DESC_LENGTH_INTERFACE,     /**< \brief �ӿ��������ֽ��� */
    AM_USB_DESC_TYPE_INTERFACE,       /**< \brief �ӿ����������ͱ�ţ��̶�Ϊ0x04 */
    0x00,                             /**< \brief �ýӿڱ��,�ӿ������������0��ʼ,�Դ����� */
    0x00,                             /**< \brief ��ѡ���õ�����ֵ���ýӿڵı��ñ�ţ� */
    __USBD_MSC_ENDPOINT_COUNT,        /**< \brief �ýӿ�ʹ�õĶ˵������������˵�0�� */
    AM_USBD_CONFIG_MSC_CLASS_CODE,    /**< \brief MSC_CLASS�� */
    AM_USBD_MSC_SUBCLASS,             /**< \brief msc������ */
    AM_USBD_MSC_PROTOCOL,             /**< \brief mscЭ������ */
    0x00,                             /**< \brief �����ýӿڵ��ַ�������, 0x00��ʾû�� */

    /**\brief ����˵������� */
    AM_USB_DESC_LENGTH_ENDPOINT,      /**< \brief �˵��������ֽ��� */
    AM_USB_DESC_TYPE_ENDPOINT,        /**< \brief �˵����������ͱ�ţ��̶�Ϊ0x05 */
    (__USBD_MSC_ENDPOINT_IN | (AM_USB_IN << AM_USB_REQ_TYPE_DIR_SHIFT)),
    __USBD_MSC_ENDPOINT_IN_ATTRIBUTE, /**< \brief �˵����� 02��ʾ����  */

    AM_USB_SHORT_GET_LOW(__USBD_MSC_ENDPOINT_IN_PACKSIZE),
    AM_USB_SHORT_GET_HIGH(__USBD_MSC_ENDPOINT_IN_PACKSIZE), /**< \brief �˵�һ�����շ���������С */

    __USBD_MSC_ENDPOINT_IN_QUERY_TIME,   /* ������ѯ�˵�ʱ��ʱ������10ms  */

    /**\brief ����˵������� */
    AM_USB_DESC_LENGTH_ENDPOINT,         /**< \brief �˵��������ֽ��� */
    AM_USB_DESC_TYPE_ENDPOINT,           /**< \brief �˵����������ͱ�ţ��̶�Ϊ0x05 */

    /**\brief �˵��ַ��������� */
    (__USBD_MSC_ENDPOINT_OUT | (AM_USB_OUT << AM_USB_REQ_TYPE_DIR_SHIFT)),

    __USBD_MSC_ENDPOINT_OUT_ATTRIBUTE,   /**< \brief �˵����� */

    AM_USB_SHORT_GET_LOW(__USBD_MSC_ENDPOINT_OUT_PACKSIZE),
    AM_USB_SHORT_GET_HIGH(__USBD_MSC_ENDPOINT_OUT_PACKSIZE), /**< \brief �˵�һ�����շ���������С */

    __USBD_MSC_ENDPOINT_OUT_QUERY_TIME,     /**< \brief ������ѯ�˵�ʱ��ʱ���� 10ms */
};

/*******************************************************************************
 * �ַ���������,����û���Ҫ�޸���������Ϣ��ע��ʹ�õ���UINCODE��(ע���С��)
 ******************************************************************************/
/**< \brief ������Ʒ���ַ��������� */
static const uint8_t __g_usb_msc_desc_str_iproduct[16] = {
    sizeof(__g_usb_msc_desc_str_iproduct), /**< \brief �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,               /**< \brief �ַ������������ͱ�ţ��̶�Ϊ0x03 */

     0x55, 0x00, /**< \brief U */
     0x42, 0x00, /**< \brief S */
     0x53, 0x00, /**< \brief B */
     0x21, 0x6a, /**< \brief ģ */
     0xdf, 0x62, /**< \brief �� */
     0x55, 0x00, /**< \brief U */
     0xd8, 0x76  /**< \brief �� */
};
/*******************************************************************************
 * ����ID�ַ���������
 * ����ʹ����ʽӢ���ʹ�ü������ĵ�ԭ�������ʹ�ü������ģ�������������ӻ�Ҫ�ַ���������
 * ��ʽӢ�������IDΪ0x0409���������ĵ�����IDΪ0x0804��ע���С�ˡ�
******************************************************************************/
static const uint8_t __g_usb_msc_desc_str_language_id[4] = {
    sizeof(__g_usb_msc_desc_str_language_id),  /**< \brief �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,                   /**< \brief �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x04,
    0x08,                                      /**< \brief �������� */
};

/**< \brief �������̵��ַ��������� */
static const uint8_t __g_usb_msc_desc_str_imanufacturer[22] = {
    sizeof(__g_usb_msc_desc_str_imanufacturer),       /**< \brief �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,       /**< \brief �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x7f, 0x5e, /**< \brief �� */
    0xde, 0x5d, /**< \brief �� */
    0xf4, 0x81, /**< \brief �� */
    0xdc, 0x8f, /**< \brief Զ */
    0x35, 0x75, /**< \brief �� */
    0x50, 0x5b, /**< \brief �� */
    0x09, 0x67, /**< \brief �� */
    0x50, 0x96, /**< \brief �� */
    0x6c, 0x51, /**< \brief �� */
    0xf8, 0x53, /**< \brief ˾ */
};

/**< \brief �����豸���кŵ��ַ��������� */
static const uint8_t __g_usb_msc_desc_str_iserialnumber[22] = {
    sizeof(__g_usb_msc_desc_str_iserialnumber),  /**< \brief �ַ����������ֽ��� */
    AM_USB_DESC_TYPE_STRING,                     /**< \brief �ַ������������ͱ�ţ��̶�Ϊ0x03 */
    0x32, 0x00, /**< \brief 2 */
    0x30, 0x00, /**< \brief 0 */
    0x31, 0x00, /**< \brief 1 */
    0x38, 0x00, /**< \brief 8 */
    0x2d, 0x00, /**< \brief - */
    0x31, 0x00, /**< \brief 1 */
    0x30, 0x00, /**< \brief 0 */
    0x2d, 0x00, /**< \brief - */
    0x32, 0x00, /**< \brief 2 */
    0x39, 0x00, /**< \brief 9 */
};


/******************************************************************************
 * ����������Ϣ
 *****************************************************************************/
static const am_usbd_descriptor_t __g_usb_msc_descriptor[] = {
    /**\brief �豸������ */
    {
        (AM_USB_DESC_TYPE_DEVICE << 8) | (0x00),
        sizeof(__g_usb_msc_desc_dev),
        __g_usb_msc_desc_dev
    },

    /**\brief ���������������¼������� */
    {
        (AM_USB_DESC_TYPE_CONFIGURE << 8) | (0x00),
        sizeof(__g_usb_msc_desc_conf),
        __g_usb_msc_desc_conf
    },

    /**\brief �ַ�������������������id */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | (0x00),
        sizeof(__g_usb_msc_desc_str_language_id),
        __g_usb_msc_desc_str_language_id
    },

    /**\brief �ַ������������������� */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_MSC_VENDOR_STRING_INDEX,
        sizeof(__g_usb_msc_desc_str_imanufacturer),
        __g_usb_msc_desc_str_imanufacturer
    },

    /**\brief �ַ�����������������Ʒ */
    {
        (AM_USB_DESC_TYPE_STRING << 8) | __USBD_MSC_PRODUCT_STRING_INDEX,
        sizeof(__g_usb_msc_desc_str_iproduct),
        __g_usb_msc_desc_str_iproduct
    },

    /**\brief �ַ����������������豸���к� */
    {
        (AM_USB_DESC_TYPE_STRING << 8)| __USBD_MSC_DEVICE_STRING_INDEX,
        sizeof(__g_usb_msc_desc_str_iserialnumber),
        __g_usb_msc_desc_str_iserialnumber
    },
};

/******************************************************************************
 * ƽ̨��ʼ�����������ʼ�������Ѿ��豸��Ϣ
 ******************************************************************************/
extern USB_OTG_CORE_HANDLE USB_OTG_dev;
/**
 * \brief ƽ̨��ʼ��
 */
static void __usb_msc_init (void) {
    /**\brief ʹ��ʱ�� */
    am_clk_enable(CLK_USBFS);

    am_gpio_pin_cfg(PIOA_9, GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));/**< \brief VBUS */
    /**\brief ����PIOA_11 PIOA_12ΪUSB����   */
    am_gpio_pin_cfg(PIOA_11, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) |
                             GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));/**< \brief USBDM */
    am_gpio_pin_cfg(PIOA_12, GPIO_MODE(AMHW_HC32F460_GPIO_MODE_AIN) |
                             GPIO_AFIO(AMHW_HC32F460_AFIO_USBF));/**< \brief USBDP */
    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_MSC_cb,
            &USR_cb);
}


static  uint8_t __g_readme_data[]= {
    "**USB�豸��  ZLGģ��U��**\r\n"
     "1.���ж�ʹ��PC����ϵͳ�����ʹ��WIN10,�ǵ��޸�am_hwconf_xxxx_usb_msc.c�ļ���ϵͳ��������;\r\n"
     "2.���ϴ��ڣ����ļ��϶���U���У����ӡ�϶��ļ�����Ϣ;\r\n"
};


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

static const uint8_t __g_fat_root_dir[] = {

    /**\brief ���̱��zlgmcu �ļ�U�� */
     'Z', 'L', 'G', 'M', 'C', 'U', 0x20, 0x20, 0x55, 0xC5, 0xCC,
    0x08,                  /**< \brief �ļ����ԣ���ʾ���̱�� */
    0x00,                  /**< \brief ���� */
    0x00,                  /**< \brief ����ʱ�����ʱ��� */

    /**\brief �ļ�����ʱ�䣬15��48��26�� */
    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),
    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),

    /**\brief �ļ��������ڣ�2018��10��29�� */
    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),
    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),

    /**\brief ���������ڣ�2018��10��29�� */
    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),
    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),

    0x00, 0x00,            /**< \brief ��ʼ�غŸ�λ�ֽڣ�FAT12/16����Ϊ0 */

    /**\brief ����޸�ʱ�䣬15��36��47�� */
    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),
    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),

    /**\brief ����޸����ڣ�2018��11��2�� */
    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),
    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),

    0x00, 0x00,               /**< \brief ��ʼ�ص��� */
    0x00, 0x00, 0x00, 0x00,   /**< \brief �ļ����� */
    /**\brief ��Ŀ¼�µĲ����ļ� */
    /**\brief �ļ�����README.TXT�� */
    'R',  'E',   'A',  'D', 'M', 'E', ' ', ' ',  'T', 'X', 'T',
    0x01,                  /**< \brief �ļ����ԣ���ʾֻ���ļ�  */
    0x00,                  /**< \brief ���� */
    0x00,                  /**< \brief ����ʱ�����ʱ��� */

    /**\brief �ļ�����ʱ�䣬15��48��26�� */
    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),
    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_CREAT_TIME1, __USBD_MSC_FILE_CREAT_TIME2, __USBD_MSC_FILE_CREAT_TIME3),

    /**\brief �ļ���������,2018��10��29�� */
    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),
    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_CREAT_DATE1, __USBD_MSC_FILE_CREAT_DATE2, __USBD_MSC_FILE_CREAT_DATE3),

    /**\brief ���������� ,15��36��47�� */
    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),
    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),

    0x00, 0x00,            /**< \brief ��ʼ�غŸ�λ�ֽڣ�FAT12/16����Ϊ0 */

    /**\brief ����޸�ʱ��,15��36��47�� */
    (uint8_t)AM_TIME_LB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),
    (uint8_t)AM_TIME_HB(__USBD_MSC_FILE_MODIFIED_TIME1, __USBD_MSC_FILE_MODIFIED_TIME2, __USBD_MSC_FILE_MODIFIED_TIME3),

    /**\brief ����޸����ڣ�2018��11��2�� */
    (uint8_t)AM_DATE_LB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),
    (uint8_t)AM_DATE_HB(__USBD_MSC_FILE_MODIFIED_DATE1,__USBD_MSC_FILE_MODIFIED_DATE2, __USBD_MSC_FILE_MODIFIED_DATE3),

    0x02, 0x00,            /**< \brief ��ʼ�ص��֣���2��(������) */

    /**\brief �ļ����� */
    (sizeof(__g_readme_data) - 1) & 0xff, ((sizeof(__g_readme_data) - 1) >> 8) & 0xff, 0x00, 0x00,
};

/**
 * \brief ƽ̨ȥ��ʼ��
 */
static void __usb_msc_deinit (void) {
    am_clk_disable(CLK_USBFS);                 /**< \brief ����USBʱ�� */
}

/**\brief �豸��Ϣ*/
static const am_usbd_devinfo_t __g_usbd_msc_info = {
        __g_usb_msc_descriptor,                                                 /**< \brief ��������ַ */
        sizeof(__g_usb_msc_descriptor) / sizeof(__g_usb_msc_descriptor[0]),     /**< \brief ���������� */
};

/**\brief ����USB�豸��Ϣ */
static const am_hc32f460_usbd_devinfo_t  __g_hc32f460_usbd_msc_info = {
    HC32F460_USB_OTG_FS_BASE,                  /**< \brief �Ĵ�������ַ */
    INUM_USBFS_GLB,                            /**< \brief �жϺ� */
    __usb_msc_init,                            /**< \brief ƽ̨��ʼ�� */
    __usb_msc_deinit,                          /**< \brief ƽ̨ȥ��ʼ�� */
    &__g_usbd_msc_info,
};

/** \brief USB MSC�豸ʵ�� */
am_usbd_msc_t      __g_usb_msc_dev;

/** \brief USB�豸ʵ�� */
am_hc32f460_usbd_dev_t  __g_hc32f460_usbd_msc;

/**< \brief ����SCSI������� */
static uint8_t __g_sici_cmd_buff[AM_USBD_MAX_EP_DATA_CNT] = {0};

const am_usbd_msc_diskinfo_t __g_usbd_msc_disk_info = {
    __USBD_MSC_SYS_WIN7,
    0,

    AM_USBD_MSC_DISD_SIZE,
    AM_USBD_MSC_SECTOR_SIZE,
    AM_USBD_MSC_DISD_SIZE / AM_USBD_MSC_SECTOR_SIZE,
    (AM_USBD_MSC_DISD_SIZE / 256 / 1024 + 1) * 512,
    (AM_USBD_MSC_DISD_SIZE / 256 / 1024 * 2 + 1) * 512,
    (AM_USBD_MSC_DISD_SIZE / 256 / 1024 * 2 + 17) * 512,

    /**\brief ָ�����  */
    __g_sici_cmd_buff,

    /**\brief FAT��Ŀ¼ */
    __g_fat_root_dir,
    sizeof(__g_fat_root_dir),

    /**\brief README�ļ����� */
    __g_readme_data,
    sizeof(__g_readme_data),
};


/** \brief usb_mscʵ����ʼ�������usb_msc��׼������ */
am_usbd_msc_handle am_hc32f460_usb_msc_inst_init (void)
{
    return am_usbd_msc_init(&__g_usb_msc_dev,
                            &__g_usbd_msc_disk_info,
                            am_hc32f460_usbd_init(&__g_hc32f460_usbd_msc, &__g_hc32f460_usbd_msc_info));
}

/** \brief usb_msc���ʼ�� */
void am_hc32f460_usb_msc_inst_deinit (void)
{
    am_usb_msc_deinit(&__g_usb_msc_dev);
}

/**
 * @}
 */

/* end of file */
