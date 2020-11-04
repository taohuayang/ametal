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
 * \brief ��ͨ��˾��MB85ϵ��MB85RSXXоƬ���� 
 * 
 * ��֪����оƬ�� 
 *   - MB85RS64
 * 
 * \internal
 * \par Modification history
 * - 1.00 19-12-09  RZ, first implementation.
 * \endinternal
 */
 
#ifndef __AM_MB85RSXX_H
#define __AM_MB85RSXX_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "ametal.h"
#include "am_types.h"
#include "am_gpio.h"
#include "am_spi.h"
#include "am_nvram.h"

/**
 * \addtogroup am_if_mb85rsxx
 * \copydoc am_mb85rsxx.h
 * @{
 */


/**
 * \brief MB85RSXX ʵ����Ϣ
 */
typedef struct am_mb85rsxx_devinfo {
 
    uint16_t          spi_mode;      /**< \brief ����ʹ�õ�SPIģʽ */
    int               spi_cs_pin;    /**< \brief SPIƬѡ����       */
    uint32_t          spi_speed;     /**< \brief ʹ�õ�SPI����     */
} am_mb85rsxx_devinfo_t;
     
/**
 * \brief MB85RSXX ʵ��
 */
typedef struct am_mb85rsxx_dev {

    /**< \brief SPI�豸              */
    am_spi_device_t              spi_dev;

    /**< \brief mb85rsxx�豸�ṩ�� NVRAM ��׼���� */
    am_nvram_dev_t               *p_serv;

    /**< \brief ʵ����Ϣ             */
    const am_mb85rsxx_devinfo_t  *p_devinfo;

} am_mb85rsxx_dev_t;

/** \brief ���� MB85RSXX ��ʵ��������� */
typedef struct am_mb85rsxx_dev *am_mb85rsxx_handle_t;


/** 
 * \brief ��ʼ�� MB85RSXX����ȡ���� MB85RSXX �� handle
 * 
 * \param[in] p_dev      : ָ�� MB85RSXX ʵ����ָ��
 * \param[in] p_devinfo  : ָ�� MB85RSXX ʵ����Ϣ��ָ��
 * \param[in] handle     : SPI��׼����handle,ʹ�ø� handle �� MB85RSXX ����ͨ��
 *
 * \return MB85RSXX ��������������ʼ��ʧ�ܣ��򷵻�ֵΪNULL
 */
am_mb85rsxx_handle_t am_mb85rsxx_init(am_mb85rsxx_dev_t            *p_dev,
                                      const am_mb85rsxx_devinfo_t  *p_devinfo,
                                      am_spi_handle_t               spi_handle);

/**
 * \brief ��ȡ����
 *
 * \param[in] handle : MB85RSXX �������
 * \param[in] addr   : ��ȡ���ݵ��׵�ַ
 * \param[in] p_buf  : ��ȡ���ݴ�ŵĻ�����
 * \param[in] len    : ���ݶ�ȡ�ĳ���
 *
 * \retval  AM_OK     : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡ����ʧ��, ��������
 * \retval -AM_EIO    : ��ȡ����ʧ��, SPIͨ�ų���
 */
int am_mb85rsxx_read(am_mb85rsxx_handle_t  handle,
                     uint32_t              addr,
                     uint8_t              *p_buf,
                     uint32_t              len);


/** 
 * \brief д������
 *
 * \param[in] handle : MB85RSXX �������
 * \param[in] addr   : д�����ݵ��׵�ַ
 * \param[in] p_buf  : д�����ݴ�ŵĻ�����
 * \param[in] len    : ���ݶ�ȡ�ĳ���
 *
 * \retval  AM_OK     : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡ����ʧ��, ��������
 * \retval -AM_EIO    : ��ȡ����ʧ��, SPIͨ�ų���
 */
int am_mb85rsxx_write(am_mb85rsxx_handle_t  handle,
                      uint32_t              addr,
                      uint8_t              *p_buf,
                      uint32_t              len);

                            
/** 
 * \brief ��ȡMB85RSXX״̬�Ĵ�����ֵ
 * 
 * \param[in]  handle : MB85RSXX �������
 * \param[out] p_stat : ��ȡ����״̬�Ĵ�����ֵ
 *
 * \retval  AM_OK     : ��ȡ״̬�Ĵ����ɹ�
 * \retval -AM_EINVAL : ��ȡʧ��, ��������
 * \retval -AM_EIO    : ��ȡʧ��, SPIͨ�ų���
 */
int am_mb85rsxx_status_read(am_mb85rsxx_handle_t  handle,
                            uint8_t              *p_stat);

/** 
 * \brief ����MB85RSXX״̬�Ĵ�����ֵ
 * 
 * \param[in] handle : MB85RSXX �������
 * \param[in] val    : д��״̬�Ĵ�����ֵ
 *
 * \retval  AM_OK     : д��״̬�Ĵ����ɹ�
 * \retval -AM_EINVAL : д��ʧ��, ��������
 * \retval -AM_EIO    : д��ʧ��, SPIͨ�ų���
 *
 */
int am_mb85rsxx_status_write(am_mb85rsxx_handle_t  handle,
                             uint8_t               val);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __AM_MB85RSXX_H */

/* end of file */
