/*******************************************************************************
*                                 AWORKS
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief modbus register function code head file.
 *
 * \internal
 * \par modification history
 * - 1.03 2017-03-29  mkr, transplant from aworks.
 * - 1.02 2015-05-22  cod, fix code style and comments, a little improve.
 * - 1.01 2013-03-29  liuweiyun, fix code style and comments, a little improve.
 * - 1.00 2012-07-05  ygy, first implementation
 * \endinternal
 */

#ifndef __AM_MB_REGFUNCTION_H /* { */
#define __AM_MB_REGFUNCTION_H

/**
 * \addtogroup grp_am_if_mb_regfunction
 * \copydoc am_mb_regfunction.h
 * @{
 */

#include "am_mb_slave.h"
#include "am_mb_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ��ȡ��վ��Ϣ
 * @note  ��ȡModbus��ջ����˵������ǰ״̬������һЩ������Ϣ��
 *
 * @param[in]     : slave �ӻ����
 * @param[in,out] : p_frame ��վ��Ϣ������
 *
 * @return ID��վ��Ϣ����
 */
uint16_t am_mb_get_slave_id (am_mb_slave_handle slave, uint8_t *p_frame);

/**
 * \brief ��ȡ������Ĵ�����
 *
 * @param[in] : funCode ������
 *
 * @return    : �������Ӧ�Ĵ�����
 */
am_mb_fn_code_handler_t am_mb_fn_code_handler_get (am_mb_slave_handle slave,
                                                   uint8_t       funcode);

/**
 * \brief ����Ȧ�����봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 *		      ע�������Ȧ��������ص�����
 *
 * @param[in]     slave   : �ӻ����
 * @param[in,out] p_pdu   : ���������PDU������
 * @param[in,out] p_len   : PDU����ָ��
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_read_coils (am_mb_slave_handle slave,
                                   	   uint8_t 	    *p_pdu,
                                       uint16_t 	*p_len);

/**
 * \brief ����ɢ�������봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mb_register_funcode_callback
 * 		      ע�������ɢ����������ص�����
 *
 * @param[in]    slave   : �ӻ����
 * @param[in,out] p_pdu  : ���������PDU������
 * @param[in,out] p_len  : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_read_discrete_inputs (am_mb_slave_handle slave,
                                                 uint8_t 	  *p_pdu,
                                                 uint16_t 	  *p_len);

/**
 * \brief ������Ĵ��������봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 * 	                ע���������Ĵ�����������ص�����
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_read_hold_regs (am_mb_slave_handle slave,
                                           uint8_t 	    *p_pdu,
                                           uint16_t 	*p_len);

/**
 * \brief ������Ĵ��������봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 * 		     ע���������Ĵ�����������ص�����
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_read_input_regs (am_mb_slave_handle slave,
                                            uint8_t 	 *p_pdu,
                                            uint16_t 	 *p_len);

/**
 * \brief д������Ȧ�����봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 * 		     ע����д��Ȧ��������ص����������д�����Ȧ�Ѿ���ע��д��Ȧ��������ص�������
 * 		     �Ͳ���Ҫ��ע�ᡣ
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_write_single_coil (am_mb_slave_handle slave,
                                         	  uint8_t 	   *p_pdu,
                                              uint16_t 	   *p_len);

/**
 * \brief д�����Ĵ��������봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 *        ͬʱҪʹ��am_mbRegisterFunCodeCallback
 *        ע����д�Ĵ�����������ص����������д����Ĵ����Ѿ���ע��д�Ĵ����������
 *        �ص��������Ͳ���Ҫ��ע��
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_write_single_reg (am_mb_slave_handle slave,
                                             uint8_t 	  *p_pdu,
                                             uint16_t 	  *p_len);

/**
 * \brief д�����Ȧ�����봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 * 		     ע����д��Ȧ��������ص����������д������Ȧ�Ѿ���ע��д��Ȧ��������ص�������
 * 		     �Ͳ���Ҫ��ע��
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_write_multiple_coils (am_mb_slave_handle slave,
                                                 uint8_t 	  *p_pdu,
                                                 uint16_t 	  *p_len);

/**
 * \brief д����Ĵ��������봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 * 		     ע����д�Ĵ�����������ص����������д����Ĵ����Ѿ���ע��д�Ĵ����������
 * 		     �ص��������Ͳ���Ҫ��ע��
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_write_multiple_regs (am_mb_slave_handle slave,
                                                uint8_t 	 *p_pdu,
                                                uint16_t 	 *p_len);

/**
 * \brief ��д����Ĵ��������봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     ͬʱҪʹ��am_mbRegisterFunCodeCallback
 * 		     ע�������д�Ĵ�����������ص�����������Ѿ�ע�������д�Ĵ����������
 * 		     �ص��������Ͳ���Ҫ��ע��
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu :���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
am_mb_exception_t am_mb_fn_rw_multiple_regs (am_mb_slave_handle slave,
										     uint8_t 	  *p_pdu,
										     uint16_t 	  *p_len);

/**
 * \brief ����ӻ���Ϣ�����봦����.
 * @note  �����Ҫ�ù��ܣ���Ҫʹ�ú���am_mb_slave_register_handler��ע�ᡣ
 * 		     �ӻ�����ʹ��am_mb_slave_set_id�����ôӻ�����Ϣ��
 *
 * @param[in]     slave : �ӻ����
 * @param[in,out] p_pdu : ���������PDU������
 * @param[in,out] p_len : PDU����
 * @return ���û���쳣������am_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 * @see am_mb_slave_set_id
 */
am_mb_exception_t am_mb_fn_report_slave_id (am_mb_slave_handle slave,
                                       	    uint8_t 	 *p_pdu,
                                            uint16_t     *p_len);

#ifdef __cplusplus
}
#endif

/* @} grp_am_if_mb_regfunction */

#endif /* @} __AM_MB_REGFUNCTION_H */

