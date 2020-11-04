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
 * \brief ���״����� AS7262 (UARTģʽ) ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_AS7262_UART_H
#define __AM_SENSOR_AS7262_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_sensor_as7262.h"
#include "am_uart_rngbuf.h"

/* \brief  AS7262 �����ʶ */
#define AM_AS7262_RECEIVE_INVALID       0x01    /* ����������Ч */
#define AM_AS7262_PARAMETER_INVALID     0x02    /* ���ز���ʧ�� */

/**
 * \brief ������ AS7262 (UARTģʽ) �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_as7262_uart_devinfo {

    const am_sensor_as7262_devinfo_t       *p_devinfo;

    am_uart_handle_t (*pfn_uart_handle_get) (void);         /**< \brief UART�����ȡ���� */

    void (*pfn_uart_deinit) (am_uart_handle_t uart_handle); /**< \brief UART���ʼ������ */

    uint32_t                                baudrate;       /**< \brief UART������ */

    uint8_t                                *p_uart_rxbuf;   /**< \brief ���ڴ��ڽ��յĻ������������С��32����     */

    uint8_t                                *p_uart_txbuf;   /**< \brief ���ڴ��ڷ��͵Ļ������������С��32����     */

    uint16_t                                rxbuf_size;     /**< \brief ���ڴ��ڽ��յĻ�������С */

    uint16_t                                txbuf_size;     /**< \brief ���ڴ��ڷ��͵Ļ�������С */

} am_sensor_as7262_uart_devinfo_t;

/**
 * \breif ������ AS7262 (UARTģʽ) �豸�ṹ�嶨��
 */
typedef struct am_sensor_as7262_uart_dev {
    am_sensor_as7262_dev_t                  isa;                    /**< \breif ��������׼���� */

    volatile int                            cmd_proc_state;         /**< \brief ������״̬  */

    am_uart_handle_t                        uart_handle;            /**< \brief UART���*/

    struct am_rngbuf                        rx_rngbuf;              /**< \brief �������ݻ��λ�����      */

    struct am_rngbuf                        tx_rngbuf;              /**< \brief �������ݻ��λ�����      */

    const am_sensor_as7262_uart_devinfo_t  *sensor_uart_dev_info;   /**< \brief �豸��Ϣ */

    am_wait_t                               ack_wait;               /**< \brief ���ڽ�������Ӧ��ĵȴ��ṹ��       */

    am_wait_t                               rx_wait;                /**< \brief ���ڽ������ݵĵȴ��ṹ��   */

    volatile uint32_t                       timeout_ms;             /**< \brief ���ճ�ʱʱ��                */

    uint8_t                                *p_cmd_rxbuf;            /**< \brief �����Ӧ���ջ�����  */

    volatile int                            cmd_rxbuf_len;          /**< \brief �����Ӧ���ջ������ĳ���  */

    volatile int                            cmd_rx_len;             /**< \brief �����Ӧ�Ѿ����յĳ���  */

    am_softimer_t                           timer;                  /**< \brief �����ʱ�������ж�һ֡�Ƿ������� */
} am_sensor_as7262_uart_dev_t;

/**
 * \brief ������ AS7262 (UARTģʽ) ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���AS7262(UARTģʽ)�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���AS7262(UARTģʽ)�豸��Ϣ��ָ��
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_as7262_uart_init (
        am_sensor_as7262_uart_dev_t             *p_dev,
        const am_sensor_as7262_uart_devinfo_t   *p_devinfo);

/**
 * \brief ������ AS7262 (UARTģʽ) ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_as7262_uart_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_as7262_uart_deinit (am_sensor_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_AS7262_UART_H */

/* end of file */

