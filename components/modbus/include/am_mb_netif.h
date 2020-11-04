/*******************************************************************************
*                                 AWORKS
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief modbus netif header file
 *
 * \internal
 * \par modification history
 * - 1.00 2017-03-29  mkr, first implementation
 * \endinternal
 */

#ifndef __AM_MB_NETIF_H /* { */
#define __AM_MB_NETIF_H

/**
 * \addtogroup grp_am_if_mb_netif
 * \copydoc am_mb_netif.h
 * @{
 */

#include "am_mb_port.h"
#include "am_mb_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief pdu data buffer */
#if AM_MB_SER_PDU_RECV_BUF_ENABLE
#define __AM_MB_SER_ADU_BUF_MAX      2
#else
#define __AM_MB_SER_ADU_BUF_MAX      1
#endif

/** \brief receive pdu data deal with state */
enum am_mb_pdu_proc_state {
    AM_STATA_PDU_NO_PROCESS,
    AM_STATE_PDU_IN_PROCESS,
};
/******************************************************************************
 * RTUģʽ˽������
 ******************************************************************************/
/** \brief state of rtu recv */
enum am_mb_rtu_recv_state {
    AM_RTU_STATE_RX_INIT,
    AM_RTU_STATE_RX_IDLE,
    AM_RTU_STATE_RX_RCV,
    AM_RTU_STATE_RX_ERROR,
};

/** \brief state of rtu send */
enum am_mb_rtu_send_state {
    AM_RTU_STATE_TX_IDLE,
    AM_RTU_STATE_TX_XMIT,
};

/** RTU˽������  */
struct am_mb_rtu {
    enum am_mb_rtu_recv_state recv_state; /**< \brief recv state */
    enum am_mb_rtu_send_state send_state; /**< \brief send state */

#if AM_MB_SER_PDU_RECV_BUF_ENABLE > 0
    /** \brief recive PDU data state */
    enum am_mb_pdu_proc_state pdu_state;

    /** \brief PDU buffer in process data postion*/
    uint8_t  pdu_buf_proc_pos;
#endif

    uint8_t  slave_addr;   /**< \brief slave address */
    uint8_t  pdu_buf_pos;  /**< \brief recive PDU data buffer postion */
    uint16_t snd_data_len; /**< \brief send data length */
    uint8_t *snd_data;     /**< \brief send data buffer */

    /** \brief pdu buffer */
    uint8_t  pdu_buf[__AM_MB_SER_ADU_BUF_MAX][AM_MB_MAX_SER_ADU_LENGTH];
    /** \brief recv data count  */
    uint16_t rcv_data_pos[__AM_MB_SER_ADU_BUF_MAX];

    /** \brief �����վ�¼��ӿڣ��ϱ��ϲ�  */
    am_mb_event_t   *p_event;

    /** \brief ������Ϣ  */
    am_mb_serial_t   serial;

    /** \brief ��ʱ����Ϣ  */
    am_mb_timer_t    timer;
};
/******************************************************************************
 * ASCIIģʽ˽������
 ******************************************************************************/
/** \brief state of ASCII receive */
enum am_mb_ascii_recv_state {
    AM_ASCII_STATE_RX_IDLE,      /**< \brief Receiver is in idle state. */
    AM_ASCII_STATE_RX_RCV_ADDR,  /**< \brief recevier the slave addr state */
    AM_ASCII_STATE_RX_RCV,       /**< \brief Frame is beeing received. */
    AM_ASCII_STATE_RX_WAIT_EOF,  /**< \brief Wait for End of Frame. */
    AM_ASCII_STATE_RX_ERR,       /**< \brief Error occur, aband this frame */
};

/** \brief state of ASCII send */
enum am_mb_ascii_send_state {
    AM_ASCII_STATE_TX_IDLE,      /**< \brief Transmitter is in idle state. */
    AM_ASCII_STATE_TX_START,     /**< \brief Starting transmission (':' sent). */
    AM_ASCII_STATE_TX_DATA,      /**< \brief Sending of data (Address, Data, LRC). */
    AM_ASCII_STATE_TX_END,       /**< \brief End of transmission. */
    AM_ASCII_STATE_TX_NOTIFY     /**< \brief Notify sender that the frame has been sent. */
};

