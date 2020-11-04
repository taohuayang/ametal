/*******************************************************************************
*                                 AMORKS
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      amorks.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief user interface of modbus master protocol.
 *
 * \internal
 * \par modification history
 * - 1.00 2017-03-06  mkr, transplant from amorks
 * \endinternal
 */
#ifndef __AM_MB_MASTER_H  /* { */
#define __AM_MB_MASTER_H

/**
 * \addtogroup grp_am_if_mb_master
 * \copydoc am_mb_master.h
 * @{
 */

#include "am_mb_err.h"
#include "am_mb_comm.h"
#include "am_mb_m_netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ����PDU���ݴ���ӿ�
 * @note  �û�ע���Զ��幦����ʱ���趨������ͽӿ�ע�ᡣ
 * @note  �û�ʹ�øýӿڽ�p_params����ת��Ϊp_pdudata���ݣ������������룩,������PDU
 *        ���ݳ���(p_pdudata_len)���Դ˸�֪Э��ջ������PDU���ݼ����ͳ��ȡ�
 *
 * @param[in]           p_params : �û��Զ������;
 *                                 �ò���Ϊam_mb_master_request�ӿڵ�p_param����.
 * @param[in][out]     p_pdudata : PDU�������ݻ��������û�������ת�����������С�
 * @param[in][out] p_pdudata_len : PDU�������ݻ��������ȣ��ò�������ʱ����֪�û�
 *                                 PDU���ݻ���������󳤶ȡ�
 * @return ������PDU���ݴ���ʧ�ܣ��򷵻���Ӧ�������ͣ���֮����AM_MB_ERR_NOERR��
 */
typedef am_mb_err_t (*am_mb_snd_funcode_handler_t) (void    *p_params,
                                                    uint8_t *p_pdudata,
                                                    uint8_t *p_pdudata_len);

/**
 * \brief ����PDU���ݴ���ӿ�
 * @note  �û�ע���Զ��幦����ʱ���趨������ͽӿ�ע�ᡣ
 * @note  �û�ʹ�øýӿڽ�PDU����������ת��Ϊp_params.
 *
 * @param[in][out]  p_params : �û��Զ������,
 *                             �ò���Ϊam_mb_master_request�ӿڵ�p_param����.
 * @param[in]      p_pdudata : PDU���ݻ�����(������������).
 * @param[in]    pdudata_len : PDU���ݻ���������.
 * @return ��PDU���ݴ���ʧ�ܣ��򷵻���Ӧ�������ͣ���֮����AM_MB_ERR_NOERR��
 */
typedef am_mb_err_t (*am_mb_rcv_funcode_handler_t) (void    *p_params,
                                                    uint8_t *p_pdudata,
                                                    uint8_t  pdudata_len);

/** \brief  function code handler type */
typedef struct am_mb_m_funcode_handler {
    uint8_t                     funcode;     /** \brief function_code */
    am_mb_snd_funcode_handler_t snd_handler; /** \brief send handle interface */
    am_mb_rcv_funcode_handler_t rcv_handler; /** \brief recv handle interface */
} am_mb_m_funcode_handler_t;

/******************************************************************************/

/** \brief Modbus ��վ����  */
typedef struct am_mb_master_serv {
    /** \brief point to asii/rtu mode private data */
    void                     *p_cookie;

    uint8_t                   slave_addr; /**< \brief slave address */
    enum am_mb_mode           mode;       /**< \brief master mode   */
    enum am_mb_master_status  status;     /**< \brief master status */

    /** \brief �û�ע�Ṧ���뻺�� */
    am_mb_m_funcode_handler_t *p_funcode_hdl;

    /** \brief ��֧��ע��Ĺ�������� */
    uint8_t                    funcode_num;

    am_mb_event_t            event;     /**< \brief Master event */

    const am_mb_m_netif_t     *p_netif;   /**< \brief net interface */

    uint32_t ack_timeout;  /**< \brief master wait ack timeout */
    uint32_t bd_delay;     /**< \brief rtu/ascii broadcast delay time */

} am_mb_master_serv_t;

/** \brief Modbus ��վ��� */
typedef am_mb_master_serv_t *am_mb_master_handle;

