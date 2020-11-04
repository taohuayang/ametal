/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief PCF8551�����ӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-02-25  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_PCF8551_H
#define __AM_PCF8551_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_i2c.h"

/**
 * @addtogroup am_if_pcf8551
 * @copydoc am_pcf8551.h
 * @{
 */
 
/**
 * \name PCF8551��������
 * 
 *     ������������ am_pcf8551_ioctl() ������ cmd ��������p_arg������ʵ����������
 * ����Ĳ�ͬ����ͬ��
 *
 * @{
 */

/**
 * \brief ����֡�ʣ���λHz
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ���õ�LCD֡�ʣ�
 * ��Чֵ�У�32��64��96��128��Ĭ��ֵ64
 */
#define  AM_PCF8551_FRAME_FREQ_SET     1

/**
 * \brief ��������ģʽ
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ���õ�����ģʽ��
 * ��Чֵ�У�4��ʹ��COM0-COM3
 *           3��ʹ��COM0-COM2
 *           2��ʹ��COM0-COM1
 *           1��ʹ��COM0
 */
#define  AM_PCF8551_DRIVE_MODE_SET     2

/**
 * \brief ��˸����
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ���õ���˸Ƶ��
 * ��Чֵ�У�0���ر���˸
 *           1����˸Ƶ��Ϊ0.5Hz
 *           2����˸Ƶ��Ϊ1Hz
 *           3����˸Ƶ��Ϊ2Hz
 */
#define  AM_PCF8551_BLINK_FREQ_SET     3

/**
 * \brief PCF8551 �豸��Ϣ�ṹ��
 */
typedef struct am_pcf8551_devinfo {

    /** \brief I2C 7λ �豸��ַ */
    uint8_t i2c_addr;

} am_pcf8551_devinfo_t;    
    
/**
 * \breif PCF8551 �豸�ṹ�嶨��
 */
typedef struct am_pcf8551_dev {

    /** \brief i2c�豸ʵ�� */
    am_i2c_device_t i2c_dev;    

    /** \brief �豸��Ϣ */
    const am_pcf8551_devinfo_t *dev_info;

} am_pcf8551_dev_t;

typedef am_pcf8551_dev_t *am_pcf8551_handle_t;

/**
 * \brief PCF8551 ��ʼ��
 *
 * \param[in] p_dev     : ָ��PCF8551�豸��ָ��
 * \param[in] p_devinfo : ָ��PCF8551�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��׼�����
 */
am_pcf8551_handle_t am_pcf8551_init (am_pcf8551_dev_t           *p_dev,
                                     const am_pcf8551_devinfo_t *p_devinfo,
                                     am_i2c_handle_t             handle);

/**
 * \brief PCF8551 ���ʼ��
 *
 * \param[in] handle   : PCF8551 ��ʼ����ȡ�ı�׼������
 *
 * \return ��׼�����
 */
am_err_t am_pcf8551_deinit (am_pcf8551_handle_t handle);

/**
 * \brief PCF8551 ���ƺ���
 *
 * \param[in]     handle : PCF8551 ��ʼ����ȡ�ı�׼������
 * \param[in]     cmd    : PCF8551 ����ָ��
 * \param[in,out] p_arg  : �����Ӧ�Ĳ���
 *
 * \return ��׼�����
 */
int am_pcf8551_ioctl (am_pcf8551_handle_t  handle,
                      int                  cmd,
                      void                *p_arg);

/**
 * \brief PCF8551��ʾ
 *
 * \param[in] handle   : PCF8551��׼������
 * \param[in] ram_addr : �Դ��ַ���Դ��ַ��Χ0x04-0x17
 * \param[in] p_data   : �Դ�����
 * \param[in] len      : ���ݳ���
 *
 * \return ��׼�����
 */
int am_pcf8551_display (am_pcf8551_handle_t handle,
                        uint8_t             ram_addr,
                        uint8_t            *p_data,
                        uint8_t             len);

/**
 * \brief PCF8551����ʾ
 *
 * \param[in] handle : PCF8551��׼������
 *
 * \return ��׼�����
 */
int am_pcf8551_display_on (am_pcf8551_handle_t handle);

/**
 * \brief PCF8551����ʾ
 *
 * \param[in] handle : PCF8551��׼������
 *
 * \return ��׼�����
 */
int am_pcf8551_display_off (am_pcf8551_handle_t handle);

/**
 * \brief PCF8551��λ
 *
 * \param[in] handle : PCF8551��׼������
 *
 * \return ��׼�����
 */
int am_pcf8551_software_rst (am_pcf8551_handle_t handle);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _AM_PCF8551_H */

/* end of file */    


