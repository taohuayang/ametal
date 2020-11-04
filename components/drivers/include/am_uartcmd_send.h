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
 * \brief UARTCMD�ײ���������
 * 
 * \internal
 * \par Modification history
 * - 1.01 16-08-03  sky, modified.
 * - 1.00 15-09-03  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_UARTCMD_SEND_H
#define __AM_UARTCMD_SEND_H
 
#include "am_types.h"
#include "am_uart_rngbuf.h"

/**
 * @addtogroup am_if_uartcmd
 * @copydoc am_uartcmd.h
 * @{
 */
 
/** 
 * \name UARTCMD��ͨ��ģʽ������ģʽ
 * @{
 */

#define AM_UARTCMD_MODE_AUTO_CHECK         0         /**< \brief �Զ����ģʽ  */
#define AM_UARTCMD_MODE_UART               2         /**< \brief ����ģʽ      */
#define AM_UARTCMD_MODE_MASTER       (1 << 4)        /**< \brief ����ģʽ���������ܣ� */
#define AM_UARTCMD_MODE_SLAVE        (0 << 4)        /**< \brief �ӻ�ģʽ��Ĭ�ϣ� */

/** @}*/

/**
 * \name UARTCMD�����ӷ�ʽ
 * @{
 */

#define AM_UARTCMD_CMNT_UART        0            /**< \brief UART���� */
#define AM_UARTCMD_CMNT_I2C         1            /**< \brief I2C���� */

/** @} */

 /** 
 * \name UARTCMD��֡��ʽ
 * @{
 */

#define AM_UARTCMD_FRAME_FMT_OLD  0             /**< \brief  ��֡��ʽ      */
#define AM_UARTCMD_FRAME_FMT_NEW  1             /**< \brief  ��֡��ʽ      */

 /** @} */
 
/**
 * \name ֧�ֵĲ�����
 * @{
 */

#define  AM_UARTCMD_BAUDRATE_9600      9600     /**< \brief ������ 9600   */
#define  AM_UARTCMD_BAUDRATE_19200     19200    /**< \brief ������ 19200  */
#define  AM_UARTCMD_BAUDRATE_28800     28800    /**< \brief ������ 28800  */
#define  AM_UARTCMD_BAUDRATE_38400     38400    /**< \brief ������ 38400  */
#define  AM_UARTCMD_BAUDRATE_57600     57600    /**< \brief ������ 57600  */
#define  AM_UARTCMD_BAUDRATE_115200    115200   /**< \brief ������ 115200 */
#define  AM_UARTCMD_BAUDRATE_172800    172800   /**< \brief ������ 172800 */
#define  AM_UARTCMD_BAUDRATE_230400    230400   /**< \brief ������ 230400 */

/** @}*/

/**
 * \brief UARTCMD�Զ������Ϣ�ṹ��
 */
typedef struct am_uartcmd_auto_detect_info {

    /**
     * \brief ���ģʽ�����ü�⶯�����Ƿ�����жϡ�������⡢��ɶ����� #AM_UARTCMD_MIFARE_CARD_AD_HALT
     */
    uint8_t        ad_mode;

    /**
     * \brief ��������ģʽ������������������һ��������ͬʱ���� #AM_UARTCMD_MIFARE_CARD_TX_TX1
     */
    uint8_t        tx_mode;

    /**
     * \brief ����ģʽ��������п������п� #AM_UARTCMD_MIFARE_CARD_REQ_IDLE
     */
    uint8_t        req_mode;

    /**
     * \brief ��֤ģʽ��E2��Կ��֤��ֱ����֤����֤ #AM_UARTCMD_MIFARE_CARD_AUTH_E2
     */
    uint8_t        auth_mode;           /**< \brief ��֤ģʽ */

    /**
     * \brief ��Կ���ͣ�#AM_UARTCMD_IC_KEY_TYPE_A �� #AM_UARTCMD_IC_KEY_TYPE_B
     *        ���auth_modeѡ�����AM_UARTCMD_MIFARE_CARD_AUTH_NO��
     *        ��key_type����Ϊ����ֵ
     */
    uint8_t        key_type;

    /** \brief ��Կ */
    uint8_t        key[16];

    /** \brief ��Կ���� */
    uint8_t        key_len;

    /**
     * \brief ��֤���
     *          S50�� 0��63��
     *          S70�� 0��255��
     *          PLUS CPU 2K�� 0��127��
     *          PLUS CPU 4K�� 0��255��
     */
    uint8_t        nblock;

} am_uartcmd_auto_detect_info_t;

/**
 * \brief ��׼��UARTCMD�豸����ṹ�嶨��
 */
typedef struct am_uartcmd_serv {

    void          *p_cookie;            /**< \brief �����������ڲ�ʹ�� */

    uint32_t       timeout_ms;          /**< \brief ����ȴ�ʱ��(����) */

    uint8_t        frame_seq;           /**< \brief ��¼���� */
    uint8_t        work_mode;           /**< \brief ��ǰʹ�õĹ���ģʽ(����ģʽ) */
    uint8_t        cur_addr;            /**< \brief ��ǰ����ĵ�ַ(7bit) */

    uint8_t        auto_detect;         /**< \brief �Զ����ģʽ */
    uint8_t        auto_detect_read;    /**< \brief �Զ�������־ */
    am_pfnvoid_t   pfn_callback;        /**< \brief �ص����� */
    void          *p_arg;               /**< \brief �ص������Ĳ��� */

    am_pfnvoid_t                  pfn_cmd_timeout_set;          /**< \brief ָ�ʱʱ������ */
    am_pfnvoid_t                  pfn_frame_proc;               /**< \brief ֡������ */
    am_pfnvoid_t                  pfn_auto_detect_trigger_set;  /**< \brief �Զ���ⴥ������ */
    am_uartcmd_auto_detect_info_t *p_auto_detect_info;           /**< \brief �Զ������Ϣ */

} am_uartcmd_serv_t;

/**
 * \brief UARTCMD��׼����handle����
 */
typedef am_uartcmd_serv_t *am_uartcmd_send_handle_t;

/** 
 * \brief UARTCMD������ͨ�ţ��豸����
 */
typedef struct am_uartcmd_uart_dev {

    /** \brief UARTCMD ��׼���� */
    am_uartcmd_serv_t         uartcmd_serv;

    /** \brief ���ڣ������������豸           */
    am_uart_rngbuf_dev_t     uart_ringbuf_dev;
    
    /** \brief ���ڣ�������������׼����handle */
    am_uart_rngbuf_handle_t  uart_ringbuf_handle;

    /** \brief ֡������ */
    am_pfnvoid_t   pfn_frame_proc;

} am_uartcmd_uart_dev_t;

/** 
 * \brief UARTCMD (UARTͨ��ģʽ) ��Ϣ����
 */
typedef struct am_uartcmd_uart_dev_info {

    /** \brief ���ڴ��ڽ��յĻ������������С��64����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��64����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t     rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t     txbuf_size;

    /** \brief ��UARTCMDͨ�ŵĲ�����(UARTģʽ��ʹ��) */
    uint32_t     baudrate;

    /** \brief ��ʼ��ʱʹ�õ�ģʽ #AM_UARTCMD_MODE_AUTO_CHECK */
    uint8_t      now_mode;

    /** \brief UARTCMD�Ĵӻ���ַ(7bit) */
    uint8_t      local_addr;

} am_uartcmd_uart_dev_info_t;

