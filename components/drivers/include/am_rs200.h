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
 * \brief RS200�ӿں���
 *
 * \internal
 * \par Modification History
 * - 1.00 19-12-12  RZ, first implementation.
 * \endinternal
 */

#ifndef __AM_RS200_H
#define __AM_RS200_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "am_uart_rngbuf.h"

/**
 * @addtogroup am_if_rs200
 * @copydoc am_rs200.h
 * @{
 */

/**
 * \name RS200��������
 * 
 *     ������������ am_rs200_ioctl() ������ cmd ��������p_arg������ʵ����������
 * ����Ĳ�ͬ����ͬ��
 *
 * @{
 */

/**
 * \brief ��ȡRS200�̼��汾
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ�̼��汾
 *
 */
#define  AM_RS200_VERSION_GET                      1

/**
 * \brief ��ȡ����״̬
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ����״̬
 *
 */
#define  AM_RS200_RAIN_STA_GET                     2

/**
 * \brief ��ȡϵͳ״̬
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾϵͳ״̬
 *
 */
#define  AM_RS200_SYS_STA_GET                      3

/**
 * \brief ��ȡ��ѧϵͳУ׼ֵ
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ��ѧϵͳУ׼ֵ
 *
 */
#define  AM_RS200_OPTICAL_SYS_VALUE_GET            4

/**
 * \brief ��������״̬���Ƶ��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ����״̬���Ƶ��
 *
 */
#define  AM_RS200_RAIN_STA_OUT_FRE_SET             5

/**
 * \brief ��ȡ����״̬���Ƶ��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ����״̬���Ƶ��
 *
 */
#define  AM_RS200_RAIN_STA_OUT_FRE_GET             6

/**
 * \brief ����������С�����ֵV1
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ������С�����ֵV1
 *
 */
#define  AM_RS200_THRESHOLD_V1_SET                 7

/**
 * \brief ��ȡ������С�����ֵV1
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ������С�����ֵV1
 *
 */
#define  AM_RS200_THRESHOLD_V1_GET                 8

/**
 * \brief ����С�����������ֵV2
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾС�����������ֵV2
 *
 */
#define  AM_RS200_THRESHOLD_V2_SET                 9

/**
 * \brief ��ȡС�����������ֵV2
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾС�����������ֵV2
 *
 */
#define  AM_RS200_THRESHOLD_V2_GET                 10

/**
 * \brief ����������������ֵV3
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾС�����������ֵV2
 *
 */
#define  AM_RS200_THRESHOLD_V3_SET                 11

/**
 * \brief ��ȡ������������ֵV3
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾС�����������ֵV2
 *
 */
#define  AM_RS200_THRESHOLD_V3_GET                 12

/**
 * \brief ����������С�����ֵS1
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ������С�����ֵS1
 *
 */
#define  AM_RS200_THRESHOLD_S1_SET                 13

/**
 * \brief ��ȡ������С�����ֵS1
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ������С�����ֵS1
 *
 */
#define  AM_RS200_THRESHOLD_S1_GET                 14

/**
 * \brief ����С�����������ֵS2
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾС�����������ֵS2
 *
 */
#define  AM_RS200_THRESHOLD_S2_SET                 15

/**
 * \brief ��ȡС�����������ֵS2
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾС�����������ֵS2
 *
 */
#define  AM_RS200_THRESHOLD_S2_GET                 16

/**
 * \brief ����������������ֵS3
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ������������ֵS3
 *
 */
#define  AM_RS200_THRESHOLD_S3_SET                 17

/**
 * \brief ��ȡ������������ֵS3
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ������������ֵS3
 *
 */
#define  AM_RS200_THRESHOLD_S3_GET                 18

/**
 * \brief ����10���ж�Ϊ�������ֵN1
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ10���ж�Ϊ�������ֵN1
 *
 */
#define  AM_RS200_THRESHOLD_N1_SET                 19

/**
 * \brief ��ȡ10���ж�Ϊ�������ֵN1
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ10���ж�Ϊ�������ֵN1
 *
 */
#define  AM_RS200_THRESHOLD_N1_GET                 20

/**
 * \brief ����10���ж�Ϊ�������ֵN2
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ10���ж�Ϊ�������ֵN2
 *
 */
#define  AM_RS200_THRESHOLD_N2_SET                 21

/**
 * \brief ��ȡ10���ж�Ϊ�������ֵN2
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ10���ж�Ϊ�������ֵN2
 *
 */
