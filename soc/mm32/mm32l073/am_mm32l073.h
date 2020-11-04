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
 * \brief mm32l073 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_MM32L073_H
#define __AM_MM32L073_H

#ifdef __cplusplus
extern "C" {
#endif

#include "soc_cfg.h"

/** \brief оƬ���Ŷ��� */
#include "mm32l073_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "mm32l073_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "mm32l073_regbase.h"

/** \brief оƬ����ӳ�� */
#include "mm32l073_periph_map.h"

/** \brief ʱ��ID���� */
#include "mm32l073_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "mm32l073_dma_chan.h"

/**
 * \name Cortex-M0 �ں˴���������������
 * @{
 */
#ifndef AM_CORTEX_M0
#define AM_CORTEX_M0             1
#endif

#if defined AM_CORTEX_M0

#define __MPU_PRESENT            0  /**< \brief M0����MPU */
#define __NVIC_PRIO_BITS         2  /**< \brief M0��Ϊ2 */
#define __Vendor_SysTickConfig   1  /**< \brief ����Ϊ1 ��������SysTick */

#include "core_cm0.h"

#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_MM32L073_H */

/* end of file */
