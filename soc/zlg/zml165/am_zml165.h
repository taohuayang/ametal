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
 * \brief zml165 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_ZML165_H
#define __AM_ZML165_H

#ifdef __cplusplus
extern "C" {
#endif

#include "soc_cfg.h"

/** \brief оƬ���Ŷ��� */
#include "zml165_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "zml165_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "zml165_regbase.h"

/** \brief оƬ����ӳ�� */
#include "zml165_periph_map.h"

/** \brief ʱ��ID���� */
#include "zml165_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "zml165_dma_chan.h"

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

#endif /* __AM_ZML165_H */

/* end of file */