/** \brief ASCII��ߵ��ֽڱ�־  */
enum am_mb_byte_pos {
    AM_BYTE_HIGH_NIBBLE,   /**< \brief Character for high nibble of byte. */
    AM_BYTE_LOW_NIBBLE     /**< \brief Character for low nibble of byte. */
};

/** ASCII˽������  */
struct am_mb_ascii {
    enum am_mb_ascii_recv_state recv_state;  /**< \brief recv state */
    enum am_mb_ascii_send_state send_state;  /**< \brief send state */

#if AM_MB_SER_PDU_RECV_BUF_ENABLE > 0
    /** \brief recive pdu data state */
    enum am_mb_pdu_proc_state pdu_state;

    /** \bref pdu buffer in process data postion*/
    uint8_t  pdu_buf_proc_pos;
#endif
    uint8_t  slave_addr;    /**< \brief slave address  */
    uint8_t  high_nibble;   /**< \brief =1 high nibble  =0 low nibble  */
    uint8_t  recv_byte;     /**< \brief the number of bytes recived */
    uint8_t  pdu_buf_pos;   /**< \brief recive pdu data buffer postion */
    uint16_t snd_data_len;  /**< \brief send data length */
    uint8_t *snd_data;      /**< \brief send data buffer */

    /** \brief recv data count  */
    uint16_t rev_data_pos[__AM_MB_SER_ADU_BUF_MAX];

    /** \brief pdu buffer */
    uint8_t  pdu_buffer[__AM_MB_SER_ADU_BUF_MAX][AM_MB_MAX_SER_ADU_LENGTH];

    /** \brief �����վ�¼��ӿڣ��ϱ��ϲ�  */
    am_mb_event_t   *p_event;

    /** \brief ������Ϣ  */
    am_mb_serial_t   serial;

    /** \brief ��ʱ����Ϣ  */
    am_mb_timer_t    timer;
};

/******************************************************************************
 * TCPģʽ˽������
 ******************************************************************************/
#if AM_MB_TCP_ENABLE

/**
 * \brief ��վTCPģʽ���������ӹ��Ӻ���ԭ��
 * @note  ����˽������ӵ��øù��Ӻ���.
 *
 * @param[in] p_arg  : �û��Զ������
 * @param[in] p_info : ���յ�������Ϣ
 *
 * @retval TRUE  : ������ո�����
 * @retval FALSE : �ܾ����ո�����
 */
typedef bool_t (*am_mb_tcp_accept_hook_t) (void                        *p_arg,
                                           struct am_mb_slave_tcp_info *p_info);

/**
 * \brief ��վTCPģʽ�����ӶϿ����Ӻ���
 * @note  �ѽ��յ������쳣�Ͽ���
 *        �����Ӵﵽ����ֵ��������Ϊ�ﵽ����ֵ���������������ʱ�������Ͽ�ʱ���øù��Ӻ���
 *
 * @param[in] p_arg  : �û��Զ������
 * @param[in] socket : �Ͽ����ӵ�socket
 *
 */
typedef void (*am_mb_tcp_close_hook_t) (void *p_arg, int socket);

struct am_mb_tcp {
    uint8_t         tcp_buf[AM_MB_MAX_TCP_ADU_LENGTH];   /**< \brief TCP���ݻ��� */
    uint16_t        tcp_buf_pos;                         /**< \brief ���������ݵ�ǰλ�� */
    uint16_t        tcp_frame_bytesleft;                 /**< \brief ��Ҫ�������ݳ��� */
    uint16_t        port;                                /**< \brief �˿ں� */
    am_mbs_event_t *p_event;                             /**< \brief �����վ�¼��ӿڣ��ϱ��ϲ�  */
    bool_t          is_accept_new;                       /**< \brief ���Ӵﵽ����ֵ���Ƿ������������������ */

