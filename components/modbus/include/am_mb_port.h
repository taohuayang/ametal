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
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief Modbus Port interface from AWorks.
 *
 * \internal
 * \par modification history
 * - 1.00 2017-03-29  mkr, first implementation
 * - 1.01 2017-12-20  mkr, adding 'AM_MB_EVENT_SENDING' status
 *                         when sending data for asyn.
 * \endinternal
 */
#ifndef __AW_MB_PORT_H  /* { */
#define __AW_MB_PORT_H

/**
 * \addtogroup grp_am_if_mb_port
 * \copydoc am_mb_port.h
 * @{
 */

#include "am_mb_compiler.h"
#include "am_mb_err.h"
#include "am_mb_comm.h"
#include "am_timer.h"
#include "am_softimer.h"
#include "am_int.h"
#include "am_wait.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum am_mb_ev_type {
    AM_MB_EVENT_INIT,        /**< �¼���ʼ��                */
    AM_MB_EVENT_READY,       /**< ��ʼ������¼�        */
    AM_MB_EVENT_RECEIVED,    /**< ���յ�һ֡�����¼�     */
    AM_MB_EVENT_SENDING,     /**< ���ڷ��� */
    AM_MB_EVENT_SEND_OUT,    /**< ����֡��������¼� */
    AM_MB_EVENT_STOP,        /**< ֹͣ�¼� */
    AM_MB_EVENT_TIMEOUT      /**< ��ʱ�¼� */
} am_mb_event_type_t;

typedef struct am_mb_event {
    am_wait_t          ev_wait;  /**< \brief Wait Event */
    am_mb_event_type_t ev_type;  /**< \brief Event Type */
} am_mb_event_t;

/**
 * \brief     ��ʼ���¼��ӿ�
 *
 * @return  ���û�д��󷵻�MB_ERR_NOERR
 *
 */
am_mb_err_t am_mb_event_init(am_mb_event_t *p_event, am_mb_event_type_t event);

/**
 * \brief �����¼��ӿ�
 *
 * @param[in] p_event   : �¼����
 * @param[in] event_val : ���͵��¼�
 * @return ���û�д��󷵻�MB_ERR_NOERR
 */
am_mb_err_t am_mb_event_post(am_mb_event_t     *p_event,
                             am_mb_event_type_t event);

/**
 * \brief ��ѯ�¼��ӿ�.
 *              ���ڻ�ȡ�¼�
 * @param[in]      p_event     : �¼����
 * @param[in][out] p_event_val : ��ȡ�¼�����
 * @param[in]      is_noblock  �� �Ƿ�����
 *
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
am_mb_err_t am_mb_event_get (am_mb_event_t      *p_event,
                             am_mb_event_type_t *p_event_val,
                             am_bool_t           is_noblock);

/**
 * \brief ��ѯ�¼��ӿ�(������)
 *            ���ڻ�ȡ�¼�
 * @param[in]      p_event     : �¼����
 * @param[in][out] p_event_val : ��ȡ�¼�����
 *
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
am_mb_err_t am_mb_event_noblock_get (am_mb_event_t      *p_event,
                                     am_mb_event_type_t *p_event_val);

/**
 * \brief �¼�ɾ��
 *
 * @param[in]  p_event : �¼����
 *
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
am_mb_err_t am_mb_event_delete (am_mb_event_t *p_event);

/*****************************************************************************/
/** ���ڽ���/����״̬ */
enum am_mb_serial_rxtx_status {
    AM_SER_RXTX_DISABLE,   /**< \brief ��ֹ����/���� */
    AM_SER_RXTX_ENABLE,    /**< \brief ʹ�ܽ���/����  */
};

typedef struct am_mb_serial {
    const void         *p_hdl;    /**< \brief serial handle.֮������void *����Ϊ�����豸�����л��λ�����ģʽ��һ����ж�ģʽ */
    am_bool_t           rx_en;    /**< \brief rx enable. */
    am_bool_t           tx_en;    /**< \brief tx enable. */
    uint8_t             tx_char;  /**< \brief tx char. */
    uint8_t             rx_char;  /**< \brief rx char. */

    void (*tx_int_callback) (void *p_arg); /**< \brief tx interrupt callback.*/
    void (*rx_int_callback) (void *p_arg); /**< \brief rx interrupt callback.*/
    void  *p_arg;                          /**< \brief rx and tx int arg. */

} am_mb_serial_t;

/** \brief ������·�豸��Ϣ */
typedef struct am_mb_serial_info {
    am_uart_handle_t  uart;     /**< \brief �����豸��� */
    uint32_t          baudrate; /**< \brief ������ */
    enum am_mb_parity parity;   /**< \brief У�� */
    am_bool_t         rs485_en; /**< \brief RS485ʹ�� */
} am_mb_serial_info_t;


/**
 * \brief ��ʼ������.
 *           �����򿪴��ں����ô��ڵ�
 *
 * @param[in] p_serial  : Modbus�����豸
 * @param[in] p_hdl     : Ametal�����豸���ֵ
 * @param[in] dataBits  : ����λ����(7bits or 8bits)
 * @param[in] baud_rate : ������
 * @param[in] parity    �� ��żУ��ģʽ
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR�����򷵻�AW_MB_ERR_EPORTERR
 */
