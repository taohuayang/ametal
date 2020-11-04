#ifndef __AM_ZSN603_H
#define __AM_ZSN603_H

#include "ametal.h"
#include "am_i2c.h"
#include "zsn603.h"
#include "am_gpio.h"
#include "am_uart_rngbuf.h"

typedef struct am_zsn603_dev_info{
    int8_t   rst_pin;           /** \brief ��λ����    ���û�����Ҫʹ�ô�����   ��-1����*/
    int8_t   mode_det_pin;     /** \brief ģʽѡ������    ���û�����Ҫʹ�ô�����   ��-1����  */
    uint8_t  local_address;     /** \brief ��ʼ��local address  */
    /* \brief ��IICģʽ��  �˳�ԱΪ�ж����ź�
     *        ��UARTģʽ��  �˳�ԱΪ�����ʱ�ʶ
     */
    uint8_t other_para;

}am_zsn603_dev_info_t;

/**
 * \brief ZSN600x �豸��ʼ������(UARTͨ��ģʽ)
 *
 * \param[in]  p_dev           : ZSN603�豸
 * \param[in]  p_dev_info      : ZSN603�豸����
 * \param[in]  p_arg           : ���亯��ָ�����
 *
 * \retval ���� : ��Ӧ������
 * \retval  0 : ִ�гɹ�
 */
zsn603_handle_t am_zsn603_uart_init(zsn603_dev_t                *p_dev,
                                    const am_zsn603_dev_info_t  *p_dev_info,
                                    void                        *p_arg);


/**
 * \brief ZSN600x �豸��ʼ������(I2Cͨ��ģʽ)
 *
 * \param[in]  p_dev           : ZSN603�豸
 * \param[in]  p_dev_info      : ZSN603�豸����
 * \param[in]  p_arg           : ���亯��ָ�����
 *
 * \retval ���� : ��Ӧ������
 * \retval  0 : ִ�гɹ�
 */
zsn603_handle_t am_zsn603_i2c_init(zsn603_dev_t                *p_dev,
                                   const am_zsn603_dev_info_t  *p_dev_info,
                                   void                        *p_arg);
/**
 * \brief ���ÿ���ZSN603�Ĵ��ڵĲ�����  �˺����������ò�����ָ��֮����������������
 *
 * \param[in]  p_dev           : ZSN603�豸
 * \param[in]  baud_flag       : �����ʱ�ʶ  ��ѡ����Ϊ
 *                        ZSN603_BAUD_172800     ZSN603_BAUD_115200
 *                        ZSN603_BAUD_57600      ZSN603_BAUD_38400
 *                        ZSN603_BAUD_28800      ZSN603_BAUD_19200
 *                        ZSN603_BAUD_230400     ZSN603_BAUD_9600
 * \retval ���� : ��Ӧ������
 * \retval  0 : ִ�гɹ�
 */
int am_zsn603_set_uart_baud(zsn603_dev_t  *p_dev,
                            uint8_t        baud_flag);
#endif


