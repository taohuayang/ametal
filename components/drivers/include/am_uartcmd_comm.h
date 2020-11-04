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
 * - 1.00 15-09-  win, first implementation.
 * \endinternal
 */
#ifndef __AM_UARTCMD_COMM_H
#define __AM_UARTCMD_COMM_H

#ifdef __cplusplus
extern "C" {
#endif

//#define UARTCMD_COMM_MODE_UART        0x00
//#define UARTCMD_COMM_MODE_I2C         0x01
//#define UARTCMD_COMM_MODE_SPI       0x02

#define UARTCMD_PROTOCOL_OLD_FRAME
#define UARTCMD_PROTOCOL_OLD_LENGTH   6     /**< \brief ��ͨѶ֡Э�鳤�� */
#define UARTCMD_PROTOCOL_LENGTH       10    /**< \brief ͨѶ֡Э�鳤�� */

#define UARTCMD_COMM_STATUS_IDLE           0x00  /**< \brief UARTCMD ���ڿ���״̬ */
#define UARTCMD_COMM_STATUS_RX_BUSY        0x01  /**< \brief ֡���ڽ���״̬ */
#define UARTCMD_COMM_STATUS_RX_OK          0x02  /**< \brief ֡������� */
#define UARTCMD_COMM_STATUS_TX_BUSY        0x03  /**< \brief ֡���ڷ���״̬ */
#define UARTCMD_COMM_STATUS_TX_OK          0x04  /**< \brief ֡������� */
#define UARTCMD_COMM_STATUS_EXECUTING      0x05  /**< \brief ֡���ڴ��� */
#define UARTCMD_COMM_STATUS_EXECUTED       0x06  /**< \brief ֡������� */

#define UARTCMD_RX_TIMEOUT            4440  /**< \brief ֡���ճ�ʱ4.44ms */

#define UARTCMD_FRAME_EXT             0x03  /**< \brief ֡������ */

#define UARTCMD_VERSION_SIZE          20    /**< \brief �����汾���ֽ��� */
#define UARTCMD_SN_SIZE               16    /**< \brief �������кŵ��ֽ��� */
#define UARTCMD_RECORD_SIZE           128   /**< \brief ���Լ�¼�ļ��Ĵ�С */


#define UARTCMD_COMM_MODE_MASK        0x0F  /**< \brief ͨ��ģʽ���� */
#define UARTCMD_COMM_MODE_AUTO        0x00  /**< \brief �Զ���� */
#define UARTCMD_COMM_MODE_I2C         0x01  /**< \brief I2C */
#define UARTCMD_COMM_MODE_UART        0x02  /**< \brief UART */
#define UARTCMD_COMM_MODE_WG          0x03  /**< \brief WG */

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_COMM_H */

/* end of file */
