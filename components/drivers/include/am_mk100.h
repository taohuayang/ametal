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
 * \brief MK100�ײ���������
 * 
 * \internal
 * \par Modification history
 * - 1.00 19-12-20  mxy, first implementation.
 * \endinternal
 */
#ifndef __AM_MK100_H
#define __AM_MK100_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart_rngbuf.h"
#include "am_uart.h"

/**
 * \addtogroup am_mk100
 * \copydoc am_mk100.h
 * @{
 */
    
#define AM_MK100_DEFAULT_BAUDRATE                   9600          /**< \brief  Ĭ�ϲ�������9600 */
#define AM_MK100_FRAME_LEN                          5             /**< \brief  ֡������5���ֽ� */
#define AM_MK100_DIR_CW                             0x00          /**< \brief  ˳ʱ�뷽�� */
#define AM_MK100_DIR_CCW                            0x01          /**< \brief  ��ʱ�뷽�� */

#define AM_MK100_DIRECTION_UP                       0x00          /**< \brief  �� */
#define AM_MK100_DIRECTION_DOWN                     0x01          /**< \brief  �� */ 
#define AM_MK100_DIRECTION_LEFT                     0x02          /**< \brief  �� */
#define AM_MK100_DIRECTION_RIGHT                    0x03          /**< \brief  �� */

#define AM_MK100_BAUDRATE_TEST                      0x00          /**< \brief  ���ò��Բ����� */
#define AM_MK100_BAUDRATE_2400                      0x01          /**< \brief  ����2400������ */
#define AM_MK100_BAUDRATE_4800                      0x02          /**< \brief  ����4800������ */
#define AM_MK100_BAUDRATE_9600                      0x03          /**< \brief  ����9600������ */
#define AM_MK100_BAUDRATE_56000                     0x04          /**< \brief  ����56000������ */
#define AM_MK100_BAUDRATE_115200                    0x05          /**< \brief  ����115200������ */

#define AM_MK100_SET_ROTATION_FUNC                  0x00          /**< \brief  ������ת���� */
#define AM_MK100_SET_INFRARED_DETECT                0x10          /**< \brief  ������ת+������¼�⣨�����⣩*/
#define AM_MK100_SET_STATUS_DETECT                  0x20          /**< \brief  ������ת+������¼�⣨״̬��⣩ */
#define AM_MK100_SET_LEFT_RIGNH_DETECT              0x33          /**< \brief  ʹ�����ҷ����ƶ���� */
#define AM_MK100_SET_UP_DOWN_DETECT                 0x3C          /**< \brief  ʹ�����·����ƶ���� */
#define AM_MK100_SET_UP_DOWN_LEFT_RIGNH_DETECT      0x3F          /**< \brief  ʹ�����������ƶ���� */

#define AM_MK100_GET_ANGLE                          0x2F          /**< \brief  �����ж��Զ��ϱ�ģʽ�����ݣ���ʾ�ǽǶ�ֵ */
#define AM_MK100_GET_KNOB_POS                       0x2E          /**< \brief  �����ж��Զ��ϱ�ģʽ�����ݣ���ʾ�Ǵ���ťλ�� */
/**
 * \brief mk100 �豸��Ϣ
 */