/**
 * \brief ��ʼ��UARTCMD��ʹ��UART��֡ͨ��ģʽ������ȡ������UARTCMD�ı�׼����handle
 *
 * ��ظ���ʵ��Ӳ��ʹ�ú���ͨ�����ӷ�ʽѡ����ʹ��UART����ʹ�øú�����ʼ��
 * �Ի��handle��������ʹ��am_uartcmd_i2c_init()�������handle��
 *
 * \param[in] p_dev        : ָ��UARTCMD�豸��ָ��
 * \param[in] uart_handle  : ��UARTCMD������UART������ʹ�ø�handle����UARTͨ��
 * \param[in] p_uart_info  : UARTͨ��ģʽ�����Ϣ
 *
 * \return ���� UARTCMD �Ĳ�������������ʼ��ʧ�ܣ��򷵻�NULL
 */
am_uartcmd_send_handle_t am_uartcmd_uart_new_init (am_uartcmd_uart_dev_t            *p_dev,
                                            am_uart_handle_t                 uart_handle,
                                            const am_uartcmd_uart_dev_info_t *p_uart_info);



/**
 * \brief ��UARTCMD�Ĳ�Ʒ���汾��Ϣ���磺��UARTCMDSP/T V1.00��
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] p_info     : ����װ�ػ�ȡ��Ϣ�Ļ���������СӦΪ 20 �ֽ�
 *
 * \retval AM_OK      : ��ȡ��Ϣ�ɹ�
 * \retval -AM_EINVAL : ��ȡ��Ϣʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡ��Ϣʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_info_get (am_uartcmd_send_handle_t handle,
                        uint8_t           *p_info);

/**
 * \brief ����IC���ӿڣ�ִ�гɹ�������IC���ӿڣ�������Ĭ��֧��TypeA��
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ic_port_config (am_uartcmd_send_handle_t handle);

/**
 * \brief �ر�IC���ӿ�
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 *
 * \retval AM_OK      : �رճɹ�
 * \retval -AM_EINVAL : �ر�ʧ�ܣ���������
 * \retval -AM_EIO    : �ر�ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ic_port_close (am_uartcmd_send_handle_t handle);
                            
/**
 * \name IC���ӿڵ�Э�飨����ģʽ��
 * @{
 */
#define  AM_UARTCMD_IC_ISOTYPE_A      0x00    /**< \brief ISO14443-3A */
#define  AM_UARTCMD_IC_ISOTYPE_B      0x04    /**< \brief ISO14443-3B */
/** @}*/

/**
 * \brief ����IC���ӿ�Э�飨����ģʽ��TypeA ���� TypeB
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] isotype    : IC���ӿڵ�Э�����ͣ�ʹ�����к� ��
 *                          - #AM_UARTCMD_IC_ISOTYPE_A
 *                          - #AM_UARTCMD_IC_ISOTYPE_B
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ic_isotype_set (am_uartcmd_send_handle_t handle,
                              uint8_t            isotype);
                             
/**
 * \name IC���ܳ�����
 * @{
 */

#define  AM_UARTCMD_IC_KEY_TYPE_A      0x60    /**< \brief ���� A  */
#define  AM_UARTCMD_IC_KEY_TYPE_B      0x61    /**< \brief ���� B  */

/** @}*/

/**
 * \brief װ��IC����Կ
 *
 * ���������Կ������ģ���ڲ���ģ���������Կ����ʧ��UARTCMDSP/Tģ�鹲�ܱ���
 * A��Կ16�顢B��Կ16�顣
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_UARTCMD_IC_KEY_TYPE_A
 *                          - #AM_UARTCMD_IC_KEY_TYPE_B
 * \param[in] key_sec    : ��Կ��������ţ����ɱ���16����Կ�����ţ�0 ~ 15
 * \param[in] p_key      : ��Կ������
 * \param[in] key_length : ��Կ�ĳ��ȣ�ֻ��Ϊ6��6�ֽ���Կ����16��16�ֽ���Կ��
 *
 * \retval AM_OK      : װ����Կ�ɹ�
 * \retval -AM_EINVAL : װ��ʧ�ܣ���������
 * \retval -AM_EIO    : װ��ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ic_key_load (am_uartcmd_send_handle_t  handle,
                           uint8_t             key_type,
                           uint8_t             key_sec,
                           uint8_t            *p_key,
                           uint8_t             key_length);

/**
 * \brief ����IC���ӿڵļĴ���ֵ
 *
 * ��������ģ���϶�д��оƬ�ڲ��ļĴ���ֵ��ͨ�����������ʵ�ֺܶ���������
 * ������ɵĹ�����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] reg_addr   : �Ĵ�����ַ����Χ��0x00 ~ 0x3F
 * \param[in] reg_val    : ���õļĴ���ֵ
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ic_reg_set (am_uartcmd_send_handle_t handle,
                          uint8_t            reg_addr,
                          uint8_t            reg_val);

/**
 * \brief ��ȡIC���ӿڵļĴ���ֵ
 *
 * ��������������ģ���϶�д��оƬ�ڲ��ļĴ���ֵ��
 * ͨ�����������ʵ�ֺܶ������������ɵĹ�����
 *
 * \param[in]  handle     : UARTCMD�Ĳ������
 * \param[in]  reg_addr   : �Ĵ�����ַ����Χ��0x00 ~ 0x3F
 * \param[out] p_val      : ��ȡ�Ĵ���ֵ��ָ��
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ic_reg_get (am_uartcmd_send_handle_t  handle,
                          uint8_t             reg_addr,
                          uint8_t            *p_val);

/**
 * \brief ���ò�����
 *
 * ������UARTͨ�Ź����иı�ͨ�ŵĲ����ʣ�����������ֵ������
 *
 * \param[in] handle        : UARTCMD�Ĳ������
 * \param[in] baudrate_flag : �����ʱ�־������֧�����еĲ����ʣ�Ӧʹ�ú�
 *                            AM_UARTCMD_BAUDRATE_* �������ò�����Ϊ115200��
 *                            ��ʹ�ú� #AM_UARTCMD_BAUDRATE_115200
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_baudrate_set (am_uartcmd_send_handle_t handle,
                            uint32_t           baudrate_flag);

/**
 * \name ����������ʽ
 * @{
 */

#define  AM_UARTCMD_ANT_TX1_ONLY      1    /**< \brief ��TX1��������         */
#define  AM_UARTCMD_ANT_TX2_ONLY      2    /**< \brief ��TX2��������         */
#define  AM_UARTCMD_ANT_TX1_AND_TX2   3    /**< \brief TX1��TX2ͬʱ��������  */
#define  AM_UARTCMD_ANT_NONE          0    /**< \brief ͬʱ�ر�TX1��TX2      */

/** @}*/
      
/**
 * \brief ��������������ʽ����������򿪡��ر�ĳ��������������
 *
 * \param[in] handle       : UARTCMD�Ĳ������
 * \param[in] antmode_flag : ʹ�ú� AM_UARTCMD_ANT_*����#AM_UARTCMD_ANT_TX1_ONLY
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_ant_mode_set (am_uartcmd_send_handle_t handle,
                            uint8_t            antmode_flag);

/**
 * \brief ����֡��ʽ�������л��¡���֡��ʽ�����óɹ�����粻��ʧ
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] flag       : ֡��ʽ���־����ʹ�����к꣺
 *                           - #AM_UARTCMD_FRAME_FMT_NEW
 *                           - #AM_UARTCMD_FRAME_FMT_OLD
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 *
 * \note ֡�л��ɹ�����Ҫ���µ���Ŀ��֡��ʽ�ĳ�ʼ��������
 */ 
