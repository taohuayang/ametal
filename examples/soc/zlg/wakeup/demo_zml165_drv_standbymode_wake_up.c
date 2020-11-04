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
 * \brief ����ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * - �������裺
 *   1. �ϵ�ǰ�� WAKE_UP ���ӵ��͵�ƽ��
 *   2. �ȴ� MCU �������ģʽ��
 *   3. �� WAKE_UP ���ӵ��ߵ�ƽ��ʹ WAKE_UP �ϲ��������ػ��� MCU��
 *
 * - ʵ������
 *   1. �ɹ��������ģʽʱ���������"enter standby!"��
 *      ���򴮿����"WAKE_UP must be low!"��
 *   2. WAKE_UP ���������غ�MCU ��λ���С�
 *
 * \note
 *    ֻ���� WAKE_UP Ϊ�͵�ƽ��ʱ����ܽ������ģʽ
 *
 * \par Դ����
 * \snippet demo_zlg116_drv_standbymode_wake_up.c src_zlg116_drv_standbymode_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_zlg116_drv_standbymode_wake_up
 * \copydoc demo_zlg116_drv_standbymode_wake_up.c
 */
 
/** [src_zlg116_drv_standbymode_wake_up] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zml165_pwr.h"

/**
 * \brief �������
 */
void demo_zml165_drv_standbymode_wake_up_entry (void)
{

    /* �������� */
    am_zml165_wake_up_cfg(AM_ZML165_PWR_MODE_STANBY, NULL, NULL);

    /* �������ģʽ */
    if (am_zml165_pwr_mode_into(AM_ZML165_PWR_MODE_STANBY) != AM_OK) {

        /* ֻ���� WAKE_UP Ϊ�͵�ƽ��ʱ����ܽ������ģʽ */
        AM_DBG_INFO("WAKE_UP must be low!\r\n");
    }

    /* ��Ӧ��ִ�е������Ϊ����ģʽ����֮��оƬ��ֱ�Ӹ�λ */
    AM_DBG_INFO("error!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg116_drv_standbymode_wake_up] */

/* end of file */