typedef struct am_mk100_devinfo {
    /** \brief ���ڴ��ڽ��յĻ������������С��32����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��32����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t     rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t     txbuf_size;

} am_mk100_devinfo_t;

/**
 * \brief mk100�豸ʵ��
 */
typedef struct am_mk100_dev {
    /** \brief UART ���λ�����ʵ�����                    */
    am_uart_rngbuf_handle_t uart_rngbuf_handle;
    /** \brief UARTʵ�����                    */
    am_uart_handle_t uart_handle;
    /** \brief �������                    */
    uint8_t error_frame[AM_MK100_FRAME_LEN];
    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_mk100_devinfo_t *p_devinfo;
} am_mk100_dev_t;

/**
 * \brief mk100�豸���
 */
typedef struct am_mk100_dev *am_mk100_handle_t;
/**
 * \brief mk100��ʼ��
 *
 * \param[in] p_dev              : mk100�豸ָ��
 * \param[in] p_devinfo          : mk100�豸��Ϣָ��
 * \param[in] uart_handle        : uart���
 *
 * \return    am_mk100_handle_t  ��mk100���
 */
am_mk100_handle_t am_mk100_init (am_mk100_dev_t           *p_dev,
                                 const am_mk100_devinfo_t *p_devinfo,
                                 am_uart_handle_t          uart_handle);
/**
 * \brief ��ȡ�Ƕ�ֵ
 *
 * \param[in] handle                  : mk100���
 * \param[in] gear                    : �ȼ�
 * \return    -AM_EINVAL              : ����
 *            >=0                     : �Ƕ�ֵ
 */
int am_mk100_get_angle(am_mk100_handle_t handle, uint8_t gear);
/**
 * \brief ��ȡ����ťλ��
 *
 * \param[in] handle                  : mk100���
 * \return    -AM_EINVAL              : ����
 *            >=0                     : ����ťλ��
 */             
int am_mk100_get_knob(am_mk100_handle_t handle);
/**
 * \brief ��ȡ��ǰ�ų�ǿ����ֵ��������upper_limit��lower_limitָ����ڴ���
 *
 * \param[in] handle                  : mk100���
 * \param[in] upper_limit             : ����
 * \param[in] lower_limit             : ����
 * \return    -AM_EINVAL              : ����
 *            AM_OK                   : �ɹ�
 */                                 
int am_mk100_get_strength_threshold(am_mk100_handle_t handle, uint8_t* upper_limit, uint8_t* lower_limit);
/**
 * \brief ��ȡ��ǰ��ת����
 *
 * \param[in] handle                  : mk100���
 * \return    -AM_EINVAL              : ����
 *            >=0                     : ��ǰ��ת����
 */
int am_mk100_get_rotation_direction(am_mk100_handle_t handle);
/**
 * \brief ��ȡ��ǰ�ų�ǿ����ֵ״̬��������upper_limit_status��lower_limit_statusָ����ڴ���
 *
 * \param[in] handle                  : mk100���
 * \param[in] upper_limit_status      : 0x01 ��ʾ��ǰ��ǿ���Ѵﵽ���ޣ� 0x00 ��ʾ��ǰ��ǿ��δ�ﵽ����
 * \param[in] lower_limit_status      : 0x01 ��ʾ��ǰ��ǿ���Ѵﵽ���ޣ� 0x00 ��ʾ��ǰ��ǿ��δ�ﵽ����
 * \return    -AM_EINVAL              : ����
 *            AM_OK                   : �ɹ�
 */
int am_mk100_get_strength_threshold_status(am_mk100_handle_t handle, am_bool_t* upper_limit_status, am_bool_t* lower_limit_status);
/**
 * \brief ��ȡ���򴫸�������
 *
 * \param[in] handle                  : mk100���
 * \param[in] direction               : �����������ҷֱ�ΪAM_MK100_DIRECTION_UP��AM_MK100_DIRECTION_DOWN��AM_MK100_DIRECTION_LEFT��AM_MK100_DIRECTION_RIGHT    
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : �÷��������
 */
int am_mk100_get_direction_data(am_mk100_handle_t handle, uint8_t direction);
/**
 * \brief ��ȡ���⴫��������
 *
 * \param[in] handle                  : mk100���
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ���⴫��������
 */
int am_mk100_get_infrared_data(am_mk100_handle_t handle);
/**
 * \brief ���õ�ǰ�Ƕ�ֵ
 *
 * \param[in] handle                  : mk100���
 * \param[in] angle                   : �Ƕ�ֵ��0~360
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õĽǶ�ֵ
 */
int am_mk100_set_angle(am_mk100_handle_t handle, uint16_t angle);
/**
 * \brief ���õ�ǰ�ų�ǿ����ֵ����
 *
 * \param[in] handle                  : mk100���
 * \param[in] limit                   : ��ֵ���ޣ����ֵΪ0x07
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õ���ֵ����
 */
int am_mk100_set_strength_upper_limit(am_mk100_handle_t handle, uint8_t limit);
/**
 * \brief ���õ�ǰ�ų�ǿ����ֵ����
 *
 * \param[in] handle                  : mk100���
 * \param[in] limit                   : ��ֵ���ޣ����ֵΪ0x07
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õ���ֵ����
 */
int am_mk100_set_strength_lower_limit(am_mk100_handle_t handle, uint8_t limit);
/**
 * \brief ���õ�ǰ��ת����
 *
 * \param[in] handle                  : mk100���
 * \param[in] direction               : ����AM_MK100_DIR_CW: ˳ʱ�롢AM_MK100_DIR_CCW :��ʱ��
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õķ���
 */
int am_mk100_set_rotation_direction(am_mk100_handle_t handle, uint8_t direction);
/**
 * \brief ���򴫸�����ʼֵУ׼
 *
 * \param[in] handle                  : mk100���
 * \return    -AM_EINVAL              : ����
 *            AM_OK                   : �ɹ�
 */
int am_mk100_direction_cal(am_mk100_handle_t handle);
/**
 * \brief ���÷��򴫸�������
 *
 * \param[in] handle                  : mk100���
 * \param[in] threshold               : ���򴫸�������
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õķ��򴫸�������
 */
int am_mk100_set_direction_parameter(am_mk100_handle_t handle, uint8_t direction, uint16_t threshold);
/**
 * \brief ���ú��⴫��������
 *
 * \param[in] handle                  : mk100���
 * \param[in] data                    : ���⴫��������
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õĺ��⴫��������
 */
int am_mk100_set_infrared_parameter(am_mk100_handle_t handle, uint16_t data);
/**
 * \brief ����ϵͳ������
 *
 * \param[in] handle                  : mk100���
 * \param[in] baudrate_setting        : ������ѡ��ֻ������AM_MK100_BAUDRATE_***��Щ�궨��
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ���õĲ�����
 */
int am_mk100_set_baudrate(am_mk100_handle_t handle, uint8_t baudrate_setting);
/**
 * \brief ����ϵͳ����
 *
 * \param[in] handle                  : mk100���
 * \param[in] mode                    : ����ѡ��ֻ��������Ч�����룺
 *                                      AM_MK100_SET_ROTATION_FUNC��
 *                                      AM_MK100_SET_INFRARED_DETECT��
 *                                      AM_MK100_SET_STATUS_DETECT��
 *                                      AM_MK100_SET_LEFT_RIGNH_DETECT��
 *                                      AM_MK100_SET_UP_DOWN_DETECT��
 *                                      AM_MK100_SET_UP_DOWN_LEFT_RIGNH_DETECT
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ����
 */
int am_mk100_set_system_func(am_mk100_handle_t handle, uint8_t mode);
/**
 * \brief ����ϵͳΪ��ѯģʽ
 *
 * \param[in] handle                  : mk100���
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰģʽ
 */
int am_mk100_set_query_mode(am_mk100_handle_t handle);
/**
 * \brief ����ϵͳΪ�����ϱ�ģʽ, �����иı�ʱ�����������ɺ���Ҫ��am_mk100_get_report����ȡ���ݣ�����������ʱ����������ݶ�ȡ����
 *
 * \param[in] handle                  : mk100���
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰģʽ
 */
int am_mk100_set_report_change_mode(am_mk100_handle_t handle);
/**
 * \brief ����ϵͳΪ�����ϱ�ģʽ, �̶�Ƶ�������������ɺ���Ҫ��am_mk100_get_report����ȡ���ݣ�����������ʱ����������ݶ�ȡ����
 *
 * \param[in] handle                  : mk100���
 * \param[in] time                    : �̶����ʱ��,��λΪ ms����ΧΪ 50 - 2000
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰģʽ
 */
int am_mk100_set_report_periodically_mode(am_mk100_handle_t handle, uint16_t time);
/**
 * \brief ������ť������
 *
 * \param[in] handle                  : mk100���
 * \param[in] sensitivity             : �����ȵȼ�ѡ�ֵ�ķ�ΧΪ 2-50
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ�����ȵȼ�
 */
int am_mk100_set_knob_sensitivity(am_mk100_handle_t handle, uint8_t sensitivity);
/**
 * \brief ������ʱ���ڿ��
 *
 * \param[in] handle                  : mk100���
 * \param[in] delay_window            : ��ʱ���ڿ�ȣ���λΪ����ʱ�� 10ms��ֵ�ķ�ΧΪ 10-100���������õ�ֵΪ 50������˴�����ʱ��Ϊ 500ms
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ��ʱ���ڿ��
 */
int am_mk100_set_delay_window(am_mk100_handle_t handle, uint8_t delay_window);
/**
 * \brief ���ý���͹���ʱ��
 *
 * \param[in] handle                  : mk100���
 * \param[in] enter_low_power_time    : ����͹���ʱ�䣬��λΪ��, ֵ�ķ�ΧΪ 0-255
 * \return    -AM_EINVAL              : ����
 *            >= 0                    : ��ǰ�趨��ʱ��
 */
int am_mk100_set_enter_low_power_time(am_mk100_handle_t handle, uint8_t enter_low_power_time);
/**
 * \brief ��ȡ�Զ��ϱ�ģʽʱMK100���ص�֡
 *
 * \param[in] handle                  : mk100���
 * \param[in] p_type                  : ָ���ŷ������ݵ����ͣ��ֱ�Ϊ�Ƕ����ݻ����ťλ������
 * \param[in] p_data                  : ָ��������
 * \return    -AM_EINVAL              : ����
 *            AM_OK                   : �ɹ�
 */
int am_mk100_get_report(am_mk100_handle_t handle, uint8_t* p_type, uint8_t *p_data);
/**
 * \brief ��ӡ�������
 *
 * \param[in] handle              : mk100���
 * \return    �� 
 */
void am_mk100_display_error_recevice(am_mk100_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_MK100_H */

/* end of file */