am_mb_err_t am_mb_serial_port_init (am_mb_serial_t            *p_serial,
                                    uint8_t                    databits,
                                    const am_mb_serial_info_t *p_serial_info);

/**
 * \brief ���ô��ڵĽ��պͷ��͹���״̬.
 * �����ֹ���չ��ܣ������жϱ���Ϊ��ʹ�ܲ��Ҳ��ܽӽ������ݡ�
 * @note ���ʹ�ܷ��͹��ܣ�������ʹ��ʱ����aw_mb_send_int_callback�����������жϡ�
 *
 * @param[in] recvStatu ʹ�ܻ��ֹ���չ���
 * @param[in] sndStatus ʹ�ܻ��ֹ���͹���
 */
void am_mb_serial_port_set_rxtx_status (am_mb_serial_t  *p_serial,
                                        am_bool_t        recv_en,
                                        am_bool_t        send_en);

/**
 * \brief �رմ���
 *
 * @param[in] p_serial : ���ھ��
 */
void am_mb_serial_port_close (am_mb_serial_t *p_serial, am_bool_t is_master);

/**
 * \brief �Ӵ��ڶ�ȡһ���ֽ�����
 * @note  �ú�������Ϊ�������ģ����ڴ����жϴ�������ͨ��aw_mb_recv_int_callback����
 *
 * @param[in]  p_serial : ���ھ��
 * @param[out] p_data   : ��ȡ���ݻ���
 */
void am_mb_serial_port_getchar (am_mb_serial_t *p_serial, uint8_t *p_data);

/**
 * \brief ����һ���ֽ����ݵ�����
 * @note  �ú�������Ϊ�������ģ����ڴ����жϴ�������ͨ��aw_mb_send_int_callback����
 *
 * @param[in] p_serial : ���ھ��
 * @param[in] data     : Ҫ���͵�����
 */
void am_mb_serial_port_putchar (am_mb_serial_t *p_serial, uint8_t data);
/*****************************************************************************/
typedef struct aw_mb_timer {

    am_softimer_t     sf_tmr;      /**< \brief software timer handler */
    am_timer_handle_t hw_tmr;      /**< \brief hardware timer handler */
    uint8_t           hwtmr_chan;  /**< \brief Ӳ����ʱ��ͨ���� */
    am_bool_t         is_hwtmr;    /**< \brief �Ƿ�ʹ��Ӳ����ʱ�� */

    /**
     * \brief ��ʱ����ֵ����λ΢����
     * - ʹ��Ӳ����ʱ��ʱ����ʾÿ΢������Ҫ�Ķ�ʱ������ֵ
     * - ʹ�������ʱ��ʱ�������ʱ��ÿһ��ʱֵ�����΢������1ms��ʱ����ʱΪ1000��
     */
    uint32_t          precisions;

    /**
     * \brief ����Ķ�ʱֵ��΢��
     */
    uint32_t          expires;

    /** \brief ��ʱ���жϻص����� */
    void (*tmr_int_callback) (void *p_arg);
    void  *p_arg;   /**< \brief ��ʱ���жϻص��������� */
} am_mb_timer_t;

/** \brief ��ʱ���豸��Ϣ */
typedef struct aw_mb_timer_info {
    am_timer_handle_t timer;    /**< \brief ��ʱ��Ӳ����� */
    uint32_t          chan;     /**< \brief ��ʱ��ͨ���� */
} aw_mb_timer_info_t;

/**
 * \brief ��ʼ����ʱ��
 * \param[in] p_timer   : Modbus��ʱ���豸
 * \param[in] hwtmr_hdl : Ӳ����ʱ�����ֵ��ΪNULLʱ��ʹ��Ӳ����ʱ����ʹ�������ʱ��
 * \param[in] time      : ��ʱʱ�䣬��΢��(us)����
 * \return ���û�д��󷵻�MB_ERR_NOERR�����򷵻�MB_ERR_EPORTERR
 */
am_mb_err_t am_mb_timer_init (am_mb_timer_t            *p_timer,
                              const aw_mb_timer_info_t *p_timer_info);

/**
 * \brief ʹ�ܶ�ʱ��
 *
 * @note �����ʱ���Ѿ�ʹ�ܣ������¼���
 */
void am_mb_timer_enable (am_mb_timer_t *p_timer);

/**
 * \brief ��ֹ��ʱ��
 */
void am_mb_timer_disable (am_mb_timer_t *p_timer);

/**
 * \brief �رն�ʱ�����ͷŶ�ʱ��
 */
void am_mb_timer_close (am_mb_timer_t *p_timer);

/**
 * \brief �������ö�ʱ��
 *
 * @param[in] p_timer   : ��ʱ�����
 * @param[in] is_hw_tmr : �Ƿ�ʹ��Ӳ����ʱ��
 * @return ���û�д��󷵻�MB_ERR_NOERR�����򷵻�MB_ERR_EPORTERR
 */
