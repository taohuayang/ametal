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
 * - 1.00 19-09-30
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg118_clktrim.h"
#include "hw/amhw_zlg118_clktrim.h"
#include "zlg118_periph_map.h"
#include "zlg118_inum.h"
#include "am_int.h"
#include "am_zlg118_clk.h"
#include "zlg118_clk.h"

/* �жϷ����� */
am_local void __clktrim_irq_handler(void *parg)
{
    /* �����ж� */
    am_int_disable(INUM_CLKTRIM);
    amhw_zlg118_clktrim_int_enable(ZLG118_CLKTRIM, 0);

    /* ����У׼ */
    amhw_zlg118_clktrim_trim_start(ZLG118_CLKTRIM, 0);
    *(int *)parg = 1;
    if(0 == amhw_zlg118_clktrim_ifr_get(ZLG118_CLKTRIM,
                                        AMHW_CLKTRIM_CALCNT_OF)) {
        amhw_zlg118_clktrim_ifr_clear(ZLG118_CLKTRIM, AMHW_CLKTRIM_XTH_FAULT);
				amhw_zlg118_clktrim_ifr_clear(ZLG118_CLKTRIM, AMHW_CLKTRIM_XTL_FAULT);
    }
    amhw_zlg118_clktrim_ifr_clear(ZLG118_CLKTRIM, AMHW_CLKTRIM_CALCNT_OF);
    amhw_zlg118_clktrim_ifr_clear(ZLG118_CLKTRIM, AMHW_CLKTRIM_STOP);
}

/**
 * \brief CLKTRIM���ģʽ����
 */
uint8_t am_zlg118_clktrim_monitor (uint16_t                     rcntval,
                                   uint16_t                     ccntval,
                                   amhw_clktrim_refclk_sel_t    refclk_sel,
                                   amhw_clktrim_calclk_sel_t    calclk_sel)
{
    int       break_flag = 0;
    uint8_t   ret        = AM_OK;

    am_clk_enable(CLK_CLOCKTRIM);

    /* ѡ��ο�ʱ�� */
    amhw_zlg118_clktrim_refclk_sel(ZLG118_CLKTRIM, refclk_sel);

    /* ѡ�񱻱����ʱ�� */
    amhw_zlg118_clktrim_calclk_sel(ZLG118_CLKTRIM, calclk_sel);

    /* ���ü��ʱ���� */
    amhw_zlg118_clktrim_refcon_set(ZLG118_CLKTRIM, rcntval);

    /* ���ñ����ʱ�����ʱ�� */
    amhw_zlg118_clktrim_calcon_set(ZLG118_CLKTRIM, ccntval);

    /* ʹ�ܼ�ع��� */
    amhw_zlg118_clktrim_mon_enable(ZLG118_CLKTRIM, 1);

    /* �����ж� */
    am_int_connect(INUM_CLKTRIM,
                   __clktrim_irq_handler,
                   (void *)&break_flag);

    /* ʹ���ж� */
    amhw_zlg118_clktrim_int_enable(ZLG118_CLKTRIM, 1);
    am_int_enable(INUM_CLKTRIM);

    /* ��ʼ��� */
    amhw_zlg118_clktrim_trim_start(ZLG118_CLKTRIM, 1);

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
uint8_t am_zlg118_clktrim_calibrate (uint16_t                     rcntval,
                                     amhw_clktrim_refclk_sel_t    refclk_sel,
                                     amhw_clktrim_calclk_sel_t    calclk_sel)
{
    int       break_flag = 0;
    uint16_t  calcnt     = 0;
    am_bool_t ret        = AM_OK;

    am_clk_enable(CLK_CLOCKTRIM);

    /* ѡ��ο�ʱ�� */
    amhw_zlg118_clktrim_refclk_sel(ZLG118_CLKTRIM, refclk_sel);

    /* ѡ�񱻱�У׼ʱ�� */
    amhw_zlg118_clktrim_calclk_sel(ZLG118_CLKTRIM, calclk_sel);

    /* ����У׼ʱ�� */
    amhw_zlg118_clktrim_refcon_set(ZLG118_CLKTRIM, rcntval);

    /* �����ж� */
    am_int_connect(CLKTRIM_IRQn,
                   __clktrim_irq_handler,
                   (void *)&break_flag);

    /* ʹ���ж� */
    amhw_zlg118_clktrim_int_enable(ZLG118_CLKTRIM, 1);
    am_int_enable(INUM_CLKTRIM);

    /* ��ʼУ׼ */
    amhw_zlg118_clktrim_trim_start(ZLG118_CLKTRIM, 1);

    while(0 == break_flag) {
        ;
    }
    if(1 == amhw_zlg118_clktrim_ifr_get(ZLG118_CLKTRIM,
                                        AMHW_CLKTRIM_CALCNT_OF)) {
        ret = -AM_ERROR;
    }

    calcnt = amhw_zlg118_clktrim_calcnt_get(ZLG118_CLKTRIM);

    am_clk_disable(CLK_CLOCKTRIM);

    if(ret != AM_OK) {
        return ret;
    }

    return ((calcnt * 1000) / rcntval);
}

/* end of file */