int am_uartcmd_frame_fmt_set (am_uartcmd_send_handle_t handle,
                             uint8_t            flag);

/**
 * \brief �����豸����ģʽ�ʹӻ���ַ
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] mode       : ģ��Ĺ���ģʽ������ʹ�����к�ֵ��
 *                         - #AM_UARTCMD_MODE_MASTER      ����ģʽ
 *                         - #AM_UARTCMD_MODE_SLAVE       �ӻ�ģʽ ��Ĭ�ϣ�
 *                         - #AM_UARTCMD_MODE_AUTO_CHECK  �Զ����ģʽ
 *                         - #AM_UARTCMD_MODE_I2C         I2Cģʽ
 *                         - #AM_UARTCMD_MODE_UART        UARTģʽ
 *
 * \param[in] new_addr   : ���õ�UARTCMD�ӻ���ַ�����һλΪ0����Чֵ0x02 ~ 0xFE
 *
 * \retval AM_OK      : ���óɹ�,���óɹ��󣬺���Ӧ��ʹ���µĵ�ַͨ��
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_mode_addr_set (am_uartcmd_send_handle_t handle,
                             uint8_t            mode,
                             uint8_t            new_addr);
      
/**
 * \brief ��ȡ�豸����ģʽ�ʹӻ���ַ
 *
 * \param[in]  handle     : UARTCMD�Ĳ������
 * \param[out] p_mode     : ���ڻ�ȡģ�鹤��ģʽ��ָ�룬��ȡ��ֵ��λ�������£�
 *                          - bit7 ~ 4��0,�ӻ�ģʽ; 1,�Զ���⿨Ƭģʽ������ģʽ��
 *                          - bit3 ~ 0��0,�Զ����ģʽ; 1,I2Cͨ��ģʽ; 2,UARTģʽ 
 * \param[out] p_addr     : ���ڻ�ȡ��ǰ��UARTCMD�Ĵӻ���ַ��ָ��
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_mode_addr_get (am_uartcmd_send_handle_t  handle,
                             uint8_t            *p_mode,
                             uint8_t            *p_addr);
                             
/**
 * \brief װ���û���Կ��ģ�������ṩ��2��16�ֽڵĴ洢�ռ����ڱ����û���Կ��
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] key_sec    : ��Կ��������ţ����ɱ���2���û���Կ�����ţ�0 ~ 1
 * \param[in] p_key      : ��Կ����������Կ�ĳ��ȹ̶�Ϊ16�ֽ�
 *
 * \retval AM_OK      : װ����Կ�ɹ�
 * \retval -AM_EINVAL : װ��ʧ�ܣ���������
 * \retval -AM_EIO    : װ��ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_user_key_load (am_uartcmd_send_handle_t handle,
                             uint8_t            key_sec,
                             uint8_t           *p_key);
                              
/**
 * \brief дEEPROM��ģ���ڲ�ӵ��һ��256Byte��EEPROM
 *
 * \param[in] handle      : UARTCMD�Ĳ������
 * \param[in] eeprom_addr : EEPROM��Ƭ�ڵ�ַ��0 ~ 255
 * \param[in] p_buf       : д�����ݵĻ�����
 * \param[in] nbytes      : д�����ݵ��ֽ��������247�ֽ�
 *
 * \retval AM_OK      : д�����ݳɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_eeprom_write (am_uartcmd_send_handle_t handle,
                            uint8_t            eeprom_addr,
                            uint8_t           *p_buf,
                            uint8_t            nbytes);

/**
 * \brief ��EEPROM��ģ���ڲ�ӵ��һ��256Byte��EEPROM
 *
 * \param[in]  handle      : UARTCMD�Ĳ������
 * \param[in]  eeprom_addr : EEPROM��Ƭ�ڵ�ַ��0 ~ 255
 * \param[out] p_buf       : �������ݵĻ�����
 * \param[in]  nbytes      : �������ݵ��ֽ��������249�ֽ�
 *
 * \retval AM_OK      : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_eeprom_read (am_uartcmd_send_handle_t handle,
                           uint8_t            eeprom_addr,
                           uint8_t           *p_buf,
                           uint8_t            nbytes);

/**
 * \brief �л�����
 *
 * \param[in]  handle      : UARTCMD�Ĳ������
 * \param[in]  ante_num    : ���߱��
 *
 * \retval AM_OK      : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 */
int am_uartcmd_ante_select (am_uartcmd_send_handle_t  handle,
                           uint8_t             ante_num);

/**
 * \name Mifare������ģʽ
 * @{
 */

#define AM_UARTCMD_MIFARE_CARD_REQ_IDLE 0x26 /**< \brief IDLEģʽ,������еĿ� */
#define AM_UARTCMD_MIFARE_CARD_REQ_ALL  0x52 /**< \brief ALLģʽ,�������еĿ�  */

/** @}*/ 

/**
 * \brief Mifare���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] handle      : UARTCMD�Ĳ������
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_MIFARE_CARD_REQ_IDLE
 *                           - #AM_UARTCMD_MIFARE_CARD_REQ_ALL
 * \param[in] p_atq       : ��ȡ����Ӧ����Ϣ��ATQ����ָ�룬��ֵΪ16λ����ͬ��
 *                          ���ͷ��ص���Ϣ��ͬ,�������ͷ��ص�ATQ���£�
 *
 *            Mifare1 S50    | Mifare1 S70 | Mifare1 Light | Mifare0 UltraLight 
 *       --------------------|-------------|---------------|-------------------
 *              0x0004       |    0x0002   |    0x0010     |      0x0044 
 *       ----------------------------------------------------------------------
 *          Mifare3 DESFire  |   SHC1101   |    SHC1102    |      11RF32
 *       --------------------|-------------|---------------|-------------------
 *               0x0344      |    0x0004   |    0x3300     |      0x0004
 *
 * \retval AM_OK      : ����ɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 *
 * \note ���������ߺ󣬴���Ƶ���л�ȡ�������Ӷ��õ縴λ����λ�󿨴���IDLEģʽ��
 * ����������ģʽ����һ������ʱ����ʱ�Ŀ�������Ӧ������ĳһ�ſ��ɹ������˹���
 * ������Halt�����DeSelect������������Haltģʽ����ʱ�Ŀ�ֻ��ӦALL��0x52��
 * ģʽ�����󣬳��ǽ����뿪���߸�Ӧ�����ٽ��롣
 */ 
int am_uartcmd_mifare_card_request (am_uartcmd_send_handle_t handle,
                                   uint8_t            req_mode,
                                   uint16_t          *p_atq);

/**
 * \name Mifare������ײ�ȼ�
 * @{
 */
#define AM_UARTCMD_MIFARE_CARD_ANTICOLL_1  0x93  /**< \brief ��һ������ײ  */
#define AM_UARTCMD_MIFARE_CARD_ANTICOLL_2  0x95  /**< \brief �ڶ�������ײ  */
#define AM_UARTCMD_MIFARE_CARD_ANTICOLL_3  0x97  /**< \brief ����������ײ  */
/** @}*/ 