#define  AM_RS200_THRESHOLD_N2_GET                 22

/**
 * \brief ����10���ж�Ϊ�������ֵN3
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ���ͣ���ֵ��ʾ10���ж�Ϊ�������ֵN3
 *
 */
#define  AM_RS200_THRESHOLD_N3_SET                 23

/**
 * \brief ��ȡ10���ж�Ϊ�������ֵN3
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ10���ж�Ϊ�������ֵN3
 *
 */
#define  AM_RS200_THRESHOLD_N3_GET                 24

/**
 * \brief ���û������ģʽ
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ����
 * 0���˳��������ģʽ��1�����뻷�����ģʽ
 *
 */
#define  AM_RS200_OPTICAL_TEST_MODE_SET            25

/**
 * \brief ��ȡ������ֵ
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾ������ֵ
 *
 */
#define  AM_RS200_OPTICAL_TEST_VALUE_GET           26

/**
 * \brief ��ȡоƬ�¶�
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ָ�����ͣ���ֵ��ʾоƬ�¶�
 *
 */
#define  AM_RS200_TEMP_GET                         27

/**
 * \brief ���ù�ѧ˯��״̬
 *
 * ��ʱ�� p_arg ����������Ϊ  uint16_t ����
 * 0���˳���ѧ�ߣ�1�������ѧ˯��
 *
 */
#define  AM_RS200_LIGHT_SLEEP_MODE_SET             28

/**
 * \brief RS200ʵ����Ϣ�ṹ�嶨��
 */
typedef struct am_rs200_devinfo {

    /** \brief ���ڴ��ڽ��յĻ������������С��32����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��32����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t     rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t     txbuf_size;

    /** \brief �������ô��ڽ��ճ�ʱ */
    uint32_t     timeout_ms;
} am_rs200_devinfo_t;

/**
 * \brief RS200�豸�ṹ�嶨��
 */
typedef struct am_rs200_dev {

    /** \brief UART���λ������豸 */
    am_uart_rngbuf_dev_t      rngbuf_dev;
    
    /** \brief UART���λ�����ʵ����� */
    am_uart_rngbuf_handle_t   rngbuf_handle;
    
    /** \brief UARTʵ����� */
    am_uart_handle_t          uart_handle;

    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_rs200_devinfo_t *p_devinfo;

} am_rs200_dev_t;

/** \brief ����RS200�������  */
typedef struct am_rs200_dev *am_rs200_handle_t;

/**
 * \brief RS200��ʼ������
 *
 * ʹ��RS200ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����RS200��handle��
 *
 * \param[in] p_dev      : ָ��RS200�豸��ָ��
 * \param[in] p_devinfo  : ָ��RS200�豸��Ϣ��ָ��
 * \param[in] handle     : UART��׼������������ʹ�ø�UART�����RS200ͨ�ţ�
 *
 * \return ����RS200��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_rs200_handle_t am_rs200_init (am_rs200_dev_t           *p_dev,
                                 const am_rs200_devinfo_t *p_devinfo,
                                 am_uart_handle_t          handle);

/**
 * \brief RS200���ƺ���
 *
 * \param[in] handle    : RS200ʵ�����
 * \param[in] cmd       : ����ָ����磺#AM_RS200_RAIN_STA_OUT_FRE_SET
 * \param[in,out] p_arg : �����Ӧ�Ĳ��������磺2
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_EIO     : ִ�д���
 * \retval -AM_ENOTSUP : ָ�֧��
 *
 * \note ����
 */
int am_rs200_ioctl (am_rs200_handle_t  handle,
                    int                cmd,
                    void              *p_arg);

/**
 * \brief ��ȡRS200����״̬
 *
 * \param[in] handle : RS200ʵ�����
 * \param[in] p_data : ״̬��ŵ�ַ
 *
 * \retval AM_OK     : ����ָ��ִ�гɹ�
 * \retval ����      : ִ�д���
 *
 */
int am_rs200_rain_sta_get (am_rs200_handle_t handle, uint16_t *p_data);

/**
 * \brief ��ȡRS200���յ�����
 *
 * \param[in] handle : RS200ʵ�����
 * \param[in] p_buf  : ���ݴ�ŵ�ַ 
 * \param[in] len    : ���յ����ݳ���               
 *
 * \retval ���ճɹ��ֽ���
 *
 */
int am_rs200_recv (am_rs200_handle_t  handle,
                   uint8_t           *p_buf,
                   uint32_t           len);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_RS200_H */

/* end of file */
