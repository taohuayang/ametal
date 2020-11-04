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
 * \brief HC32F460 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-01-15  cds, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_H
#define __AM_HC32F460_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#include "hc32f460_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "hc32f460_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "hc32f460_regbase.h"

/** \brief оƬ����ӳ�� */
#include "hc32f460_periph_map.h"

/** \brief ʱ��ID���� */
#include "hc32f460_clk.h"

/**
 * \name Cortex-M4 �ں˴���������������
 * @{
 */
#ifndef AM_CORTEX_M4
#define AM_CORTEX_M4             1
#endif

#if defined AM_CORTEX_M4

#define __MPU_PRESENT            1  /**< \brief M4 ���� MPU */
#define __NVIC_PRIO_BITS         4  /**< \brief M4 ��Ϊ 4 */
#define __Vendor_SysTickConfig   0  /**< \brief ����Ϊ 1 �������� SysTick */

#include "core_cm4.h"

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_H */

/* end of file */