/**
 * \brief Mifare���ķ���ײ����
 *
 *  ��Ҫ�ɹ�ִ��һ�������������������ɹ������ܽ��з���ײ���������򷵻ش���
 *
 * \param[in] handle         : UARTCMD�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_3
 *
 * \param[in] know_uid : ��֪�Ŀ����к�
 * \param[in] nbit_cnt : λ������������֪�����к�uid��λ������ֵС��32��
 *                       - ��nbit_cntֵΪ0,�����û����֪���кţ����кŵ�����λ
 *                         ��Ҫ�ӱ�������á�
 *                       - ��nbit_cnt��Ϊ0�������к�������֪�����кŵ�ֵ����ʾ
 *                         ���кŵ�ǰnbit_cntλΪ��֪���к�����ʾǰnbit_cntλ��
 *                         ֵ������λ��Ҫ��������á�
 * \param[in] *p_uid   : ����ײ���ȡ���Ŀ����к�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  ����ISO14443A��׼�������кŶ���ȫ��Ψһ�ģ���������Ψһ�ԣ�����ʵ�ַ�
 * ��ײ���㷨�߼������������ſ�ͬʱ�����߸�Ӧ��������������ܹ��ҵ�һ�����кŽ�
 * ��Ŀ���������
 */ 
int am_uartcmd_mifare_card_anticoll (am_uartcmd_send_handle_t handle,
                                    uint8_t            anticoll_level,
                                    uint32_t           know_uid,
                                    uint8_t            nbit_cnt,
                                    uint32_t          *p_uid);
                       
/**
 * \brief Mifare����ѡ�����
 *
 *  ��Ҫ�ɹ�ִ��һ�η���ײ��������سɹ������ܽ��п�ѡ����������򷵻ش���
 *
 * \param[in] handle         : UARTCMD�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_3
 * \param[in] uid   : ǰһ������ײ������ȡ��UID
 * \param[in] p_sak : ���ص���Ϣ����bit2Ϊ1�������UID������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  �������кų��������֣�4�ֽڡ�7�ֽں�10�ֽڡ� 4�ֽڵ�ֻҪ��һ��ѡ�񼴿�
 * �õ����������кţ���Mifare1 S50/S70�ȣ�7�ֽڵ�Ҫ�ö���ѡ����ܵõ�����������
 * �ţ�ǰһ�����õ������кŵ�����ֽ�Ϊ������־0x88�������к���ֻ�к�3�ֽڿ��ã�
 * ��һ��ѡ���ܵõ�4�ֽ����кţ����߰�˳�����Ӽ�Ϊ7�ֽ����кţ���UltraLight
 * ��DesFire�ȣ�10�ֽڵ��Դ����ƣ�������δ���ִ��࿨��
 */ 
int am_uartcmd_mifare_card_select (am_uartcmd_send_handle_t handle,
                                  uint8_t            anticoll_level,
                                  uint32_t           uid,
                                  uint8_t           *p_sak);

/**
 * \brief Mifare���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *  ��HALT״̬�£���������Ӧ������������IDLEģʽ�����󣬳��ǽ�����λ���뿪���߸�
 *  Ӧ�����ٽ��롣��������Ӧ������������ALL����
 *
 * \param[in] handle         : UARTCMD�Ĳ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_mifare_card_halt (am_uartcmd_send_handle_t handle);

                               
/**
 * \brief Mifare��E2��Կ��֤
 *
 *     ��ģ���ڲ��Ѵ������Կ�뿨����Կ������֤��ʹ�ø�����ǰӦ���á�װ��IC����Կ��
 * ��������Կ�ɹ�����ģ���ڡ����⣬��Ҫ��֤�Ŀ��������Ų�����ģ������Կ������ȡ�
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_UARTCMD_IC_KEY_TYPE_A
 *                          - #AM_UARTCMD_IC_KEY_TYPE_B
 * \param[in] p_uid      : �����кţ�4�ֽ�
 * \param[in] key_sec    : ��Կ���ţ�0 ~ 7
 * \param[in] nblock     : ��Ҫ��֤�Ŀ���ţ�ȡֵ��Χ�뿨�����йأ�
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 * 
 * \note PLUS CPUϵ�еĿ��Ŀ�����4�ֽں�7�ֽ�֮�֣�����7�ֽڿ��ŵĿ���
 *       ֻ��Ҫ�����ŵĸ�4�ֽڣ��ȼ�2����ײ�õ��Ŀ��ţ���Ϊ��֤�Ŀ��ż��ɡ�
 */
int am_uartcmd_mifare_card_e2_authent (am_uartcmd_send_handle_t  handle,
                                      uint8_t             key_type,
                                      uint8_t            *p_uid,
                                      uint8_t             key_sec,
                                      uint8_t             nblock);

/**
 * \brief Mifare��ֱ����Կ��֤
 *
 *    �����������Ϊ�������ݣ�����ڴ�֮ǰ�����á�װ��IC����Կ���������ǰ��
 * ΪPLUS CPU���ĵȼ�2��ȼ�3�������������ֻ��6�ֽڣ���ģ���Զ������������
 * ����2�Σ�ȡǰ16�ֽ���Ϊ��ǰ��֤��Կ��
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_UARTCMD_IC_KEY_TYPE_A
 *                          - #AM_UARTCMD_IC_KEY_TYPE_B
 * \param[in] p_uid      : �����кţ�4�ֽ�
 * \param[in] p_key      : ��Կ������
 * \param[in] key_len    : ��Կ�ĳ��ȣ�ֻ��Ϊ6��6�ֽ���Կ����16��16�ֽ���Կ��
 * \param[in] nblock     : ��Ҫ��֤�Ŀ���ţ�ȡֵ��Χ�뿨�����йأ�
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 * 
 * \note PLUS CPUϵ�еĿ��Ŀ�����4�ֽں�7�ֽ�֮�֣�����7�ֽڿ��ŵĿ���
 *       ֻ��Ҫ�����ŵĸ�4�ֽڣ��ȼ�2����ײ�õ��Ŀ��ţ���Ϊ��֤�Ŀ��ż��ɡ�
 */
int am_uartcmd_mifare_card_direct_authent (am_uartcmd_send_handle_t  handle,
                                          uint8_t             key_type,
                                          uint8_t            *p_uid,
                                          uint8_t            *p_key,
                                          uint8_t             key_len,
                                          uint8_t             nblock);
          
