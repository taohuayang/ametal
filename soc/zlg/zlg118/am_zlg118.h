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
 * \brief ZLG118 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-03  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_H
#define __AM_ZLG118_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#include "../zlg118/zlg118_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "../zlg118/zlg118_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "../zlg118/zlg118_regbase.h"

/** \brief оƬ����ӳ�� */
#include "../zlg118/zlg118_periph_map.h"

/** \brief ʱ��ID���� */
#include "../zlg118/zlg118_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "../zlg118/zlg118_dma_chan.h"

/**
 * \name Cortex-M0+ �ں˴���������������
 * @{
 */

#ifndef AM_CORTEX_M0

#define AM_CORTEX_M0             1

#endif

#if defined AM_CORTEX_M0

#define __MPU_PRESENT            0  /**< \brief M0+����MPU          */
#define __NVIC_PRIO_BITS         2  /**< \brief M0+��Ϊ2            */
#define __Vendor_SysTickConfig   0  /**< \brief ����Ϊ1 ��������SysTick */

#include "core_cm0plus.h"

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_H */

/* end of file */
