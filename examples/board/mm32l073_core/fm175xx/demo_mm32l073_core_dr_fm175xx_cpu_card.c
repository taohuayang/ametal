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
 * \brief fm175xx��CPU�����в��ԣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *   2. ��ȷ���Ӻ����ߣ�
 *   3. ��CPU���������߸�Ӧ����
 *
 * - ʵ������
 *   1. ����Ƭ�������߸�Ӧ���󴮿ڴ�ӡ����Ƭ��ID��
 *   2. ������õĿ�Ƭ��CPU��������ӡATS��COSָ��Ĳ��������
 *
 * \par Դ����
 * \snippet demo_am116_dr_fm175xx_cpu_card.c src_am116_dr_fm175xx_cpu_card
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_cpu_card
 * \copydoc demo_am116_dr_fm175xx_cpu_card.c
 */

/** [src_am116_dr_fm175xx_cpu_card] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief ��CPU������
 */
void demo_am116_core_dr_fm175xx_cpu_card (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_cpu_card(handle);
}

/** [src_am116_dr_fm175xx_cpu_card] */

/* end of file */