/**
 * \brief Mifare�����ݶ�ȡ
 *
 *     ����֤�ɹ�֮�󣬲��ܶ���Ӧ�Ŀ����ݣ�����֤�Ŀ�������ű�����ͬһ�������ڣ�
 * Mifare1���ӿ��0��ʼ��˳��ÿ4����1����������Ҫ��һ�ſ��еĶ���������в�������
 * ��ĳһ����������Ϻ󣬱������һ����������ܶ���һ������ֱ�ӽ�����֤�������
 * ���������ʼ����������PLUS CPU��������һ������������Կ�͵�ǰ��������Կ��ͬ��
 * ����Ҫ�ٴ���֤��Կ��ֱ�Ӷ����ɡ�
 *
 * \param[in]  handle     : UARTCMD�Ĳ������
 * \param[in]  nblock     : ��ȡ���ݵĿ��
 *                          - S50��0 ~ 63
 *                          - S70��0 ~ 255
 *                          - PLUS CPU 2K��0 ~ 127
 *                          - PLUS CPU 4K��0 ~ 255
 * \param[out] p_buf      : ��Ŷ�ȡ�����ݣ���СΪ 16
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_read (am_uartcmd_send_handle_t  handle,
                                uint8_t             nblock,
                                uint8_t            *p_buf);

/**
 * \brief Mifare��д����,д֮ǰ����ɹ�������Կ��֤��
 *
 *      �Կ���ĳһ�������֤�ɹ��󣬼��ɶ�ͬһ�����ĸ�������д������ֻҪ��������������
 *  ���а���λ������β������飬���Ǹ��������Ψһ����������PLUS CPU���ȼ�2��3��AES��
 *  Կ����������λ���޸���Կ��
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵĿ��
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 * \param[in] p_buf      : д�����ݻ���������С����Ϊ 16
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_write (am_uartcmd_send_handle_t  handle,
                                 uint8_t             nblock,
                                 uint8_t            *p_buf);
                                
/**
 * \brief Mifare��д����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵĿ��, 1 ~ 15
 * \param[in] p_buf      : д�����ݻ���������С����Ϊ 4
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * ������ֻ��UltraLight����Ч����UltraLight�����ж�������Mifare1��һ����
 */
int am_uartcmd_ultralight_card_write (am_uartcmd_send_handle_t  handle,
                                     uint8_t             nblock,
                                     uint8_t            *p_buf);

/**
 * \name Mifare��ֵ����ģʽ
 * @{
 */

#define AM_UARTCMD_MIFARE_CARD_VALUE_ADD  0xC1  /**< \brief ��  */
#define AM_UARTCMD_MIFARE_CARD_VALUE_SUB  0xC0  /**< \brief ��  */

/** @}*/

/**
 * \brief Mifareֵ��������Mifare����ֵ����мӼ�����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] mode       : ֵ������ģʽ�������Ǽӻ����ʹ�����к꣺
 *                          - AM_UARTCMD_MIFARE_CARD_VALUE_ADD
 *                          - AM_UARTCMD_MIFARE_CARD_VALUE_SUB
 * \param[in] nblock     : ����ֵ�����Ŀ��
 *                           - S50��0 ~ 63
 *                            - S70��0 ~ 255
 *                            - PLUS CPU 2K��0 ~ 127
 *                            - PLUS CPU 4K��0 ~ 255
 * \param[in] ntransblk  : �����ţ�������ֵ��ŵĿ��
 * \param[in] value      : 4�ֽ��з�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * \note Ҫ���д�������������ݱ���Ҫ��ֵ��ĸ�ʽ���ɲο�NXP������ĵ���������
 * ���봫������ͬ���򽫲�����Ľ��д��ԭ���Ŀ��ڣ���������봫���Ų���ͬ��
 * �򽫲�����Ľ��д�봫����ڣ����������ڵ����ݱ����ǣ�ԭ���ڵ�ֵ���䡣
 * ���ڵȼ�2��PLUS CPU����֧��ֵ��������ȼ�1��3֧�֡�
 */
int am_uartcmd_mifare_card_val_operate (am_uartcmd_send_handle_t  handle,
                                       uint8_t             mode,
                                       uint8_t             nblock,
                                       uint8_t             ntransblk,
                                       int32_t             value);

/**
 * \brief Mifare����λ��ͨ�����ز��źŹر�ָ����ʱ�䣬�ٿ�����ʵ�ֿ�Ƭ��λ��
 * 
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] time_ms    : �رյ�ʱ�䣨��λ:ms����0Ϊһֱ�ر�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note �ú����������źŹر������룬��һֱ�رգ���ȵ�ִ��һ����������ʱ�򿪡�
 */
int am_uartcmd_mifare_card_reset (am_uartcmd_send_handle_t  handle,
                                 uint8_t             time_ms);

/**
 * \brief Mifare������ú������ڼ��Ƭ�������󡢷���ײ��ѡ�������������ϡ�
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_MIFARE_CARD_REQ_IDLE
 *                           - #AM_UARTCMD_MIFARE_CARD_REQ_ALL
 * \param[in] p_atq      : ����Ӧ��
 * \param[in] p_saq      : ���һ��ѡ��Ӧ��SAK
 * \param[in] p_len      : ���кŵ�ʵ�ʳ��ȣ�4�ֽڡ�7�ֽڻ�10�ֽ�
 * \param[in] p_uid      : ���кŻ�����������Ӧ�������кų��ȱ���һ�£�
 *                         �粻ȷ����������ʹ����󳤶�10��
 * \param[in]  uid_len   �� p_uid ��ָ�������ĳ���
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int uartcmd_card_active (am_uartcmd_send_handle_t  handle,
                                  uint8_t             req_mode,
                                  uint16_t           *p_atq,
                                  uint8_t            *p_saq,
                                  uint8_t            *p_len,
                                  uint8_t            *p_uid,
                                  uint8_t             uid_len);

/**
 * \brief Mifareֵ����������ֵ���ֵ
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵ�ֵ���ַ
 * \param[in] value      : ���õ�ֵ
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_val_set (am_uartcmd_send_handle_t  handle,
                                   uint8_t             nblock,
                                   int32_t             value);
               
/**
 * \brief Mifareֵ��������ȡֵ���ֵ
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵ�ֵ���ַ
 * \param[in] p_value    : ��ȡֵ��ָ��
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_val_get (am_uartcmd_send_handle_t  handle,
                                   uint8_t             nblock,
                                   int32_t            *p_value);

/**
 * \brief �����
 *
 *     �ú�������ģ����չ���ܣ�����ģ����Ƭ�������ⳤ����ϵ����ݴ����������
 * NXP���Ƴ���NTAG213F������Ultralight Cϵ�п�Ƭ�����Ǹÿ�Ƭ�����������������
 * ��д��Կ�������ܡ��������Կ��֤��������ô��������亯����ʵ�֡�
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] p_tx_buf   : �������ݵĻ�����
 * \param[in] tx_nbytes  : �����ֽ���
 * \param[in] p_rx_buf   : �������ݵĻ�����
 * \param[in] rx_nbytes  : �����ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_cmd_trans (am_uartcmd_send_handle_t  handle,
                                     uint8_t            *p_tx_buf,
                                     uint8_t             tx_nbytes,
                                     uint8_t            *p_rx_buf,
                                     uint8_t             rx_nbytes);

/**
 * \brief ���ݽ���
 *
 * �������ö�д���뿨Ƭ�����ݽ�����ͨ���ú�������ʵ�ֶ�д���������й��ܡ�
 *
 * \param[in]  handle     : UARTCMD�Ĳ������
 * \param[in]  p_data_buf : ��Ҫ�������͵�����
 * \param[in]  len        : �������ݵĳ���
 * \param[in]  wtxm_crc   : b7~b2,wtxm��b1,RFU(0); b0,0,CRC��ֹ�ܣ�1,CRCʹ�ܡ�
 * \param[in]  fwi        : ��ʱ�ȴ�ʱ�����, ��ʱʱ��=����0x01 << fwi*302us��
 * \param[out] p_rx_buf   : ���ݽ�����Ӧ֡��Ϣ
 * \param[in]  buf_size   : ���ջ�Ӧ��Ϣ�Ļ�������С
 * \param[in]  p_real_len : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                         Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_data_exchange (am_uartcmd_send_handle_t  handle,
                                         uint8_t            *p_data_buf,
                                         uint8_t             len,
                                         uint8_t             wtxm_crc,
                                         uint8_t             fwi,
                                         uint8_t            *p_rx_buf,
                                         uint8_t             buf_size,
                                         uint16_t           *p_real_len);

/**
 * \name Mifare�����ģʽ
 * @{
 */

