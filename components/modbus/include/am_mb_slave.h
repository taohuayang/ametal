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
 * \brief modbus�ӻ�Э��ջ�û��ӿ�ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 2017-03-29  mkr, transplant from aworks
 * \endinternal
 */

#ifndef __AM_MB_SLAVE_H /* { */
#define __AM_MB_SLAVE_H

/**
 * \addtogroup grp_am_if_mb_slave
 * \copydoc am_mb_slave.h
 * @{
 */

#include "am_mb_config.h"
#include "am_mb_err.h"
#include "am_mb_comm.h"
#include "am_mb_netif.h"
#include "am_mb_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief �ӻ�ID��Ϣ������ */
#define AM_MB_FUNC_OTHER_REP_SLAVEID_BUF  32

/** ������ص��������� */
enum am_mb_func_cb_type {
	AM_MB_FUNC_COILS_CALLBACK,                /**< \brief ��д��Ȧ�����ص� */
	AM_MB_FUNC_DISCRETEINPUTS_CALLBACK,       /**< \brief ����ɢ�������ص� */
	AM_MB_FUNC_HOLDREGISTERS_CALLBACK,        /**< \brief ��д���ּĴ����ص� */
	AM_MB_FUNC_INPUTREGISTERS_CALLBACK,       /**< \brief ������Ĵ����ص� */
};

/** ������ص������������� */
enum am_mb_func_cb_op {
	AM_MB_FUNC_CALLBACK_READ,   /**< \brief ������ */
	AM_MB_FUNC_CALLBACK_WRITE,  /**< \brief д���� */
};

typedef struct am_mb_slave_serv am_mb_slave_serv_t;

/** Modbus��վ������� */
typedef am_mb_slave_serv_t *am_mb_slave_handle;

/******************************************************************************/

/**
 * \file
 *
 * callback function
 *
 * Read the ON/OFF status of discrete outputs(DO)in the slave. The coils status
 * is packed as per bit of data field. Status is indicated as: 1=ON, 0=OFF.
 * The LSB of the first data byte contains the coil addressed in the query.
 * If the coil quantity is not a multiple of eight, the remaining bits in the
 * final data byte will be padded with zeros.
 *
 * For example. addr = 0x0013  num = 10,
 * status of coils 20 ~ 27 is ON-ON-OFF-OFF-ON-OFF-ON-OFF 28~29 ON-ON,
 * so the buf[0] = 01010011(0x53)  buf[1] = 00000011
 *
 * buf[0]:
 * 7  |6  |5  |4  |3  |2  |1  |0
 * ---|---|---|---|---|---|---|---
 * 27 |26 |25 |24 |23 |22 |21 |20
 * OFF|ON |OFF|ON |OFF|OFF|ON |ON
 * 0  |1  |0  |1  |0  |0  |1  |1
 *
 * buf[1]:
 * 7  |6  |5  |4  |3  |2  |1  |0
 * ---|---|---|---|---|---|---|----
 * -  |-  |-  |-  |-  |-  |29 |28
 * 0  |0  |0  |0  |0  |0  |ON |ON
 * 0  |0  |0  |0  |0  |0  |1  |1
 */

/**
 * \brief ��д��Ȧ������ɢ������д����Ĵ�����������Ĵ����ص�����ԭ��
 * @note  ��ʹ�ñ����ṩ�Ķ�д��Ȧ������ɢ������д����Ĵ�����
 * 		     ������Ĵ����ȹ����봦����ʱ����Ҫע��
 * @code
 * am_mb_exception_t my_coils_callback(am_mb_slave_t slave,
 *                                     uint8_t   *buf,
 *                                     uint16_t   addr,
 *                                     uint16_t   num)
 * {
 *     //����Ȧ����
 * }
 *
 * //������slave֮ǰ�������²�����
 * am_mb_slave_register_callback(slave,
 *                            	 am_MB_FUNC_COILS_CALLBACK,
 *                            	 am_MB_FUNC_CALLBACK_READ,
 *                            	 my_coils_callback);
 * @endcode
 *
 * @param[in]     slave �ӻ����
 * @param[in,out] buf   ��д����������
 * @param[in]     addr  ��д������ʼ��ַ
 * @param[in]     num   ��д��������
 * @return ���û���쳣������AM_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 * @see am_mb_slave_register_callback
 */