/** \brief Modbus ��վ�豸 */
typedef struct am_mb_master_dev {
    /** \brief modbus master service */
    am_mb_master_serv_t mb_master_serv;

    union mode {
#if AM_MB_MASTER_RTU_ENABLE
        am_mb_m_rtu_t   mbm_rtu;     /**< \brief RTU mode private data */
#endif

#if AM_MB_MASTER_ASCII_ENABLE
        am_mb_m_ascii_t mbm_ascii;   /**< \brief ASCII mode private data */
#endif

#if AM_MB_MASTER_HANDLECP_ENABLE
        am_mb_m_tcp_t   mbm_tcp;     /**< \brief TCP mode private data */
#endif
    } common;

} am_mb_master_dev_t;

typedef struct am_mb_master_info {
    aw_mb_timer_info_t  timer;  /**< \brief ��ʱ���豸��Ϣ */
    am_mb_serial_info_t serial; /**< \brief ������·�豸��Ϣ */

    enum am_mb_mode     mode;   /**< \brief ��վ����ģʽ */
} am_mb_master_info_t;
/******************************************************************************/

/**
 * \brief ����Modbus��վ����
 *
 * @note �ڵ���������վ����֮ǰ�������ȵ��øú���.
 * @note TCPģʽ�£�����ͬһ��վ�����в�����ͬһ���߳���.�û���ʹ�øýӿڽ����������.
 *
 * @brief p_m_dev  Modbus��վ�豸
 *
 * @return Modbus��վ���������������󷵻�NULL
 */
am_mb_master_handle am_mb_master_create (am_mb_master_dev_t *p_dev);

/**
 * \brief ����Modbus��վ
 *
 * @note �ýӿڱ�������վֹͣ��δ�����µ���.
 *
 * @param[in] master           : Modbus��վ���
 * @param[in] p_dev_handle     �� ���������紮���豸���
 * @param[in] p_params         : ���ò�����
 *                               ����AM_MB_RTU/AM_MB_ASCIIģʽ��
 *                               ʹ��am_mb_master_serial_params_t��Ϊ����;
 *                               ����AM_MB_TCPģʽ,
 *                               ʹ��am_mb_tcp_client_params��Ϊ����.
 *                               ���û������������ò������ò����ɴ���NULL����.
 * @retval: AM_MB_ERR_NOERR    : ��վ���óɹ�.
 * @retval: AM_MB_ERR_EINVAL   : ��������.
 * @retval: AM_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬.
 * @retval: AM_MB_ERR_EIO      : �������ó���.
 */
am_mb_err_t am_mb_master_config (am_mb_master_handle        master,
                                 const am_mb_master_info_t *p_info);

/**
 * \brief �رա�ɾ����վ
 * @note  �˳�ϵͳ���߲���Ҫ��ʹ����վʱ����
 *
 * @param[in] master : Modbus��վ���
 *
 * @return ���û�д��󷵻�AM_MB_ERR_NOERR
 */
am_mb_err_t am_mb_master_delete (am_mb_master_handle master);

/**
 * \brief ����Modbus��վ
 *
 * @param[in] master           : Modbus��վ���
 *
 * @retval: AM_MB_ERR_NOERR    : ��վ�����ɹ�
 * @retval: AM_MB_ERR_EINVAL   : ��������
 * @retval: AM_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬
 * @retval: AM_MB_ERR_EIO      : TCPģʽ�£����ӽ���ʧ��.
 * @retval: AM_MB_ERR_ETIMEDOUT: TCPģʽ�£����ӳ�ʱ
 */
am_mb_err_t am_mb_master_start (am_mb_master_handle master);

/**
 * \brief ֹͣModbus��վ
 *
 * @note ���øýӿڽ�����ֹͣ���䣻
 *
 * @param[in] master           : Modbus��վ���
 *
 * @retval: AM_MB_ERR_NOERR    : ��վֹͣ�ɹ�
 * @retval: AM_MB_ERR_EINVAL   : ��������
 * @retval: AM_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬
 * @retval: AM_MB_ERR_EIO      : IO����
 */
am_mb_err_t am_mb_master_stop (am_mb_master_handle master);

