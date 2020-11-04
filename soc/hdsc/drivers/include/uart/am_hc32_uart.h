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
 * \brief UART����������UART��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-19  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_UART_H
#define __AM_HC32_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "hw/amhw_hc32_uart.h"

/**
 * \addtogroup am_hc32_if_uart
 * \copydoc am_hc32_uart.h
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
#define AM_HC32_UART_ERRCODE_UART_OTHER_INT  3

/** @} */

/**
 * \brief �����豸��Ϣ�ṹ�壬���豸��Ϣ���ڴ��ڳ�ʼ��
 */
typedef struct am_hc32_uart_devinfo {

    uint32_t    uart_reg_base;  /**< \brief ָ��UART�Ĵ������ָ�� */
    uint8_t     inum;           /**< \brief �����жϺ� */
    int         clk_num;        /**<  \brief ʱ��ID */
    uint32_t    cfg_flags;      /**< \brief �������ñ�־ */
    am_bool_t   asyn_hd;        /**< \brief �첽��˫��ģʽ�����ߣ���־ */
    uint32_t    baud_rate;      /**< \brief ��ʼ�������� */

    /**
     * \brief ָ��ʹ�ܵ��ж�,AMHW_HC32_UART_INT_*��ֵ����AMHW_HC32_UART_INT_*��
     */
    uint32_t    other_int_enable;

    /** \brief RS485 ������ƺ���, AM_TRUE: ����ģʽ�� AM_FALSE: ����ģʽ */
    void (*pfn_rs485_dir) (am_bool_t is_txmode);

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */

} am_hc32_uart_devinfo_t;

/**
 * \brief �����豸�ṹ�嶨��
 */
typedef struct am_hc32_uart_dev {

    am_uart_serv_t  uart_serv; /**< \brief ��׼UART���� */

    /** \brief ָ���û�ע���txchar_get���� */
    int (*pfn_txchar_get)(void *, char *);

    /** \brief ָ���û�ע���rxchar_put���� */
    int (*pfn_rxchar_put)(void *, char);

    /** \brief ָ���û�ע��Ĵ���ص����� */
    int (*pfn_err)(void *, int, void *, int);

    void     *txget_arg;                    /**< \brief txchar_get�������� */
    void     *rxput_arg;                    /**< \brief rxchar_put�������� */
    void     *err_arg;                      /**< \brief ����ص������û����� */

    uint8_t   channel_mode;                 /**< \brief ����ģʽ �ж�/��ѯ */
    uint32_t  clk_rate;                     /**< \brief ����ģʽʱ��Ƶ�� */
    uint32_t  baud_rate;                    /**< \brief ���ڲ����� */
    uint16_t  options;                      /**< \brief Ӳ������ѡ�� */

    uint32_t  other_int_enable;             /**< \brief ָ��ʹ�ܵ������ж� */

    am_bool_t rs485_en;                     /**< \brief �Ƿ�ʹ���� 485 ģʽ */

    const am_hc32_uart_devinfo_t *p_devinfo; /**< \brief ָ���豸��Ϣ������ָ�� */

} am_hc32_uart_dev_t;

/**
 * \brief ��ʼ��UART������UART��׼����������
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 * \param[in] p_devinfo : ָ�򴮿��豸��Ϣ������ָ��
 *
 * \return UART��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_uart_handle_t am_hc32_uart_init(am_hc32_uart_dev_t           *p_dev,
                                     const am_hc32_uart_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��UARTʱ�����ʼ��UART���ͷ������Դ
 *
 * \param[in] p_dev : ָ�򴮿��豸��ָ��
 */
void am_hc32_uart_deinit (am_hc32_uart_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_UART_H */

/* end of file */