typedef am_mb_exception_t (*am_mb_slave_fn_code_callback_t)(am_mb_slave_handle  slave,
	                                                        uint8_t            *p_buf,
                                                            uint16_t            addr,
                                                            uint16_t            num);

/**
 * \brief �û������봦����ԭ��.
 * @note  ���ӻ��յ�һ֡�����Ժ󣬽����ݹ�������ö�Ӧ�Ĵ�������
 * 		     ���������û�ͨ��\a am_mb_slave_register_handler ��ע�ᡣ
 *		     ͬʱ�Ѿ���������Ķ�д��Ȧ������ɢ������д����Ĵ�����������Ĵ���
 * 		     �ȴ�����
 *
 * @param[in] slave Modbus��վ���
 * @param[in,out] p_pdubuf PDU����(����������)
 *         - [in]  ����PDU����
 *         - [out] Ӧ��PDU����
 * @param[in,out] p_pdulen PDU���ݳ���
 *         - [in]  ����PDU���ݳ���
 *         - [out] Ӧ��PDU���ݳ���
 * @return ���û���쳣������AM_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
typedef am_mb_exception_t (*am_mb_fn_code_handler_t) (am_mb_slave_handle  slave,
                                                  	  uint8_t            *p_pdubuf,
                                                  	  uint16_t           *p_pdulen);

/** \brief function code handler type */
typedef struct am_funcode_handle {
    uint8_t                 funcode;
    am_mb_fn_code_handler_t handler;
} am_funcode_handle_t;

/******************************************************************************/

/** \brief Modbus ��վ���� */
typedef struct am_mb_slave_serv {
    void                     *p_cookie;  /**< \brief  */
    enum am_mb_slave_status   status;    /**< \brief ��վ״̬  */
    enum am_mb_mode           mode;      /**< \brief ��ǰ����ģʽ */
    const struct am_mb_netif *p_netif;   /**< \brief ģʽ�ӿ� */
    /** \brief �û�ע�Ṧ����� */
    am_funcode_handle_t      *p_funcode_hdl;
    /** \brief ��֧��ע��Ĺ�������� */
    uint8_t                   funcode_hdl_max;

    am_mb_event_t             event;   /**< \brief ��վ�¼� */

    /** \brief ͨ�ù�����ص�  */
    am_mb_slave_fn_code_callback_t fn_read_coils_cb;
    am_mb_slave_fn_code_callback_t fn_write_coils_cb;
    am_mb_slave_fn_code_callback_t fn_read_discre_cb;
    am_mb_slave_fn_code_callback_t fn_read_input_cb;
    am_mb_slave_fn_code_callback_t fn_read_hold_cb;
    am_mb_slave_fn_code_callback_t fn_write_hold_cb;
#if 1
    /** \brief �û�ID��Ϣ���ɲ�����  */
    uint8_t  id[AM_MB_FUNC_OTHER_REP_SLAVEID_BUF];
    uint16_t id_len;
#endif
} am_mb_slave_serv_t;

/** \brief Modbus��վ�豸 */
typedef struct am_mb_slave_dev {
    /** \brief modbus slave service */
    am_mb_slave_serv_t am_mb_slave_serv;

    union mode {
        struct am_mb_rtu   mb_rtu;   /**< \brief RTU mode private data */
        struct am_mb_ascii mb_ascii; /**< \brief ASCII mode private data */
#if AM_MB_TCP_ENABLE
        struct am_mb_tcp   mb_tcp;   /**< \brief TCP mode private data */
#endif
    } common;

} am_mb_slave_dev_t;

/** \brief modbus slave info  */
typedef struct am_mb_slave_info {
    aw_mb_timer_info_t  timer_info;  /**< \brief ��ʱ���豸��Ϣ */
    am_mb_serial_info_t serial_info; /**< \brief ������·�豸��Ϣ */
    uint8_t             slave_addr;  /**< \brief �ӻ���ַ */
    enum am_mb_mode     mode;        /**< \brief ģʽ */
} am_mb_slave_info_t;