/** \brief ִ����һ���Զ�����ִ��Halt����  */
#define AM_UARTCMD_MIFARE_CARD_AD_HALT  0x08

/** @}*/

/**
 * \name Mifare����������ģʽ
 * @{
 */

#define AM_UARTCMD_MIFARE_CARD_TX_IN_TURN   0x00 /**< \brief TX1��TX2�������� */
#define AM_UARTCMD_MIFARE_CARD_TX_TX1       0x01 /**< \brief ��TX1���� */
#define AM_UARTCMD_MIFARE_CARD_TX_TX2       0x02 /**< \brief ��TX2���� */
#define AM_UARTCMD_MIFARE_CARD_TX_ALL       0x03 /**< \brief TX1��TX2ͬʱ���� */

/** @}*/

/**
 * \name Mifare����Կ��֤ģʽ
 * @{
 */

#define AM_UARTCMD_MIFARE_CARD_AUTH_E2      0x45 /**< \brief E2��Կ��֤(E) */
#define AM_UARTCMD_MIFARE_CARD_AUTH_DIRECT  0x46 /**< \brief ֱ����Կ��֤(F) */
#define AM_UARTCMD_MIFARE_CARD_AUTH_NO      0x00 /**< \brief ����֤ */

/** @}*/

/**
 * \brief ����Mifare���Զ����
 * \note ���Զ�����ڼ䣬�����������κγ����Զ����������ģ������ݳ���С��3
 *       ��������˳��Զ����ģʽ��������am_uartcmd_mifare_card_active()
 *       ����ڴ��ڼ䣬ģ�齫���������ݳ��ȴ���2������
 *
 * \param[in] handle    : UARTCMD�Ĳ������
 * \param[in] p_adinfo  : �Զ������Ϣ
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_auto_detect_start (am_uartcmd_send_handle_t                  handle,
                                             const am_uartcmd_auto_detect_info_t *p_adinfo);

/**
 * \brief �ر�Mifare���Զ����
 *
 * \param[in] handle  : UARTCMD�Ĳ������
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_auto_detect_stop (am_uartcmd_send_handle_t handle);

/**
 * \brief Mifare���Զ����ص���������
 *
 * \param[in] handle       : UARTCMD�Ĳ������
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص�������ڲ���
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_auto_detect_cb_set (am_uartcmd_send_handle_t  handle,
                                              am_pfnvoid_t        pfn_callback,
                                              void               *p_arg);

/**
 * \name Mifare�����Զ�����ʶ
 * @{
 */

#define AM_UARTCMD_MIFARE_CARD_AD_READ_CANCEL    0x00  /**< \brief ȡ����� */
#define AM_UARTCMD_MIFARE_CARD_AD_READ_CONTINUE  0x01  /**< \brief ������� */

/** @} */

/**
 * \brief Mifare��Ƭ��Ϣ
 */
typedef struct am_uartcmd_mifare_card_info {
    uint8_t     tx_mode;        /**< \brief ��������ģʽ */
    uint8_t     uid_len;        /**< \brief UID(��Ψһ���к�)���ȣ�4��7��10 */
    uint8_t     uid[10];        /**< \brief UID */
    uint8_t     card_data[16];  /**< \brief ��Ƭ���� */
} am_uartcmd_mifare_card_info_t;

/**
 * \brief Mifare����ȡ�Զ������������
 *
 * \param[in]  handle      : UARTCMD�Ĳ������
 * \param[out] p_card_info : ָ���ſ�Ƭ���ݵ�ָ��
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_mifare_card_auto_detect_read (am_uartcmd_send_handle_t            handle,
                                            am_uartcmd_mifare_card_info_t *p_card_info);




/**
 * \name PICCA������ģʽ
 * @{
 */
#define AM_UARTCMD_PICCA_REQ_IDLE 0x26 /**< \brief IDLEģʽ,������еĿ� */
#define AM_UARTCMD_PICCA_REQ_ALL  0x52 /**< \brief ALLģʽ,�������еĿ�  */
/** @}*/ 

/**
 * \brief PICCA���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] handle      : UARTCMD�Ĳ������
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_PICCA_REQ_IDLE
 *                           - #AM_UARTCMD_PICCA_REQ_ALL
 * \param[in] p_atq       : ��ȡ����Ӧ����Ϣ��ATQ����ָ�룬��ֵΪ16λ����ͬ��
 *                          ���ͷ��ص���Ϣ��ͬ,�������ͷ��ص�ATQ���£�
 *
 *            Mifare1 S50    | Mifare1 S70 | Mifare1 Light | Mifare0 UltraLight 
 *       --------------------|-------------|---------------|-------------------
 *              0x0004       |    0x0002   |    0x0010     |      0x0044 
 *       ----------------------------------------------------------------------
 *          Mifare3 DESFire  |   SHC1101   |    SHC1102    |      11RF32
 *       --------------------|-------------|---------------|-------------------
 *               0x0344      |    0x0004   |    0x3300     |      0x0004
 *
 * \retval AM_OK      : ����ɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 *
 * \note ���������ߺ󣬴���Ƶ���л�ȡ�������Ӷ��õ縴λ����λ�󿨴���IDLEģʽ��
 * ����������ģʽ����һ������ʱ����ʱ�Ŀ�������Ӧ������ĳһ�ſ��ɹ������˹���
 * ������Halt�����DeSelect������������Haltģʽ����ʱ�Ŀ�ֻ��ӦALL��0x52��
 * ģʽ�����󣬳��ǽ����뿪���߸�Ӧ�����ٽ��롣
 */ 
int am_uartcmd_picca_request (am_uartcmd_send_handle_t handle,
                             uint8_t            req_mode,
                             uint16_t          *p_atq);

/**
 * \name PICCA������ײ�ȼ�
 * @{
 */
#define AM_UARTCMD_PICCA_ANTICOLL_1  0x93  /**< \brief ��һ������ײ  */
#define AM_UARTCMD_PICCA_ANTICOLL_2  0x95  /**< \brief �ڶ�������ײ  */
#define AM_UARTCMD_PICCA_ANTICOLL_3  0x97  /**< \brief ����������ײ  */
/** @}*/ 

/**
 * \brief PICCA���ķ���ײ����
 *
 *  ��Ҫ�ɹ�ִ��һ�������������������ɹ������ܽ��з���ײ���������򷵻ش���
 *
 * \param[in] handle         : UARTCMD�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_3
 *
 * \param[in] know_uid : ��֪�Ŀ����к�
 * \param[in] nbit_cnt : λ������������֪�����к�uid��λ������ֵС��32��
 *                       - ��nbit_cntֵΪ0,�����û����֪���кţ����кŵ�����λ
 *                         ��Ҫ�ӱ�������á�
 *                       - ��nbit_cnt��Ϊ0�������к�������֪�����кŵ�ֵ����ʾ
 *                         ���кŵ�ǰnbit_cntλΪ��֪���к�����ʾǰnbit_cntλ��
 *                         ֵ������λ��Ҫ��������á�
 * \param[in] *p_uid   : ����ײ���ȡ���Ŀ����к�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  ����ISO14443A��׼�������кŶ���ȫ��Ψһ�ģ���������Ψһ�ԣ�����ʵ�ַ�
 * ��ײ���㷨�߼������������ſ�ͬʱ�����߸�Ӧ��������������ܹ��ҵ�һ�����кŽ�
 * ��Ŀ���������
 */ 
