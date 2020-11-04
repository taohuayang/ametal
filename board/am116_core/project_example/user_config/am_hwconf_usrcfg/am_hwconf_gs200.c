/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GS200 �û������ļ�
 * \sa am_hwconf_gs200.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-16  fzb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_gs200.h"
#include "am_zlg116_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_gs200
 * \copydoc am_hwconf_gs200.c
 * @{
 */

am_local uint8_t __g_gs200_txbuf[128];      /**< \brief ���ͻ����� */
am_local uint8_t __g_gs200_rxbuf[128];      /**< \brief ���ջ����� */
am_local uint8_t __g_gs200_cmd_txbuf[5];    /**< \brief ����ͻ����� */

/** \brief �豸ʵ�� */
am_local am_gs200_dev_t __g_gs200_dev;

/** \brief �豸��Ϣ */
am_local am_const am_gs200_devinfo_t __g_gs200_devinfo = {
    9600,                       /**< \brief ģ�鵱ǰʹ�õĲ����� */
    __g_gs200_rxbuf,            /**< \brief ���ջ��� */
    __g_gs200_txbuf,            /**< \brief ���ͻ��� */
    __g_gs200_cmd_txbuf,        /**< \brief ����ͻ��� */
    sizeof(__g_gs200_rxbuf),    /**< \brief ���ջ��泤�� */
    sizeof(__g_gs200_txbuf),    /**< \brief ���ͻ��泤�� */
    AM_GS200_COM_FRAME_LEN,     /**< \brief ����ͻ��泤�� */
};

/**
 * \brief  GS200 ʵ����ʼ������� GS200 ��׼����������
 *
 * \return  GS200 ��׼����������
 */
am_gs200_handle_t am_gs200_inst_init (void)
{
    am_uart_handle_t uart_handle = am_zlg116_uart2_inst_init();

    return am_gs200_init(&__g_gs200_dev,
                         &__g_gs200_devinfo,
                         uart_handle);
}

/**
 * @}
 */

/* end of file */