/******************************************************************************/
/**
 * \brief ��������ʼ��һ��Modbus��վ
 * @note  �ڵ������дӻ�����֮ǰ�������ȵ��øú���
 * @note  ����ͬ���紴�������վ
 *
 * @param[in] p_s_dev : ָ���վ�豸��ָ��
 * @param[in] mode    : ͨ��ģʽ
 * @param[in] p_param : ��ʼ������������MB_RTU/MB_ASCIIģʽʹ��
 *                      struct am_mb_serial_param��Ϊ����
 *                      ����AM_MB_TCPģʽ��param��Ϊ�˿ںŲ���ʹ��,ֱ�Ӵ����β�
 * @param[out] p_err  : �����. ����Դ���Ų�����Ȥ���Դ���NULL������
 * ���ش���ֵ��
 * -AM_MB_ERR_NOERR           : ��ʼ���ɹ�.
 * -AM_MB_ERR_EINVAL          : �����������.
 * -AM_MB_ERR_ALLOC_FAIL      : �ڴ治�㣬�����վʧ��.
 * -AM_MB_ERR_MODE_NO_SUPPORT : ģʽ��֧��
 * -AM_MB_ERR_EPORTERR        �� ����ģʽ�����䴮�ڻ�Ӳ����ʱ��ʧ��.
 * -AM_MB_ERR_EIO             : TCPģʽ������˴���ʧ��.
 * @return Modbus��վ���������������󷵻�NULL
 */
am_mb_slave_handle am_mb_slave_init (am_mb_slave_dev_t        *p_dev,
                                     const am_mb_slave_info_t *p_info,
								     am_mb_err_t              *p_err);

/**
 * \brief �ر�Modbus��վ.
 * @note  �˳�ϵͳ���߲���Ҫ��ʹ�ôӻ�ʱ����
 *
 * @param[in] slave : Modbus��վ���
 *
 * @retval AM_MB_ERR_NOERR     : �޴���.
 * @retval AM_MB_ERR_EINVAL    : ��վ��������.
 * @retval AM_MB_ERR_EILLSTATE : Э��ջ�Ƿ�״̬.
 */
am_mb_err_t am_mb_slave_close (am_mb_slave_handle slave);

/**
 * \brief ����Modbus��վ.
 * @note  �ú��������ڵ���am_mb_slave_init��������ߵ���am_mb_slave_stop�����󱻵���
 *
 * @param[in] slave            : Modbus��վ���
 *
 * @retval AM_MB_ERR_NOERR     : �޴���.
 * @retval AM_MB_ERR_EINVAL    : ��վ��������.
 * @retval AM_MB_ERR_EILLSTATE : Э��ջ�Ƿ�״̬.
 */
am_mb_err_t am_mb_slave_start (am_mb_slave_handle slave);

/**
 * \brief ֹͣModbus��վ.
 *
 * @param[in] slave            : Modbus��վ���
 *
 * @retval AM_MB_ERR_NOERR     : �޴���.
 * @retval AM_MB_ERR_EINVAL    : ��վ��������.
 * @retval AM_MB_ERR_EILLSTATE : Э��ջ�Ƿ�״̬.
 */
am_mb_err_t am_mb_slave_stop (am_mb_slave_handle slave);

/**
 * \brief ע�Ṧ���봦����.
 * @note  ��ʼ��Modbus��վ�Ժ󣬿��Ե��øú�����ע���Ӧ�Ĺ����봦������������չ������
 *
 * @note ����ע��Ĺ����봦����������am_mb_config.h��AM_MB_FUNC_CODE_HANDLER_MAX���塣
 *       �����ø������޷���ע�ᡣͬһ��������ֻ����һ�������������ע������ͬ
 *       һ�������봦��������ֻʹ�����ע��Ĵ�������
 * @param[in] slave    : Modbus��վ���
 * @param[in] funcode  : �������
 * @param[in] handler  : �����봦����
 *
 * @retval  AM_MB_ERR_NOERR  : �޴���;
 * @retval  AM_MB_ERR_EINVAL : ��������;
 * @retval  AM_MB_ERR_ENORES : �޷���ע�Ṧ����.
 */
am_mb_err_t am_mb_slave_register_handler (am_mb_slave_handle       slave,
                                    	  uint8_t                  funcode,
                                    	  am_mb_fn_code_handler_t  handler);