am_mb_err_t am_mb_timer_reselect (am_mb_timer_t *p_timer, am_bool_t is_hw_tmr);

/**
 * \brief ���ö�ʱ����ʱֵ
 *
 * \param[in] p_timer  ��ʱ�����
 * \param[in] us       ΢��ֵ
 *
 * \return N/A
 */
am_static_inline void am_mb_timer_timeout_set (am_mb_timer_t *p_timer,
                                               uint32_t       us)
{
    p_timer->expires = us;
}

/*****************************************************************************/
/**
 * \brief Modbus TCP��ʼ��
 * @note  ���ö˿ڣ���ʼ����
 * \param  tcpport TCP�˿�
 *
 * \retval AW_MB_ERR_NOERR      ��ʼ���ɹ�
 */
am_mb_err_t am_mb_tcp_port_init(void *p_cookie, uint16_t tcpport);

/**
 * \brief �ر�TCP����
 */
void am_mb_tcp_port_close (void *p_cookie);

/**
 * \brief TCP����ֹͣ
 */
void am_mb_tcp_port_disable (void *p_cookie);


/**
 * \brief ��ȡTCP��������
 *
 * @note ��ȡһ֡������Modbus TCP����,
 *            �ڽ��յ����ݺ���á���ȡ���ݺ�������գ����ó�ʼ����ƫ����
 *
 * \param **pp_tcpframe ��������֡����
 * \param  *p_tcplen     ֡���ݳ���
 *
 */
void am_mb_tcp_port_getrequest (void     *p_cookie,
                                uint8_t **pp_tcpframe,
                                uint16_t *p_tcplen);

/**
 * \brief TCP�������Ӧ����
 * @note  ��Ӧ���󣬷���һ֡��Ӧ���ݻؿͻ���
 *
 * \param *p_tcpframe ֡����
 * \param  tcplen          ֡���ݳ���
 *
 * \retval AW_MB_ERR_NOERR ����֡���ͳɹ�
 */
am_mb_err_t am_mb_tcp_port_sndresponse (void          *p_cookie,
                                        const uint8_t *p_tcpframe,
                                        uint16_t       tcplen);

/**
 * \brief  ��ѯ�����׽��ֺ͵�ǰ���ӵ�Modbus TCP�ͻ��˵����¼���
 * \note   �˹��ܼ���¿ͻ��˵����Ӻ������ӿͻ��˷��͵�����.
 *         ���һ���µĿͻ������ӣ�������ʣ�µĿͻ��˲�ۣ�ֻ��һ��Ŀǰ�豸֧�֣���
 *         ��ô���ӱ����ܣ���Ϊ�µĿͻ����׽��ֵ��¼����󱻼���(aw_mb_port_acceptclient())��
 *         �ͻ����ڷ���FD_CLOSE�󣬿ͻ������ӱ��ͷŵģ�aw_mb_port_releaseclient����
 *
 * \retval AW_MB_ERR_EIO    �ڲ�IO����
 * \retval AW_MB_ERR_NOERR  û�д���
 */
am_mb_err_t am_mb_port_tcp_poll (void *p_cookie);

/**
 * \brief ��վRTUģʽ��ʱ��ѡ��
 *
 * \param *p_cookie  : RTUģʽ���
 * \param  is_hw_tmr : �Ƿ�ʹ��Ӳ����ʱ��
 *
 * \retval AW_MB_ERR_NOERR ���óɹ�
 */
am_mb_err_t am_mbs_rtu_timer_select (void *p_cookie, am_bool_t is_hw_tmr);

/**
 * \brief ��վASCIIģʽ��ʱ��ѡ��
 *
 * \param *p_cookie  : ASCIIģʽ���
 * \param  is_hw_tmr : �Ƿ�ʹ��Ӳ����ʱ��
 *
 * \retval AW_MB_ERR_NOERR ���óɹ�
 */
am_mb_err_t am_mbs_ascii_timer_select (void *p_cookie, am_bool_t is_hw_tmr);

/**
 * \brief ��վRTUģʽ��ʱ��ѡ��
 *
 * \param *p_cookie  : RTUģʽ���
 * \param  is_hw_tmr : �Ƿ�ʹ��Ӳ����ʱ��
 *
 * \retval AW_MB_ERR_NOERR ���óɹ�
 */
am_mb_err_t am_mb_m_rtu_timer_select (void *p_cookie, am_bool_t is_hw_tmr);

/**
 * \brief ��վASCIIģʽ��ʱ��ѡ��
 *
 * \param *p_cookie  : ASCIIģʽ���
 * \param  is_hw_tmr : �Ƿ�ʹ��Ӳ����ʱ��
 *
 * \retval AW_MB_ERR_NOERR ���óɹ�
 */
am_mb_err_t am_mb_m_ascii_timer_select (void *p_cookie, am_bool_t is_hw_tmr);

#ifdef __cplusplus
}
#endif

/** @} grp_aw_mb_port_if */

#endif /* } __AW_MB_M_PORT_H */

/* end of file */

