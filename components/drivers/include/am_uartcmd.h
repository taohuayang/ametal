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
 * \brief 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-11-12  win, first implementation.
 * \endinternal
 */
 
#ifndef __AM_UARTCMD_H
#define __AM_UARTCMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_list.h"
#include "am_common.h"
#include "am_uartcmd_flash.h"

struct uartcmd_cmd_mifare_var;

/**
 * \brief ��֡��ʽ�ṹ��
 */
struct am_uartcmd_frame {
    uint8_t   local_addr;   /**< \brief ������ַ��ͬI2C */
    uint8_t   slot_index;   /**< \brief IC����������� */
    uint8_t   smc_seq;      /**< \brief SMC���к� */
    uint8_t   cmd_class;    /**< \brief �������� */
};

/**
 * \brief UARTCMD �豸��Ϣ�ṹ��
 */
typedef struct am_uartcmd_devinfo {
    uint32_t  int_pin;         /**< \brief �ж����ź� */
//    uint32_t  sbr_pin;         /**< \brief SBR���ź�  */
//    uint32_t  dbr_pin;         /**< \brief DBR���ź�  */
    uint32_t  rxd_pin;        /**< \brief ADR1���ź� */
    uint32_t  txd_pin;        /**< \brief ADR0���ź� */
//    uint32_t  sadr_pin;        /**< \brief SADR���ź� */
//    uint32_t  restore1;        /**< \brief �ظ��������ÿ�������1 */
//    uint32_t  restore2;        /**< \brief �ظ��������ÿ�������2 */                         
    uint32_t  led_num;         /**< \brief LED���ź�  */

    uint32_t  frame_max;       /**< \brief ֡����󳤶� */
    void     *p_frame_buf;     /**< \brief ���֡�Ļ��������û����룩 */

    /** \brief �����FLASH�еĹ̼�������Ϣ�����ڻ�ԭ�������� */
    const uartcmd_flash_devinfo_t *p_flash_devinfo;

    /** \brief ����û��޸ĺ����� */
    const uartcmd_flash_devinfo_t *p_flash_usr_devinfo;

    void     *p_iap_buf;       /**< \brief ģ���ڲ�IAP����ʹ�õĻ���������СΪ512B */
    uint32_t  iap_buf_size;    /**< \brief ģ���ڲ�IAP������������С */

    /** \brief �˳��Զ����ģʽ���������Ϣ���ȵ�����ֵ������ܳ�����ֵ */
    uint32_t  info_len_limit;

} am_uartcmd_devinfo_t;

/**
 * \brief UARTCMD �豸�ṹ��
 */
typedef struct am_uartcmd_dev {
    
    /** \brief UARTCMD �豸��Ϣ�ṹ�� */
    const am_uartcmd_devinfo_t *p_devinfo;
    
    uint8_t               status;           /**< \brief ��ǰUARTCMD ����״̬ */
    uint8_t               frame_type;       /**< \brief ������ǰ֡������ */
    uint8_t               antenna;          /**< \brief ��������ģʽ */
    uint8_t               comm_mode;        /**< \brief ��ǰͨѶģʽ */
    uint8_t               work_mode;        /**< \brief ����ģʽ */
    int                   result;           /**< \brief ����ִ�н�� */
    am_bool_t             wait_send;        /**< \brief �Զ���⵽�����ݣ��ȴ��û���ȡ */
    am_bool_t             update_addr;      /**< \breif �Ƿ���µ�ַ */
    am_bool_t             update_speed;     /**< \brief �Ƿ�������� */
   
    uint32_t              rx_count;         /**< \brief ���ռ��� */
    uint32_t              tx_count;         /**< \brief ���ͼ��� */
    uint32_t              temp_count;       /**< \brief ������Ϸ��ͼ��� */

    struct am_list_head   frame_head;       /**< \brief ֡���͵�ͷ��� */
    struct am_list_head   cmd_head;         /**< \brief �������͵�ͷ��� */
    struct am_list_head   serial_head;      /**< \brief �����豸��ͷ��� */

    struct uartcmd_cmd_mifare_var *p_var;
    struct am_uartcmd_frame        frame;

} am_uartcmd_dev_t;

/** \brief ����������������� */
typedef am_uartcmd_dev_t *am_uartcmd_handle_t;

/**
 * \brief UARTCMD ��ʼ������
 *
 * \param[in] p_dev      : UARTCMD �豸�ṹ��
 * \param[in] p_devinfo  : UARTCMD �豸��Ϣ�ṹ�� 
 * \param[in] comm_mode  : ͨ��ģʽ
 * \param[in] work_mode  : ����ģʽ
 * \param[in] frame_type : ֡����
 *
 * \return UARTCMD�����������ΪNULL�����ʼ��ʧ��
 */
am_uartcmd_handle_t am_uartcmd_init (am_uartcmd_dev_t           *p_dev,
                                     const am_uartcmd_devinfo_t *p_devinfo,
                                     uint8_t                     comm_mode,
                                     uint8_t                     work_mode,
                                     uint8_t                     frame_type);
                                     
/**
 * \brief ��UARTCMD �������ж�����
 * 
 * \param[in] handle   : UARTCMD ������
 * \param[in] p_rx_buf : ���������ݴ�ŵĻ�����
 * \param[in] nbytes   : �������ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������  
 */
int am_uartcmd_buf_read (am_uartcmd_handle_t handle, void *p_rx_buf, uint32_t nbytes);

/**
 * \brief ��UARTCMD ��������д����
 * 
 * \param[in] handle   : UARTCMD ������
 * \param[in] p_tx_buf : д������ݴ�ŵĻ�����
 * \param[in] nbytes   : д����ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������  
 */
int am_uartcmd_buf_write (am_uartcmd_handle_t handle, void *p_tx_buf, uint32_t nbytes);

/**
 * \brief ֪ͨ UARTCMD ģ��������ȫ��д�뻺����
 *
 * \param[in] handle : UARTCMD������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_uartcmd_recv_finished (am_uartcmd_handle_t handle);

/**
 * \brief UARTCMD ִ�к���
 *        UARTCMD ģ����߼��ɸú���ʵ��
 *
 * \param[in] handle : UARTCMD ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : �������� 
 */
int am_uartcmd_execute (am_uartcmd_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_UARTCMD_H */

/* end of file */