/**
 * \brief ע���д��Ȧ������ɢ������д����Ĵ�����������Ĵ����ص�����.
 * @note  ��ʹ�ñ����ṩ�Ķ�д��Ȧ������ɢ������д����Ĵ�����������Ĵ���������
 *           ������ʱ, ����ʹ�øú������лص�����ע�ᣬ�����������÷Ƿ��������쳣
 *
 * @param[in] slave �ӻ����
 * @param[in] type ������ص���������
 * @param[in] op ������ص�������������
 * @param[in] callback �ص�����
 *
 * @retval AM_MB_ERR_NOERR  : ע��ɹ�.
 * @retval AM_MB_ERR_EINVAL : �����������.
 */
am_mb_err_t am_mb_slave_register_callback (am_mb_slave_handle             slave,
                                           enum am_mb_func_cb_type        type,
                                           enum am_mb_func_cb_op          op,
                                           am_mb_slave_fn_code_callback_t callback);

/**
 * \brief Modbus��վ��ѯ����.
 * @note  ��������֡�����������֡����ΪModbus��վЭ��ĺ��ġ��ú������뱻�����Եĵ��á�
 *        ��ʱ������������Ӧ�ú���վҪ���ʱ������
 * @note  �ýӿ�����RTU��ASCII��TCPģʽ.
 * @note  RTU/ASCII����ģʽ�£��ýӿ�����ʱ��ȡ����am_mb_slave_cfgЭ��ջ���ýӿڡ�
 *        TCPģʽ�£��ýӿ�Ϊ��������
 *
 * @param[in] slave : Modbus��վ���
 *
 * @retval AM_MB_ERR_NOERR     : �޴���;
 * @retval AM_MB_ERR_EINVAL    : ��������;
 * @retval AM_MB_ERR_EILLSTATE : Э��ջ�Ƿ�״̬.
 * @retval AM_MB_ERR_ENORES    : ����ģʽ����Ӧʱ�յ��µ�����.
 * @retval AM_MB_ERR_EIO       : IO����. ����ģʽ������״̬����. TCPģʽ������ʧ��.
 */
am_mb_err_t am_mb_slave_poll (am_mb_slave_handle slave);

/** \brief ��վ�������� */
typedef int am_mbs_cfg_type_t;
#define AM_MBS_TYPE_USED_HW_TMR        0x01   /**< \brief ʹ��Ӳ����ʱ�� */
#define AM_MBS_TYPE_TCP_NUM            0x03   /**< \brief TCPģʽ���������������� */
#define AM_MBS_TYPE_ACCEPT_TCP_NUM_GET 0x04   /**< \brief ��ȡ��ǰ�ѽ��յ������� */
#define AM_MBS_TYPE_ALLOW_NEW_TCP      0x05   /**< \brief ���Ӵﵽ����ֵ������رվ����������������� */

/**
 * \brief ��վ��������
 *
 * @note ���޵��øýӿڣ����������Ͱ���am_mb_config.h�в�������.
 *
 * @param[in] type  : �������ͣ�
 * - AM_MBS_TYPE_TCP_NUM            : ������������������p_argΪ��������uint32_t��;
 * - AM_MBS_TYPE_ACCEPT_TCP_NUM_GET : ��ȡ��ǰ�ѽ���������������p_argΪ��ȡ����������uint32_t *��;
 * - AM_MBS_TYPE_ALLOW_NEW_TCP      : �ﵽ�������޺�������������Ӷ��Ͽ�������,p_argΪ1ʱ����;
 *
 * @param[in] p_arg :  ���ò�����ȡ������������
 *
 * @return �����óɹ�������AM_MB_ERR_NOERR,��֮��������Ӧ����ֵ.
 */
am_mb_err_t am_mb_slave_ioctl (am_mb_slave_handle slave,
                               am_mbs_cfg_type_t  type,
                               void              *p_arg);

/**
 * \brief ��վģʽ��ȡ
 *
 * @param[in]      slave  : Modbus��վ���
 * @param[in][out] p_mode : ��վ����ģʽ
 *
 * @retval AM_MB_ERR_EINVAL : �����������
 * @retval AM_MB_ERR_NOERR  : �޴���
 */
am_mb_err_t am_mb_slave_mode_get (am_mb_slave_handle  slave,
                                  enum am_mb_mode    *p_mode);

