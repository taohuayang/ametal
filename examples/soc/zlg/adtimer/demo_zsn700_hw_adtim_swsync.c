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
 * \par Դ����
 * \snippet demo_zsn700_hw_adtim_swsync.c src_zsn700_hw_adtim_swsync
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_adtim_swsync
 * \copydoc demo_zsn700_hw_adtim_swsync.c
 */

/** [src_zsn700_hw_adtim_swsync] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_clk.h"
#include "am_zsn700.h"
#include "hw/amhw_zsn700_adtim.h"

/**
 * \brief �������
 */
void demo_zsn700_hw_adtim_swsync_entry (void *p_tim_cfg)
{
    amhw_zsn700_adtim_basecnt_cfg_t basecnt;
    amhw_zsn700_adtim_sw_sync_t    *p_cfg = (amhw_zsn700_adtim_sw_sync_t *)
                                            p_tim_cfg;

    amhw_zsn700_adtim_t *p_hw_adtim4 = (amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE;
    amhw_zsn700_adtim_t *p_hw_adtim5 = (amhw_zsn700_adtim_t *)ZSN700_TIM5_BASE;
    amhw_zsn700_adtim_t *p_hw_adtim6 = (amhw_zsn700_adtim_t *)ZSN700_TIM6_BASE;

    uint16_t tim4_data = 0;
    uint16_t tim5_data = 0;
    uint16_t tim6_data = 0;

    am_clk_enable(CLK_TIM456);

    /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
    basecnt.cntmode   = AMHW_ZSN700_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_ZSN700_ADTIM_CNT_DIR_UP;
    basecnt.cntclkdiv = AMHW_ZSN700_ADTIM_PCLK_DIV1;

    if(p_cfg->adtim4 == AM_TRUE) {
        amhw_zsn700_adtim_init(p_hw_adtim4, &basecnt);
    }

    if(p_cfg->adtim5 == AM_TRUE) {
        amhw_zsn700_adtim_init(p_hw_adtim5, &basecnt);
    }

    if(p_cfg->adtim6 == AM_TRUE) {
        amhw_zsn700_adtim_init(p_hw_adtim6, &basecnt);
    }

    while (1) {

        AM_DBG_INFO("state----tim4:%5d, tim5:%5d, tim6:%5d\r\n",
                     p_cfg->adtim4,
                     p_cfg->adtim5,
                     p_cfg->adtim6);

        /* ���ͬ������ */
        amhw_zsn700_adtim_swsyncstart(p_cfg);

        /* �ֱ��ȡ��ʱ���ļ���ֵ  */
        tim4_data = amhw_zsn700_adtim_getcount(p_hw_adtim4);
        tim5_data = amhw_zsn700_adtim_getcount(p_hw_adtim5);
        tim6_data = amhw_zsn700_adtim_getcount(p_hw_adtim6);

        AM_DBG_INFO("start----tim4:%5d, tim5:%5d, tim6:%5d\r\n",
                    tim4_data,
                    tim5_data,
                    tim6_data);

        am_mdelay(1000);

        /* ���ͬ��ֹͣ */
        amhw_zsn700_adtim_swsyncstop(p_cfg);

        /* �ֱ��ȡ��ʱ���ļ���ֵ  */
        tim4_data = amhw_zsn700_adtim_getcount(p_hw_adtim4);
        tim5_data = amhw_zsn700_adtim_getcount(p_hw_adtim5);
        tim6_data = amhw_zsn700_adtim_getcount(p_hw_adtim6);

        AM_DBG_INFO("stop-----tim4:%5d, tim5:%5d, tim6:%5d\r\n",
                    tim4_data,
                    tim5_data,
                    tim6_data);

        /* ���ͬ������ */
        amhw_zsn700_adtim_swsyncclear(p_cfg);

        /* �ֱ��ȡ��ʱ���ļ���ֵ  */
        tim4_data = amhw_zsn700_adtim_getcount(p_hw_adtim4);
        tim5_data = amhw_zsn700_adtim_getcount(p_hw_adtim5);
        tim6_data = amhw_zsn700_adtim_getcount(p_hw_adtim6);

        AM_DBG_INFO("clear----tim4:%5d, tim5:%5d, tim6:%5d\r\n",
                    tim4_data,
                    tim5_data,
                    tim6_data);

        AM_DBG_INFO("\r\n\r\n");
    }
}
/** [src_zsn700_hw_adtim_swsync] */

/* end of file */
