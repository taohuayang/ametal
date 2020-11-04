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
 * \brief HC32F07X оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-17  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_H
#define __AM_HC32_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#include "hc32f07x_pin.h" 	
 
/** \brief оƬ�жϱ�Ŷ��� */
#include "hc32f07x_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "hc32f07x_regbase.h"

/** \brief оƬ����ӳ�� */
#include "hc32f07x_periph_map.h"

/** \brief ʱ��ID���� */
#include "hc32f07x_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "hc32f07x_dma_chan.h"


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

#endif /* __AM_HC32F07X_H */

/* end of file */