    int             listen_socket;                       /**< \brief ����socket */
    int             cur_socket;                          /**< \brief ��ǰ����socket���  */
    int             socket_num;                          /**< \brief ���������ӵ�socket��  */
    int             accept_num;                          /**< \brief ��ǰ������  */
    int            *p_sockets;                           /**< \brief socket��  */

    am_mb_tcp_accept_hook_t accept_hook;         /**< \brief TCP�������ӹ��Ӻ���  */
    am_mb_tcp_close_hook_t  close_hook;          /**< \brief TCP�ر����ӹ��Ӻ���  */
    void                   *p_arg;               /**< \brief TCP���ӹ��Ӻ�������  */

};
#endif
/******************************************************************************
 * ��վ����
 ******************************************************************************/
/** slave status type */
enum am_mb_slave_status {
    AM_STATE_UNUSE,
    AM_STATE_INIT,
    AM_STATE_DISABLE,
    AM_STATE_ENABLE,
};

/** data-link common interface */
struct am_mb_netif {
    /** \brief ��ȡ��վ��ַ */
    uint8_t     (*slave_addr_get)(void *p_cookie);
    /** \brief ���ô�վ��ַ */
    am_mb_err_t (*slave_addr_set)(void *p_cookie, uint8_t addr);
    /** \brief ��ʼ��Modbus��վ */
    am_mb_err_t (*init)(void           *p_cookie, const void *p_param,
                        am_mb_event_t  *p_ev);
    /** \brief �ر�Modbus��վ */
    void        (*close)(void *p_cookie);
    /** \brief ����Modbus��վ */
    void        (*start)(void *p_cookie);
    /** \brief ֹͣModbus��վ */
    void        (*stop) (void *p_cookie);
    /** \brief ��վ�������� */
    am_mb_err_t (*recv) (void      *p_cookie,
                         uint8_t   *slave_addr,
                         uint8_t  **pp_pdu,
                         uint16_t  *p_len);
    /** \brief ��վ�������� */
    am_mb_err_t (*send) (void *p_cookie, uint8_t *p_pud, uint16_t len);
};
/******************************************************************************/
#if AM_MB_TCP_ENABLE
/**
 * \brief ����TCP������
 *
 * @param[in] p_cookie : TCP���
 * @param[in] tcp_num  : ����������
 *
 * @return    p_err   ����ţ����û�д�����ֵΪam_MB_ERR_NOERR
 */
am_mb_err_t am_mb_netif_tcp_num_set (void *p_cookie, uint16_t tcp_num);

/**
 * \brief ��ȡ�ѽ�����������
 *
 * @param[in] p_cookie : Modbus TCP�豸���
 * @return �ѽ��յ�������
 */
am_static_inline uint16_t am_mb_netif_tcp_num_get (void *p_cookie)
{
    return ((struct am_mb_tcp *)p_cookie)->accept_num;
}

/**
 * \brief �Ƿ���������������رվ����ӣ�����������
 *
 * @param[in] p_cookie : Modbus TCP�豸���
 * @param[in] is_allow : �Ƿ�����.
 */
void am_mb_netif_allow_new_tcp (void *p_cookie, bool_t is_allow);

/**
 * \brief TCP���Ӻ���ע��
 * @param[in]
 * @param[in] accept_hook : �������ӹ��Ӻ���
 * @param[in] close_hook  : �Ͽ����ӹ��Ӻ���
 * @param[in] p_arg       : ���Ӻ�������
 */
void am_mb_netif_tcp_hook_register (void                    *p_cookie,
                                    am_mb_tcp_accept_hook_t  accept_hook,
                                    am_mb_tcp_close_hook_t   close_hook,
                                    void                    *p_arg);
#endif

#ifdef __cplusplus
}
#endif

/* @} grp_am_if_mb_netif */

#endif /* } __AM_MB_NETIF_H */

/* end of file */
