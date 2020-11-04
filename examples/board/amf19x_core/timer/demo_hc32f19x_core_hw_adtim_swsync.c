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
 * \brief �߼���ʱ��������ͬ����ʼ��ͬ��ֹͣ��ͬ���������̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڴ�ӡ����������Ϣ��
 *   2.��1�д���state���������ͬ���Ķ�ʱ��״̬   1������ͬ��     0�����������ͬ��
 *     ��2�п�ʼ��start��ʱÿ����ʱ���ļ���ֵ�����д�ӡ����Ӧ���ǵȲ��ʱ����������
 *                                  �ֱ��ȡ�Ĵ���ֵ�Ĺ����������ڼ�����
 *     ��3��ֹͣ��stop��ʱÿ����ʱ���ļ���ֵ
 *     ��4�����㣨clear��ʱÿ����ʱ���ļ���ֵ
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32f19x_hw_adtim_swsync.c src_hc32f19x_hw_adtim_swsync
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f19x_hw_adtim_swsync
 * \copydoc demo_hc32f19x_hw_adtim_swsync.c
 */

/** [src_hc32f19x_hw_adtim_swsync] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_hc32_adtim.h"
#include "am_hc32f19x_inst_init.h"
#include "demo_hc32_entries.h"
#include "demo_amf19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32f19x_core_hw_adtim_swsync_entry (void)
{
    amhw_hc32_adtim_sw_sync_t adtim_sync;

    AM_DBG_INFO("demo amf19x_core hw adtim swsync!\r\n");

    /* ���ͬ������ʹ��    AM_TRUE���������ͬ������      AM_FALSE�����������ͬ������*/
    adtim_sync.adtim4 = AM_TRUE;
    adtim_sync.adtim5 = AM_TRUE;
    adtim_sync.adtim6 = AM_TRUE;

    demo_hc32_hw_adtim_swsync_entry(&adtim_sync);
}
/** [src_hc32f19x_hw_adtim_swsync] */

/* end of file */