/** \brief ��վ��д���� */
typedef struct am_mb_master_rw_param {
     uint16_t  rd_addr;     /**< \brief ����ʼ��ַ  */
     uint16_t  rd_num;      /**< \brief ����Ŀ            */
     uint16_t *p_rd_buf;    /**< \brief ������            */
     uint16_t  wr_addr;     /**< \brief д��ʼ��ַ  */
     uint16_t  wr_num;      /**< \brief д��Ŀ            */
     uint16_t *p_wr_buf;    /**< \brief д����            */
} am_mb_master_rw_param_t;

/**
 * \brief ��վ����
 * @note  �ýӿ�����վ������������ɵ���.
 * @note  �ýӿ�Ϊͬ�������ӿ�.
 * @note  ��վ����ʱʱ�䣬ͨ���ӿ� am_mb_master_ack_timeout_set ����
 *
 * @note
 * @param[in] master       : Modbus��վ���
 * @param[in] slave_addr   : �����Ŀ��ӻ���ַ
 * @param[in] funcode      : ������
 * @param[in][out] p_param : ��д����;
 *                           ��ΪЭ��ջ֧�ֹ����룬
 *                           �ò���Ϊam_mb_master_rw_param_t����;
 *                           ��Ϊ�û��Զ��幦���룬�ò������û��Զ��塣
 *
 * @return ���û�д��󷵻�AM_MB_ERR_NOERR��������ʧ�ܣ��ɲ鿴����������͡�
 *
 */
am_mb_err_t am_mb_master_request (am_mb_master_handle master,
                                  uint8_t        slave_addr,
                                  uint8_t        funcode,
                                  void          *p_params);

/**
 * \brief ע���Զ��幦���봦��ӿڵ�ָ����վ.
 * @note  ���� ��վ�󣬿�ע���û��Զ��幦���봦��ӿڡ�
 * @note  �ýӿڽ������봦��ӿ�ע��ɹ��󣬿�ʹ��am_mb_master_request�ӿ�������
 * @note  �û������¶���Э��ջĬ�Ϲ����봦��ӿڡ����û����ע��ͬһ�����봦��ӿڣ�
 *        ��ʹ�����ע��Ĺ����봦��ӿڡ�
 * @note  ����ע��Ĺ����봦����������am_mb_config.h��
 *        AM_MB_MASTER_FUNCODE_HANDLER_MAX���壬�����ø������޷���ע�ᡣ
 *
 * @param[in] master      : ��վ���
 * @param[in] funcode     : �������
 * @param[in] snd_handler : ���ʹ�����
 * @param[in] rcv_handler : ���մ���������Ϊд�������û����账�����PDU���ݣ�
 *                          �ɽ��˽ӿ���NULL��
 * @return ע��ɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������.
 *
 * \code
 * #include "am_mb_master.h"
 *
 * #define MB_MASK_WRITE_REG_FUNCODE  22
 * struct wr_mask_param {
 *     uint16_t addr;
 *     uint16_t and_mask;
 *     uint16_t or_mask;
 * } my_mask_param;
 *
 * am_mb_err_t __mb_snd_mask_handler (void    *p_params,
 *                                    uint8_t *p_pdudata,
 *                                    uint8_t *pdudata_len)
 * {
 *     struct wr_mask_param *p_mask_param = (struct wr_mask_param *)p_params;
 *
 *     p_pdudata[0] = (uint8_t)(p_mask_param->addr >> 8);
 *     p_pdudata[1] = (uint8_t)(p_mask_param->addr);
 *     p_pdudata[2] = (uint8_t)(p_mask_param->and_mask >> 8);
 *     p_pdudata[3] = (uint8_t)(p_mask_param->and_mask);
 *     p_pdudata[4] = (uint8_t)(p_mask_param->or_mask >> 8);
 *     p_pdudata[5] = (uint8_t)(p_mask_param->or_mask);
 *
 *     *pdudata_len = 6;
 *
 *     return AM_MB_ERR_NOERR;
 * }
 *     //ע��д�Ĵ������빦���봦����
 *     am_mb_master_funcode_register(master,
 *                                   MB_MASK_WRITE_REG_FUNCODE,
 *                                   __mb_snd_mask_handler,
 *                                   NULL);
 *     //д�Ĵ�������
 *     my_mask_param.addr     = 1000;
 *     my_mask_param.and_mask = 0x01;
 *     my_mask_param.or_mask  = 0;
 *     am_mb_master_request(master,
 *                          SLAVE_ADDR,
 *                          MB_MASK_WRITE_REG_FUNCODE,
 *                          &my_mask_param);
 * \endcode
 */
