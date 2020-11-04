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
 * \brief modbus������Ϣ
 *
 * \internal
 * \par modification history
 * - 1.03 2017-03-29  mkr, transplant from aworks.
 * - 1.02 2015-05-18  cod, fix code style and comments, a little improve.
 * - 1.01 2013-03-29  liuweiyun, fix code style and comments, a little improve.
 * - 1.00 2012-05-03  ygy, first implementation
 * \endinternal
 */

#ifndef __AM_MB_COMM_H /* { */
#define __AM_MB_COMM_H

/**
 * \addtogroup grp_am_if_mb_comm
 * \copydoc am_mb_comm.h
 * @{
 */
#include "am_types.h"
#include "am_uart.h"
#include "am_timer.h"
#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

/**
 * \name Modbus��ַ
 * @{
 */
#define AM_MB_ADDRESS_BROADCAST    0   /**< \brief Modbus�㲥��ַ */
#define AM_MB_ADDRESS_MIN          1   /**< \brief ��С�ӻ���ַ */
#define AM_MB_ADDRESS_MAX          247 /**< \brief ���ӻ���ַ */
/** @} */

/**
 * \name ���ù�����
 * @{
 */
#define AM_MB_FUNC_NONE                           0   /**< \brief ��ʹ�õĹ����� */
#define AM_MB_FUNC_READ_COILS                     1   /**< \brief ����Ȧ������ */
#define AM_MB_FUNC_READ_DISCRETE_INPUTS           2   /**< \brief ����ɢ�������� */
#define AM_MB_FUNC_READ_HOLDING_REGISTER          3   /**< \brief ������Ĵ��������� */
#define AM_MB_FUNC_READ_INPUT_REGISTER            4   /**< \brief ������Ĵ��������� */
#define AM_MB_FUNC_WRITE_SINGLE_COIL              5   /**< \brief д������Ȧ������ */
#define AM_MB_FUNC_WRITE_REGISTER                 6   /**< \brief д�����Ĵ��������� */
#define AM_MB_FUNC_WRITE_MULTIPLE_COILS          15   /**< \brief д����߹����� */
#define AM_MB_FUNC_WRITE_MULTIPLE_REGISTERS      16   /**< \brief д����Ĵ��������� */
#define AM_MB_FUNC_READWRITE_MULTIPLE_REGISTERS  23   /**< \brief ��д����Ĵ��������� */
#define AM_MB_FUNC_OTHER_REPORT_SLAVEID          17   /**< \brief ��ȡ�ӻ���Ϣ */

#define AM_MB_FUNC_ERROR                         128  /**< \brief �쳣������ */
/** @} */

/**
 * \name PDU(Э�����ݵ�Ԫ) defines
 * @{
 */
#define AM_MB_PDU_SIZE_MAX     253 /**< \brief ���PDU���� */
#define AM_MB_PDU_SIZE_MIN     1   /**< \brief �����볤�� */
#define AM_MB_PDU_FUNC_OFF     0   /**< \brief ��������PDU��ƫ�� */
#define AM_MB_PDU_DATA_OFF     1   /**< \brief ������PDU��ƫ�� */
/** @} */

/**
 * \name Modbus TCP MBAP defines
 * @{
 */
#define AM_MB_TCP_TID          0	/**< \brief �������ʶ�� */
#define AM_MB_TCP_PID          2	/**< \brief Э���ʶ�� */
#define AM_MB_TCP_LEN          4	/**< \brief ���� */
#define AM_MB_TCP_UID          6	/**< \brief ��Ԫ��ʶ�� */
#define AM_MB_TCP_FUNC         7	/**< \brief ������ */
/** @} */

/**
 * \name PID define
 * @{
 */
#define AM_MB_TCP_PROTOCOL_ID 	   0    /**< \brief Э���ʶ�� ID*/
/** @} */

/**
 * \name  TCP pseudo address define
 * @{
 */
#define AM_MB_TCP_PSEUDO_ADDRESS   255     /**< \brief Modbus TCPα��ַ */
/** @} */
/******************************************************************************/

/** �쳣���� */
typedef enum am_mb_exception {
	AM_MB_EXP_NONE                 = 0x00,     /**< \brief û���쳣 */
    AM_MB_EXP_ILLEGAL_FUNCTION     = 0x01,     /**< \brief �Ƿ����� */
    AM_MB_EXP_ILLEGAL_DATA_ADDRESS = 0x02,     /**< \brief �Ƿ����ݵ�ַ */
    AM_MB_EXP_ILLEGAL_DATA_VALUE   = 0x03,     /**< \brief �Ƿ�����ֵ */
    AM_MB_EXP_SLAVE_DEVICE_FAILURE = 0x04,     /**< \brief �ӻ��豸���� */
    AM_MB_EXP_ACKNOWLEDGE          = 0x05,     /**< \brief ȷ�� */
    AM_MB_EXP_SLAVE_BUSY           = 0x06,     /**< \brief �ӻ��豸æ */
    AM_MB_EXP_MEMORY_PARITY_ERROR  = 0x08,     /**< \brief �洢��ż�Բ��*/
    AM_MB_EXP_GATEWAY_PATH_FAILED  = 0x0A,     /**< \brief ����·�������� */
    AM_MB_EXP_GATEWAY_TGT_FAILED   = 0x0B      /**< \brief ����Ŀ���豸��Ӧʧ�� */
} am_mb_exception_t;

/** ������żУ��ģʽ */
enum am_mb_parity {
	AM_MB_PAR_NONE,    /**< \brief ��У�� */
	AM_MB_PAR_ODD,     /**< \brief ��У�� */
	AM_MB_PAR_EVEN     /**< \brief żУ�� */
};

/** ͨ��ģʽ���� */
enum am_mb_mode {
	AM_MB_RTU,         /**< \brief ����RTUģʽ�Ĵ���MODBUS   */
	AM_MB_ASCII,       /**< \brief ����ASCIIģʽ�Ĵ���MODBUS */
	AM_MB_TCP,         /**< \brief ����TCP/IPЭ��ջ��MODBUS  */
};

#ifdef __cplusplus
}
#endif

/** @} grp_am_if_mb_comm */

#endif /* } __AM_MB_COMM_H */

/* end of file */
