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
 * \brief GS200�ӿں���
 *
 * \internal
 * \par Modification History
 * - 1.00 19-12-16  fzb, first implementation.
 * \endinternal
 */


#ifndef __AM_GS200_H
#define __AM_GS200_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "am_softimer.h"
#include "am_uart_rngbuf.h"

/**
 * @addtogroup am_if_gs200
 * @copydoc am_gs200.h
 * @{
 */

#define  AM_GS200_COM_FRAME_LEN             (0x05)  /* �����   */

/**
 * \name GS200ͨ�ÿ���ָ��(֡��ʶ)
 * @{
 */
#define  AM_GS200_SET_BAUDRATE              (0x01)  /* ����ģ��ͨѶ�ӿڲ�����ָ��       */
#define  AM_GS200_SET_GESTURE_STATE         (0x02)  /* ����ģ�����ƹ���ʹ�������ָ��   */
#define  AM_GS200_SET_WORKING_CONDITION     (0x03)  /* ���ù���״ָ̬��                 */
#define  AM_GS200_SET_HOVERING_GESTURE_MODE (0x04)  /* ������ͣ����(��ʱ/����)���ָ��  */
#define  AM_GS200_SET_HOVERING_TIMING_TIME  (0x05)  /* ������ͣ���ƶ�ʱ���ʱ����     */
#define  AM_GS200_SET_HOVERING_SINGLE_TIME  (0x06)  /* ������ͣ���Ƶ��δ���ʱ��         */
/* GS200 ���ڿ���ָ�� */
#define  AM_GS200_NREAD                     (0x07)  /* ��ȡ���ջ��������ѽ��յ����ݸ��� */
#define  AM_GS200_NWRITE                    (0x08)  /* ��ȡ���ͻ���������д������ݸ��� */
#define  AM_GS200_FLUSH                     (0x09)  /* ��շ��ͻ������ͽ��ջ�����       */
#define  AM_GS200_WFLUSH                    (0x0A)  /* ��շ��ͻ�����                   */
#define  AM_GS200_RFLUSH                    (0x0B)  /* ��ս��ջ�����                   */
#define  AM_GS200_TIMEOUT                   (0x0C)  /* ���ý��ճ�ʱʱ��(��λ��ms)       */

/* \brief  GS200 ����������ѡ�� */
#define  AM_GS200_BAUDRATE_9600             (0x00)  // (Ĭ��)
#define  AM_GS200_BAUDRATE_4800             (0x01)
#define  AM_GS200_BAUDRATE_115200           (0x02)

//����ģ�����ƹ���ʹ�����������ѡ��
#define  AM_GS200_SET_MOVEUP_DISABLE        (0x01)  /* ���ý�ֹGS200����������ƶ��� */
#define  AM_GS200_SET_MOVEDOWN_DISABLE      (0x02)  /* ���ý�ֹGS200����������ƶ��� */
#define  AM_GS200_SET_MOVELEFT_DISABLE      (0x03)  /* ���ý�ֹGS200����������ƶ��� */
#define  AM_GS200_SET_MOVERIGHT_DISABLE     (0x04)  /* ���ý�ֹGS200����������ƶ��� */
#define  AM_GS200_SET_HOVER_DISABLE         (0x05)  /* ���ý�ֹGS200�����ͣ���ƶ��� */

#define  AM_GS200_SET_MOVEUP_ENABLE         (0x11)  /* ����ʹ��GS200����������ƶ��� */
#define  AM_GS200_SET_MOVEDOWN_ENABLE       (0x12)  /* ����ʹ��GS200����������ƶ��� */
#define  AM_GS200_SET_MOVELEFT_ENABLE       (0x13)  /* ����ʹ��GS200����������ƶ��� */
#define  AM_GS200_SET_MOVERIGHT_ENABLE      (0x14)  /* ����ʹ��GS200����������ƶ��� */
#define  AM_GS200_SET_HOVER_ENABLE          (0x15)  /* ����ʹ��GS200�����ͣ���ƶ��� */

//���ù���ģʽָ��
#define  AM_GS200_SET_SLEEP_MODE            (0x01)  /* ����GS200��������˯��ģʽ */
#define  AM_GS200_SET_WAKEUP                (0x02)  /* ��������GS200ģ�� */

