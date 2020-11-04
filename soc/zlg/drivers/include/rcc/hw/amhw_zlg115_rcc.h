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
 * \brief RCC �����ӿ�
 *
 *  ����ֱ��ʹ���� ZLG116 ����Ĵ�������ַ�� ��ˣ��������������� ZLG116
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-11  sdy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG115_RCC_H
#define __AMHW_ZLG115_RCC_H

#include "am_types.h"
#include "zml165_regbase.h"

/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AMHW_ZLG115_SYSCLK_HSI_DIV6,  /**< \brief HSI ����  6 ��Ƶ��Ϊϵͳʱ�� */
    AMHW_ZLG115_SYSCLK_HSE,       /**< \brief HSE ��Ϊϵͳʱ�� */
    AMHW_ZLG115_SYSCLK_HSI,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_ZLG115_SYSCLK_LSI,       /**< \brief LSI �����Ϊϵͳʱ�� */
}amhw_zlg115_sys_clk_src;


#endif

/* end of file */
