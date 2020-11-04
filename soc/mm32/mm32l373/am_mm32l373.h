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
 * \brief MM32L373 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AM_MM32L373_H
#define __AM_MM32L373_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#include "mm32l373_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "mm32l373_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "mm32l373_regbase.h"

/** \brief оƬ����ӳ�� */
#include "mm32l373_periph_map.h"

/** \brief ʱ��ID���� */
#include "mm32l373_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "mm32l373_dma_chan.h"

/**
 * \name Cortex-M3 �ں˴���������������
 * @{
 */
#ifndef AM_CORTEX_M3
#define AM_CORTEX_M3             1
#endif

#if defined AM_CORTEX_M3

#define __MPU_PRESENT            0  /**< \brief M3 ���� MPU */
#define __NVIC_PRIO_BITS         4  /**< \brief M3 ��Ϊ 4 */
#define __Vendor_SysTickConfig   0  /**< \brief ����Ϊ 1 �������� SysTick */

#include "core_cm3.h"

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_MM32L373_H */

/* end of file */