am_mb_err_t am_mb_master_funcode_register ( \
                                    am_mb_master_handle         master,
                                    uint8_t                     funcode,
                                    am_mb_snd_funcode_handler_t snd_handler,
                                    am_mb_rcv_funcode_handler_t rcv_handler);

/** \brief ��վ�������Ͷ���  */
typedef int am_mbm_cfg_type_t;
#define AM_MBM_TYPE_USE_HW_TIMER      0x01    /**< \brief ʹ��Ӳ����ʱ�� */
#define AM_MBM_TYPE_BOARDCAST_DELAY   0x02    /**< \brief �㲥��ʱʱ��, p_argΪ�㲥��ʱʱ��(ms)(uint32_t)   */
#define AM_MBM_TYPE_UID_AS_ADDR       0x03    /**< \brief TCPģʽUID��Ϊ��վ��ַ, p_argΪ�Ƿ���Ϊ��վ��ַ(bool_t)   */
#define AM_MBM_TYPE_TCP_CONTMOUT      0x04    /**< \brief TCPģʽ���ӳ�ʱʱ�䣬 p_argΪ��ʱʱ�䣨ms��(uint32_t)   */
#define AM_MBM_TYPE_ACK_TIMEOUT_SET   0x05    /**< \brief ����Ӧ��ʱ�����ã� p_argΪ��ʱʱ�䣨ms��(uint32_t)   */
#define AM_MBM_TYPE_ACK_TIMEOUT_GET   0x06    /**< \brief ����Ӧ��ʱ���ȡ�� p_argΪ��ʱʱ�䣨ms��(uint32_t *)   */

/**
 * \brief ��վ��������
 * @note  ���޵��øýӿڣ������ò�������am_mb_config.h�в�������.
 * @note  �ýӿ�����վ����ǰ����.
 *
 * @param[in] master : ��վ���
 * @param[in] type   : ��������:
 *                     - AM_MBM_TYPE_USER_FUNCODE   : �����Զ��幦��������Ĭ�ϲ�����Ϊ��������
 *                                                   Ϊ#AM_MB_MASTER_FUNCODE_HANDLER_MAX
 *                     - AM_MBM_TYPE_BOARDCAST_DELAY: �㲥��ʱʱ�䣬
 *                                                   Ĭ�ϲ�������ʱʱ��Ϊ#AM_MB_MASTER_DELAY_MS_CONVERT
 *                     - AM_MBM_TYPE_UID_AS_ADDR    : TCPģʽUID��Ϊ��վ��ַ����, Ĭ�ϲ���Ϊ��վ��ַ
 *                     - AM_MBM_TYPE_TCP_CONTMOUT   : TCPģʽ���ӳ�ʱʱ�䣬Ĭ�ϳ�ʱʱ��Ϊ#AM_MB_TCP_CONNECT_TIMEOUT
 *                     - AM_MBM_TYPE_ACK_TIMEOUT_SET: ����Ӧ��ʱ�����ã� Ĭ��ʱ��Ϊ#am_mb_master_handleIMEOUT_MS_RESPOND
 *                                                   ��ӿ�am_mb_master_ack_timeout_set����һ��
 *                     - AM_MBM_TYPE_ACK_TIMEOUT_GET: ����Ӧ��ʱ���ȡ����ӿ�am_mb_master_ack_timeout_get����һ��
 * @param[in] p_arg  : �������Ͳ���
 * @return ���óɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������.
 */
am_mb_err_t am_mb_master_ioctl (am_mb_master_handle    master,
                                am_mbm_cfg_type_t      type,
                                void                  *p_arg);

/**
 * \brief ��������Ӧ��ʱʱ��
 *
 * @param[in]      master      : ��վ���
 * @param[in]      timeout     : Ӧ��ʱʱ�䣨���룩, ȡֵ��Χ50 ~ 100000ms
 *
 * @retval AM_MB_ERR_EINVAL    : ��������
 */
am_mb_err_t am_mb_master_ack_timeout_set (am_mb_master_handle master,
                                          uint32_t       timeout);

/**
 * \brief ��ȡ����Ӧ��ʱʱ��
 *
 * @param[in]      master      : ��վ���
 *
 * @return Ӧ��ʱʱ���ȡ�� ����0Ϊ�����������
 */
