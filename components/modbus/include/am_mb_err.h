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
 * \brief modbus�����ͷ�ļ�.
 *
 * \internal
 * \par modification history
 * - 1.02 2017-03-29  mkr, transplant from aworks.
 * - 1.02 2015-05-18  cod, fix code style and comments, a little improve.
 * - 1.01 2013-03-29  liuweiyun, fix code style and comments, a little improve.
 * - 1.00 2012-05-03  ygy, first implementation
 * \endinternal
 */

#ifndef __AM_MB_ERR_H /* { */
#define __AM_MB_ERR_H

/**
 * \addtogroup grp_am_if_mb_err
 * \copydoc am_mb_err.h
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** ����� */
typedef enum am_mb_err {
	AM_MB_ERR_NOERR,                   /**< \brief û�д��� */
	AM_MB_ERR_ALLOC_FAIL,              /**< \brief �����ڴ�ʧ�� */
	AM_MB_ERR_ENOREG,                  /**< \brief �Ƿ�ע���ַ */
	AM_MB_ERR_EINVAL,                  /**< \brief �Ƿ����� */
	AM_MB_ERR_EPORTERR,                /**< \brief �˿ڴ��� */
	AM_MB_ERR_ENORES,                  /**< \brief ��Դ���� */
	AM_MB_ERR_EIO,                     /**< \brief I/O���� */
	AM_MB_ERR_EILLSTATE,               /**< \brief Э��ջ�Ƿ�״̬ */
	AM_MB_ERR_ETIMEDOUT,               /**< \brief ��ʱ���� */
	AM_MB_ERR_ECRC,                    /**< \brief CRC����  */
	AM_MB_ERR_EFRAME_LEN,              /**< \brief ֡���ȴ��� */
	AM_MB_ERR_EUNEXECPTION_FUNCTION,   /**< \brief ���ڴ����ܴ��� */
	AM_MB_ERR_ILLEGAL_FUNCTION,        /**< \brief �Ƿ����� */
	AM_MB_ERR_ILLEGAL_DATA_ADDRESS,    /**< \brief �Ƿ����ݵ�ַ */
	AM_MB_ERR_ILLEGAL_DATA_VALUE,      /**< \brief �Ƿ�����ֵ */
	AM_MB_ERR_SLAVE_DEVICE_FAILURE,    /**< \brief �ӻ��豸���� */
	AM_MB_ERR_ACKNOWLEDGE,             /**< \brief ȷ�� */
	AM_MB_ERR_SLAVE_BUSY,              /**< \brief �ӻ��豸æ */
	AM_MB_ERR_MEMORY_PARITY_ERROR,     /**< \brief �洢��ż�Բ��*/
	AM_MB_ERR_GATEWAY_PATH_FAILED,     /**< \brief ����·�������� */
	AM_MB_ERR_GATEWAY_TGT_FAILED,      /**< \brief ����Ŀ���豸��Ӧʧ�� */

	AM_MB_ERR_MODE_NO_SUPPORT,         /**< \brief ��֧�ֵ�ͨѶģʽ */
	AM_MB_ERR_THREAD_FAIL,             /**< \brief �̴߳���ʧ�� */
	AM_MB_ERR_EVENT_FAIL,              /**< \brief �¼�����ʧ�� */
	AM_MB_ERR_EVENT_WAIT,              /**< \brief �ȴ��¼�ʱ����δ֪���� */
	AM_MB_ERR_OPEN_FILE,               /**< \brief ��ͨ���ļ�ʧ�� */
	AM_MB_ERR_UNKOWN_EXP,              /**< \brief δ֪�쳣 */

	AM_MB_ERR_MASTER_RCV_ERR,          /**< \brief ��վ�������ݴ���  */
} am_mb_err_t;

#ifdef __cplusplus
}
#endif

/** @} grp_am_if_mb_err */

#endif /* } __AM_MB_ERR_H */

/* end of file */