/**
 * \brief ����Modbus��վ��Ϣ.
 * ��������Modbus��վ����˵������ǰ״̬������һЩ������Ϣ��
 * @note ��ʵ�ֶ�����Modbus��վ��Ϣ��󳤶�Ϊ32���ֽڣ����У�
 *    - ջ����˵��ռһ���ֽ�
 *    - ��ǰ״̬ռһ���ֽ�
 *    - ������Ϣ����<= 30����Ϣ\n
 *  ��ʹ����Ҫ�ر�ע��.
 * @note �ýӿ�֧�������ã�Ĭ�ϲ�֧��
 *
 * @param[in] slave        : Modbus��վ���
 * @param[in] slave_id     : ����˵��
 * @param[in] is_running   : ��ǰ״̬��> 0��ʾ�����У�== 0��ʾֹͣ״̬
 * @param[in] p_additional : ����һЩ������Ϣ
 * @param[in] alen         : ����һЩ������Ϣ����
 *
 * @retval AM_MB_ERR_NOERR  : �޴���;
 * @retval AM_MB_ERR_EINVAL : ��������;
 * @retval AM_MB_ERR_ENORES : ��Դ����.
 */
am_mb_err_t am_mb_slave_set_id (am_mb_slave_handle slave,
                                uint8_t            slave_id,
                                uint8_t            is_running,
                                const uint8_t     *p_additional,
                                uint16_t           alen);

/**
 * \brief ����Modbus��վ��ַ.
 * @note  Ĭ��������ڵ���am_mb_slave_init���г�ʼ��ʱ����ʼ�����������Ѿ������ô�վ��ַ��
 * 		     ���������Ҫ������ʱ�޸Ĵ�վ��ַ������ʹ�øú�����
 *
 * @param[in] slave         : Modbus��վ���
 * @param[in] addr          : �µ�Modbus��վ��ַ
 *
 * @retval AM_MB_ERR_NOERR  : �޴���;
 * @retval AM_MB_ERR_EINVAL : ��������; ��վ�����ڣ���ַ��������ַ�� �����õ�ַΪ�㲥��ַ
 */
am_mb_err_t am_mb_slave_set_addr (am_mb_slave_handle slave, uint8_t addr);

/**
 * \brief �����û��Զ��幦�����ڴ�
 *
 * @param[in] p_slave : ��վ�豸ʵ��.
 * @param[in] p_buf   : �û��Զ��幦���뻺������ʼ��ַ
 * @param[in] num     : �������
 *
 * @return    p_err   ����ţ����û�д�����ֵΪam_MB_ERR_NOERR
 */
am_mb_err_t am_mbs_user_funcode_alloc (am_mb_slave_handle   slave,
                                       am_funcode_handle_t *p_buf,
                                       uint8_t              num);

#if AM_MB_TCP_ENABLE

/**
 * \brief ��������TCP��Ϣ
 */
struct sockaddr;
struct am_mb_slave_tcp_info {
    int              socket;      /**< \brief ����socket����������socket����  */
    struct sockaddr *p_sockaddr;  /**< \brief IP��ַ��Ϣ  */
};

/**
 * \brief TCPģʽsocket���ӹ��Ӻ���ע��
 *
 * @param[in] master      : ��վ���
 * @param[in] accept_hook : ���������ӹ��Ӻ���
 * @param[in] close_hook  : ���ӱ����Ͽ�����ﵽ�������޶Ͽ������Ӻ���
 * @param[in] p_arg       : ���Ӻ�������
 *
 * @retval AM_MB_ERR_NOERR     : ע��ɹ���
 * @retval AM_MB_ERR_EINVAL    : ��������
 * @retval AM_MB_ERR_EILLSTATE : Э��ջ�Ƿ�״̬
 */
am_mb_err_t am_mb_slave_tcp_hook_register (am_mb_slave_t            slave,
                                           am_mb_tcp_accept_hook_t  accept_hook,
                                           am_mb_tcp_close_hook_t   close_hook,
                                           void                    *p_arg);
#endif

#ifdef __cplusplus
}
#endif

/** @} grp_am_if_mb_slave */

#endif /* } __AM_MB_SLAVE_H */

/* end of file */