uint32_t am_mb_master_ack_timeout_get (am_mb_master_handle master);

/**
 * \brief ��ǰ�����Ƿ�Ϊ�㲥����
 *
 * @param[in] p_master : ��վ�豸
 * @retval TRUE  : ����Ϊ�㲥����
 * @retval FALSE : ����ǹ㲥����
 */
am_static_inline am_bool_t am_mb_m_is_broadcast (am_mb_master_handle p_master)
{
    return p_master->slave_addr == AM_MB_ADDRESS_BROADCAST ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ��ȡ�����봦��ӿ�
 *
 * @param[in] p_master : ��վ�豸
 * @param[in] funcode  : ������
 * @return ������Ӧ�����봦��ӿڣ����޸ù����봦��ӿڣ�����NULL.
 */
const am_mb_m_funcode_handler_t *am_mb_m_funcode_handler_get (
                                         am_mb_master_handle p_master,
                                         uint8_t             funcode);
/**
 * \brief ��ȡӦ��ʱʱ���ȡ
 *
 * @param[in] p_master : ��վ�豸
 * @return    ��ʱʱ��
 */
am_static_inline uint32_t am_mb_m_ack_timeout_get (am_mb_master_handle p_master)
{
    return p_master->ack_timeout;
}


/**
 * \brief ��ȡ�㲥�ӳٻ�ȡ
 *
 * @param[in] p_master : ��վ�豸
 * @return    ��ʱʱ��
 */
am_static_inline uint32_t am_mb_master_broadcast_delay_get (
                                        am_mb_master_handle p_master)
{
    return p_master->bd_delay;
}

#if am_mb_master_handleCP_ENABLE
/**
 * \brief TCP��վ�������Ӻ���ԭ��
 * @note  �ù��Ӻ�������am_mb_master_start����ʱִ��.
 *
 * @param[in] p_arg  : �û��Զ������
 * @param[in] socket : ����socket
 *
 * @return ��������������AM_MB_ERR_NOERR.
 */
typedef am_mb_err_t (*am_mb_master_handlecp_hook_t) (void *p_arg, int socket);

/**
 * \brief TCPģʽsocket���ӹ��Ӻ���ע��
 *
 * @param[in] master   : ��վ���
 * @param[in] tcp_hook : ���Ӻ���
 * @param[in] p_arg    : ���Ӻ�������
 *
 * @retval AM_MB_ERR_NOERR     : ע��ɹ���
 * @retval AM_MB_ERR_EINVAL    : ��������
 * @retval AM_MB_ERR_EILLSTATE : Э��ջ�Ƿ�״̬
 */
am_mb_err_t am_mb_master_handlecp_hook_register (am_mb_master_handle          master,
                                            am_mb_master_handlecp_hook_t tcp_hook,
                                            void                   *p_arg);

/**
 * \brief TCPģʽ�Ƿ񽫵�ַ��ΪUID
 *
 * @param[in] p_master : ��վ�豸
 * @return    ��ʱʱ��
 */
am_static_inline bool_t am_mbm_is_uid_as_addr (am_mb_m_dev_t *p_master)
{
    return p_master->uid_as_addr;
}

/**
 * \brief ��ȡTCPģʽ��ʱʱ���ȡ
 *
 * @param[in] p_master : ��վ�豸
 * @return    ��ʱʱ��
 */
am_static_inline uint32_t am_mb_tcp_contm_get (am_mb_m_dev_t *p_master)
{
    return p_master->tcp_contm;
}
#endif

/**
 * \brief �����û�������
 *
 * @param[in] p_master : ��վ�豸
 * @param[in] num      : �û���������
 * @return ���޴��󷵻�AM_MB_ERR_NOERR
 */
am_mb_err_t am_mb_master_user_funcode_alloc (am_mb_master_handle        master,
                                             am_mb_m_funcode_handler_t *p_buf,
                                             uint8_t                    num);

/*****************************************************************************
 * Common Function's Code Interface(��������������ӿ�)
 *****************************************************************************/
/**
 * \brief ����Ȧ����
 * @note ������[0x01]
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��Ȧ��ʼ��ַ
 * @param[in] quantity      : ��Ȧ��, ȡֵ��Χ1~2000
 * @param[in][out] p_rd_val : ��ȡ��Ȧֵ
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_coils_read (am_mb_master_handle master,
                              uint8_t             slave_addr,
                              uint16_t            start_addr,
                              uint16_t            quantity,
                              uint8_t            *p_rd_val);

/**
 * \brief ����ɢ������
 * @note ������[0x02]
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��ɢ��������ʼ��ַ
 * @param[in] quantity      : ��ɢ����ȡ����, ȡֵ��Χ1~2000
 * @param[in][out] p_rd_val : ��ȡ��ɢ��ֵ
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_discrete_inputs_read (am_mb_master_handle master,
                                        uint8_t             slave_addr,
                                        uint16_t            start_addr,
                                        uint16_t            quantity,
                                        uint8_t            *p_rd_val);

/**
 * \brief �����ּĴ�������
 * @note ������[0x03]
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��ʼ��ַ
 * @param[in] quantity      : ��ȡ���ּĴ���������ȡֵ��Χ1~125
 * @param[in][out] p_rd_val : ��ȡ���ּĴ���ֵ
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_holding_reg_read (am_mb_master_handle master,
                                    uint8_t             slave_addr,
                                    uint16_t            start_addr,
                                    uint16_t            quantity,
                                    uint16_t           *p_rd_val);

/**
 * \brief ������Ĵ�������
 * @note ������[0x04]
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��ʼ��ַ
 * @param[in] quantity      : ��ȡ����Ĵ���������ȡֵ��Χ1~125
 * @param[in][out] p_rd_val : ��ȡ����Ĵ���ֵ
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_input_reg_read (am_mb_master_handle master,
                                  uint8_t             slave_addr,
                                  uint16_t            start_addr,
                                  uint16_t            quantity,
                                  uint16_t           *p_rd_val);

/**
 * \brief д������Ȧ����
 * @note ������[0x05]
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] coil_addr  : д��Ȧ��ַ
 * @param[in] coil_val   : д��Ȧֵ��ֵΪ0x0000(COIL OFF)�� 0xFF00(COIL ON).
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_single_coil_write (am_mb_master_handle master,
                                     uint8_t             slave_addr,
                                     uint16_t            coil_addr,
                                     uint16_t            coil_val);

/**
 * \brief д�����Ĵ�������
 * @note ������[0x06]
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] reg_addr   : д�Ĵ�����ַ
 * @param[in] reg_val    : д��Ĵ���ֵ
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_single_reg_write (am_mb_master_handle master,
                                    uint8_t             slave_addr,
                                    uint16_t            reg_addr,
                                    uint16_t            reg_val);

/**
 * \brief д�����Ȧ����
 * @note ������[0x0F]
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] start_addr : д��Ȧ��ʼ��ַ
 * @param[in] quantity   : д��Ȧ������0x01~0x7b0��
 * @param[in] p_wr_buf   : д��Ȧֵ(������)
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_multiple_coils_write (am_mb_master_handle master,
                                        uint8_t             slave_addr,
                                        uint16_t            start_addr,
                                        uint16_t            quantity,
                                        uint8_t            *p_wr_buf);

/**
 * \brief д����Ĵ�������
 * @note ������[0x10]
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] start_addr : д�Ĵ�����ʼ��ַ
 * @param[in] quantity   : д�Ĵ�������
 * @param[in] p_wr_buf   : д�Ĵ���ֵ(������)
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_multiple_regs_write (am_mb_master_handle master,
                                       uint8_t             slave_addr,
                                       uint16_t            start_addr,
                                       uint16_t            quantity,
                                       uint16_t           *p_wr_buf);

/**
 * \brief ��д����Ĵ�������
 * @note ������[0x17]
 *
 * @param[in]      master     : ��վ���
 * @param[in]      slave_addr : Ŀ��ӻ���ַ
 * @param[in][out] p_rw_param : ��д����
 *
 * @return ִ�гɹ�����AM_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
am_mb_err_t am_mb_multiple_regs_read_write ( \
                                        am_mb_master_handle      master,
                                        uint8_t                  slave_addr,
                                        am_mb_master_rw_param_t *p_rw_param);
/*****************************************************************************/


#ifdef __cplusplus
}
#endif

/** @} grp_am_if_mb_master */

#endif /* } __AM_MB_MASTER_H */

/* end of file */

