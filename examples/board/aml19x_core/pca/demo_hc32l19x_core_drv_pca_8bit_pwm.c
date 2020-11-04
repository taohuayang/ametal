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
 * \brief PCA 8bit PWM���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 *
 * - ʵ������
 *   1. PCAͨ��0��PB4�������PWM��ռ�ձ�Ϊ40%��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l19x_drv_pca_8bit_pwm.c src_hc32l19x_drv_pca_8bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-11-22  RZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l19x_drv_pca_8bit_pwm
 * \copydoc demo_hc32l19x_drv_pca_8bit_pwm.c
 */

/** [src_hc32l19x_drv_pca_8bit_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32_pca.h"
#include "am_hc32l19x_inst_init.h"
#include "demo_aml19x_core_entries.h"

/**
 * \brief �������
 */
void demo_hc32l19x_core_drv_pca_8bit_pwm_entry (void)
{
    am_hc32_pca_handle_t handle;

    AM_DBG_INFO("demo aml19x_core pca 8bit pwm entry!\r\n");

    handle = am_hc32_pca1_inst_init();

    am_hc32_pca_pwm_set(handle, 0, 0, HC32_PCA_PWM_8, 0, 102);

    am_hc32_pca_start(handle);

    while(1) {

    }
}
/** [src_hc32l19x_drv_pca_8bit_pwm] */

/* end of file */
