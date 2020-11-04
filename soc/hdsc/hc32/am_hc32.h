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
 * \brief HC32 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-03  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_H
#define __AM_HC32_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#ifdef HC32X3X
#include "../hc32/hc32x3x_pin.h" /**< \brief ������HC32F030��HC32L13X */
#else    
#include "../hc32/hc32_pin.h"    /**< \brief ������HC32L/F17X��HC32L/F19X */
#endif
    
/** \brief оƬ�жϱ�Ŷ��� */
#include "../hc32/hc32_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "../hc32/hc32_regbase.h"

/** \brief оƬ����ӳ�� */
#include "../hc32/hc32_periph_map.h"

/** \brief ʱ��ID���� */
#include "../hc32/hc32_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "../hc32/hc32_dma_chan.h"

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

#endif /* __AM_HC32_H */

/* end of file */
