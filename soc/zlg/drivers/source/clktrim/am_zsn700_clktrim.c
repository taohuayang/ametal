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
 * \brief CLKTRIM����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18
 * \endinternal
 */

#include "ametal.h"
#include "am_zsn700_clktrim.h"
#include "hw/amhw_zsn700_clktrim.h"
#include "zsn700_periph_map.h"
#include "zsn700_inum.h"
#include "am_int.h"
#include "am_zsn700_clk.h"
#include "zsn700_clk.h"

/* �жϷ����� */
am_local void __clktrim_irq_handler(void *parg)
{
    /* �����ж� */
    am_int_disable(INUM_CLKTRIM);
    amhw_zsn700_clktrim_int_enable(ZSN700_CLKTRIM, 0);

    /* ����У׼ */
    amhw_zsn700_clktrim_trim_start(ZSN700_CLKTRIM, 0);
    *(int *)parg = 1;
    if(0 == amhw_zsn700_clktrim_ifr_get(ZSN700_CLKTRIM,
                                        AMHW_CLKTRIM_CALCNT_OF)) {
        amhw_zsn700_clktrim_ifr_clear(ZSN700_CLKTRIM, AMHW_CLKTRIM_XTH_FAULT);
				amhw_zsn700_clktrim_ifr_clear(ZSN700_CLKTRIM, AMHW_CLKTRIM_XTL_FAULT);
    }
    amhw_zsn700_clktrim_ifr_clear(ZSN700_CLKTRIM, AMHW_CLKTRIM_CALCNT_OF);
    amhw_zsn700_clktrim_ifr_clear(ZSN700_CLKTRIM, AMHW_CLKTRIM_STOP);
}

/**
 * \brief CLKTRIM���ģʽ����
 */
uint8_t am_zsn700_clktrim_monitor (uint16_t                     rcntval,
                                   uint16_t                     ccntval,
                                   amhw_clktrim_refclk_sel_t    refclk_sel,
                                   amhw_clktrim_calclk_sel_t    calclk_sel)
{
    int       break_flag = 0;
    uint8_t   ret        = AM_OK;

    am_clk_enable(CLK_CLOCKTRIM);

    /* ѡ��ο�ʱ�� */
    amhw_zsn700_clktrim_refclk_sel(ZSN700_CLKTRIM, refclk_sel);

    /* ѡ�񱻱����ʱ�� */
    amhw_zsn700_clktrim_calclk_sel(ZSN700_CLKTRIM, calclk_sel);

    /* ���ü��ʱ���� */
    amhw_zsn700_clktrim_refcon_set(ZSN700_CLKTRIM, rcntval);

    /* ���ñ����ʱ�����ʱ�� */
    amhw_zsn700_clktrim_calcon_set(ZSN700_CLKTRIM, ccntval);

    /* ʹ�ܼ�ع��� */
    amhw_zsn700_clktrim_mon_enable(ZSN700_CLKTRIM, 1);

    /* �����ж� */
    am_int_connect(INUM_CLKTRIM,
                   __clktrim_irq_handler,
                   (void *)&break_flag);

    /* ʹ���ж� */
    amhw_zsn700_clktrim_int_enable(ZSN700_CLKTRIM, 1);
    am_int_enable(INUM_CLKTRIM);

    /* ��ʼ��� */
    amhw_zsn700_clktrim_trim_start(ZSN700_CLKTRIM, 1);

    while(0 == break_flag) {
        ;
    }
    if(2 == break_flag) {
        ret = -AM_ERROR;
    }

    am_clk_disable(CLK_CLOCKTRIM);

    return ret;
}

/**
 * \brief CLKTRIMУ׼ģʽ����
 */
uint8_t am_zsn700_clktrim_calibrate (uint16_t                     rcntval,
                                     amhw_clktrim_refclk_sel_t    refclk_sel,
                                     amhw_clktrim_calclk_sel_t    calclk_sel)
{
    int       break_flag = 0;
    uint16_t  calcnt     = 0;
    am_bool_t ret        = AM_OK;

    am_clk_enable(CLK_CLOCKTRIM);

    /* ѡ��ο�ʱ�� */
    amhw_zsn700_clktrim_refclk_sel(ZSN700_CLKTRIM, refclk_sel);

    /* ѡ�񱻱�У׼ʱ�� */
    amhw_zsn700_clktrim_calclk_sel(ZSN700_CLKTRIM, calclk_sel);

    /* ����У׼ʱ�� */
    amhw_zsn700_clktrim_refcon_set(ZSN700_CLKTRIM, rcntval);

    /* �����ж� */
    am_int_connect(CLKTRIM_IRQn,
                   __clktrim_irq_handler,
                   (void *)&break_flag);

    /* ʹ���ж� */
    amhw_zsn700_clktrim_int_enable(ZSN700_CLKTRIM, 1);
    am_int_enable(INUM_CLKTRIM);

    /* ��ʼУ׼ */
    amhw_zsn700_clktrim_trim_start(ZSN700_CLKTRIM, 1);

    while(0 == break_flag) {
        ;
    }
    if(1 == amhw_zsn700_clktrim_ifr_get(ZSN700_CLKTRIM,
                                        AMHW_CLKTRIM_CALCNT_OF)) {
        ret = -AM_ERROR;
    }

    calcnt = amhw_zsn700_clktrim_calcnt_get(ZSN700_CLKTRIM);

    am_clk_disable(CLK_CLOCKTRIM);

    if(ret != AM_OK) {
        return ret;
    }

    return ((calcnt * 1000) / rcntval);
}

/* end of file */
