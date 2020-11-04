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
 * \brief ֹͣģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. MCU ����ֹͣģʽʱ�� ���Դ��ڴ�ӡ������Ϣ��
 *   2. ָ�������ϵ��жϻ��� MCU��������� wake_up������������С�
 *
 * \par Դ����
 * \snippet demo_zlg116_drv_stopmode_wake_up.c src_zlg116_drv_stopmode_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_zlg116_drv_stopmode_wake_up
 * \copydoc demo_zlg116_drv_stopmode_wake_up.c
 */
 
/** [src_zlg116_drv_stopmode_wake_up] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_ZML165_pwr.h"

/**
 * \brief �����жϷ�����
 */
static void gpio_isr (void *p_arg)
{
    ;
}

/**
 * \brief �������
 */
void demo_zml165_drv_stopmode_wake_up_entry (void)
{

    /* �������� */
    am_zml165_wake_up_cfg(AM_ZML165_PWR_MODE_STOP, gpio_isr, (void *)0);

    /* ����ͣ��ģʽ */
    am_zml165_pwr_mode_into(AM_ZML165_PWR_MODE_STOP);

    AM_DBG_INFO("wake_up!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}

/** [src_zlg116_drv_stopmode_wake_up] */
 
/* end of file */
