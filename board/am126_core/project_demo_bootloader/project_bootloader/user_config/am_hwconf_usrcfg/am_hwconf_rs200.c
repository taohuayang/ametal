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
 * \brief RS200 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-17  RZ, first implementation.
 * \endinternal
 */

#include "am_rs200.h"
#include "am_common.h"
#include "am_zlg116_inst_init.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define  RS200_RX_BUF_SIZE  16   /**< \brief ���ջ��λ�������С��Ӧ��Ϊ2^n  */
#define  RS200_TX_BUF_SIZE  16   /**< \brief ���ͻ��λ�������С��Ӧ��Ϊ2^n  */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
/** \brief UART ���ջ��λ�����  */
am_local uint8_t __rs200_rxbuf[RS200_RX_BUF_SIZE];

/** \brief UART ���ͻ��λ�����  */
am_local uint8_t __rs200_txbuf[RS200_TX_BUF_SIZE];

/** \brief RS200�豸��Ϣʵ�� */
am_const am_local struct am_rs200_devinfo __g_rs200_info = {
    __rs200_rxbuf,
    __rs200_txbuf,
    RS200_RX_BUF_SIZE,
    RS200_TX_BUF_SIZE,
    200
};

/** \breif RS200 �豸�ṹ�嶨�� */
am_local struct am_rs200_dev __g_rs200_dev;

/** \brief RS200 �豸ʵ���� */
am_rs200_handle_t am_rs200_inst_init (void)
{
    return am_rs200_init(&__g_rs200_dev,
                         &__g_rs200_info,
                          am_zlg116_uart2_inst_init());
}

/* end of file */
