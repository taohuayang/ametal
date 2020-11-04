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
 * \brief LVD ϵͳ��λ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PIOB_7�����ƽ�������õĻ�׼��ѹ����ϵͳ���ڸ�λ״̬�����ٴθ��ڻ�׼��ѹLED��˸һ�Σ�ϵͳ����������
 *   ����������ӡ "Mcu is running!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32_hw_lvd_int.c src_hc32_hw_lvd_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-09  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_lvd_int
 * \copydoc demo_hc32_hw_lvd_int.c
 */

/** [src_hc32_hw_lvd_int] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_board.h"
#include "am_hc32_lvd.h"
#include "hw/amhw_hc32_lvd.h"
#include "hw/amhw_hc32_rcc_reset.h"

/** \brief LVD�������� */
#define __LVD_TRI_TYPE         AMHW_HC32_LVD_HTEN

/** \brief LVD�˲�ʱ�� */
#define __LVD_DEB_TIME         AMHW_HC32_LVD_DEB_TIME_7P2_MS

/** \brief LVD��������*/
#define __LVD_TRI_ACT          AMHW_HC32_LVD_TRI_ACT_SYSTEM_RESET

/**
 * \brief LVD ��ʼ��
 */
static void __lvd_hw_init (amhw_hc32_lvd_t       *p_hw_base,
                           amhw_hc32_lvd_vids_t   lvd_vids,
                           uint32_t               lvd_src)
{
    /* CR �Ĵ������� */
    amhw_hc32_lvd_cr_clr (p_hw_base);

    /* ��������ʹ�� */
    amhw_hc32_lvd_tri_enable (p_hw_base, __LVD_TRI_TYPE);

    /* �����˲�ʱ��ѡ�� */
    amhw_hc32_lvd_deb_time_sel (p_hw_base, __LVD_DEB_TIME);

    /* ʹ�������˲� */
    amhw_hc32_lvd_deb_time_enable (p_hw_base);

    /* ��ֵ��ѹѡ�� */
    amhw_hc32_lvd_vids_sel (p_hw_base, lvd_vids);

    /* �����Դѡ�� */
    amhw_hc32_lvd_src_sel (p_hw_base, lvd_src);

    /* ������������ */
    amhw_hc32_lvd_tri_act_sel (p_hw_base, __LVD_TRI_ACT);
}

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 */
void demo_hc32_hw_lvd_system_reset_entry (amhw_hc32_lvd_t     *p_hw_base,
                                          amhw_hc32_lvd_vids_t lvd_vids,
                                          uint32_t             lvd_src)
{
    if (p_hw_base == NULL) {
        return;
    }

    /* �жϸ�λ��־ */
    if (amhw_hc32_rcc_reset_flag_check (AMHW_HC32_RCC_RESET_FLAG_LVD)) {

        am_led_off(LED0);
        am_mdelay(500);
        am_led_on(LED0);
        am_mdelay(500);
        am_led_off(LED0);

        /* �����λ��־ */
        amhw_hc32_rcc_reset_flag_clr(AMHW_HC32_RCC_RESET_FLAG_LVD);
    }

    /* LVD��ʼ�� */
    __lvd_hw_init(p_hw_base, lvd_vids, lvd_src);

    /* LVDʹ�� */
    amhw_hc32_lvd_enable (p_hw_base);

    AM_FOREVER {

        am_kprintf ("Mcu is running!\r\n");

        am_mdelay(1000);
    }
}

/* end of file */
