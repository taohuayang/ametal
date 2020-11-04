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
 * \brief USART����������USART��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG237_USART_H
#define __AM_ZLG237_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "hw/amhw_zlg237_usart.h"

/**
 * \addtogroup am_zlg237_if_usart
 * \copydoc am_zlg237_usart.h
 * @{
 */

/**
 * \name �������ţ�����ص�������code���������������ݸ��û���ָ����ǰ�Ĵ�������
 *
 *  ����ص������Ĳ���ԭ�ͣ�\n
 *  int uart_err(void *p_arg, int code, void *p_data, int size);
 *  p_arg���û�ע����û�������p_data��size��ͬ�Ĵ������Ͱ�������Ϣ������ͬ��
 *  ����ʹ��am_uart_callback_set() �������ô��ڴ���ص�������
 * @{
 */

/**
 * \brief �û�ָ���������жϷ���,p_data������Ϊuint32_t��ֵΪ���ڵ��ж�״̬����
 *        ���û��жϾ�����ж�Դ��sizeΪ1��
 */
#define AM_ZLG237_USART_ERRCODE_USART_OTHER_INT  3

/**
 * \brief ����������ص�XON�ַ����壬Ĭ��0x11
 */
#define AM_ZLG237_USART_XON       0x11

/**
 * \brief ����������ص�XOFF�ַ����壬Ĭ��0x13
 */
#define AM_ZLG237_USART_XOFF      0x13

/** @} */

/**
 * \brief �����豸��Ϣ�ṹ�壬���豸��Ϣ���ڴ��ڳ�ʼ��
 */
typedef struct am_zlg237_usart_devinfo {

    uint32_t usart_reg_base;     /**< \brief ָ��USART�Ĵ������ָ�� */

    uint8_t  inum;              /**< \brief �����жϺ� */

    int      clk_num;           /**<  \brief ʱ��ID */

    /**
     * \brief �������ñ�־��AMHW_ZLG237_USART_DATA_*���AMHW_ZLG237_USART_PARITY_*��
     *        ��AMHW_ZLG237_USART_STOP_*�Ļ�ֵ
     *        (�磺AMHW_ZLG237_USART_DATA_8BIT|AMHW_ZLG237_USART_PARITY_NO
     *                                       |AMHW_ZLG237_USART_STOP_1BIT)
     */
    uint8_t  cfg_flags;

    uint32_t baud_rate;         /**< \brief ��ʼ�������� */

    /**
     * \brief ָ��ʹ�ܵ������ж�,AMHW_ZLG237_USART_INT_*��ֵ����AMHW_ZLG237_USART_INT_*���
     *        ��ֵ������(# AMHW_ZLG237237_USART_INT_TX_EMPTY_ENABLE),
     *                (# AMHW_ZLG237_USART_INT_RX_VAL_ENABLE)�������жϡ�
     */
    uint32_t other_int_enable;

    /** \brief RS485 ������ƺ���, AM_TRUE: ����ģʽ�� AM_FALSE: ����ģʽ */
    void (*pfn_rs485_dir) (am_bool_t is_txmode);

    void (*pfn_plfm_init)(void);    /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void);  /**< \brief ƽ̨ȥ��ʼ������ */

    uint32_t  gpio_ck[2];           /**< \brief ck ���������ض��� */

    uint32_t  gpio_cts[2];          /**< \brief cts ���������ض��� */

    uint32_t  gpio_rts[2];          /**< \brief rts ����������ض��� */

} am_zlg237_usart_devinfo_t;

/**
 * \brief �����豸�ṹ�嶨��
 */
typedef struct am_zlg237_usart_dev {

    am_uart_serv_t  uart_serv; /**< \brief ��׼USART���� */

    /** \brief ָ���û�ע���txchar_get���� */
    int (*pfn_txchar_get)(void *, char *);

    /** \brief ָ���û�ע���rxchar_put���� */
    int (*pfn_rxchar_put)(void *, char);

    /** \brief ָ���û�ע��Ĵ���ص����� */
    int (*pfn_err)(void *, int, void *, int);

    void     *txget_arg;                    /**< \brief txchar_get�������� */
    void     *rxput_arg;                    /**< \brief rxchar_put�������� */
    void     *err_arg;                      /**< \brief ����ص������û����� */

    uint8_t   flowctl_mode;                 /**< \brief ����ģʽ���ޣ������Ӳ����   */
    uint8_t   flowctl_tx_stat;              /**< \brief ���ط�����״̬�����������أ� */

    uint8_t   channel_mode;                 /**< \brief ����ģʽ �ж�/��ѯ */
    uint32_t  baud_rate;                    /**< \brief ���ڲ����� */
    uint16_t  options;                      /**< \brief Ӳ������ѡ�� */

    uint32_t  other_int_enable;             /**< \brief ָ��ʹ�ܵ������ж� */

    am_bool_t rs485_en;                     /**< \brief �Ƿ�ʹ���� 485 ģʽ */

    const am_zlg237_usart_devinfo_t *p_devinfo; /**< \brief ָ���豸��Ϣ������ָ�� */

} am_zlg237_usart_dev_t;

/**
 * \brief ��ʼ��USART������USART��׼����������
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 * \param[in] p_devinfo : ָ�򴮿��豸��Ϣ������ָ��
 *
 * \return USART��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_uart_handle_t am_zlg237_usart_init(am_zlg237_usart_dev_t              *p_dev,
                                      const am_zlg237_usart_devinfo_t    *p_devinfo);


/**
 * \brief ����ȥ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 */
void am_zlg237_usart_deinit (am_zlg237_usart_dev_t *p_dev);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG237_USART_H */

/* end of file */
