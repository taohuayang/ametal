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
 * \brief ZSN700 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_H
#define __AM_ZSN700_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#include "../zsn700/zsn700_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "../zsn700/zsn700_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "../zsn700/zsn700_regbase.h"

/** \brief оƬ����ӳ�� */
#include "../zsn700/zsn700_periph_map.h"

/** \brief ʱ��ID���� */
#include "../zsn700/zsn700_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "../zsn700/zsn700_dma_chan.h"

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

#endif /* __AM_ZSN700_H */

/* end of file */
