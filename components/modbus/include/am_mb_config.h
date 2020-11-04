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
 * \brief Modbus�û������ļ�
 *
 * \internal
 * \par modification history
 * - 1.03 2017-03-29  mkr, transplant from aworks
 * - 1.02 2015-05-13  cod, Modify for aworks1.0, fix code style
 * - 1.01 2012-12-04  liuweiyun, Modify for aworks1.0, fix code style
 * - 1.00 2012-05-13  ygy, first implementation
 * \endinternal
 */

#ifndef __AM_MB_CONFIG_H
#define __AM_MB_CONFIG_H

/**
 * \addtogroup grp_am_if_mb_config
 * \copydoc am_mb_config.h
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Modbus Common Configuration
 ******************************************************************************/

/**
 * \brief �������ADU����
 * - �ó��Ȱ����ӻ���ַ�ͼ������ݳ���
 * - ����ĳЩӦ�ã����ܲ���Ҫ�ܳ���һ֡���ݣ����Կ����ʵ������Խ���RAMʹ��
 * - RTUģʽ����Ϊ4~256�� ASCIIģʽ����Ϊ3~255
 */
#define AM_MB_MAX_SER_ADU_LENGTH   256

/**
 * \brief TCPģʽ�����ADU����
 * - ����ĳЩӦ�ã����ܲ���Ҫ�ܳ���һ֡���ݣ����Կ����ʵ������Խ���RAMʹ��
 */
#define AM_MB_MAX_TCP_ADU_LENGTH   256

/**
 * \brief RTUģʽT3.5ʱ�����ã���λ��΢�룩
 * - ��RTUģʽ�У������Ŷ�t3.5��֡���ӳ�ʱ�䣩����Ĵ����жϵĴ���
 *   �ڽϸߵ�ͨ�Ų������£��⽫����CPU�������أ�
 *   ��˵�������С�ڻ����19200λ/�������£������ϸ�������������ʱ
 * - ���������ʴ���19200λ/��ʱ��Ӧ��ʹ�ù̶�ֵ������֡���ӳ�ʱ������Ϊ1.750ms
 * - ��ʹ��ASCIIģʽʱ������Ҫ�Ըú��������
 */
#define AM_MB_SERIAL_RTU_BAUDRATE_OVER_19200_FRAME_DELAY_US    1750ul

/**
 * \brief ASCIIģʽ�ַ��䳬ʱ����
 * ��ASCIIģʽ�У��ַ��䳬ʱʱ��û�й̶������Ը��ݾ�������������
 */
#define AM_MB_ASCII_TIMEOUT_SEC    1

/*******************************************************************************
 * Modbus Slave Station Configuration
 ******************************************************************************/
/** �ӻ�ͨ��ģʽ���� */
#define AM_MB_SERIAL_ASCII_ENABLE  1   /**< \brief ����ASCIIģʽ */
#define AM_MB_SERIAL_RTU_ENABLE    1   /**< \brief ����RTUģʽ */
#define AM_MB_TCP_ENABLE           0   /**< \brief TCP/IPģʽ,�ݲ�֧��TCP/IPģʽ */

/**
 * \brief ʹ�ܽ���˫���壨RTU��ASCIIģʽ��
 * ���ʹ�ܸ����ã���ʹ��2*AM_MB_MAX_SER_ADU_LENGTH RAM�ռ���������PDU����֡��
 * ʹ�øù��ܣ����Ա�֤�ڵ�һ֡����ʱ����һ֡���ݵ���ʱ����֤�ڶ�֡����������
 */
#define AM_MB_SER_PDU_RECV_BUF_ENABLE  1

/*******************************************************************************
 * Modbus Master Station Configuration
 ******************************************************************************/
/** ��վͨ��ģʽ���� */
#define AM_MB_MASTER_RTU_ENABLE    1   /**< \brief ����RTUģʽ */
#define AM_MB_MASTER_ASCII_ENABLE  1   /**< \brief ����ASCIIģʽ */
#define AM_MB_MASTER_TCP_ENABLE    0   /**< \brief TCP/IPģʽ */

/**
 * \brief ��վ�ȴ���վӦ��ʱʱ�䣨���룩
 */
#define AM_MB_MASTER_TIMEOUT_MS_RESPOND  2000
#if ((AM_MB_MASTER_TIMEOUT_MS_RESPOND < 50)  ||\
     (AM_MB_MASTER_TIMEOUT_MS_RESPOND > 100000))
#error "AM_MB_MASTER_TIMEOUT_MS_RESPOND value must be in 50~100000ms"
#endif

/**
 * \brief ��վ�㲥ʱ��ת���ӳ�ʱ�䣨���룩
 */
#define AM_MB_MASTER_DELAY_MS_CONVERT   100

/**
 * \brief TCPģʽ�µ�Ԫ��ʾ��ʹ�ô�վ��ַʹ��
 * - ����ĳЩӦ�ã���Modbus���������ӵ�������·����ʹ�õ�Ԫ��ʾ��ʶ���վ��ַ
 * - ��ʹ�ܣ���Ԫ��ʾ������Ŀ���վ��ַʹ�ã�����ʹ�ܣ���Ԫ��ʾ��ֵĬ��Ϊ0xFF
 */
#define AM_MB_TCP_UID_AS_SLAVEADDR   0

/**
 * \brief ��վTCPģʽ�£�Ĭ�����ӳ�ʱʱ��(ms)
 */
#define AM_MB_TCP_CONNECT_TIMEOUT    5000

#ifdef __cplusplus
}
#endif

/* @} grp_am_if_mb_config */

#endif /* } __AM_MB_CONFIG_H */


/* end of file */