//������ͣ�������ʹ��
#define  AM_GS200_SET_OUTPUT_TIMING_ENABLE  (0x02)  /* ����GS200��ָͣ�ʱ���ʹ�� */
#define  AM_GS200_SET_OUTPUT_SINGLE_ENABLE  (0x03)  /* ����GS200��ָͣ������ʹ�� */


/**
 * \brief GS200ʵ����Ϣ�ṹ�嶨��
 */
typedef struct am_gs200_devinfo {

    /** \brief ģ���ʼ��������        */
    uint32_t    baudrate;

    /** \brief ���ڴ��ڽ��յĻ������������С��32����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��32����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ��������ͻ�����  */
    uint8_t     *p_cmd_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t    rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t    txbuf_size;

    /** \brief ��������ͻ������Ĵ�С  */
    uint16_t    cmd_txbuf_len;

} am_gs200_devinfo_t;

/**
 * \brief GS200�豸�ṹ�嶨��
 */
typedef struct am_gs200_dev {

    /** \brief ������״̬  */
    volatile int                cmd_proc_state;

    /** \brief UARTʵ�����                    */
    am_uart_handle_t            uart_handle;

    /** \brief �������ݻ��λ�����      */
    struct am_rngbuf            rx_rngbuf;

    /** \brief �������ݻ��λ�����      */
    struct am_rngbuf            tx_rngbuf;

    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_gs200_devinfo_t *p_devinfo;

    /** \brief ���ڽ�������Ӧ��ĵȴ��ṹ��       */
    am_wait_t                   ack_wait;

    /** \brief ���ڽ������ݵĵȴ��ṹ��   */
    am_wait_t                   rx_wait;

    /** \brief ���ճ�ʱʱ��                */
    volatile uint32_t           timeout_ms;

    /** \brief �����Ӧ���ջ�����  */
    uint8_t                    *p_cmd_rxbuf;

    /** \brief �����Ӧ���ջ������ĳ���  */
    volatile int                cmd_rxbuf_len;

    /** \brief �����Ӧ�Ѿ����յĳ���  */
    volatile int                cmd_rx_len;

    /** \brief �����ʱ�������ж�һ֡�Ƿ���ճ�ʱ */
    am_softimer_t               timer;
} am_gs200_dev_t;


/** \brief ����GS200�������  */
typedef struct am_gs200_dev *am_gs200_handle_t;

/**
 * \brief GS200 ��ʼ������
 *
 * ʹ��GS200ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����GS200��handle��
 *
 * \param[in] p_dev      : ָ��GS200�豸��ָ��
 * \param[in] p_devinfo  : ָ��GS200�豸��Ϣ��ָ��
 * \param[in] uart_handle : UART��׼������������ʹ�ø�UART�����GS200ͨ�ţ�
 *
 * \return ����GS200��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_gs200_handle_t am_gs200_init (am_gs200_dev_t             *p_dev,
                                 const am_gs200_devinfo_t   *p_devinfo,
                                 am_uart_handle_t           uart_handle);

/**
 * \brief GS200 ���ƺ���
 *
 * \param[in] handle    : GS200ʵ�����
 * \param[in] cmd       : ����ָ����磺#AM_GS200_SET_BAUDRATE
 * \param[in,out] p_arg : �����Ӧ�Ĳ��������磺 115200
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_EIO     : ִ�д���
 * \retval -AM_ENOTSUP : ָ�֧��
 *
 * \note ����
 */
int am_gs200_ioctl(am_gs200_handle_t    handle,
                   int                  cmd,
                   void                 *p_arg);

/**
 * \brief ��������
 *
 * \param[in] handle : GS200ʵ�����
 * \param[in] p_buf  : �����͵�����
 * \param[in] len    : ���ݳ���
 *
 * \return �Ǹ�����ʵ�ʷ��͵��ֽ���������������ʧ��
 */
int am_gs200_send (am_gs200_handle_t    handle,
                   const uint8_t        *p_buf,
                   int                  len);


/**
 * \brief ��������
 *
 * \param[in] handle : GS200ʵ�����
 * \param[in] p_buf  : �������ݵĻ�����
 * \param[out] len   : �������ݳ���
 *
 * \return �Ǹ�����ʵ�ʽ��յ��ֽ���������������ʧ��
 */
int am_gs200_recv (am_gs200_handle_t    handle,
                   uint8_t              *p_buf,
                   int                  len);

#ifdef __cplusplus
}
#endif

#endif