int am_uartcmd_picca_anticoll (am_uartcmd_send_handle_t handle,
                              uint8_t            anticoll_level,
                              uint32_t           know_uid,
                              uint8_t            nbit_cnt,
                              uint32_t          *p_uid);
                       
/**
 * \brief PICC A����ѡ�����
 *
 *  ��Ҫ�ɹ�ִ��һ�η���ײ��������سɹ������ܽ��п�ѡ����������򷵻ش���
 *
 * \param[in] handle         : UARTCMD�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_UARTCMD_MIFARE_CARD_ANTICOLL_3
 * \param[in] uid   : ǰһ������ײ������ȡ��UID
 * \param[in] p_sak : ���ص���Ϣ����bit2Ϊ1�������UID������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  �������кų��������֣�4�ֽڡ�7�ֽں�10�ֽڡ� 4�ֽڵ�ֻҪ��һ��ѡ�񼴿�
 * �õ����������кţ���Mifare1 S50/S70�ȣ�7�ֽڵ�Ҫ�ö���ѡ����ܵõ�����������
 * �ţ�ǰһ�����õ������кŵ�����ֽ�Ϊ������־0x88�������к���ֻ�к�3�ֽڿ��ã�
 * ��һ��ѡ���ܵõ�4�ֽ����кţ����߰�˳�����Ӽ�Ϊ7�ֽ����кţ���UltraLight
 * ��DesFire�ȣ�10�ֽڵ��Դ����ƣ�������δ���ִ��࿨��
 */ 
int am_uartcmd_picca_select (am_uartcmd_send_handle_t handle,
                            uint8_t            anticoll_level,
                            uint32_t           uid,
                            uint8_t           *p_sak);

/**
 * \brief PICCA���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *  ��HALT״̬�£���������Ӧ������������IDLEģʽ�����󣬳��ǽ�����λ���뿪���߸�
 *  Ӧ�����ٽ��롣��������Ӧ������������ALL����
 *
 * \param[in] handle         : UARTCMD�Ĳ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_picca_halt (am_uartcmd_send_handle_t handle);

/**
 * \brief PICC TypeA��RATS��request for answer to select��
 *
 *     RATS��request for answer to select����ISO14443-4Э������ģ�鷢��RATS��
 * ��Ƭ����ATS��answer to select����ΪRATS��Ӧ����ִ�и�����ǰ�������Ƚ���һ��
 * ��ѡ���������ִ�й�һ��RATS��������ٴ�ִ��RATS��������Ƚ�����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] cid        : ����ʶ����card IDentifier��ȡֵ��Χ0x00��0x0E��
 * \param[in] p_ats_buf  : ���ڽ��ջ�Ӧ����Ϣ����ͬ�����ֽ������в�ͬ
 * \param[in] bufsize    : ��������С
 * \param[in] p_rx_len   : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                         Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_picca_rats (am_uartcmd_send_handle_t  handle,
                          uint8_t             cid,
                          uint8_t            *p_ats_buf,
                          uint8_t             bufsize,
                          uint16_t           *p_rx_len);

/**
 * \brief PICC TypeA��PPS��request for answer to select��
 *
 *     PPS��protocal and parameter selection����ISO14443-4Э���������ڸı���
 * �ص�ר��Э�������������Ǳ���ģ�����ֻ֧��Ĭ�ϲ�������������Ĳ�������Ϊ
 * 0���ɡ���ִ�и�����ǰ�������ȳɹ�ִ��һ��RATS���
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] dsi_dri    : ģ���뿨ͨ�Ų�����,����Ϊ0��Ĭ�ϣ�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_picca_pps (am_uartcmd_send_handle_t  handle,
                         uint8_t             dsi_dri);
                         
/**
 * \brief PICC TypeA���������
 *
 *   ��������ISO14443-4Э���������ڽ���Ƭ��Ϊ����HALT��״̬�����ڹ���
 *��HALT��״̬�Ŀ������á���������������ΪALL�������¼����ֻ��ִ�С�RATS��
 * ����Ŀ����ø����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_picca_deselect (am_uartcmd_send_handle_t  handle);
                             
/**
 * \brief PICC��T=CL
 *
 *     T=CL�ǰ�˫�����鴫��Э�飬ISO14443-4Э��������ڶ�д���뿨Ƭ֮�������
 * ������һ�����ISO14443Э���CPU�����ø�Э�����д��ͨ�š����ø�����ʱֻ��Ҫ
 * ��CPU��COS�����������Ϊ���뼴�ɣ���������������͡�����ʶ��CID��֡�ȴ�ʱ��
 * FWT���ȴ�ʱ����չ��������WTXM��waiting time extensionmultiplier�����ȵ��ɸ�
 * �����Զ���ɡ�
 *
 * \param[in] handle      : UARTCMD�Ĳ������
 * \param[in] p_cos_buf   : COS����
 * \param[in] cos_bufsize ��COS����ĳ���
 * \param[in] p_res_buf   : ���ڽ��ջ�Ӧ����Ϣ����ͬCOS����ֽ������в�ͬ
 * \param[in] res_bufsize : ���ջ�Ӧ��Ϣ�Ļ�������С
 * \param[in] p_rx_len    : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                          Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_picc_tpcl (am_uartcmd_send_handle_t  handle,
                         uint8_t            *p_cos_buf,
                         uint8_t             cos_bufsize,
                         uint8_t            *p_res_buf,
                         uint8_t             res_bufsize,
                         uint16_t           *p_rx_len);

/**
 * \brief ���ݽ���
 *
 * �������ö�д���뿨Ƭ�����ݽ�����ͨ���ú�������ʵ�ֶ�д���������й��ܡ�
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] p_data_buf : ��Ҫ�������͵����ݣ���������ʵ��ʹ�õĿ��йأ�
 * \param[in] len        : �������ݵĳ���
 * \param[in] wtxm_crc   : b7~b2,wtxm��b1,RFU(0); b0,0-CRC��ֹ�ܣ�1-CRCʹ�ܡ�
 * \param[in] fwi        : ��ʱ�ȴ�ʱ�����, ��ʱʱ��=����0x01 << fwi*302us��
 * \param[in] p_rx_buf   : ���ݽ�����Ӧ֡��Ϣ
 * \param[in] bufsize    : ���ջ�Ӧ��Ϣ�Ļ�������С
 * \param[in] p_rx_len   : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                         Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_picc_data_exchange (am_uartcmd_send_handle_t  handle,
                                  uint8_t            *p_data_buf,
                                  uint8_t             len,
                                  uint8_t             wtxm_crc,
                                  uint8_t             fwi,
                                  uint8_t            *p_rx_buf,
                                  uint8_t             bufsize,
                                  uint16_t           *p_rx_len);

/**
 * \brief PICC A����λ��ͨ�����ز��źŹر�ָ����ʱ�䣬�ٿ�����ʵ�ֿ�Ƭ��λ��
 * 
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] time_ms    : �رյ�ʱ�䣨��λ:ms����0Ϊһֱ�ر�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note �ú����������źŹر������룬��һֱ�رգ���ȵ�ִ��һ����������ʱ�򿪡�
 */
