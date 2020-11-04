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
#include "am_hc32f07x_clktrim.h"
#include "hw/amhw_hc32_clktrim.h"
#include "hc32_periph_map.h"
#include "hc32_inum.h"
#include "am_int.h"
#include "am_hc32_clk.h"
#include "hc32_clk.h"

/* �жϷ����� */
am_local void __clktrim_irq_handler(void *parg)
{
    /* �����ж� */
    am_int_disable(INUM_CLKTRIM);
    amhw_hc32_clktrim_int_enable(HC32_CLKTRIM, 0);
    *(int *)parg = 1;
    if(0 == amhw_hc32_clktrim_ifr_get(HC32_CLKTRIM,
                                        AMHW_CLKTRIM_CALCNT_OF)) {
        amhw_hc32_clktrim_ifr_clear(HC32_CLKTRIM, AMHW_CLKTRIM_XTH_FAULT);
				amhw_hc32_clktrim_ifr_clear(HC32_CLKTRIM, AMHW_CLKTRIM_XTL_FAULT);
    }
    amhw_hc32_clktrim_ifr_clear(HC32_CLKTRIM, AMHW_CLKTRIM_CALCNT_OF);
    amhw_hc32_clktrim_ifr_clear(HC32_CLKTRIM, AMHW_CLKTRIM_STOP);
}

/**
 * \brief CLKTRIM���ģʽ����
 */
uint8_t am_hc32f07x_clktrim_monitor (uint16_t                     rcntval,
                                   uint16_t                     ccntval,
                                   amhw_clktrim_refclk_sel_t    refclk_sel,
                                   amhw_clktrim_calclk_sel_t    calclk_sel)
{
    int       break_flag = 0;
    uint8_t   ret        = AM_OK;

    am_clk_enable(CLK_CLOCKTRIM);

    /* ѡ��ο�ʱ�� */
    amhw_hc32_clktrim_refclk_sel(HC32_CLKTRIM, refclk_sel);

    /* ѡ�񱻱����ʱ�� */
    amhw_hc32_clktrim_calclk_sel(HC32_CLKTRIM, calclk_sel);

    /* ���ü��ʱ���� */
    amhw_hc32_clktrim_refcon_set(HC32_CLKTRIM, rcntval);

    /* ���ñ����ʱ�����ʱ�� */
    amhw_hc32_clktrim_calcon_set(HC32_CLKTRIM, ccntval);

    /* ʹ�ܼ�ع��� */
    amhw_hc32_clktrim_mon_enable(HC32_CLKTRIM, 1);

    /* �����ж� */
    am_int_connect(INUM_CLKTRIM,
                   __clktrim_irq_handler,
                   (void *)&break_flag);

    /* ʹ���ж� */
    amhw_hc32_clktrim_int_enable(HC32_CLKTRIM, 1);
    am_int_enable(INUM_CLKTRIM);

    /* ��ʼ��� */
    amhw_hc32_clktrim_trim_start(HC32_CLKTRIM, 1);

    while(0 == break_flag) {
        if(HC32_CLKTRIM->refcnt > 0){

        } else {
            if(HC32_CLKTRIM->calcnt > rcntval){
                break;
						}
        }
    }

    if(1 == break_flag) {
        ret = -AM_ERROR;
    }
    amhw_hc32_clktrim_trim_start(HC32_CLKTRIM, 0);
		
		/* �Ͽ��ж� */
	  am_int_disconnect(CLKTRIM_IRQn,
                      __clktrim_irq_handler,
                      (void *)&break_flag);
    am_clk_disable(CLK_CLOCKTRIM);

    return ret;
}

/**
 * \brief CLKTRIMУ׼ģʽ����
 */
uint16_t am_hc32f07x_clktrim_calibrate (uint16_t                     rcntval,
                                     amhw_clktrim_refclk_sel_t    refclk_sel,
                                     amhw_clktrim_calclk_sel_t    calclk_sel)
{
    int       break_flag = 0;
    uint16_t  calcnt     = 0;
    am_bool_t ret        = AM_OK;

    am_clk_enable(CLK_CLOCKTRIM);

    /* ѡ��ο�ʱ�� */
    amhw_hc32_clktrim_refclk_sel(HC32_CLKTRIM, refclk_sel);

    /* ѡ�񱻱�У׼ʱ�� */
    amhw_hc32_clktrim_calclk_sel(HC32_CLKTRIM, calclk_sel);

    /* ����У׼ʱ�� */
    amhw_hc32_clktrim_refcon_set(HC32_CLKTRIM, rcntval);

    /* �����ж� */
    am_int_connect(CLKTRIM_IRQn,
                   __clktrim_irq_handler,
                   (void *)&break_flag);

    /* ʹ���ж� */
    amhw_hc32_clktrim_int_enable(HC32_CLKTRIM, 1);
    am_int_enable(INUM_CLKTRIM);

    /* ��ʼУ׼ */
    amhw_hc32_clktrim_trim_start(HC32_CLKTRIM, 1);

    while(0 == break_flag) {
        ;
    }
    if(1 == amhw_hc32_clktrim_ifr_get(HC32_CLKTRIM,
                                        AMHW_CLKTRIM_CALCNT_OF)) {
        ret = -AM_ERROR;
    }

    calcnt = amhw_hc32_clktrim_calcnt_get(HC32_CLKTRIM);

	/* ����У׼ */
    amhw_hc32_clktrim_trim_start(HC32_CLKTRIM, 0);
		
		/* �Ͽ��ж� */
	  am_int_disconnect(CLKTRIM_IRQn,
                      __clktrim_irq_handler,
                      (void *)&break_flag);
    am_clk_disable(CLK_CLOCKTRIM);

    if(ret != AM_OK) {
        return ret;
    }

    return ((calcnt * 1000) / rcntval);
}

/* end of file */