int am_uartcmd_picca_reset(am_uartcmd_send_handle_t  handle,
                          uint8_t             time_ms);
                          
/**
 * \brief PICC A������ú������ڼ��Ƭ�������󡢷���ײ��ѡ�������������ϡ�
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_PICCA_REQ_IDLE
 *                           - #AM_UARTCMD_PICCA_REQ_ALL
 * \param[in] p_atq      : ����Ӧ��
 * \param[in] p_saq      : ���һ��ѡ��Ӧ��SAK
 * \param[in] p_len      : ���кų��ȣ�4�ֽڻ�7�ֽ�
 * \param[in] p_uid      : ���кŻ�����������Ӧ�������кų��ȱ���һ��
 * \param[in] uid_len    : p_uid ��ָ�������ĳ���
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_picca_active (am_uartcmd_send_handle_t  handle,
                            uint8_t             req_mode,
                            uint16_t           *p_atq,
                            uint8_t            *p_saq,
                            uint8_t            *p_len,
                            uint8_t            *p_uid,
                            uint8_t             uid_len);

/**
 * \name PICCB������ģʽ
 * @{
 */

#define AM_UARTCMD_PICCB_REQ_IDLE 0x00 /**< \brief IDLEģʽ,������еĿ� */
#define AM_UARTCMD_PICCB_REQ_ALL  0x08 /**< \brief ALLģʽ,�������еĿ�  */

/** @}*/ 

/**
 * \brief PICC B������
 *
 *    �ڵ��øú���ǰ����Ҫȷ��IC����ģʽ�Ѿ�����ΪTypeBģʽ��
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_PICCB_REQ_IDLE
 *                           - #AM_UARTCMD_PICCB_REQ_ALL
 * \param[in] p_uid      : UID�����Ϣ������Ϊ12
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_piccb_active (am_uartcmd_send_handle_t  handle,
                            uint8_t             req_mode,
                            uint8_t            *p_uid);

/**
 * \brief PICC B����λ��ͨ�����ز��źŹر�ָ����ʱ�䣬�ٿ�����ʵ�ֿ�Ƭ��λ��
 * 
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] time_ms    : �رյ�ʱ�䣨��λ:ms����0Ϊһֱ�ر�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note �ú����������źŹر������룬��һֱ�رգ���ȵ�ִ��һ����������ʱ�򿪡�
 */
int am_uartcmd_piccb_reset (am_uartcmd_send_handle_t  handle,
                           uint8_t             time_ms);

/**
 * \brief PICCA���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] handle      : UARTCMD�Ĳ������
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_PICCB_REQ_IDLE
 *                           - #AM_UARTCMD_PICCB_REQ_ALL
 * \param[in] slot_time   : ʱ϶������0 ~ 4
 * \param[in] p_uid       : ���ص�UID�����Ϣ������Ϊ12
 *
 * \retval AM_OK      : ����ɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_piccb_request (am_uartcmd_send_handle_t  handle,
                             uint8_t             req_mode,
                             uint8_t             slot_time,
                             uint8_t            *p_uid);

/**
 * \brief PICC B ���ķ���ײ����
 *
 * \param[in] handle      : UARTCMD�Ĳ������
 * \param[in] slot_flag   : ʱ϶��ǣ�2 ~ 16���ò���ֵ�����������ʱ϶�����й�
 *                          ϵ���������������ʱ϶����Ϊn�����ʱ϶���N < 2^n
 * \param[in] p_uid       : ���ص�UID�����Ϣ������Ϊ12
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_uartcmd_piccb_anticoll (am_uartcmd_send_handle_t  handle,
                              uint8_t             slot_flag,
                              uint8_t            *p_uid);
                             
/**
 * \brief PICC B���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *     �ú�������B�Ϳ�������ִ�й�������ǰ��������ִ�гɹ���һ���������ִ��
 * ��������ɹ��󣬿�Ƭ���ڹ���״̬��ģ�����ͨ��ALL��ʽ����Ƭ����������IDLE��
 * ʽ����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] p_pupi     : PUPI,��СΪ4�ֽڵı�ʶ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_piccb_halt (am_uartcmd_send_handle_t handle,
                          uint8_t            *p_pupi);
 
/**
 * \brief �޸�B���Ĵ�������
 *
 *     �ú�������B�Ϳ�������ִ�й�������ǰ��������ִ�гɹ���һ���������ִ��
 * ��������ɹ��󣬿�Ƭ���ڹ���״̬��ģ�����ͨ��ALL��ʽ����Ƭ����������IDLE��
 * ʽ����
 *
 * \param[in] handle     : UARTCMD�Ĳ������
 * \param[in] p_pupi     : PUPI,��СΪ4�ֽڵı�ʶ��
 * \param[in] cid        : ȡֵ��ΧΪ 0 - 14, ����֧��CID��������Ϊ0
 * \param[in] protype    : ֧�ֵ�Э��
 *                          - bit3 : 1-PCD��ֹ��PICC����ͨ��,0-PCD��PICC����ͨ��
 *                          - bit2 ~ bit1 : 
 *                              - 11 : 10 etu + 512 / fs
 *                              - 10 : 10 etu + 256 / fs
 *                              - 01 : 10 etu + 128 / fs
 *                              - 00 : 10 etu + 32 / fs
 *                          - bit0 : 1-��ѭISO14443-4,0-����ѭISO14443-4
 *                                   (�������֤�����λ����Ϊ1)
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_uartcmd_piccb_attrib_set (am_uartcmd_send_handle_t handle,
                                uint8_t           *p_pupi,
                                uint8_t            cid,
                                uint8_t            protype);

/**
 * \brief ��ȡ���֤��Ϣ
 *
 * \param[in]  handle   : UARTCMD�Ĳ������
 * \param[in]  req_mode : ����ģʽ����ʹ�����к꣺
 *                           - #AM_UARTCMD_PICCB_REQ_IDLE
 *                           - #AM_UARTCMD_PICCB_REQ_ALL
 * \param[out] p_info : ���֤��Ϣ����������СӦΪ8�ֽڣ�
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * \note Ҫ���ж����֤��Ϣ���������ȵ��� am_uartcmd_ic_isotype_set �ӿڽ�����������ΪB��,
 *       ��ȡ���֮��Ӧ����������� am_uartcmd_ic_isotype_set �������ͻ�ԭ�򲻻�ԭ��
 */
int am_uartcmd_id_card_info_get (am_uartcmd_send_handle_t handle, uint8_t req_mode, uint8_t *p_info);

/**
 * \brief ָ�ʱʱ������
 *
 * \param[in]  handle     : UARTCMD�Ĳ������
 * \param[in]  timeout_ms : ָ�ʱʱ�䣨���룩
 *
 * \retval AM_OK : ���óɹ�
 * \retval ����     : ����ʧ��
 */
int am_uartcmd_cmd_timeout_set (am_uartcmd_send_handle_t handle, uint32_t timeout_ms);

/** 
 * @}
 */
 
#endif /* __AM_UARTCMD_H */

/* end of file */
